<?php

/**
 * @file
 * Contains \Drupal\bgapi\Plugin\resource\file\v1_0\FileUpload__1_0
 */

namespace Drupal\bgapi\Plugin\resource\file\v1_0;

use Drupal\restful\Exception\UnauthorizedException;
use Drupal\restful\Plugin\resource\ResourceEntity;

/**
 * Class FileUpload__1_0
 * @package Drupal\bgapi\Plugin\Resource\file\v1_0
 *
 * @Resource(
 *   name = "file_upload:1.0",
 *   resource = "file_upload",
 *   label = "File upload",
 *   description = "A file upload wrapped with RESTful.",
 *   authenticationTypes = {
 *     "token"
 *   },
 *   authenticationOptional = FALSE,
 *   dataProvider = {
 *     "entityType": "file",
 *     "options": {
 *       "scheme": "public"
 *     }
 *   },
 *   menuItem = "file-upload",
 *   majorVersion = 1,
 *   minorVersion = 0
 * )
 */
class FileUpload__1_0 extends ResourceEntity {

  /**
   * {@inheritdoc}
   *
   * If "File entity" module exists, determine access by its provided
   * permissions otherwise, check if variable is set to allow anonymous users to
   * upload. Defaults to authenticated user.
   */
  public function access() {
    // The getAccount method may return an UnauthorizedException when an
    // authenticated user cannot be found. Since this is called from the access
    // callback, not from the page callback we need to catch the exception.
    try {
      $account = $this->getAccount();
    }
    catch (UnauthorizedException $e) {
      // If a user is not found then load the anonymous user to check
      // permissions.
      $account = drupal_anonymous_user();
    }
    if (module_exists('file_entity')) {
      return user_access('bypass file access', $account) || user_access('create files', $account);
    }

    return (variable_get('restful_file_upload_allow_anonymous_user', FALSE) || $account->uid) && parent::access();
  }

}
