@echo off

cd ..
make

mkdir bin
move libreterminal.exe bin
make clean

cd bin
libreterminal

cd ..
:: Please run this through the cmd, not PowerShell

