project(Tools VERSION 1.0.0)
set(TGNAME ${PROJECT_NAME})
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SUBDIRS *.cmake)
foreach(sub ${SUBDIRS})
    include(${sub})
    foreach(H ${HEADERS})
        list(APPEND ALL_HEADERS ${INC_DIR}/${H}.hpp)
    endforeach()
endforeach()
add_library(${TGNAME} INTERFACE)
target_include_directories(${TGNAME} INTERFACE ${INC_DIR})
target_include_directories(${TGNAME} INTERFACE
    $<BUILD_INTERFACE: ${INC_DIR}>
    $<INSTALL_INTERFACE: ${TGNAME}>
)
install( DIRECTORY ${INC_DIR} DESTINATION include/${TGNAME})
