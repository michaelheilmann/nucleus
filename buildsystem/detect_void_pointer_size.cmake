# Copyright (c) 2018 Michael Heilmann
#
# Detect void pointer size.
# Void pointer size detection defines the numeric variable to ${target}_SIZEOF_VOID_POINTER.

macro(detect_void_pointer_size parent_target_name target_name language)
  set(${target_name}_SIZEOF_VOID_POINTER ${CMAKE_SIZEOF_VOID_P})
  message("  - ${target_name} void pointer size: ${${target_name}_SIZEOF_VOID_POINTER}")
endmacro(detect_void_pointer_size)
