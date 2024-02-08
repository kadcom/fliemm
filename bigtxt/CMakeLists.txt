CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(fmem LANGUAGES C)

# Make an ancient C Standard as default
SET(CMAKE_C_STANDARD 90)

# Set stricted flags for GCC and Clang 
IF(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
# Set stricted flags for MSVC
ELSEIF(CMAKE_C_COMPILER_ID MATCHES "MSVC")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /WX /EHsc")
# Set stricted flags for WATCOM 
ELSEIF(CMAKE_C_COMPILER_ID MATCHES "WATCOM")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -we -wx")
ELSE()
    MESSAGE(WARNING "Unknown compiler, using default flags")
ENDIF()

INCLUDE_DIRECTORIES(inc)
ADD_SUBDIRECTORY(src)