# `Nucleus_NonNull`
*Function annotation indicating that pointer parameters expect non-null pointers as argument values.*

## C Specification
```
#define Nucleus_NonNull(...) ...
```

## Description
This function annotation indicates that some pointer parameters expect non-null pointers as argument values.

The macro receives a list of 1-based parameter indices. If the index of a pointer parameter is in the specified list,
that parameter expects a non-null pointer as its argument value.

For example, in the following function declaration this macro is used to annotate the parameters `y` and `w` as
expecting pointers as their arguments that are not null pointers
```
Nucleus_NonNull(2,4) void f(char *x, char *y, char *z, char *w);
```

If no index list is specified, all pointer parameters expect non-null pointers as their arguments.
For example, in the following function declaration this macro is used to annotate all the parameters
as expecting pointers as their arguments that are not null pointers
```
Nucleus_NonNull() void f(char *x, char *y, char *z, char *w);
```
