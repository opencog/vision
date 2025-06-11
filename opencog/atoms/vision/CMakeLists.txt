
OPENCOG_GEN_CXX_ATOMTYPES(atom_types.script
   atom_types.h
   atom_types.definitions
   atom_types.inheritance)

OPENCOG_GEN_SCM_ATOMTYPES(atom_types.script vision_types.scm)
OPENCOG_GEN_PYTHON_ATOMTYPES(atom_types.script vision_types.pyx)

ADD_CUSTOM_TARGET(vision_atom_types
	DEPENDS atom_types.h vision_types.scm vision_types.pyx)

# == Types ==
add_library(vision_types SHARED atom_types_init.cc)
add_dependencies(vision_types vision_atom_types)
target_include_directories(vision_types PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(vision_types PUBLIC ${ATOMSPACE_LIBRARIES})

# == Python types ==
IF (HAVE_CYTHON)
	SET(CYTHON_FLAGS "-3" "-f" "-Wextra")
	INCLUDE_DIRECTORIES(${Python3_INCLUDE_DIRS})
	CYTHON_ADD_MODULE_PYX(vision "vision.pyx" "vision_types.pyx")
	ADD_LIBRARY(vision_cython SHARED vision.cpp)
	ADD_DEPENDENCIES(vision_cython vision_types)

	# MUST set --no-as-needed, otherwise, the shared lib that
	# initializes the types will fail to load (and initialize
	# the types.)
	TARGET_LINK_LIBRARIES(vision_cython
		${NO_AS_NEEDED}
		vision
		vision_types
		${ATOMSPACE_LIBRARIES}
		${Python3_LIBRARIES}
	)

	SET_TARGET_PROPERTIES(vision_cython PROPERTIES
		PREFIX ""
		OUTPUT_NAME vision)

	INSTALL(TARGETS
		vision_cython
		DESTINATION "${PYTHON_DEST}")
ENDIF (HAVE_CYTHON)

# == The Library ==
set(VISION_SOURCES
   ${SOURCES_DIR}/atoms/vision/ImageNode.cpp
   ${SOURCES_DIR}/atoms/vision/ImageValue.cpp
   ${SOURCES_DIR}/atoms/vision/ImageBlurLink.cpp
   ${SOURCES_DIR}/atoms/vision/ImageWriteLink.cpp
   ${SOURCES_DIR}/atoms/vision/ImageFilter2DLink.cpp
   ${SOURCES_DIR}/atoms/vision/ImageHalfSizeLink.cpp
)

set(VISION_HEADERS
   ${SOURCES_DIR}/atoms/vision/ImageNode.hpp
   ${SOURCES_DIR}/atoms/vision/ImageValue.hpp
   ${SOURCES_DIR}/atoms/vision/ImageBlurLink.hpp
   ${SOURCES_DIR}/atoms/vision/ImageWriteLink.hpp
   ${SOURCES_DIR}/atoms/vision/ImageFilter2DLink.hpp
   ${SOURCES_DIR}/atoms/vision/ImageHalfSizeLink.hpp
)

add_library(
   vision
   SHARED
	${VISION_SOURCES}
	${VISION_HEADERS}
)
add_library(AtomSpace::Vision ALIAS vision)

target_include_directories(vision
   PRIVATE
		${CMAKE_BINARY_DIR}
)
target_link_libraries(vision
	PRIVATE
		vision_types
	PUBLIC
		${ATOMSPACE_LIBRARIES}
		${OpenCV_LIBS}
)

# == Installation ==
install(
	TARGETS
		vision_types
		vision
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

add_guile_extension(SCM_CONFIG vision "opencog-ext-path-vision-types")

add_guile_module(FILES
	vision.scm
	${CMAKE_CURRENT_BINARY_DIR}/vision_types.scm
	MODULE_DESTINATION "${GUILE_SITE_DIR}/opencog/vision"
	DEPENDS vision_atom_types
)
