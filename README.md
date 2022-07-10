# **darr**, a generic dynamic array library in C
**darr** is a dynamic array library conforming to C99 or later. A dynamic array is a data structure that with contiguous memory like an array. Unlike normal arrays, dynamic arras grow and shrink automatically when data is inserted or deleted. Dynamic arrays should be used over other data structures when its important to have one contiguous memory region that stores all data. For example, iterating over all data in a dynamic array is faster than iterating over all data in a binary tree, because contiguous memory region are cache friendly.

## Key features:
- Conforms to c99 standard and later
- Smart memory preallocation by growing and shrinking the memory exponentially to reduce number of memory allocation calls
- Tested (see folder tests)
- Premissive MIT license
- User friendly: All functions return arrays and can be passed to any functions that handle arrays
- Transparency: The dynamic array's meta data is hidden from the user
