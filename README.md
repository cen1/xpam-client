# Xpam client
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

## Build dynamic StormLib
```
git clone git@github.com:ladislav-zezula/StormLib.git
cd StormLib
git checkout v9.25
"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvarsall.bat" amd64
cmake -B ./build_dynamic -DBUILD_SHARED_LIBS=ON -DUNICODE=ON
cd build_dynamic
cmake --build . --config Release
```

## Copy dependent libs to release folders

We use Windows deployment tool to copy the necessary libraries to debug and release folders.

```
Visual Studio -> Tools -> Command line -> Developer command prompt
C:/Qt/6.5.3/msvc2019_64/bin/qtenv2.bat
cd C:/path/to/xpam-client/build-xpam-Desktop_Qt_6_5_3_MSVC2019_64bit-Debug/debug
windeployqt --debug xpam.exe
cd C:/path/to/xpam-client/build-xpam-Desktop_Qt_6_5_3_MSVC2019_64bit-Release/release
windeployqt --release xpam.exe
```

Finally, copy zlib, quazip, stormlib and libtorrent dlls manually.

Additionally, copy qt6core5compat(d).dll, libssl-3-x64.dll, libcrypto-3-x64.dll from Qt installation.

#  Update.json as gist
There was an issue with line endings and hash mismatch which is now taken care of with a .gitattributes directive. You can copy and paste the file as is, do not remove the final newline.

# Preparing a dota map update

1. Create a folder `v7.04h0`
2. Put all files in this folder as a flat structure.
```
-- DotA_Allstars_7.04h0.w3x
-- dota704h0files.mpq
-- instructions.txt
```
3. Edit `instructions.txt` with a list of files and move operations to appropriate folders.
```
MOVE DotA_Allstars_7.04h0.w3x MAPPATH_126
MOVE dota704h0files.mpq W3PATH_126
```
```
Possible actions: `MOVE, DELETE or ICONS`  
Possible locations: `EUROPATH, SOUNDPATH, W3PATH, W3PATH_126, MAPPATH, MAPPATH_126`  
```
4. Select all files and create a .zip (do not zip the folder!)
5. Calculate hash: `sha1sum v7.04h0.zip`
6. Create a pull request to [update.json](https://github.com/cen1/xpam-client/blob/master/xpam/update.json). Replace the oldest map or add a new entry. Keep the mirror hostnames and paths the same, just replace the final zip name.