# `darr` - A Generic Dynamic Array Library in C
## Why use `darr`?
`darr` is a dynamic array library conforming to C99 standard and later. A dynamic array is a data structure with contiguous memory like an array. Unlike normal arrays, dynamic arrays grow and shrink automatically when data is inserted or deleted. Dynamic arrays outperform other data structures such as binary trees when it is crucial to have all data stored in one contiguous memory region. For example, iterating over all data in a dynamic array is faster than iterating over all data in a binary tree, because contiguous memory regions are cache friendly.

## Key features:
- Permissive MIT license
- Smart memory handling to minimize number of memory allocation calls
- User friendly: All functions return pointer to the contiguous data (think of it as an pointer to an array)
- Compatible: The array pointer can be passed to any function expecting arrays.
- Safe: The dynamic array's meta-data is hidden from the user.
- Automatically tested in CI (functionality and memory safety).
- Conforms to C99 standard and later.

## Usage Example
See test file [test.c](tests/test.c) to see an example how to use the library.

## How does the library work internally?
Each returned array pointer by the library is the address of the `data` member of `darr_container` in [darr.c](darr.c). Because the offset of the `data` member to the root of the struct constant, the library is able to obtain the internal meta-data, which allows the meta-data to be completely hidden. For this to work, the library uses [Flexible Array Member](https://en.wikipedia.org/wiki/Flexible_array_member).
