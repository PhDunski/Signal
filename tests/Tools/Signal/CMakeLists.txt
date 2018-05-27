enable_testing()
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRCS Main
         Connection
         Blocking
         MultipleSlots
         Scope
         Disconnection)
		 
foreach(H ${HEADERS})
	LIST(APPEND ALL_HEADERS ${INC_DIR}/${H}.hpp)
endforeach()
foreach(S ${SRCS})
    add_executable(${S} ${SRC_DIR}/${S}.cpp ${ALL_HEADERS})
    target_include_directories(${S} PUBLIC ${INC_DIR})
    target_link_libraries(${S} Catch Tools) 
    add_test(NAME ${S} COMMAND ${S})
endforeach()

