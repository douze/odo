#!/bin/bash
conan install . -if build/ -s build_type=Debug -s compiler=clang -s compiler.version=10 -s compiler.libcxx=libstdc++11 -e CC=/usr/bin/clang-10 -e CXX=/usr/bin/clang++-10 -b outdated
