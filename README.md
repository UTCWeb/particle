
# UTCWeb's Particle
## UTC Developer Cheat Sheet
### Warning
1. The module and the submodule both have a master and develop branch.
1. If working on the git submodule don't update utccloud parent repo until you have commited changes. (data can be lost if you update utccloud while working on particle subtheme.
1. Only commit the changes on the parent git repo when you want utccloud to refer to the latest revision of the particle repo. In other words, it should be done once per PR to the main repo.

### Setup
1. `git submodule update --init --recursive` -> the first time the submodule is added to your repo (on MacOS, linux handles this fine).
1. `git submodule update --recursive` -> after is beeing added once.
1. `composer install` and `npm install` -> if blt setup and sync have not been used.


### Things to remember

1. gulp -> `npm run dev:drupal`
1. `npm start` -> starts the living stylesheet
1. `ads run drush cr` -> might be needed from time to time.

Other npm commands can be found in package.json.
```json
    "start": "npm run dev:pl",
    "pl": "node ./apps/pl-default/pl-app.js",
    "setup": "patternlab install --config ./apps/pl-default/patternlab-config.json && patternlab build --config ./apps/pl-default/patternlab-config.json",
    "export:pl": "patternlab export --config ./apps/pl-default/patternlab-config.json",
    "dev:pl": "cross-env-shell NODE_ENV=development \"npm run pl & webpack-dev-server --config ./apps/pl-default/webpack.config.js --hot\"",
    "build:pl": "cross-env-shell NODE_ENV=production \"npm run pl && webpack --config ./apps/pl-default/webpack.config.js\"",
    "dev:drupal": "cross-env-shell NODE_ENV=development \"webpack --watch --config ./apps/drupal-default/webpack.config.js\"",
    "build:drupal": "cross-env-shell NODE_ENV=production \"webpack --hide-modules --config ./apps/drupal-default/webpack.config.js\"",
    "lint:js": "eslint --ext .js,.vue ./",
    "lint:css": "stylelint '**/*.css'",
    "lint": "npm run lint:js; npm run lint:css;",
    "fmt:js": "npm run lint:js -- --fix",
    "fmt:css": "npm run lint:css -- --fix && prettier --write '**/*.css'",
    "fmt:svg": "svgo -f ./source/default/_patterns/01-atoms/svg/icons --config=./.svgo.yml",
    "fmt": "npm run fmt:svg; npm run fmt:js; npm run fmt:css; prettier --write .",
    "test:backstop:ref": "node tools/tests/vrt/backstop-example-reference.js",
    "test:backstop:test": "node tools/tests/vrt/backstop-example-test.js",
    "test:pa11y": "pa11y-ci --config tools/tests/accessibility/pa11y.js",
    "test:unit:default": "NODE_ENV=test jest --projects source/default/",
    "test:unit": "npm run test:unit:default",
    "test:tools:generators": "NODE_ENV=test jest --projects tools/generators/",
    "test": "npm run test:unit",
    "ci": "npm run lint && npm run test && npm run build:pl && npm run build:drupal",
    "new": "yo new-component",
    "postinstall": "cd tools/generators/new-component && npm link"
```

---

## Particle: A design system integrating to Pattern Lab and a Drupal 8 theme

[![GitHub (pre-)release](https://img.shields.io/github/release/phase2/particle/all.svg)](https://github.com/phase2/particle/releases)
[![Build Status](https://travis-ci.org/phase2/particle.svg?branch=master)](https://travis-ci.org/phase2/particle)
[![Greenkeeper badge](https://badges.greenkeeper.io/phase2/particle.svg)](https://greenkeeper.io/)

![Particle mascot: Astrogoat](apps/pl-default/pattern-lab/_patterns/01-atoms-demo/image/astrogoat.png?raw=true 'Astrogoat')

Particle is an opinionated set of tools and examples to:

1.  Build an application-agnostic **design system**
1.  Apply that design system to a locally-served **Pattern Lab** for rapid
    prototyping
1.  Apply that design system to a **Drupal theme**

In depth documentation about frontend approach using this project at
[Phase2 Frontend Docs](https://phase2.gitbook.io/frontend/)

## Prerequisites

- [Node `^8`, `^10`, `^12`](https://nodejs.org)
- [NPM `^5`, `^6`](https://www.npmjs.com/)
- [PHP `^7`](https://php.net)

[Step-by-step instructions to install all dependencies for OSX can be found in this Gist.](https://gist.github.com/illepic/efd6ab9f452af2a99b7ade78257e6b96)

## Provides

- Drupal theme, Grav theme, and Pattern Lab app
- Strict [Atomic Design](http://atomicdesign.bradfrost.com/) component structure
- Webpack bundling of all CSS, javascript, font, and static image assets for
  multiple targets (Drupal theme, Grav theme, Pattern Lab)
- [Webpack Dev Server](https://github.com/webpack/webpack-dev-server) for local
  hosting and hot reloading of assets into Pattern Lab
- [Twig namespaced paths](https://symfony.com/doc/current/templating/namespaced_paths.html)
  automatically added into Drupal theme and Pattern Lab config. Within any twig
  file, `@atoms/thing.twig` means the same thing to Drupal theme and Pattern
  Lab.
- Iconfont auto-generation
- Auto-linting against the
  [AirBnB JavaScript Style Guide](https://github.com/airbnb/javascript)
- All Webpack files are fully configurable
- Simple [Yeoman](http://yeoman.io/) generator for Design System component
  creation

## Quickstart

Particle builds design systems in dev mode for local hosting, or production mode
for optimized asset generation.

### Quickstart A

1. Simply run:

   ```bash
   npm create @phase2/particle particle
   ```

1. Then `cd particle/` and run:

   ```bash
   npm start
   ```

### Quickstart B

1.  [Download the latest release](https://github.com/phase2/particle/releases)
1.  Extract anywhere (i.e. this readme should be at
    `any/where/particle/README.md`)
1.  Within the extracted folder run:

```bash
npm install
npm run setup
npm start
```

Simply wait until the webpack bundle output appears then visit
[http://0.0.0.0:8080/app-pl/pl/](http://0.0.0.0:8080/app-pl/pl/) (or
[http://localhost:8080/app-pl/pl/](http://localhost:8080/app-pl/pl/)) and start
working.

That's it. For **much** greater detail on the frontend approach using this
project, check out the
[Phase2 Frontend Docs](https://phase2.gitbook.io/frontend/).

## Design System Naming

The Design System Source folder is named default `./source/default`. It's handy
in multi-design setups to name this per design system and post-fix `apps` with
that design system name. For example, `apps/drupal-default/` contains the
implementation of the `default` source directory. These are intended to be
updated by the needs of your project.
