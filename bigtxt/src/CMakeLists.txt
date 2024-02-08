# if windows then include certain files 
IF(WIN32)
  SET(FILE_UTILS_SRC file_utils_win.c)
#else if posix 
ELSE()
  SET(FILE_UTILS_SRC file_utils_posix.c)
ENDIF()

# add the library
ADD_LIBRARY(file_utils ${FILE_UTILS_SRC})

# new executable 
ADD_EXECUTABLE(fmemdemo main.c)
TARGET_LINK_LIBRARIES(fmemdemo file_utils)
