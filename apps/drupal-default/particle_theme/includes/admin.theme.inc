<?php

/**
 * @file
 * Functions to support theming admin in the Particle theme.
 */

/**
 * Implements hook_preprocess_input().
 */
function particle_preprocess_input(&$variables) {
  $variables['variant'] = (string) $variables['attributes']['type'];
}
