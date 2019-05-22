cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
    endif()
endif()

project(VitaRebootShutdown)

include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "Reboot or Shutdown")
set(VITA_TITLEID  "RBSD00001")
set(VITA_VERSION  "01.08")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

link_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
	)

include_directories(
	source/resources
	source/include
	)

add_executable(${PROJECT_NAME}
	source/main.c
	source/touch.c
	)

target_link_libraries(${PROJECT_NAME}
	vita2d 
	SceDisplay_stub 
	SceGxm_stub
	SceTouch_stub 
	SceSysmodule_stub
	freetype 
	png 
	z
	m
	ScePower_stub
	SceIofilemgr_stub 
	SceCommonDialog_stub 
    )

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME} UNSAFE)

vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
    VERSION ${VITA_VERSION}
    NAME ${VITA_APP_NAME}
    FILE source/sce_sys/icon0.png sce_sys/icon0.png
    FILE source/sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
    FILE source/sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
    FILE source/sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
    FILE source/resources/reset.png resources/reset.png
    FILE source/resources/shutdown.png resources/shutdown.png
    FILE source/resources/refresh_database.png resources/refresh_database.png
    FILE source/resources/reset_database.png resources/reset_database.png
    )
