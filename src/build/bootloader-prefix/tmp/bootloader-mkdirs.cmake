# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/balmine/esp/esp-idf/components/bootloader/subproject"
  "/home/balmine/git/mi-net4104/build/bootloader"
  "/home/balmine/git/mi-net4104/build/bootloader-prefix"
  "/home/balmine/git/mi-net4104/build/bootloader-prefix/tmp"
  "/home/balmine/git/mi-net4104/build/bootloader-prefix/src/bootloader-stamp"
  "/home/balmine/git/mi-net4104/build/bootloader-prefix/src"
  "/home/balmine/git/mi-net4104/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/balmine/git/mi-net4104/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/balmine/git/mi-net4104/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
