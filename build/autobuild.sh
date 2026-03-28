#!/bin/bash

echo Automatic Building script starting for LibreTerminal...
echo NOTE: This script uses the default package manager.

source /etc/os-release

if [ $ID == "fedora" || $ID == "rhel" || $ID == "centos" || $ID == "rocky" || $ID == "almalinux" ]; then
echo "Package manager detected - DNF"

sudo dnf update
sudo dnf install git g++ make

elif [ $ID == "ubuntu" || $ID == "debian" || $ID == "linuxmint" || $ID == "pop" || $ID == "zorin" ]; then
echo "Package manager detected - APT"

sudo apt update
sudo apt install git g++ make

elif [ $ID == "arch" || $ID == "manjaro" || $ID == "endeavouros" || $ID == "garuda" || $ID == "cachyos" || $ID == "blackarch" ]; then
echo "Package manager detected - Pacman"

sudo pacman -Syu git g++ make

else

echo "No Package manager detected - Assuming you have the dependencies preinstalled"

fi

git clone https://github.com/fif3x/LibreTerminal.git
mkdir -p ~/.config/libreterminal

cd LibreTerminal
cp etc/config.conf ~/.config/libreterminal/

cd build
chmod +x build.sh
./build.sh