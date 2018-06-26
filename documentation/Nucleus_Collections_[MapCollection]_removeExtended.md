# `Nucleus_Collections_[MapCollection]_append`
*Remove an entry from a `Nucleus_Collections_[MapCollection]` object.*

## C Signature
```
Nucleus_Status
Nucleus_Collections_[MapCollection]_steal
    (
        Nucleus_Collections_[MapCollection] *mapCollection,
        [KeyType] key,
		[ValueType] *value,
		Nucleus_Boolean keyUnlockCallback,
		Nucleus_Boolean valueUnlockCallback
    )
```

## Parameters
- `mapCollection` a pointer to an initialized `Nucleus_Collections_[MapCollection]` object
- `key` the key (value) of type [MapCollection.KeyType] or a const-qualified variant thereof
- `value` the value (value) of type [MapCollection.ValueType] *
- `keyUnlockCallback` see below
- `valueUnlockCallback` see below

## Description 
This function steals an entry from a `Nucleus_Collections_[MapCollection]` object.

If this function succeeds,
- the `value` was assigned the value (value) of the entry
- `Nucleus_Status_Success` was returned.
Furthermore,
- if `keyUnlockCallback` is `Nucleus_Boolean_True` and a key unlock function is specified for the
  `Nucleus_Collections_[MapCollection]` object, this key unlock callback was invoked on the key
- if `valueUnlockCallback` is `Nucleus_Boolean_True` and a value unlock function is specified for the
  `Nucleus_Collections_[MapCollection]` object, this value unlock callback was invoked on the value

If this function fails, one of the following non-zero status codes is returned
- `Nucleus_Status_InvalidArgument` `mapCollection` or `value` is a null pointer

## Requirements

|                      | Windows                                         | Linux                                           |
|----------------------|-------------------------------------------------|-------------------------------------------------|
| *Header*             | `Nucleus/Collections/[MapCollection].h`         | `Nucleus/Collections/[MapCollection].h`         |
| *Static library*     | `Nucleus.Library.lib`                           | `libNucleus.Library.a`                          |
