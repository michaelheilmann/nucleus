# `Nucleus_[FloatingPointType]`
Aliases for the C floating point types `float`, `double`, and `long double`.*

## C Signature
```
typedef float Nucleus_Single;
typedef double Nucleus_Double;
typedef long double Nucleus_Quadruple;
```

## Description
The type definitions `Nucleus_Single`, `Nucleus_Double`, and `Nucleus_Quadruple` are aliases for the
standard C floating point types `float`, `double`, and `long double`, respectively. These       type
definitions are supporting orthogonality of naming.



# `[FloatingPointType]_Greatest`, `[FloatingPointType]_Least`

## C Signature
```
#define Nucleus_[FloatingPointType]_Least /* hidden */
#define Nucleus_[FloatingPointType]_Greatest /* hidden */
```
where `[FloatingPointType]` is one of `Single`, `Double`, or `Quadruple`.

## Description
`Nucleus_[FloatingPointType]_Least` represent the least value,
`Nucleus_[FloatingPointType]_Greatest` represents the greatest value
of values of the the type `Nucleus_[FloatingPointType]`.



# `[FloatingPointType]_NaN`

## C Signature
```
#define Nucleus_[FloatingPointType]_NaN /* hidden */
```
where `[FloatingPointType]` is one of `Single`, `Double`, or `Quadruple`.

## Description
`Nucleus_[FloatingPointType]_NaN` represent the "not a number" value the the type `Nucleus_[FloatingPointType]`.



# `[FloatingPointType]_PositiveInfinity`, `[FloatingPointType]_NegativeInfinity`

## C Signature
```
#define Nucleus_[FloatingPointType]_PositiveInfinity /* hidden */
#define Nucleus_[FloatingPointType]_NegativeInfinity /* hidden */
```
where `[FloatingPointType]` is one of `Single`, `Double`, or `Quadruple`.

## Description
`Nucleus_[FloatingPointType]_PositiveInfinity` represents the "positive infinity" value of the type `Nucleus_[FloatingPointType]`,
`Nucleus_[FloatingPointType]_NegativeInfinity` represents the "negative infinity" value of the type `Nucleus_[FloatingPointType]`.




## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/FloatingPoint.h`| `Nucleus/FloatingPoint.h` |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
