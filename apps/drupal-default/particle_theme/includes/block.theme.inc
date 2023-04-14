<?php

use Drupal\node\NodeInterface;
/**
 * @file
 * Functions to support theming blocks in the Particle theme.
 */
use Drupal\media\Entity\Media;
use Drupal\media_entity\MediaInterface;
use Drupal\file\Entity\File;
use Drupal\Component\Utility\Html;

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
    $node_bundle = null;
    if ($node) {
        if ($node instanceof NodeInterface) {
            $nid = $node->id();
            $node_bundle = $node->bundle();
        }
        if ($node instanceof NodeInterface) {
            $node_url_string = $node->toUrl()->toString();
        }
    } 
    $word= 'node';
    if (strpos((string) $node_url_string, $word) !== false) {
        $suggestions[] = ('block__' . "_id_" . $nid . "_label_" . preg_replace('/\s+/', '_', $variables['elements']['#configuration']['label']));
    } else {
        $suggestions[] = ('block__'. str_replace('-', '_', ltrim((string) $node_url_string, '/')) . "_id_" . $nid . "_label_" . preg_replace('/\s+/', '_', $variables['elements']['#configuration']['label']));
    }

    if($variables['elements']['#base_plugin_id'] == 'system_breadcrumb_block'){
        $suggestions[] = 'block__' . $variables['elements']['#base_plugin_id'] . "_" . $node_bundle;
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
    if ($variables['plugin_id'] == 'inline_block:utc_wpblogs') {
        $content = $variables['elements']['content']; //field_utcwp_categoriesid //field_utcwp_itemsperpage
        //  dd($content['#block_content']->field_utc_wpblogs->value);
        // dd($content['#block_content']->field_utcwp_itemsperpage->value);
        $id = Html::getUniqueId('utcmocsync');
        $variables['#attached'] = [
            'drupalSettings' => [
              'utc_wpblogdrupalsettings' => [ 
                $id => [
                'utcwp_blogs' => $content['#block_content']->field_utc_wpblogs->value ?? 'blank',
                'utcwp_categoriesid' => $content['#block_content']->field_utcwp_categoriesid->value ?? 'blank',
                'utcwp_itemsperpage' => $content['#block_content']->field_utcwp_itemsperpage->value ?? 'blank',
                    ],
                ],
            ],
        ];
        $variables['#attached']['library'][] = 'utccloud/utc-wpblogsfeed'; 
        $variables['#attached']['library'][] = 'utccloud/utc-wpblogsfeedsvelte'; 
            //         {{ attach_library('utccloud/utc-wpblogsfeed') }}
            // {{ attach_library('utccloud/utc-wpblogsfeedsvelte') }}
                    // \Drupal::messenger()->addStatus('Successful message.');
    }

}

function particle_block_build_alter(array &$build, \Drupal\Core\Block\BlockPluginInterface $block) {
    \Drupal::messenger()->addStatus('Successful message.');
    // Adds exra info if the plugin ID matches.
    die($block->label());
    if ($block->getPluginId() === 'inline_block:utc_wpblogs') {
        die('sucess'); 
    //   $build['#cache']['contexts'][] = 'user';
    }
  }

// function hook_block_build_BASE_BLOCK_ID_alter(array &$build, \Drupal\Core\Block\BlockPluginInterface $block) {
//     // inline_block:utc_wpblogs
//     // Explicitly enable placeholdering of the specific block.
//     $build['#create_placeholder'] = TRUE;
//   }
