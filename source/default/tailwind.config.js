/**
 * Tailwind config for design system
 *   Requires Tailwind 1.4.0 or greater
 */

const path = require('path');

// Tailwind Plugins
const tailwindForms = require('@tailwindcss/forms');

const colors = require('./tokens/colors.tailwind');
const customForms = require('./tokens/forms.tailwind');
const fontFamily = require('./tokens/font-family.tailwind');
const { fontSize } = require('tailwindcss/defaultTheme');

// Default Tailwind config can be found here: https://github.com/tailwindcss/tailwindcss/blob/v1.2.0/stubs/defaultConfig.stub.js
module.exports = {
  important: true,
  // Purge CSS from Tailwind Only.
  purge: {
    content: [path.resolve(__dirname, '_patterns/**/*.*'), path.resolve(__dirname, '../../apps/drupal-default/particle_theme/templates/**/*.*')],
    options: {
      // Whitelist Non-DS Dependent Patterns.
      whitelistPatterns: [/^bg/, /^text/, /:?-?m[xy]?-/, /:?p[xy]?-/],
      defaultExtractor: (content) => content.match(/[A-Za-z0-9-_:/]+/g) || [],
      extensions: ['yml', 'twig', 'json', 'js', 'ts'],
    },
  },
  theme: {
    colors,
    customForms,
    fontFamily, 
    extend: {
      gridTemplateRows: {
        // Adds a custom template for the utc hero block
        'utchero': '40px 1fr 1fr 70px',
        'utcheroreverse': '70px 1fr 1fr 40px',
        'utcherocenter': '25px 1fr 1fr 25px',
      },
      gridTemplateColumns: {
        // Adds a custom template for the utc hero block
        'utchero': '1fr 60% 35% 1fr',
        'utcheroright': '1fr 35% 60% 1fr',
        'utcherocenter': '1fr 45% 45% 1fr',
      },
      flex: {
        'utccard': '0 0 auto',
        'utccardbody': '1 0 65%',
        'utccardimg': '0 1 35%',
      },
      boxShadow: {
        'utccardnone': '0 0 4px 4px rgba(17,46,81,.25)',
        'utccardwhite': '0 10px 15px -3px rgb(0 0 0 / 10%), 0 4px 6px -2px rgb(0 0 0 / 5%)',
      },
      fontSize: {
        'icon-sm': '1rem',
        'icon-md': '3rem',
        'icon-lg': '5rem',
        'icon-xl': '7rem',
        'icon-2x': '9rem',
      }
    },
    minHeight: {
      '23': '23rem'
    }
  },
  variants: {
    extend: {
     margin: ['first'],
    }
  },
  plugins: [tailwindForms],
};
