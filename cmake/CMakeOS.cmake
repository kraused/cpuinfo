
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	SET(ON_LINUX  1)
ENDIF()
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET(ON_MACOSX 1)
ENDIF()
IF(${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
	SET(ON_SOLARIS 1)
ENDIF()
IF(${CMAKE_SYSTEM_NAME} MATCHES "Win")
	# TODO How to check for 64 bit?
	SET(ON_WIN64 1)
ENDIF()

