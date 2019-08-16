################################################################################
# Check packages
################################################################################

include(FindPkgConfig)

#pkg_check_modules (DRM REQUIRED libdrm)

################################################################################
# Includes
################################################################################

include_directories(
	.
#	include_directories(${DRM_INCLUDE_DIRS})
)

################################################################################
# Sources
################################################################################

#if(WITH_DRM OR WITH_WAYLAND)
#	add_subdirectory(displayBackend)
#endif()

#if(WITH_INPUT)
#	add_subdirectory(inputBackend)
#endif()

set(SOURCES
	main.cpp
        DummyBackend.cpp
)

if(WITH_MOCKBELIB)
	list(APPEND SOURCES
		MockBackend.cpp
	)
endif()

################################################################################
# Targets
################################################################################

add_executable(${PROJECT_NAME} ${SOURCES})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

################################################################################
# Libraries
################################################################################

#add_dependencies(input display)
#target_link_libraries(${PROJECT_NAME} display)


set(XENBE_LIB xenbe)

if(WITH_MOCKBELIB)
	set(XENBE_LIB xenbemock)
endif()

target_link_libraries(${PROJECT_NAME}
	${XENBE_LIB}
	pthread
)
