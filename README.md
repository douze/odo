# odo
OpenGL demo, using modern:
* Toolchain
* C++
* OpenGL

## Installation

**Prerequisites:** install 
* dependencies: pkg-config xorg-dev libx11-xcb-dev libxcb-render0-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev
* build system generator: [cmake](https://cmake.org/)
* build system: [ninja](https://ninja-build.org/)
* compiler: [clang++](https://clang.llvm.org/)
* package manager: [conan](https://conan.io/)

### Download packages

```bash
conan install . -if build/ -s build_type=Debug -s compiler=clang -s compiler.version=10 -s compiler.libcxx=libstdc++11 -e CC=clang -e CXX=clang++ -b outdated
```

#### Alternative

```bash
sh setup.sh
````

### Generate build files

```bash
CC=clang CXX=clang++ cmake -G Ninja -S . -B build/
```

#### Alternative

```bash
sh configure.sh
````

### Build

```bash
cmake --build build
```

#### Alternative

```bash
sh build.sh
````

## Usage

```bash
./build/bin/demo
````

#### Alternative

```bash
sh run
````
