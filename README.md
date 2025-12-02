# INTRO
My Goal develop Lite Code Editor.
Why everybody like freeze web editor Monaco?
Why everybody want use JavaScript for Desktop Applications?
Desktop have QT library and it more the enough to build Lite Rapid IDE.

# Compile Linux

Install Dependencies
```bash
apt  install qt5keychain-dev cmake build-essential
```
For build use
```bash
./build.sh
```

# Compile Microsoft Windows MSYS2
download from https://github.com/msys2/msys2-installer/releases/download/2025-08-30/msys2-x86_64-20250830.exe
install  MSYS2

```bash

# update
pacman -Syu

# Install compiler and CMake
pacman -S --needed base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake

# Install Qt5
pacman -S mingw-w64-x86_64-qt5 mingw-w64-x86_64-qt-creator

pacman -S git
```
RunMingw Environment

```phell
msys-mingw-env.cmd
mkdir build-windows
cd build-windows
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make -j4

```
Copy this library from MSYS64 and use this directory structure

```shell
├── libbrotlicommon.dll
├── libbrotlidec.dll
├── libbz2-1.dll
├── libdouble-conversion.dll
├── libfreetype-6.dll
├── libgcc_s_seh-1.dll
├── libglib-2.0-0.dll
├── libgraphite2.dll
├── libharfbuzz-0.dll
├── libiconv-2.dll
├── libicudt78.dll
├── libicuin78.dll
├── libicuio78.dll
├── libicutest78.dll
├── libicutu78.dll
├── libicuuc78.dll
├── libintl-8.dll
├── libmd4c.dll
├── libpcre2-16-0.dll
├── libpcre2-8-0.dll
├── libpng16-16.dll
├── libstdc++-6.dll
├── libwinpthread-1.dll
├── libzstd.dll
├── MyCodeEditor.exe
├── platforms
│   ├── qdirect2d.dll
│   ├── qminimal.dll
│   ├── qoffscreen.dll
│   ├── qwebgl.dll
│   └── qwindows.dll
├── Qt5Core.dll
├── Qt5Gui.dll
├── Qt5Widgets.dll
├── qwindows.dll
└── zlib1.dll
```

# TODO

* CMD file for build and copy dll in windows
* Action for github for build windows exe
* Action for build Linux binary
* Auto Find and create python Environment
* Run python Application using Virtual Environment
