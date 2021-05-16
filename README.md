# xpam-client
Desktop client application for eurobattle.net

Setup instructions
----------
## Qt
Use the official Qt installer to install latest stable 5.X libraries for MSVC 2019 with OpenSSL and Qt WebEngine.

Build quazip as shared library with MSVC 2019.

Afte building the project, copy the following files into your release folder:
```
libcrypto-1_1.dll
libssl-1_1.dll
Qt5WebEngineWidgets.dll
Qt5WebEngineCore.dll
Qt5Positioning.dll
Qt5WebChannel.dll
Qt5QuickWidgets.dll
Qt5Quick.dll
Qt5QmlModels.dll
Qt5Qml.dll
platforms\qwindows.dll
Qt5Widgets.dll
Qt5Network.dll
Qt5Gui.dll
Qt5Core.dll
zlib1.dll
quazip1-qt5.dll
qtwebengine_resources_200p.pak
qtwebengine_devtools_resources.pak
qtwebengine_resources.pak
qtwebengine_resources_100p.pak
QtWebEngineProcess.exe
```

