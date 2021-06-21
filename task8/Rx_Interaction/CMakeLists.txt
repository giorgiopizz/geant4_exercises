# ########################################################################################
# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(abs)

if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()
# ########################################################################################

# ---Build executable------------------------------------------------------------


add_executable(abs absorption.C)
add_executable(electrons electrons.C)
target_link_libraries(abs Garfield::Garfield ${ROOT_LIBRARIES})
target_link_libraries(electrons Garfield::Garfield ${ROOT_LIBRARIES})

# ---Copy all files locally to the build directory-------------------------------
foreach(_file)
  configure_file(${_file} ${CMAKE_CURRENT_BINARY_DIR}/${_file} COPYONLY)
endforeach()

configure_file(script.py ${CMAKE_CURRENT_BINARY_DIR}/script.py COPYONLY)

