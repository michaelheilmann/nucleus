# Copyright (c) 2018 Michael Heilmann

# Detect ISA (Instruction Set Architecture).
# Provides the following numeric constants:
# - NUCLEUS_ISA_ID_UNKNOWN
# - NUCLEUS_ISA_ID_X64
# - NUCLEUS_ISA_ID_X86
#
# Provides the following string constants:
# - NUCLEUS_ISA_STRING_UNKNOWN
# - NUCLEUS_ISA_STRING_X64
# - NUCLEUS_ISA_STRING_X86
#
# ISA detection defines ${target}_ISA_ID to NUCLEUS_ISA_ID_[X] and ${target}_ISA_STRING to NUCLEUS_ISA_STRING_[X].
# [X] is X64 or X86 if ISA detection succeeds and is UNKNOWN if ISA detection fails.
#

set(NUCLEUS_ISA_ID_UNKNOWN 0)
set(NUCLEUS_ISA_STRING_UNKNOWN "<unknown>")

set(NUCLEUS_ISA_ID_X86 1)
set(NUCLEUS_ISA_STRING_X86 "x86")

set(NUCLEUS_ISA_ID_X64 2)
set(NUCLEUS_ISA_STRING_X64 "x64")

macro(detect_isa parent_target_name target_name language)
  # Detect ISA (Instruction Set Architecture).
  set(${target_name}_ISA_ID ${NUCLEUS_ISA_ID_UNKNOWN})
  set(${target_name}_ISA_STRING ${NUCLEUS_ISA_STRING_UNKNOWN})
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(${target_name}_ISA_ID ${NUCLEUS_ISA_ID_X64})
	set(${target_name}_ISA_STRING ${NUCLEUS_ISA_STRING_X64})
  elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(${target_name}_ISA_ID ${NUCLEUS_ISA_ID_X86})
	set(${target_name}_ISA_STRING ${NUCLEUS_ISA_STRING_X86})
  endif()
  message("  - ${target_name} ISA (Instruction Set Architecture): ${${target_name}_ISA_STRING}")
endmacro(detect_isa)
