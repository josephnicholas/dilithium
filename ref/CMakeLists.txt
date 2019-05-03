cmake_minimum_required(VERSION 3.10)
project(dilithium)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER "/usr/bin/cc")
set(CMAKE_C_STANDARD_REQUIRED ON)
set(NIST_FLAGS "-march=native -mtune=native -O3 -fomit-frame-pointer -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -D_GNU_SOURCE -DMODE=3 -Wall -Wextra -march=native -mtune=native -O3 -fomit-frame-pointer ${NIST_FLAGS}")

if (APPLE AND NOT IOS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64 -fvisibility=default")
    if (NOT OpenSSL_DIR)
        EXECUTE_PROCESS(COMMAND brew --prefix openssl
                OUTPUT_VARIABLE OPENSSL_ROOT_DIR
                OUTPUT_STRIP_TRAILING_WHITESPACE)
        message(STATUS "Using OpenSSL found at ${OPENSSL_ROOT_DIR}")
    endif()
endif()

find_package(OpenSSL REQUIRED)
message(STATUS "Using OpenSSL include dir at ${OPENSSL_INCLUDE_DIR}")
include_directories(${OPENSSL_INCLUDE_DIR})
if(STATIC AND NOT IOS)
    if(UNIX)
        set(OPENSSL_LIBRARIES "${OPENSSL_LIBRARIES};${CMAKE_DL_LIBS};${CMAKE_THREAD_LIBS_INIT}")
    endif()
endif()

set(dilithium_headers
        config.h api.h params.h sign.h polyvec.h poly.h packing.h ntt.h reduce.h rounding.h symmetric.h rng.h)

set(dilithium_sources
        sign.c polyvec.c poly.c packing.c ntt.c reduce.c rounding.c fips202.c aes256ctr.c rng.c)


add_library(dilithium
        ${dilithium_headers}
        ${dilithium_sources})

target_link_libraries(dilithium
        PUBLIC
        epee
        ${OPENSSL_LIBRARIES}
        ${Boost_SYSTEM_LIBRARY}
        ${SODIUM_LIBRARY}
        PRIVATE
        ${EXTRA_LIBRARIES})
