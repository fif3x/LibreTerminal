#!/bin/bash
cd ..
make
mkdir -p bin
mv libreterminal bin
make clean

mkdir -p ~/.config/libreterminal && cp ./etc/config.conf ~/.config/libreterminal/config.conf

sudo cp bin/libreterminal /usr/bin
libreterminal

cd..

# YOU MUST be in the build folder.
