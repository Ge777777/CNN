#cmake_mininum_required(VERSION 3.18)

project(CNN)

aux_source_directory(./src DIR_SRCS)

include_directories(./include)

add_executable(CNN ${DIR_SRCS})