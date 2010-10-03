
option(ENABLE_TAU "Enable profiling" OFF)

if(${ENABLE_TAU})
	include(CMakeForceCompiler)

	cmake_force_c_compiler  (tau_cc.sh  "Tau C Compiler wrapper")
	cmake_force_cxx_compiler(tau_cxx.sh "Tai C++ Compiler wrapper")
endif()
