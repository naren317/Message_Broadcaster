#!/usr/bin/env bash

wget https://cmake.org/files/v3.17/cmake-3.17.5.tar.gz
tar -xzvf cmake-3.17.5.tar.gz
cd cmake-3.17.5/
./bootstrap
make -j$(nproc)
make install

