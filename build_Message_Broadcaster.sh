#!/usr/bin/env bash

mkdir build 2>/dev/null
cd build && cmake .. && cmake --build . --config release --clean-first
cp Message_Broadcasting_Server/Message_Broadcasting_Server /usr/bin/Message_Broadcasting_Server



