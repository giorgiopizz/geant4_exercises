# ########################################################################################
# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(gem)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()
# ########################################################################################

# ---Build executable------------------------------------------------------------
add_executable(gem RX_Interaction_GEM.C)
target_link_libraries(gem Garfield::Garfield ${ROOT_LIBRARIES})

# ---Copy all files locally to the build directory-------------------------------
foreach(_file)
  configure_file(${_file} ${CMAKE_CURRENT_BINARY_DIR}/${_file} COPYONLY)
endforeach()
