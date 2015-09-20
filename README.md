ColorPickerPlugin for QtCreator
===============================

A color picker plugin to easily insert and modify colors in QtCreator's text documents.


Build the plugin
-----------------
Put all files in `<QtCreatorSourcesDir>/src/plugins/colorpicker`.

Now open `<QtCreatorSourcesDir>/src/plugins.qbs` with your favorite text editor and add the project file to the reference list (something like `"colorpicker/colorpicker.qbs"`).

Build QtCreator. That's it.

Please note
-----------------
- This plugin is developed for QtCreator >= 3.5.0. I will not test it with earlier versions.

- I use Qbs rather than QMake. It seems that there's currently no way to develop a plugin without having the whole QtCreator project opened.

- WIP !
