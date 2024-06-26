#!/bin/bash

source config.source

# # Install ncurses
# Configure ncurses with specified options
cd srcRPI/ncurses
export CXX=$PATH_CC/arm-linux-gnueabihf-c++
./configure --with-shared --prefix=$PREFIX --host=x86_64-build_unknown-linux-gnu --target=arm-linux-gnueabihf --disable-stripping --enable-widec
# Compile ncurses using available processors
make -j$(nproc)
# Install ncurses
make install
cd $envPath


# # Install WiringPi 
echo "Installing WiringPi..."
export DESTDIR=$PREFIX
export PREFIX=""

# Install WiringPi
cd srcRPI/wiringPi/wiringPi
make -j$(nproc) V=1 
make install

# Install WiringPiDev
cd ../devLib
export CC="$CCC -I$PREFIX/include"
make -j$(nproc) V=1 
make install

# Install GPIO
cd ../gpio
make clean
export CC="$CCC"
make -j$(nproc) V=1 
make install

cd $envPath

cd rootRPI/lib
rm libwiringPi.so
rm libwiringPiDev.so
ln -s libwiringPi.so.2.50 libwiringPi.so
ln -s libwiringPiDev.so.2.50 libwiringPiDev.so