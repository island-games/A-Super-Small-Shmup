## This file is a quick tutorial on writing CMakeLists for targeting the Vita
cmake_minimum_required(VERSION 2.8.12)

## This includes the Vita toolchain, must go before project definition
# It is a convenience so you do not have to type 
# -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake for cmake. It is 
# highly recommended that you include this block for all projects.
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

## Define project parameters here
# Name of the project
project(PinaColada)
# This line adds Vita helper macros, must go after project definition in order 
# to build Vita specific artifacts (self/vpk).
include("${VITASDK}/share/vita.cmake" REQUIRED)

## Configuration options for this app
# Display name (under bubble in LiveArea)
set(VITA_APP_NAME "A Super Small SHMUP")
# Unique ID must be exactly 9 characters. Recommended: XXXXYYYYY where X = 
# unique string of developer and Y = a unique number for this app
set(VITA_TITLEID  "ISLD00000")
# Optional version string to show in LiveArea's more info screen
set(VITA_VERSION  "01.01")

## Flags and includes for building
# Note that we make sure not to overwrite previous flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g ")
# Optional. You can specify more param.sfo flags this way.
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

# Add any additional include paths here
include_directories(
)

# Add any additional library paths here
# ${CMAKE_CURRENT_BINARY_DIR} lets you use any library currently being built
link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  
)

## Build and link
# Add all the files needed to compile here
add_executable(ASUPERSMALLSHMUP
   src/main.cpp
   src/controllers.cpp
   src/splashScreen.cpp
   src/mainMenu.cpp
   src/player.cpp
   src/enemy.cpp
   src/playerBullets.cpp
   src/enemyBullets.cpp
   src/pause.cpp
   src/boss.cpp
   src/gameManager.cpp
   src/Vector2.cpp
   src/objectHolder.cpp
   src/stars.cpp
   src/explosion.cpp
   src/powerUp.cpp
   src/ufo.cpp
   
   
   
   src/controllers.h
   src/splashScreen.h
   src/mainMenu.h
   src/player.h
   src/enemy.h
   src/playerBullets.h
   src/enemyBullets.h
   src/pause.h
   src/boss.h
   src/gameManager.h
   src/Vector2.h
   src/objectHolder.h
   src/stars.h
   src/explosion.h
   src/powerUp.h
   src/ufo.h
   
   
   


)

# Library to link to (drop the -l prefix). This will mostly be stubs.
target_link_libraries(ASUPERSMALLSHMUP
   bartender
  vita2d
  zip
  SceAppMgr_stub
  SceLibKernel_stub 
  SceDisplay_stub
  SceCtrl_stub
  SceAudio_stub
  SceSysmodule_stub
  SceHid_stub
  SceTouch_stub
  SceGxm_stub
  SceCommonDialog_stub
  m
  ScePower_stub
  SceModulemgrForKernel_stub
  SceModulemgrForDriver_stub
  freetype 
  png 
  jpeg 
  z 
  c 
  SceCtrl_stub 
  ScePgf_stub 
  ScePvf_stub 
  soloud
  unrar
  bz2
  lzma
  crypto
  ssl
  pthread


  
  
  
  
  # this line is only for demonstration. It's not needed as 
                    # the most common stubs are automatically included.
)

## Create Vita files
vita_create_self(ASUPERSMALLSHMUP.self ASUPERSMALLSHMUP)
# The FILE directive lets you add additional files to the VPK, the syntax is 
# FILE src_path dst_path_in_vpk. In this case, we add the LiveArea paths.
vita_create_vpk(ASUPERSMALLSHMUP.vpk ${VITA_TITLEID} ASUPERSMALLSHMUP.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
   FILE sce_sys/icon0.png sce_sys/icon0.png
   FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
   FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
   FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
   FILE img/splashScreen.png img/splashScreen.png
   FILE img/sprites.png img/sprites.png
   FILE img/boss.png img/boss.png
   FILE img/bullet.png img/bullet.png
   FILE img/playerExplosion.png img/playerExplosion.png
   FILE img/enemyExplosion.png img/enemyExplosion.png
   FILE img/ufo.png img/ufo.png
   FILE img/ka1.ttf img/ka1.ttf
   FILE img/ARCADE_N.ttf img/ARCADE_N.ttf
   FILE snd/enemyImpact.wav snd/enemyImpact.wav 
   FILE snd/enemyLaser.wav snd/enemyLaser.wav 
   FILE snd/playerDeath.wav snd/playerDeath.wav 
   FILE snd/playerLaser.wav snd/playerLaser.wav 
   FILE snd/powerUp.wav snd/powerUp.wav 
   FILE snd/bonus.wav snd/bonus.wav 
   FILE snd/music.wav snd/music.wav 
   FILE ISLD00000.dat ISLD00000.dat


)
