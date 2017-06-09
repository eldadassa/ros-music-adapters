# - Try to find MUSIC
# Once done this will define
#  MUSIC_FOUND - System has MUSIC
#  MUSIC_INCLUDE_DIRS - The MUSIC include directories
#  MUSIC_LIBRARIES - The libraries needed to use MUSIC

find_package(PkgConfig)

find_path(MUSICADAPTER_INCLUDE_DIR NAMES Port.h InPort.h OutPort.h Adapter.h HINTS ${MUSICADAPTERS_ROOT_DIR}/include)

find_library(MUSICADAPTER_LIBRARY NAMES libmusicadapter.so HINTS ${MUSICADAPTER_ROOT_DIR}/lib)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set MUSIC_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(MUSICADAPTER DEFAULT_MSG
    MUSICADAPTER_LIBRARY MUSICADAPTER_INCLUDE_DIR)

mark_as_advanced(MUSICADAPTER_INCLUDE_DIR MUSICADAPTER_LIBRARY )

set(MUSICADAPTER_LIBRARIES ${MUSICADAPTER_LIBRARY} )
set(MUSICADAPTER_INCLUDE_DIRS ${MUSICADAPTER_INCLUDE_DIR} )
