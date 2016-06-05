TEMPLATE = aux

OBJECTS_DIR = ./
DESTDIR = ./

first.commands = fakeroot -- ./make-deb.sh
QMAKE_EXTRA_TARGETS += first


