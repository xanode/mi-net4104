# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/balmine/esp/esp-idf/components/bootloader/subproject"
  "/home/balmine/esp/hello_world/build/bootloader"
  "/home/balmine/esp/hello_world/build/bootloader-prefix"
  "/home/balmine/esp/hello_world/build/bootloader-prefix/tmp"
  "/home/balmine/esp/hello_world/build/bootloader-prefix/src/bootloader-stamp"
  "/home/balmine/esp/hello_world/build/bootloader-prefix/src"
  "/home/balmine/esp/hello_world/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/balmine/esp/hello_world/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/balmine/esp/hello_world/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
