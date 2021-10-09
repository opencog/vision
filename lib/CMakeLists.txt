# CMake boilerplate for library config export.

include(CMakePackageConfigHelpers)

set(ConfigPackageLocation lib/cmake/AtomSpaceVision)

install(EXPORT AtomSpaceVisionTargets
	FILE AtomSpaceVisionTargets.cmake
	DESTINATION ${ConfigPackageLocation}
)

configure_package_config_file(AtomSpaceVisionConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/AtomSpaceVisionConfig.cmake
	INSTALL_DESTINATION ${ConfigPackageLocation}
	PATH_VARS CMAKE_INSTALL_PREFIX
)

set(SEMANTIC_VERSION 0.0.1)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/AtomSpaceVisionConfigVersion.cmake"
	VERSION ${SEMANTIC_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/AtomSpaceVisionConfigVersion.cmake
	${CMAKE_CURRENT_BINARY_DIR}/AtomSpaceVisionConfig.cmake
	DESTINATION ${ConfigPackageLocation}
)
