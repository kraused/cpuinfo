
IF(C_IS_GNU)
 	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
ENDIF()

IF(C_IS_INTEL)
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -restrict")
ENDIF()

