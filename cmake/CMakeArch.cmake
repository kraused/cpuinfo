
IF(${CMAKE_SYSTEM_PROCESSOR} MATCHES "ppc64")
	SET(ON_PPC_64 1)
ENDIF()

# I'm typically not running my stuff on 32 bit
# machines. MacOsX strangly reports i386 as 
# processor type so I add the i386 here
IF(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64" OR
   ${CMAKE_SYSTEM_PROCESSOR} MATCHES "i386")
	SET(ON_X86_64 1)
ENDIF()

