# qmmp-plugin-ym
Input plugin for qmmp to replay YM music modules. These are often neglected on 
other players. Not anymore on qmmp. :-)

To build, you will need qtdevelopment files. On Ubuntu, what you need is usually
installed with the "libqt4-dev" package. For actual build, then execute:

 qmake

 make

The resulting plugin "plugin/libym.so" needs to be manually copied to the qmmp
install directory. On Ubuntu, this is "/usr/lib/qmmp/Input/" for Input plugins.

The qmmp player itself can be found on:
http://qmmp.ylsoftware.com/

