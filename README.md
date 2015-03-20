# qmmp-plugin-ym
Input plugin for qmmp to replay YM music modules. These are often neglected on 
other players. Not anymore on qmmp. :-)

To build, you will need qtdevelopment files. On Ubuntu, what you need is usually
installed with the "libqt4-dev" and "libqmmp-dev" package. 

For the actual build, then execute:

 qmake

 make

The resulting plugin "plugin/libym.so" needs to be manually copied to the qmmp
install directory. On Ubuntu, this is "/usr/lib/qmmp/Input/" for Input plugins.

Or else use the resulting install package in the package subdirectory.

The qmmp player itself can be found on:
http://qmmp.ylsoftware.com/

