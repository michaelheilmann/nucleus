#pragma once

#include "Nucleus/Status.h"
#include <stdbool.h> // For bool, true, false.




/// @brief Macro unconditionally casting a @a (Nucleus_LockFunction) or derived pointer into a @a (Nucleus_LockFunction) pointer.
/// @param pointer the pointer
#define NUCLEUS_LOCKFUNCTION(pointer) ((Nucleus_LockFunction *)(pointer))

/// @brief A "lock" callback.
/// @param object a pointer to an opaque object, the object to be locked
/// @remark The caller must ensure that @a is passed a proper value.
typedef void Nucleus_LockFunction(void *object);




/// @brief Macro unconditionally casting a @a (Nucleus_UnlockFunction) or derived pointer into a @a (Nucleus_UnlockFunction) pointer.
/// @param pointer the pointer
#define NUCLEUS_UNLOCKFUNCTION(pointer) ((Nucleus_UnlockFunction *)(pointer))

/// @brief An "unlock" callback.
/// @param object a pointer to an opaque object, the object to be unlocked
/// @remark The caller must ensure that @a is passed a proper value.
typedef void Nucleus_UnlockFunction(void *object);




/// @brief Macro unconditionally casting a @a (Nucleus_HashFunction) or derived pointer into a @a (Nucleus_HashFunction) pointer.
/// @param pointer the pointer
#define NUCLEUS_HASHFUNCTION(pointer) ((Nucleus_HashFunction *)(pointer))

/// @brief A "hash" callback.
/// @param a pointer to the object to be hashed.
typedef Nucleus_Status Nucleus_HashFunction(void *, unsigned int *);




/// @brief Macro unconditionally casting a @a (Nucleus_EqualToFunction) or derived pointer into a @a (Nucleus_EqualToFunction) pointer.
/// @param pointer the pointer
#define NUCLEUS_EQUALTOFUNCTION(pointer) ((Nucleus_EqualToFunction *)(pointer))

/// @brief An "equalTo" callback.
/// @param left, right pointers to the objects to be compared
/// @param [out] equal a pointer to a @a bool variable
typedef Nucleus_Status Nucleus_EqualToFunction(void *, void *, bool *);
