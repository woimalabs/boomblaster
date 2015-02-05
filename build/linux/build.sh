#!/bin/sh
touch README NEWS AUTHORS ChangeLog; autoreconf -i; ./configure; sudo make -j 4 install
