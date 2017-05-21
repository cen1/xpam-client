# xpam-client
Desktop client application for eurobattle.net

Msvc2015 with XP target is used for building.

Setup instructions
----------
 1. Get the latest Qt source. We plan to transition to 5.6 as soon as it is released because 5.5 has a critical QNetworkManager bug which makes the updater fail.
 2. Build OpenSSL with XP target. If you don't want to get through this ordeal, just download our  binaries at http://files.eurobattle.net/random/openssl-x86-shared-release-vs2015-win10.zip
 3. Open VS 2015 cmd. Install Windows 7.1A SDK and prepare your ENV for XP http://doc.qt.io/qt-5/windows-issues.html. Then configure Qt with something like: ```configure -target xp -release -qmake -opensource -nomake examples -opengl desktop -platform win32-msvc2015 -openssl -I path/to/to/openssl-x86-shared-release-vs2015-win10/include -L path/to/openssl-x86-shared-release-vs2015-win10/lib OPENSSL_LIBS="-llibeay32 -lssleay32 -lgdi32"```
 4. Run ```nmake``` or ```jom```
 5. Add the built kit to your Qt creator.

