
# Build release version by default
IF(NOT CMAKE_BUILD_TYPE)
        SET(CMAKE_BUILD_TYPE RELEASE)
ENDIF()

IF(CMAKE_BUILD_TYPE STREQUAL Debug)
	ADD_DEFINITIONS(-DDEBUG)
        IF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_INTEL)
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")
        ENDIF()
ENDIF()

IF(CMAKE_BUILD_TYPE STREQUAL Release)
	ADD_DEFINITIONS(-DNDEBUG)
        IF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_INTEL)
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
        ENDIF()
ENDIF()

