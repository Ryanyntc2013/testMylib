project(myRtsp)

cmake_minimum_required(VERSION 2.8)

SET(CMAKE_C_COMPILER   arm-hisiv500-linux-gcc)
SET(CMAKE_CXX_COMPILER arm-hisiv500-linux-g++)

aux_source_directory(. SRC_LIST)
aux_source_directory(procon PRO_CON)
aux_source_directory(common COMMON)
aux_source_directory(rtspLib RTSPLIB)

aux_source_directory(param PARAM)
aux_source_directory(encode ENCODE)

add_definitions("-DSENSOR_TYPE=HFGT500_LVDS_1080P_30FPS")

INCLUDE_DIRECTORIES(param)
INCLUDE_DIRECTORIES(encode)

INCLUDE_DIRECTORIES(procon)
INCLUDE_DIRECTORIES(rtspLib)
INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(common)


INCLUDE_DIRECTORIES(../../include/)
INCLUDE_DIRECTORIES(../common/)
add_executable(${PROJECT_NAME} ${SRC_LIST} ${PRO_CON} ${COMMON} ${RTSPLIB} ${PARAM} ${ENCODE})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} pthread)

