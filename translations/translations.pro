TEMPLATE = aux

include ( translations.pri )

myprebuild.input          = TRANSLATIONS
myprebuild.output         = ${QMAKE_FILE_BASE}.qm
myprebuild.commands       = $$[QT_INSTALL_BINS]/lupdate -silent ../plugin/plugin.pro && $$[QT_INSTALL_BINS]/lrelease -silent ../plugin/plugin.pro
myprebuild.CONFIG        += no_link target_predeps

QMAKE_EXTRA_COMPILERS += myprebuild

