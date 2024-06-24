if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/rend-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

set(package chimerarend)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Set up export components
install(
    TARGETS chimera_rend SDL3-shared SDL3_Headers
    EXPORT rendTargets
    RUNTIME COMPONENT rend_Runtime
    LIBRARY COMPONENT rend_Runtime
    NAMELINK_COMPONENT rend_Development
    ARCHIVE COMPONENT rend_Development
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
    rend_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(rend_INSTALL_CMAKEDIR)

# Install config file to the install directory
install(
    FILES cmake/install-config.cmake
    DESTINATION "${rend_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT rend_Development
)

# Install ConfigVersion file
# More package install info
install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${rend_INSTALL_CMAKEDIR}"
    COMPONENT rend_Development
)

# Install the dev component from targets defined above (I think)
install(
    EXPORT rendTargets
    NAMESPACE chimera::
    DESTINATION "${rend_INSTALL_CMAKEDIR}"
    COMPONENT rend_Development
)

# Include CPack
if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()