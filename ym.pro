TEMPLATE = subdirs

SUBDIRS = translations plugin package
 
package.file = package/package.pro
package.depends = plugin

plugin.file = plugin/plugin.pro
plugin.depends = translations

translations.file = translations/translations.pro

