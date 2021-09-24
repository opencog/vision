# CMake boilerplate mumbo-jumbo that does something.

include(CMakePackageConfigHelpers)

set(ConfigPackageLocation lib/cmake/AtomSpaceVisOps)

install(EXPORT AtomSpaceVisOpsTargets
	FILE AtomSpaceVisOpsTargets.cmake
	DESTINATION ${ConfigPackageLocation}
)

configure_package_config_file(AtomSpaceVisOpsConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/AtomSpaceVisOpsConfig.cmake
	INSTALL_DESTINATION ${ConfigPackageLocation}
	PATH_VARS CMAKE_INSTALL_PREFIX
)

set(SEMANTIC_VERSION 0.0.1)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/AtomSpaceVisOpsConfigVersion.cmake"
	VERSION ${SEMANTIC_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/AtomSpaceVisOpsConfigVersion.cmake
	${CMAKE_CURRENT_BINARY_DIR}/AtomSpaceVisOpsConfig.cmake
	DESTINATION ${ConfigPackageLocation}
)
