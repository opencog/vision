opencog_add_atom_types(atom_types.script
   atom_types.h
   atom_types.definitions
   atom_types.inheritance
   vision_types.scm
   vision_types.pyx)
add_custom_target(vision_atom_types DEPENDS atom_types.h)

set(VISION_SOURCES
   ${SOURCES_DIR}/atoms/vision/atom-types/ImageNode.cpp
   ${SOURCES_DIR}/atoms/vision/atom-types/ImageValue.cpp
)

set(VISION_HEADERS
   ${SOURCES_DIR}/atoms/vision/atom-types/ImageNode.hpp
   ${SOURCES_DIR}/atoms/vision/atom-types/ImageValue.hpp
)

add_library(
   Vision
   SHARED
      atom_types_init.cc
      ${VISION_SOURCES}
      ${VISION_HEADERS}
)
add_library(AtomSpace::Vision ALIAS Vision)

target_include_directories(Vision
   PRIVATE
      ${CMAKE_BINARY_DIR}
   PUBLIC
      ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(Vision
   PUBLIC
      atomspace
      OpenCV
)

add_dependencies(Vision vision_atom_types)

install(
   TARGETS
      Vision
   EXPORT
      AtomSpaceVisionTargets
	LIBRARY DESTINATION "lib${LIB_DIR_SUFFIX}/opencog"
)
install(
   EXPORT
      AtomSpaceVisionTargets
   NAMESPACE
      AtomSpace::
   DESTINATION
      ${VISION_CMAKE_CONFIG_DESTINATION}
)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/atom_types.h
   ${CMAKE_CURRENT_BINARY_DIR}/atom_names.h
   DESTINATION "include/opencog/vision/types"
)

add_guile_extension(SCM_CONFIG Vision "opencog-ext-path-vision-types")

add_guile_module(FILES
	vision.scm
	${CMAKE_CURRENT_BINARY_DIR}/vision_types.scm
	MODULE_DESTINATION "${GUILE_SITE_DIR}/opencog/vision"
	DEPENDS vision_atom_types
)
