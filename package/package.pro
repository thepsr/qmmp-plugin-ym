TEMPLATE = aux
TARGET   = 
CONFIG  += no_link target_predeps

QMAKE_POST_LINK  = fakeroot -- ./make-deb.sh
#QMAKE_CLEAN     += batch_output.obj


