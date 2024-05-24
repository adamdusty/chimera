if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/sdk-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

set(package chimerasdk)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Set up export components
install(
    TARGETS chimera_sdk
    EXPORT sdkTargets
    RUNTIME COMPONENT sdk_Runtime
    LIBRARY COMPONENT sdk_Runtime
    NAMELINK_COMPONENT sdk_Development
    ARCHIVE COMPONENT sdk_Development
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Write package file for installations
write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    sdk_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(sdk_INSTALL_CMAKEDIR)

# Install config file to the install directory
install(
    FILES cmake/install-config.cmake
    DESTINATION "${sdk_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT sdk_Development
)

# Install ConfigVersion file
# More package install info
install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${sdk_INSTALL_CMAKEDIR}"
    COMPONENT sdk_Development
)

# Install the dev component from targets defined above (I think)
install(
    EXPORT sdkTargets
    NAMESPACE chimera::
    DESTINATION "${sdk_INSTALL_CMAKEDIR}"
    COMPONENT sdk_Development
)

# Include CPack
if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()