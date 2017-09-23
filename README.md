# xpam-client
Desktop client application for eurobattle.net

Msvc2015 with XP target is used for building.

Setup instructions
----------
## Building dependencies on your own
 1. Get the Qt source for 5.7.1.
 2. Build OpenSSL with XP target. If you don't want to get through this ordeal, just download our  binaries at http://files.eurobattle.net/random/openssl-x86-shared-release-vs2015-win10.zip
 3. Open VS 2015 cmd. Install Windows 7.1A SDK and prepare your ENV for XP http://doc.qt.io/qt-5/windows-issues.html. Then configure Qt with something like: ```configure -target xp -release -qmake -opensource -nomake examples -opengl desktop -platform win32-msvc2015 -openssl -I path/to/to/openssl-x86-shared-release-vs2015-win10/include -L path/to/openssl-x86-shared-release-vs2015-win10/lib OPENSSL_LIBS="-llibeay32 -lssleay32 -lgdi32"```
 4. Run ```nmake``` or ```jom```
 5. Add the built kit to your Qt creator.

## Use sigmoid Qt5 binaries (recommended)
Use precompiled Qt5 binaries (shared) with openssl by sigmoid https://www.npcglib.org/~stathis/blog/precompiled-qt4-qt5/. Import project in Qt Creator, setup Qt kits and you are good to go.
