TEMPLATE = subdirs

SUBDIRS = translations plugin
 
plugin.file = plugin/plugin.pro
plugin.depends = translations

translations.file = translations/translations.pro

