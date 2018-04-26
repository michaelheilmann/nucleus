# Nucleus Unicode Module
The Nucleus Unicode Module provides functionality related to Unicode code points.

An Unicode codepoint is represented by a `Nucleus_Natural32` value.
```
typedef Nucleus_Natural32 Nucleus_Unicode_CodePoint;
```

The least Unicode codepoint value (incl.) representing a valid Unicode character.
```
#define Nucleus_Unicode_CodePoint_Least (0x0)
```

The greatest Unicode codepoint value (incl.) representing a valid Unicode character.
```
#define Nucleus_Unicode_CodePoint_Greatest (0x10FFFF)
```

Note that not every Unicode codepoint value within the bounds defined by
`Nucleus_Unicode_CodePoint_Least` (incl.)
and
`Nucleus_Unicode_CodePoint_Greatest` (incl.)
represents a valid Unicode character.

# Unicode Planes
Unicode divides its codespaces into 17 planes which divide the Unicode codespace into mutually disjoint, non-empty
intervals. The planes have zero-based indices 0 to 16.

- Plane 0 is called the Basic Multilingual Plane,
- Plane 1 is called the Supplementary Multilingual Plane,
- Plane 2 is called the Supplementary Idiographic Plane,
- Plane 14 is called the Supplementary Special-Purpose Plane, and
- Plane 15 and Plane 16 are called the Supplementary Private-Use Area Planes.

An Unicode plane index is represented by a `Nucleus_Natural8` value.
```
typedef Nucleus_Natural8 Nucleus_Unicode_PlaneIndex;
```
Symbolic constants are defined for plane indices, and the ranges of their contained Unicode codepoints
```
Nucleus_Unicode_Plane*index* /* hidden */
```
where `*index*` is within the bounds of *0* (incl.) and *16* (incl.).
The symbolic constants
`Nucleus_Unicode_Plane*index_Least`
and
`Nucleus_Unicode_Plane*index*_Greatest`
are `Nucleus_Unicode_Codepoint` values
denoting the least and the greatest codepoint of a plane.

The function allows for determinating the Unicode plane a code point resides in.
```
Nucleus_Status 
Nucleus_Unicode_getPlane
    (
        Nucleus_Unicode_CodePoint cp,
        Nucleus_Unicode_Plane *p
    )
```
`*p` is assigned the index of the Unicode plane of the Unicode code point `cp`. This function fails if and only if
`planeIndex` is a null pointer or if `cp` is outside of the bounds of `[Nucleus_Unicode_CodePoint_CodeLeast,
Nucleus_Unicode_CodePoint_Greatest]`.
