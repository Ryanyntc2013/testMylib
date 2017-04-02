project(myRtsp)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
aux_source_directory(procon PRO_CON)
aux_source_directory(common COMMON)
aux_source_directory(rtspLib RTSPLIB)

INCLUDE_DIRECTORIES(procon)
INCLUDE_DIRECTORIES(rtspLib)
INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(common)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${PRO_CON} ${COMMON} ${RTSPLIB})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} pthread)
