<?php

/**
 * @file
 * Contains \Drupal\bgapi\Plugin\resource\DataProvider\DataProviderApacheSolr.
 */

namespace Drupal\bgapi\Plugin\resource\DataProvider;

use Drupal\restful\Exception\ForbiddenException;
use Drupal\restful\Exception\ServiceUnavailableException;
use Drupal\restful\Plugin\resource\DataInterpreter\ArrayWrapper;
use Drupal\restful\Plugin\resource\DataInterpreter\DataInterpreterArray;
use Drupal\restful\Plugin\resource\DataProvider\DataProvider;
use Drupal\restful\Plugin\resource\DataProvider\DataProviderInterface;
use SolrFilterSubQuery;

class DataProviderApacheSolr extends DataProvider implements DataProviderInterface {

  /**
   * Index machine name to query against.
   *
   * @var string
   */
  protected $searchIndex;

  /**
   * Total count of results after executing the query.
   *
   * @var int
   */
  protected $totalCount;

  /**
   * Set the total results count after executing the query.
   *
   * @param int $totalCount
   */
  public function setTotalCount($totalCount) {
    $this->totalCount = $totalCount;
  }

  /**
   * Counts the total results for the index call.
   *
   * @return int
   *   The total number of results for the index call.
   */
  public function count() {
    return $this->totalCount;
  }

  /**
   * Create operation.
   *
   * @param mixed $object
   *   The thing to be created.
   *
   * @return array
   *   An array of structured data for the thing that was created.
   */
  public function create($object) {
    throw new ServiceUnavailableException(sprintf('%s is not implemented.', __METHOD__));
  }

  /**
   * Read operation.
   *
   * @param mixed $identifier
   *   The ID of thing being viewed.
   *
   * @return array
   *   An array of data for the thing being viewed.
   */
  public function view($identifier) {
    // In this case the ID is the search query.
    $options = $output = array();
    // Construct the options array.

    // Set the following options:
    // - offset: The position of the first returned search results relative to
    //   the whole result in the index.
    // - limit: The maximum number of search results to return. -1 means no
    //   limit.
    list($options['offset'], $options['limit']) = $this->parseRequestForListPagination();

    // Query SearchAPI for the results.
    $filter = new SolrFilterSubQuery('AND');
    $filter->addFilter('sm_bgimage_parents', 3);
    $filter->addFilter('entity_type', 'node');
    $filter->addFilter('bundle', 'bgimage');
    if (!empty($identifier)) {
      $filter->addFilter('entity_id', $identifier);
    }
    $query = apachesolr_drupal_query($identifier, array());
    $query->addFilterSubQuery($filter);
    $query->addParam('fl', '*');
    $query->addParam('rows', 8);



    // Query Solr and attach images to the child's document.
    list(, $response) = apachesolr_do_query($query);

    // Transform documents to array objects.
    $result = array();
    foreach ($response->response->docs as $document) {
      $result[] = $this->mapSearchResultToPublicFields($document);
    }

    $this->setTotalCount(count($result));

    return $result;
  }

  /**
   * {@inheritdoc}
   */
  public function viewMultiple(array $identifiers) {
    $return = array();
    foreach ($identifiers as $identifier) {
      try {
        $row = $this->view($identifier);
      }
      catch (ForbiddenException $e) {
        $row = NULL;
      }
      $return[] = $row;
    }

    return array_filter($return);
  }

  /**
   * Update operation.
   *
   * @param mixed $identifier
   *   The ID of thing to be updated.
   * @param mixed $object
   *   The thing that will be set.
   * @param bool $replace
   *   TRUE if the contents of $object will replace $identifier entirely. FALSE
   *   if only what is set in $object will replace those properties in
   *   $identifier.
   *
   * @return array
   *   An array of structured data for the thing that was updated.
   */
  public function update($identifier, $object, $replace = FALSE) {
    throw new ServiceUnavailableException(sprintf('%s is not implemented.', __METHOD__));
  }

  /**
   * Delete operation.
   *
   * @param mixed $identifier
   *   The ID of thing to be removed.
   */
  public function remove($identifier) {
    throw new ServiceUnavailableException(sprintf('%s is not implemented.', __METHOD__));
  }

  /**
   * Get the data interpreter.
   *
   * @param mixed $identifier
   *   The ID of thing being viewed.
   *
   * @return \Drupal\restful\Plugin\resource\DataInterpreter\DataInterpreterInterface
   *   The data interpreter.
   */
  protected function initDataInterpreter($identifier) {
    return new DataInterpreterArray($this->getAccount(), new ArrayWrapper((array) $identifier));
  }

  /**
   * Returns the ID to render for the current index GET request.
   *
   * @return array
   *   Numeric array containing the identifiers to be sent to viewMultiple.
   */
  public function getIndexIds() {
    return array('');
  }

  /**
   * Prepares the output array from the search result.
   *
   * @param \ApacheSolrDocument $document
   *   An ApacheSolr document.
   *
   * @return array
   *   The prepared output.
   */
  protected function mapSearchResultToPublicFields($document) {
    $resource_field_collection = $this->initResourceFieldCollection($document);
    // Loop over all the defined public fields.
    foreach ($this->fieldDefinitions as $public_field_name => $resource_field) {
      // Map result names to public properties.
      /* @var \Drupal\restful_search_api\Plugin\resource\Field\ResourceFieldSearchKeyInterface $resource_field */
      if (!$this->methodAccess($resource_field)) {
        // Allow passing the value in the request.
        continue;
      }
      $resource_field_collection->set($resource_field->id(), $resource_field);
    }

    return $resource_field_collection;
  }

}
