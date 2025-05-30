# qmmp-plugin-ym
Input plugin for qmmp 1.0.x - 2.2.x to replay YM music modules. These are often 
neglected on other players. Not anymore on qmmp. :-)

To build, you will need qtdevelopment files. On Ubuntu, what you need is usually
installed with the "qt6-tools-dev-tools", "qt6-base-dev" and "qmmp"
packages. 

For the actual build, then execute:

 /usr/lib/qt6/bin/qmake6

 make

The resulting plugin "plugin/libym.so" needs to be manually copied to the qmmp
install directory. On Ubuntu, this is "/usr/lib/qmmp/plugins/Input/" for Input 
plugins in qmmp 1.4.4 - 2.2.3 .

Or else use the resulting install package in the package subdirectory.

The qmmp player itself can be found on:
http://qmmp.ylsoftware.com/

