# Xpam client
Desktop client application for eurobattle.net

## Build Instructions

### Prerequisites

- CMake 3.25+
- Visual Studio 2022 with MSVC toolchain
- vcpkg (included with VS2022)
- Qt 6.11.1+ for MSVC 2022 64-bit

### Qt Installation

Install Qt 6.11.1 using Qt Online Installer. Under **Qt 6.x.x → MSVC 2022 64-bit**, install:

- Qt Base (Core, GUI, Widgets, Network)
- Qt WebEngine
- Qt WebChannel
- Qt 5 Compatibility Module (Core5Compat)

Default install path: `C:\Qt\6.11.1\msvc2022_64`

### Build

```bash
git clone https://github.com/cen1/xpam-client.git
cd xpam-client

cmake -B build -G "Visual Studio 17 2022" -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE="C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake"

cmake --build build --config Release
```

First build downloads and compiles dependencies via vcpkg (10-30 minutes).

Output: `build/bin/Release/xpam.exe`

### Dependencies

Managed by vcpkg: zlib, boost-system, libtorrent, quazip, stormlib

Qt from system installation.

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
Possible locations: `EUROPATH, GPROXYPATH, SOUNDPATH, W3PATH, W3PATH_126, MAPPATH, MAPPATH_126`  
```
4. Select all files and create a .zip (do not zip the folder!)
5. Calculate hash: `sha1sum v7.04h0.zip`
6. Create a pull request to [update.json](https://github.com/cen1/xpam-client/blob/master/xpam/update.json). Replace the oldest map or add a new entry. Keep the mirror hostnames and paths the same, just replace the final zip name.