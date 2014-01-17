Setting up the work environment:

1. Download and install Qt Creator if you don't have it already
http://download.qt-project.org/official_releases/qtcreator/3.0/3.0.0/qt-creator-opensource-windows-x86-3.0.0.exe

2. Install Perl (needed for OpenSSL build)
- http://www.activestate.com/activeperl/downloads
- add the executable to your system PATH if it was no added automatically

3. Install Visual Studio 2013 (Express for Windows Desktop)
http://www.visualstudio.com/en-us/products/visual-studio-express-vs.aspx

4. Download latest source of OpenSSL
- http://www.openssl.org/source/
- Extract to C:\git\openssl
- Run the following commands:
C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat
cd c:\git\openssl\openssl
perl Configure VC-WIN32 --prefix=C:\git\openssl\build
ms\do_ms
nmake -f ms\nt.mak 
nmake -f ms\nt.mak install

5. Install git
http://git-scm.com/
Go through the first few chapters of the online Book to setup your name and certificates etc

6. Get the Qt5.2 sources, configure and build

From Git Bash console execute:
cd c:\git
git clone https://github.com/qtproject/qt5.git

Open cmd, execute:
C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat
configure -static -qmake -opensource -nomake examples -opengl desktop -platform win32-msvc2013 -openssl -openssl-linked -I C:\git\openssl\build\include -L C:\git\openssl\build\lib OPENSSL_LIBS="-llibeay32 -lssleay32 -lgdi32"
->Accept the license with "y"
nmake 

Wait for 2 hours for qt to compile.
If you have multi-core CPU, you can use jom instead of nmake: http://qt-project.org/wiki/jom
Install it, add jom.exe to system PATH and type: jom
It should build faster than nmake.

7. Open Qt Creator
Tools->Options->Build & Run->Qt Versions->C:\git\qt5\qt5\qtbase\bin\qmake.exe
Kits->Add->Name it "Qt5-Desktop-msvc2013-static", Compiler choose MS C++ Compiler 12.0 (x86), Version choose Qt 5.2.0 (qt5) STATIC
Debugger should be auto detected

8. Get the client repo
cd c:\git
git clone git@xpam.pl:xpam

9. Open xpam.pro with Qt Creator, choose the Kit from point 7 and set debug and build paths:
C:\git\xpam\xpam\release
C:\git\xpam\xpam\debug

Done!








