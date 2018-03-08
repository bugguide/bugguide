<?php

/**
 * @file
 * Contains \Drupal\bgapi\Plugin\resource\DataProvider\DataProviderApacheSolr.
 */

namespace Drupal\bgapi\Plugin\resource\DataProvider;

use Drupal\restful\Exception\BadRequestException;
use Drupal\restful\Exception\ForbiddenException;
use Drupal\restful\Exception\ServiceUnavailableException;
use Drupal\restful\Http\RequestInterface;
use Drupal\restful\Plugin\resource\DataInterpreter\ArrayWrapper;
use Drupal\restful\Plugin\resource\DataInterpreter\DataInterpreterArray;
use Drupal\restful\Plugin\resource\DataProvider\DataProvider;
use Drupal\restful\Plugin\resource\DataProvider\DataProviderInterface;
use Drupal\restful\Plugin\resource\Field\ResourceFieldCollectionInterface;
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
   * Number of items to list per request.
   */
  const ITEMS_PER_LIST = 25;

  /**
   * {@inheritdoc}
   */
  public function __construct(RequestInterface $request, ResourceFieldCollectionInterface $field_definitions, $account, $plugin_id, $resource_path = NULL, array $options = array(), $langcode = NULL) {
    parent::__construct($request, $field_definitions, $account, $plugin_id, $resource_path, $options, $langcode);
    if (empty($this->options['urlParams'])) {
      $this->options['urlParams'] = array(
        'filter' => TRUE,
        'sort' => FALSE,
        'fields' => TRUE,
        'loadByFieldName' => FALSE,
      );
    }
  }

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
    $query = apachesolr_drupal_query('bgimage_search', array());
    $query->addFilterSubQuery($filter);
    $query->addParam('fl', '*');
    $sort_field = 'sort_label';
    $sort_direction = 'asc';
    $query->setAvailableSort($sort_field, array(
      'title' => t('Label'),
      'default' => $sort_direction,
    ));
    $query->setSolrsort($sort_field, $sort_direction);
    $query->page = $options['offset'];
    $query->addParam('rows', self::ITEMS_PER_LIST);

    $query->addFilterSubQuery($this->getFiltersFromRequest());

    // Query Solr and attach images to the child's document.
    list(, $response) = apachesolr_do_query($query);

    // Transform documents to array objects.
    $result = array();
    foreach ($response->response->docs as $document) {
      $result[] = $this->mapSearchResultToPublicFields($document);
    }

    $this->setTotalCount($response->response->numFound);

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

  /**
   * Parses the request and adds filters to the query.
   *
   * @return SolrFilterSubQuery
   *   An Apache Solr filter.
   *
   * @throws \Drupal\restful\Exception\BadRequestException
   */
  protected function getFiltersFromRequest() {
    $filter = new SolrFilterSubQuery('AND');
    $input = $this->getRequest()->getParsedInput();
    if (empty($input['filter'])) {
      // No filtering is needed.
      return $filter;
    }
    $options = $this->getOptions();
    $url_params = empty($options['urlParams']) ? array() : $options['urlParams'];
    if (empty($url_params['filter'])) {
      throw new BadRequestException('Filter parameters have been disabled in server configuration.');
    }

    foreach ($input['filter'] as $public_field => $value) {
      $resource_field = $this->fieldDefinitions->get($public_field);
      $field = $resource_field->getProperty() ?: $public_field;

      if (!is_array($value)) {
        // Request uses the shorthand form for filter. For example
        // filter[foo]=bar would be converted to filter[foo][value] = bar.
        $value = array('value' => $value);
      }
      // Set default operator.
      $value += array('operator' => '=');

      // Clean the operator in case it came from the URL.
      // e.g. filter[minor_version][operator]=">="
      $value['operator'] = str_replace(array('"', "'"), '', $value['operator']);

      $this->isValidOperatorsForFilter(array($value['operator']));

      $filter->addFilter($field, $value['value']);
    }

    return $filter;
  }

}
