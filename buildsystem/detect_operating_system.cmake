# PROBLEMS: 
# - "MINGW" and/or "MSYS" is a "toolchain". The "operating system" is still "windows".
# - We are not aware of a reliable procedure to detect what Apple "operating system" is used.
#   This configuration script detects "Mac OS" even if the "operating system" is "iOS",
#   "iOS Simulator", "watchOS", ... from within CMake?

set(NUCLEUS_OPERATING_SYSTEM_ID_UNKNOWN 0)
set(NUCLEUS_OPERATING_SYSTEM_STRING_UNKNOWN "<unknown operating system>")

set(NUCLEUS_OPERATING_SYSTEM_ID_WINDOWS 1)
set(NUCLEUS_OPERATING_SYSTEM_STRING_WINDOWS "WINDOWS")

set(NUCLEUS_OPERATING_SYSTEM_ID_UNIX 2)
set(NUCLEUS_OPERATING_SYSTEM_STRING_UNIX "UNIX")

set(NUCLEUS_OPERATING_SYSTEM_ID_LINUX 3)
set(NUCLEUS_OPERATING_SYSTEM_STRING_LINUX "LINUX")

set(NUCLEUS_OPERATING_SYSTEM_ID_MACOS 4)
set(NUCLEUS_OPERATING_SYSTEM_STRING_MACOS "MACOS")

set(NUCLEUS_OPERATING_SYSTEM_ID_CYGWIN 5)
set(NUCLEUS_OPERATING_SYSTEM_STRING_CYGWIN "CYGWIN")

set(NUCLEUS_OPERATING_SYSTEM_ID_MSYS 6)
set(NUCLEUS_OPERATING_SYSTEM_STRING_MSYS "MSYS")

set(NUCLEUS_OPERATING_SYSTEM_ID_MINGW 7)
set(NUCLEUS_OPERATING_SYSTEM_STRING_MINGW "MINGW")

set(NUCLEUS_OPERATING_SYSTEM_ID_IOS 8)
set(NUCLEUS_OPERATING_SYSTEM_STRING_IOS "IOS")

set(NUCLEUS_OPERATING_SYSTEM_ID_IOSSIMULATOR 9)
set(NUCLEUS_OPERATING_SYSTEM_STRING_IOSSIMULATOR "IOS SIMULATOR")


# Detect the operating system for the specified target by defining
macro(detect_operating_system target_name)
  if (NOT DEFINED ${target_name}_OPERATING_SYSTEM_ID)  
      set(${target_name}_OPERATING_SYSTEM_ID ${NUCLEUS_OPERATING_SYSTEM_ID_UNKNOWN})
      set(${target_name}_OPERATING_SYSTEM_STRING ${NUCLEUS_OPERATING_SYSTEM_STRING_UNKNOWN})
      if (WIN32)
        set(${target_name}_OPERATING_SYSTEM_ID ${NUCLEUS_OPERATING_SYSTEM_ID_WINDOWS})
        set(${target_name}_OPERATING_SYSTEM_STRING ${NUCLEUS_OPERATING_SYSTEM_STRING_WINDOWS})
      elseif (CYGWIN)
        set(${target_name}_OPERATING_SYSTEM_ID ${NUCLEUS_OPERATING_SYSTEM_ID_CYGWIN})
        set(${target_name}_OPERATING_SYSTEM_STRING ${NUCLEUS_OPERATING_SYSTEM_STRING_CYGWIN})  
      elseif (MSYS)
        set(${target_name}_OPERATING_SYSTEM_ID ${NUCLEUS_OPERATING_SYSTEM_ID_MSYS})
        set(${target_name}_OPERATING_SYSTEM_STRING ${NUCLEUS_OPERATING_SYSTEM_STRING_MSYS})
      endif()

      if (${${target_name}_OPERATING_SYSTEM_ID} EQUAL ${NUCLEUS_OPERATING_SYSTEM_ID_UNKNOWN})
        if("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
          set(${target_name}_OPERATING_SYSTEM_ID ${NUCLEUS_OPERATING_SYSTEM_ID_LINUX})
          set(${target_name}_OPERATING_SYSTEM_STRING ${NUCLEUS_OPERATING_SYSTEM_STRING_LINUX})
        elseif ("${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
          set(${target_name}_OPERATING_SYSTEM_ID ${NUCLEUS_OPERATING_SYSTEM_ID_MACOS})
          set(${target_name}_OPERATING_SYSTEM_STRING ${NUCLEUS_OPERATING_SYSTEM_STRING_MACOS})
        endif()
      endif()
  endif()
  message("  - ${target_name} operating system: ${${target_name}_OPERATING_SYSTEM_STRING}")
endmacro()
