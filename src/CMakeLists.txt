cmake_minimum_required(VERSION 2.6)
set(LIB_INSTALL_DIR /usr/local/lib)
set(PKG_INSTALL_DIR /usr/local/lib/pkgconfig)
set(INC_INSTALL_DIR /usr/local/include)

set (PROJECT_NAME dltwrapper)

project(${PROJECT_NAME})


SET( PKG_CONFIG_FILE_NAME ${PROJECT_NAME}.pc)

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/pkgconfig/template.pc.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/pkgconfig/${PKG_CONFIG_FILE_NAME}"
  )


set(LIB_DEPS 
    automotive-dlt #DLT Logger
)

foreach (lib ${LIB_DEPS})
find_package(PkgConfig)


SET(LIBS -lstdc++)

if(PKG_CONFIG_FOUND)
	
	pkg_check_modules(${lib} "${lib}")
	
	if(${lib}_FOUND)
		message ("Found package ${lib}")
		add_definitions(${${lib}_CFLAGS})
		set(LIBS "${LIBS} ${${lib}_LDFLAGS}")
		message("Add this following definition: ${${lib}_CFLAGS} ")
	else(${lib}_FOUND)
		message (FATAL_ERROR "Cannot Found package ${lib}")
	endif(${lib}_FOUND)
	
endif(PKG_CONFIG_FOUND)
endforeach(lib ${LIB_DEPS})


set(SRC_FILE 
    C_DLT_LOG.cpp
    DLTLogger.cpp
    )


SET(INC_FILE
    C_DLT_LOG.h
    DLTLogger.h
)

add_library(${PROJECT_NAME} SHARED
               ${SRC_FILE}
)
target_link_libraries (${PROJECT_NAME}
					   ${LIBS}
)
                       
message ("System: ${CMAKE_SYSTEM_NAME}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
set(DEF_LINUX "__LINUX__")	
add_definitions(-D${DEF_LINUX})
message ("Add following definition:${DEF_LINUX}") 
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")				


install (TARGETS ${PROJECT_NAME}
		DESTINATION ${LIB_INSTALL_DIR}) 

message ("PKG:${PKG_CONFIG_FILE_NAME}")
install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/pkgconfig/${PKG_CONFIG_FILE_NAME}
         DESTINATION ${PKG_INSTALL_DIR}
)
install (FILES ${INC_FILE}
         DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME}
)

add_definitions(-std=c++11)

add_executable(${PROJECT_NAME}_test
                test.cpp
)
target_link_libraries(${PROJECT_NAME}_test
                      ${LIBS}
                      ${PROJECT_NAME}
)
         
