cmake_minimum_required(VERSION 2.6)

project(rope)

add_subdirectory(capstone)

function(create_directory_groups)
    source_group("Other Files" REGULAR_EXPRESSION ".")

    foreach(file_name ${ARGV})
        get_filename_component(dir_name "${file_name}" PATH)
        string(REPLACE "/" "\\" group_name "${dir_name}")
        source_group("${group_name}" FILES "${file_name}")
    endforeach()
endfunction()


add_definitions(-std=c++11)

set(SRCS
  main.cpp
  elf_object.cpp
)

set(HEADERS
  elf_object.h
)

create_directory_groups(${SRCS} ${HEADERS})

add_executable(rope ${SRCS} ${HEADERS})

target_link_libraries(rope capstone-shared)
