# `Nucleus_(Integer|Natural)(8|16|32|64)
The types `Nucleus_(Integer|Natural)(8|16|32|64)` are provided. The `Nucleus_Integer(8|16|32|64)` types approximate
integers and are aliases of the `int(8|16|32|64)_t` types (as provided by `stdint.h`), the `Nucleus_Natural(8|16|32|64)`
types approximate natural numbers and are aliases of the `uint(8|16|32|64)_t` types (as provided by `stdint.h`).
`Nucleus_(Integer|Natural)(8|16|32|64)_Least` represents the least value,
`Nucleus_(Integer|Natural)(8|16|32|64)_Greatest` represents the greatest value.
`Nucleus_(Natural)(8|16|32|64)_Least` is guaranteed to be `0`.

# `Nucleus_HashValue`
The type `Nucleus_HashValue` is provided. `Nucleus_HashValue` represents hash values and is an alias of
`uint32_fast_t`. Its least value is given by `Nucleus_Hash_Least`, its greatest value by
`Nucleus_Hash_Greatest`. In particular, `Nucleus_HashValue` can be implicitly converted
without loss of information into a `size_t` value on any system.

# `Nucleus_Boolean`
The type `Nucleus_Boolean` is an alias for `bool` (as provided by `stdbool.h`). Its only values
`Nucleus_Boolean_True` and `Nucleus_Boolean_False` are aliases of the constants `true` and `false`,
respectively.
