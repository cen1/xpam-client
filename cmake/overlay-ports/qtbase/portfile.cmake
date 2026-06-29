# This is a system package overlay
# Qt6 is provided by the system installation at C:/Qt/6.11.1

set(VCPKG_POLICY_EMPTY_PACKAGE enabled)

# Install the CMake config wrapper that just sets CMAKE_PREFIX_PATH
file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/Qt6Config.cmake"
     DESTINATION "${CURRENT_PACKAGES_DIR}/share/Qt6")

file(WRITE "${CURRENT_PACKAGES_DIR}/share/${PORT}/copyright" "System-provided Qt6 installation")
