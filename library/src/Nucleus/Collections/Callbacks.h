// Copyright (c) 2018 Michael Heilmann
#pragma once




#include "Nucleus/Status.h"
#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/HashValue.h"
#include "Nucleus/Types/Size.h"




/// @brief Macro unconditionally casting a @a (Nucleus_LockFunction) or derived pointer into a @a (Nucleus_LockFunction) pointer.
/// @param pointer the pointer
#define NUCLEUS_LOCKFUNCTION(pointer) ((Nucleus_LockFunction *)(pointer))

/// @brief A "lock" callback.
/// @param object a pointer to an opaque object, the object to be locked
/// @remark The caller must ensure that @a is passed a proper value.
/// @return A "lock" callback always returns #Nucleus_Status_Success.
typedef Nucleus_Status Nucleus_LockFunction(void *object);




/// @brief Macro unconditionally casting a @a (Nucleus_UnlockFunction) or derived pointer into a @a (Nucleus_UnlockFunction) pointer.
/// @param pointer the pointer
#define NUCLEUS_UNLOCKFUNCTION(pointer) ((Nucleus_UnlockFunction *)(pointer))

/// @brief An "unlock" callback.
/// @param object a pointer to an opaque object, the object to be unlocked
/// @remark The caller must ensure that @a is passed a proper value.
/// @return An "unlock" function always returns #Nucleus_Status_Success.
typedef Nucleus_Status Nucleus_UnlockFunction(void *object);




/// @brief Macro unconditionally casting a @a (Nucleus_HashFunction) or derived pointer into a @a (Nucleus_HashFunction) pointer.
/// @param pointer the pointer
#define NUCLEUS_HASHFUNCTION(pointer) ((Nucleus_HashFunction *)(pointer))

/// @brief A "hash" callback.
/// @param a pointer to the object to be hashed.
/// @param [out] hashValue a pointer to a @a (Nucleus_HashValue) variable 
/// @return #Nucleus_Status_Success on success a non-zero status code on failure
typedef Nucleus_Status Nucleus_HashFunction(void *object, Nucleus_HashValue *hashValue);




/// @brief Macro unconditionally casting a @a (Nucleus_EqualToFunction) or derived pointer into a @a (Nucleus_EqualToFunction) pointer.
/// @param pointer the pointer
#define NUCLEUS_EQUALTOFUNCTION(pointer) ((Nucleus_EqualToFunction *)(pointer))

/// @brief An "equal to" callback.
/// @param left, right pointers to the objects to be compared
/// @param [out] equalTo a pointer to a @a (Nucleus_Boolean) variable
/// @return #Nucleus_Status_Success on success a non-zero status code on failure
typedef Nucleus_Status Nucleus_EqualToFunction(void *left, void *right, Nucleus_Boolean *equalTo);
