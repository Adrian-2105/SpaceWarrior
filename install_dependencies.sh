#!/bin/bash

# Force to the user to run this script with sudo
if [ "$EUID" -ne 0 ]; then
  echo "Please run this script with sudo:"
  echo "sudo $0 $*"
  exit
fi

# Install dependencies
sudo apt-get install -y pkg-config xorg openbox xorg-dev

# Install SDL library
cd ~
git clone https://github.com/libsdl-org/SDL
cd SDL
mkdir build
cd build
../configure
make -j4
sudo make install
cd ~
rm -rf SDL