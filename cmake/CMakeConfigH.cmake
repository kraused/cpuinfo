
CONFIGURE_FILE     (${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
                    ${CMAKE_CURRENT_BINARY_DIR}/config.h)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR})

