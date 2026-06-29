# Source files
set(XPAM_SOURCES
    main.cpp
    mainwindow.cpp
    registry.cpp
    gproxy.cpp
    config.cpp
    downloader.cpp
    torrentdownloader.cpp
    updater.cpp
    w3.cpp
    test.cpp
    mpq.cpp
    patcher.cpp
    bnethash.cpp
    rest.cpp
)

# Header files
set(XPAM_HEADERS
    mainwindow.h
    registry.h
    torrentdownloader.h
    util.h
    gproxy.h
    config.h
    winutils.h
    downloader.h
    updater.h
    w3.h
    test.h
    mpq.h
    logger.h
    patcher.h
    bnethash.h
    rest.h
)

# UI files
set(XPAM_UIS
    mainwindow.ui
)

# Qt resource files
set(XPAM_RESOURCES
    xpam.qrc
)

# Windows resource file
set(XPAM_RC
    xpam.rc
)

# Create executable
add_executable(xpam WIN32
    ${XPAM_SOURCES}
    ${XPAM_HEADERS}
    ${XPAM_UIS}
    ${XPAM_RESOURCES}
    ${XPAM_RC}
)

# Include directories
target_include_directories(xpam PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}  # For generated Qt files
)

# Compiler definitions
target_compile_definitions(xpam PRIVATE
    PSAPI_VERSION=1
    NOMINMAX
    _UNICODE
    UNICODE
    STORMLIB_NO_AUTO_LINK
)

# Link libraries
target_link_libraries(xpam PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::WebEngineWidgets
    Qt6::Widgets
    ZLIB::ZLIB
    Boost::system
    QuaZip::QuaZip
    LibtorrentRasterbar::torrent-rasterbar
    StormLib::storm
    version.lib  # Windows version API
    Psapi.lib    # Windows Process API
)

# Windows manifest for UAC elevation
if(MSVC)
    set_target_properties(xpam PROPERTIES
        LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\""
    )
endif()

# MSVC compiler settings
if(MSVC)
    target_compile_options(xpam PRIVATE
        /MP          # Multi-processor compilation
        /W3          # Warning level 3
        /EHsc        # Exception handling
        $<$<CONFIG:Release>:/O2>   # Optimization
        $<$<CONFIG:Release>:/GL>   # Whole program optimization
    )

    target_link_options(xpam PRIVATE
        $<$<CONFIG:Release>:/LTCG>      # Link-time code generation
        $<$<CONFIG:Release>:/OPT:REF>   # Eliminate unreferenced functions
        $<$<CONFIG:Release>:/OPT:ICF>   # COMDAT folding
    )
endif()

# Output directory
set_target_properties(xpam PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Qt deployment (windeployqt)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${Qt6_DIR}/../../../bin")
if(WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET xpam POST_BUILD
        COMMAND ${WINDEPLOYQT_EXECUTABLE}
            --no-compiler-runtime
            --no-system-d3d-compiler
            --no-opengl-sw
            $<$<CONFIG:Debug>:--debug>
            $<$<CONFIG:Release>:--release>
            $<TARGET_FILE:xpam>
        COMMENT "Running windeployqt for xpam..."
    )
endif()
