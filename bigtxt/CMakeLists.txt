CMAKE_MINIMUM_REQUIRED(VERSION 3.24)

# Watcom C/C++ Compiler link libraries policy
CMAKE_POLICY(SET CMP0136 NEW)

PROJECT(fmem)

ENABLE_LANGUAGE(C CXX)

# Make an ancient C Standard as default
SET(CMAKE_C_STANDARD 90)

# Set stricted flags for GCC and Clang 
IF(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
    IF (MINGW)
      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unknown-pragmas")
      ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)
    ENDIF()
# Set stricted flags for MSVC
ELSEIF(CMAKE_C_COMPILER_ID MATCHES "MSVC")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /WX /EHsc")
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE -DWIN32_LEAN_AND_MEAN)
# Set stricted flags for WATCOM 
ELSEIF(CMAKE_C_COMPILER_ID MATCHES "WATCOM|OpenWatcom")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -we -wx")
    ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)
    SET(CMAKE_WATCOM_RUNTIME_LIBRARY "SingleThreaded") # SingleThreaded, SingleThreadedDebug, MultiThreaded, MultiThreadedDebug
ELSE()
    MESSAGE(WARNING "Unknown compiler, using default flags")
ENDIF()



INCLUDE_DIRECTORIES(inc)
ADD_SUBDIRECTORY(src)
