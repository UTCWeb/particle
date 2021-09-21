<?php

/**
 * @file
 * Functions to support theming layouts in the Particle theme.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function particle_preprocess_page(&$variables) {
  // Themes are not able to declare module dependencies at this time.
  // We use this as a shortcut to guarantee the component library module exists.
  $moduleHandler = \Drupal::service('module_handler');
  if ($moduleHandler->moduleExists('components')) {
    $variables['has_components_module'] = TRUE;
  }


  // if($variables['layout']->getProvider() != 'themag_layouts') {
  //   // Adding wrapper class to layouts.
  //   $variables['attributes'] = new Drupal\Core\Template\Attribute($variables['attributes']);

  //   $layout_classes = array(
  //     'layout',
  //     str_replace('_', '-', $variables['theme_hook_original'])
  //   );
  //   $variables['attributes']->addClass($layout_classes);

  //   // Adding classes to each layout region.
  //   if (isset($variables['region_attributes']) && is_array($variables['region_attributes'])) {
  //     foreach ($variables['region_attributes'] as $region_key => $region_value) {
  //       $region_value->addClass('layout__region', 'layout__region--' . str_replace('_', '-', $region_key));
  //       $region_value->setAttribute('id','region--' . str_replace('_', '-', $region_key) );
  //     }
  //   }
  // }

}
