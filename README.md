# xpam-client
Desktop client application for eurobattle.net

Setup instructions
----------
## Qt
Use the official Qt installer to install latest 6.X libraries for MSVC 2022 with OpenSSL and Qt WebEngine.

## Build dependent libraries
- zlib
- quazip
- stormlib
- boost
- libtorrent

Build for x64, release and debug modes.

We plan to migrate to cmake+conan to make this step automated.

## Copy dependent libs to release folders

We use Windows deployment tool to copy the necessary libraries to debug and release folders.

Visual Studio -> Tools -> Command line -> Developer command prompt
C:/Qt/6.5.3/msvc2019_64/bin/qtenv2.bat
cd C:/path/to/xpam-client/build-xpam-Desktop_Qt_6_5_3_MSVC2019_64bit-Debug/debug
windeployqt --debug xpam.exe
cd C:/path/to/xpam-client/build-xpam-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/release
windeployqt --release xpam.exe

Finally, copy zlib, quazip, stormlib and libtorrent dlls manually.

Additionally, copy qt6core5compat(d).dll, libssl-3-x64.dll, libcrypto-3-x64.dll from Qt installation.