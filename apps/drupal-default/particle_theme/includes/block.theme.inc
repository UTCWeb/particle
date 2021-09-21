<?php

/**
 * @file
 * Functions to support theming blocks in the Particle theme.
 */
use Drupal\media\Entity\Media;
use Drupal\media_entity\MediaInterface;
use Drupal\file\Entity\File;
use Drupal\block\Entity\Block;

/**
 * Implements hook_theme_suggestions_block_alter().
 */

function particle_theme_suggestions_block_alter(&$suggestions, $variables)
{
    foreach ($suggestions as &$suggestion) {
        $suggestion = str_replace('particle_', 'themag_', $suggestion);
    }

    $node = \Drupal::routeMatch()->getParameter('node');
    $nid = null;
    $node_url_string = null;
    if ($node) {
        if ($node instanceof \Drupal\node\NodeInterface) {
            $nid = $node->id();
        }
        if ($node instanceof \Drupal\node\NodeInterface) {
            $node_url_string = $node->toUrl()->toString();
        }
        //$node->getTitle();
    }
    $word= 'node';
    if (strpos($node_url_string, $word) !== false) {
        $suggestions[] = ('block__' . "_id_" . $nid . "_label_" . preg_replace('/\s+/', '_', $variables['elements']['#configuration']['label']));
    } else {
        $suggestions[] = ('block__'. str_replace('-', '_', ltrim($node_url_string, '/')) . "_id_" . $nid . "_label_" . preg_replace('/\s+/', '_', $variables['elements']['#configuration']['label']));
    }

    if (!empty($variables['elements']['content']['#block_content'])) {
        $block = $variables['elements']['content']['#block_content'];
        // Add `block--BLOCK-TYPE.html.twig`.
        $suggestions[] = 'block__' . $block->bundle();
        $view_mode = $variables['elements']['#configuration']['view_mode'];
        if (!empty($view_mode)) {
            // Add `block--BLOCK-TYPE--VIEW-MODE.html.twig`.
            $suggestions[] = 'block__' . $block->bundle() . '__' . $view_mode;
        }
    }

      // Register $classes variable in case of class attributes manipulation.
  $classes = array();

  // Suggestion for block bundle.
  if (isset($variables['elements']['content']['#block_content'])) {
    $bundle = $variables['elements']['content']['#block_content']->bundle();
    array_splice($suggestions, 1, 0, 'block__block__' . $bundle);
  }

  // Suggestions for view modes.
  if (isset($variables['elements']['#configuration']['view_mode'])) {
    $view_mode = $variables['elements']['#configuration']['view_mode'];
    array_splice($suggestions, 1, 0, 'block__block__' . $view_mode);
  }

  if (isset($bundle) && isset($view_mode)) {
    array_splice($suggestions, 3, 0, 'block__block__' . $bundle . '__' . $view_mode);
  }

  // Field block suggestions
  if(isset($variables['elements']['content']['#entity_type'])) {
    if($variables['elements']['#base_plugin_id'] == 'field_block') {
      array_splice($suggestions, 3, 0, 'block__' . $variables['elements']['#base_plugin_id'] . '__' . $variables['elements']['content']['#entity_type'] . '__' . $variables['elements']['content']['#field_name']);
    }
  }


}

function particle_preprocess_block(&$variables)
{
    if ($variables['plugin_id'] == 'entity_browser_block:department_info') {
        $content = $variables['elements']['content'];
        for ($index = 0; $index <= sizeof($content)-1; $index++) {
            $variables['blocktitle'][$index] = $content[$index]['#block_content']->info->value;
            $variables['field_utc_department_building'][$index] = $content[$index]['#block_content']->get('field_utc_department_building')->view('url');
            $variables['field_utc_department_street_addr'][$index] = $content[$index]['#block_content']->get('field_utc_department_street_addr')->view('url');
            $variables['field_utc_department_email'][$index] = $content[$index]['#block_content']->get('field_utc_department_email')->view('url');
            $variables['field_utc_department_fax_number'][$index] = $content[$index]['#block_content']->get('field_utc_department_fax_number')->view('url');
            $variables['field_utc_department_mail_code'][$index] = $content[$index]['#block_content']->get('field_utc_department_mail_code')->value;
            $variables['field_utc_department_phone'][$index] = $content[$index]['#block_content']->get('field_utc_department_phone')->view('url');
        }
    }


    $variables['attributes'] =
    new Drupal\Core\Template\Attribute($variables['attributes']);
  $variables['title_attributes'] =
    new Drupal\Core\Template\Attribute($variables['title_attributes']);
  $variables['content_attributes'] =
    new Drupal\Core\Template\Attribute($variables['content_attributes']);

  // Add block class
  $variables['attributes']->addClass('block');

  // Add block--[PROVIDE] modifier class
  if(isset($variables['configuration']['provider'])) {
    $variables['attributes']
      ->addClass('block--' . str_replace('_', '-', $variables['configuration']['provider']));
  }

  // Add block--[REGION] modifier class
  if(isset($variables['elements']['#id'])) {
    // Loading block has no performance impact because is already loaded)
    $block = Block::load($variables['elements']['#id']);
    if($block !=  NULL) {
      $region = $block->getRegion();
      $variables['attributes']
        ->addClass('block--region-' . str_replace('_', '-', $region));
    }
  }

  // Add block--[PLUGIN_ID] modifier class
  if(isset($variables['configuration']['provider'])) {
    $variables['attributes']
      ->addClass('block--' . str_replace('_', '-', $variables['plugin_id']));
  }

  $variables['title_attributes']->addClass('block__title');
  $variables['content_attributes']->addClass('block__content');

  // kint($variables);
}