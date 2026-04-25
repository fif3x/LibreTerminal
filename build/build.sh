#!/bin/bash
cd ..
echo "Using 'make' on libreterminal"
make libreterminal
echo "Using 'make' on lt-plugin"
make lt-plugin
echo "----------"
mkdir -p bin
mv libreterminal bin
mv lt-plugin bin
make clean

mkdir -p ~/.config/libreterminal && mkdir -p ~/.config/libreterminal/plugins
cp ./etc/config.conf ~/.config/libreterminal/config.conf


if sudo -v 2>/dev/null; then
    echo "You have sudo privileges."
    sudo cp bin/libreterminal /usr/bin
    libreterminal
else
    echo "You do not have sudo privileges."
    ./bin/libreterminal
fi

cd ..

# YOU MUST be in the build folder.
