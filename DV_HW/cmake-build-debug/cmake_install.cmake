# Install script for directory: C:/Users/George/Desktop/git_projects/C_plus_plus/DV_HW

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/DV_HW")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/George/Desktop/git_projects/C_plus_plus/DV_HW/cmake-build-debug/1_a_i/cmake_install.cmake")
  include("C:/Users/George/Desktop/git_projects/C_plus_plus/DV_HW/cmake-build-debug/1_a_ii/cmake_install.cmake")
  include("C:/Users/George/Desktop/git_projects/C_plus_plus/DV_HW/cmake-build-debug/1_a_iii/cmake_install.cmake")
  include("C:/Users/George/Desktop/git_projects/C_plus_plus/DV_HW/cmake-build-debug/1_b_i/cmake_install.cmake")
  include("C:/Users/George/Desktop/git_projects/C_plus_plus/DV_HW/cmake-build-debug/1_b_ii/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/George/Desktop/git_projects/C_plus_plus/DV_HW/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
