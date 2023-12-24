cmake_minimum_required (VERSION 3.18.6)
project(bdc)

################################
# general config
################################

message("-- use c compiler ${CMAKE_C_COMPILER}")
message("-- use c++ compiler ${CMAKE_CXX_COMPILER}")

# set compile parameter
if (${CMAKE_C_COMPILER_ID} STREQUAL GNU)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif (${CMAKE_C_COMPILER_ID} MATCHES Clang)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_UNICODE -DUNICODE)
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

# set standard and print features
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

message("-- c compiler support features: ")
foreach(feature ${CMAKE_C_COMPILE_FEATURES})
	message("support feature: ${feature}")
endforeach()

# for LSP
if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# set output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set use folder in vs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################
# options
################################

option(BUILD_SHARED_LIBS "Build shared" ON)
option(BUILD_TESTING "Build unittest" OFF)
option(BDC_INSTALL_DEPS "bdc install deps" ON)

if (BUILD_SHARED_LIBS)
	set(BDC_LIB_TYPE SHARED)
	set(BDC_USE_DLL ON)
else()
	set(BDC_LIB_TYPE STATIC)
	set(BDC_USE_DLL OFF)
endif()

################################
# deps
################################

include(GNUInstallDirs)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/deps.cmake)

################################
# version
################################

# NTOE: don't use READ, it will add newline
#file(READ "version.txt" bdc_version)
file(STRINGS "version.txt" bdc_version)

string(REPLACE "-" ";" bdc_semver_ext ${bdc_version})
list(GET bdc_semver_ext 0 bdc_semver)
string(REPLACE "." ";" bdc_semver_list ${bdc_semver})

list(GET bdc_semver_list 0 BDC_VERSION_MAJOR)
list(GET bdc_semver_list 1 BDC_VERSION_MINOR)
list(GET bdc_semver_list 2 BDC_VERSION_PATCH)

set(BDC_VERSION "${bdc_version}")
set(BDC_SOVERSION "${BDC_VERSION_MAJOR}")

################################
# project
################################

message("--------------------------------")
message("# bdc version ${BDC_VERSION}")
message("# c compiler flags: ${CMAKE_C_FLAGS}")
message("# cxx compiler flags: ${CMAKE_CXX_FLAGS}")
message("# CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message("# BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")
message("# BUILD_TESTING: ${BUILD_TESTING}")
message("# BDC_INSTALL_DEPS: ${BDC_INSTALL_DEPS}")

# configure
set(bdc_src_dir ${CMAKE_CURRENT_LIST_DIR})
set(bdc_gen_dir ${CMAKE_CURRENT_BINARY_DIR}/gen)
configure_file(
	"${bdc_src_dir}/bdc/config.h.in"
	"${bdc_gen_dir}/bdc/config.h")
FILE(GLOB_RECURSE bdc_gen_h "${bdc_gen_dir}/bdc/*.h")

# core
set(bdc_core bdccore)
FILE(GLOB_RECURSE bdc_core_src "${bdc_src_dir}/bdc/core/*.c")
FILE(GLOB_RECURSE bdc_core_h "${bdc_src_dir}/bdc/core/*.h")
add_library(${bdc_core} ${BDC_LIB_TYPE}
	${bdc_core_src}
	${bdc_core_h}
	${bdc_gen_h})
target_include_directories(${bdc_core} PUBLIC
	$<BUILD_INTERFACE:${bdc_src_dir}>
	$<BUILD_INTERFACE:${bdc_gen_dir}>
	$<INSTALL_INTERFACE:include>)
target_link_libraries(${bdc_core} PUBLIC
	mugglec
	OpenSSL::Crypto
	OpenSSL::SSL
	LibXml2::LibXml2)
target_compile_definitions(${bdc_core}
	PRIVATE BDC_EXPORTS MUGGLE_HOLD_LOG_MACRO)
set_target_properties(${bdc_core} PROPERTIES
	DEBUG_POSTFIX d
	VERSION ${BDC_VERSION}
	SOVERSION ${BDC_VERSION_MAJOR})
if (APPLE)
	set_target_properties(${bdc_core}
		PROPERTIES
		INSTALL_RPATH "@executable_path/../lib"
		)
else ()
	set_target_properties(${bdc_core}
		PROPERTIES
		INSTALL_RPATH "\$ORIGIN/../lib"
		)
endif()

# cli
set(bdc_cli bdc)
FILE(GLOB_RECURSE bdc_cli_src "${bdc_src_dir}/bdc/cli/*.c")
FILE(GLOB_RECURSE bdc_cli_h "${bdc_src_dir}/bdc/cli/*.h")
add_executable(${bdc_cli}
	${bdc_cli_src}
	${bdc_cli_h})
target_link_libraries(${bdc_cli} PUBLIC ${bdc_core})
target_compile_definitions(${bdc_cli}
	PRIVATE MUGGLE_HOLD_LOG_MACRO)
set_target_properties(${bdc_cli} PROPERTIES
	DEBUG_POSTFIX d
	VERSION ${BDC_VERSION}
	SOVERSION ${BDC_VERSION_MAJOR})
if (APPLE)
	set_target_properties(${bdc_cli}
		PROPERTIES
		INSTALL_RPATH "@executable_path/../lib"
		)
else ()
	set_target_properties(${bdc_cli}
		PROPERTIES
		INSTALL_RPATH "\$ORIGIN/../lib"
		)
endif()

# install
install(TARGETS ${bdc_core} ${bdc_cli}
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
