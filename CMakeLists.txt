cmake_minimum_required(VERSION 2.8)

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_C_COMPILER "arm-vita-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-vita-eabi-g++")

project(VitaRebootShutdown)
set(PROJECT_TITLE "Reboot or Shutdown")
set(TITLE_ID "RBSD00001")

set(CMAKE_C_FLAGS "-Wl,-q -O3 -std=c99")

include_directories(
  ./common # This is for debugScreenPrintf()
)

add_executable(${PROJECT_NAME}.elf
	src/main.c
)

target_link_libraries(${PROJECT_NAME}.elf
	ScePower_stub
	SceCtrl_stub
	SceSysmodule_stub
	SceDisplay_stub
)

add_custom_target(${PROJECT_NAME}.vpk ALL
	COMMAND vita-elf-create ${PROJECT_NAME}.elf ${PROJECT_NAME}.velf
	COMMAND vita-make-fself -s ${PROJECT_NAME}.velf eboot.bin
	COMMAND vita-mksfoex -s TITLE_ID=${TITLE_ID} "${PROJECT_TITLE}" param.sfo
	COMMAND vita-pack-vpk -s param.sfo -a src/sce_sys/icon0.png=sce_sys/icon0.png -a src/sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png -a src/sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png -a src/sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml -b eboot.bin ${PROJECT_NAME}.vpk
)

add_dependencies(${PROJECT_NAME}.vpk ${PROJECT_NAME}.elf)
