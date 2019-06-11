cmake_minimum_required(VERSION 3.10)
project(dilithium)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(NIST_FLAGS "-O3 -fomit-frame-pointer -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -D_GNU_SOURCE -DMODE=1 -Wall -Wextra -march=native -mtune=native -O3 -fomit-frame-pointer ${NIST_FLAGS}")

if(NOT ARM)
  set(NIST_FLAGS "${NIST_FLAGS} -march=native -mtune=native") 

find_package(OpenSSL REQUIRED)

set(dilithium_headers
        config.h api.h params.h sign.h polyvec.h poly.h packing.h ntt.h reduce.h rounding.h symmetric.h rng.h)

set(dilithium_sources
        sign.c polyvec.c poly.c packing.c ntt.c reduce.c rounding.c fips202.c aes256ctr.c rng.c)


add_library(dilithium
        ${dilithium_headers}
        ${dilithium_sources})

target_link_libraries(dilithium OpenSSL::Crypto)
