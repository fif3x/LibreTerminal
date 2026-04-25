@echo off

cd ..
echo "Using 'make' on libreterminal"
make libreterminal
echo "Using 'make' on lt-plugin"
make lt-plugin

echo "----------"
mkdir bin
move libreterminal.exe bin
move lt-plugin.exe bin
make clean

mkdir "%APPDATA%\libreterminal" && mkdir "%APPDATA%"\libreterminal\plugins
copy etc\config.conf %APPDATA%\libreterminal

cd bin
libreterminal

cd ..
:: Please run this through the cmd, not PowerShell
