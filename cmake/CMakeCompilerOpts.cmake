
IF(C_IS_GNU OR C_IS_INTEL)
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unused")
ENDIF()

# Workaround Intel linking problem (Issue #576620)
IF(C_IS_INTEL)
	SET(CMAKE_EXE_LINKER_FLAGS    
		${CMAKE_EXE_LINKER_FLAGS}    -Wl,-no_compact_unwind)
	SET(CMAKE_SHARED_LINKER_FLAGS 
		${CMAKE_SHARED_LINKER_FLAGS} -Wl,-no_compact_unwind)
	SET(CMAKE_MODULE_LINKER_FLAGS 
		${CMAKE_MODULE_LINKER_FLAGS} -Wl,-no_compact_unwind)
ENDIF()

