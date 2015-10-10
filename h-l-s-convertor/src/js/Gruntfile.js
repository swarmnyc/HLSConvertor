/*
 * (C) Copyright 2014-2015 Kurento (http://kurento.org/)
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 2.1 which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-2.1.html
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 */


module.exports = function(grunt)
{
  var DIST_DIR = 'dist';

  var pkg = grunt.file.readJSON('package.json');

  const PKG_BROWSER = 'lib/browser.js';

  // Project configuration.
  grunt.initConfig({
    pkg: pkg,

    // Plugins configuration
    clean:
    {
      'doc':     '<%= jsdoc.all.dest %>',
      'browser': DIST_DIR
    },

    // Generate documentation
    jsdoc:
    {
      all:
      {
        src: [
          'README.md',
          'lib/**/*.js',
          'test/*.js'
        ],
        dest: 'doc/jsdoc'
      }
    },

    // Generate browser versions and mapping debug file
    browserify:
    {
      options: {
        alias:    ['.:<%= pkg.name %>'],
        external: [
          'es6-promise',
          'inherits',
          'kurento-client',
          'promisecallback'
        ]
      },

      'standard':
      {
        src:  PKG_BROWSER,
        dest: DIST_DIR+'/<%= pkg.name %>.js'
      },

      'minified':
      {
        src:  PKG_BROWSER,
        dest: DIST_DIR+'/<%= pkg.name %>.min.js',

        options:
        {
          browserifyOptions: {
            debug: true
          },
          plugin: [
            ['minifyify',
             {
               compressPath: DIST_DIR,
               map:          '<%= pkg.name %>.map',
               output:       DIST_DIR+'/<%= pkg.name %>.map'
             }]
          ]
        }
      }
    },

    // Generate bower.json file from package.json data
    sync:
    {
      bower:
      {
        options:
        {
          sync: [
            'name', 'description', 'license', 'keywords', 'homepage',
            'repository'
          ],
          overrides: {
            authors: (pkg.author ? [pkg.author] : []).concat(pkg.contributors || []),
            ignore: ['doc/', 'lib/', 'Gruntfile.js', 'package.json'],
            main: DIST_DIR+'/<%= pkg.name %>.js'
          }
        }
      }
    }  });

  // Load plugins
  grunt.loadNpmTasks('grunt-browserify');
  grunt.loadNpmTasks('grunt-contrib-clean');
  grunt.loadNpmTasks('grunt-jsdoc');
  grunt.loadNpmTasks('grunt-npm2bower-sync');

  // Alias tasks
  grunt.registerTask('default', ['clean', 'jsdoc', 'browserify', 'sync:bower']);
};
