# Copyright (c) 2018 Michael Heilmann
#
# Set "${target}_IS_MULTI_TARGET_GENERATOR" to "YES" (a multi-target generator is used) or "NO" (a single-target generator is used).

macro(detect_multi_target_generator parent_target_name target_name language)
  if (${${target_name}_C_COMPILER_ID}   EQUAL ${NUCLEUS_C_COMPILER_ID_MSVC} OR
      ${${target_name}_CPP_COMPILER_ID} EQUAL ${NUCLEUS_CPP_COMPILER_ID_MSVC})
    set(${target_name}_IS_MULTI_TARGET_GENERATOR YES)
  else()
    set(${target_name}_IS_MULTI_TARGET_GENERATOR NO)
  endif()
  message("  - ${target_name} multi-target generator: ${${target_name}_IS_MULTI_TARGET_GENERATOR}")
endmacro(detect_multi_target_generator)
