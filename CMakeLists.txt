
PROJECT(CPUINFO)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

LIST(APPEND
     CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

INCLUDE(CMakeOS)
INCLUDE(CMakeArch)
INCLUDE(CMakeBuildType)
INCLUDE(CMakeCompilerSuite)
INCLUDE(CMakeCompilerOpts)
INCLUDE(CMakeEnableC99)
INCLUDE(CMakeConfigH)

IF(ON_X86_64)
	ADD_EXECUTABLE(cpuinfo cpuinfo.c memory.c report.c arch/x86-64/cpuinfo.c arch/x86-64/cache.c)
ENDIF()
IF(ON_PPC_64)
	ADD_EXECUTABLE(cpuinfo cpuinfo.c memory.c report.c arch/ppc-64/cpuinfo.c)
ENDIF()

# Installation
SET(LIB_INSTALL_DIR            ${CMAKE_INSTALL_PREFIX}/lib)
SET(INCLUDE_INSTALL_DIR        ${CMAKE_INSTALL_PREFIX}/include)
SET(BIN_INSTALL_DIR            ${CMAKE_INSTALL_PREFIX}/bin)

INSTALL(TARGETS        cpuinfo
        DESTINATION    bin)

