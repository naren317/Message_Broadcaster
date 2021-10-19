#!/usr/bin/env bash

wget -O boost_1_74_0.tar.gz https://boostorg.jfrog.io/artifactory/main/release/1.74.0/source/boost_1_74_0.tar.gz
tar -xvf boost_1_74_0.tar.gz
cd boost_1_74_0/
./bootstrap.sh
./b2 --with=all -j $(nproc) install


