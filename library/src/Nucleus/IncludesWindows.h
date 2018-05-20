/// @file Nucleus/IncludesWindows.h
/// @brief Header including Windows-specific header files.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#if defined(_WIN32)

#pragma once

// Each of these symbol constants defined before the inclusion of <code>windows.h</code> disables irrelevant portions of <code>windows.h</code>.
#define NOGDICAPMASKS
#define NOVIRTUALKEYCODES
#define NOWINMESSAGES
#define NOWINSTYLES
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOKEYSTATES
#define NOSYSCOMMANDS
#define NORASTEROPS
#define NOSHOWWINDOW
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOGDI
#define NOKERNEL
#define NOUSER
// Neither NONLS mor NONMB must be defined if WideCharToMultiByte is required.
//#define NONLS
//#define NOMB
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOMSG
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOWINOFFSETS
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#endif
