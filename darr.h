/*
 * MIT License
 *
 * Copyright (c) 2022 Julian Hartmer <j.hartmer@googlemail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef DARR_H
#define DARR_H

#include <stdbool.h>
#include <stddef.h>

/*
 * iter iterates over all elements in array arr.
 */
#define ARR_FOREACH(iter, arr, size) \
	for (size_t _tmp = 0; _tmp < (size); _tmp++, iter = arr[_tmp])

/* iter iterates over all elements in dynamic array arr. */
#define DARR_FOREACH(iter, arr) \
	ARR_FOREACH (iter, arr, DARR_SIZE (arr))

/*
 * Create and return dynamic array that stores elements of type type. If
 * free_elem_fn is not NULL, it is used to internally free up entries.
 * preallocate dictates how many entries the entries are preallocated initially * When the returned array is not needed anymore, free internal memory with
 * DARR_DESTROY ().
 */
#define DARR_CREATE(type, preallocate, free_fn) \
	_darr_create(sizeof (type), preallocate, free_fn)

/* Returns capacity of dynamic array arr. */
#define DARR_SIZE(arr) \
	_darr_size((void *) (arr))

/* Returns the function used to free elements of array arr. */
#define DARR_FREE_FN(arr) \
	_darr_capacity((void *) (arr))

/* Append element elem at end of array pointed to by arr_p. */
#define DARR_APPEND(arr_p, elem) \
	_darr_append((void **) (arr_p), (void *) (elem))

/* Push r-value value of type type to array pointed to by arr_p. */
#define DARR_APPEND_RVAL(arr_p, type, value) \
 	do { \
		type _tmp = value; \
		_darr_append((void **)(arr_p), &_tmp); \
	} while (0)

/*
 * Remove and return element of dynamic array pointed to by arr_p  at index
 * The removed element is stored to the address pointed to by out.
 * On error, out is not changed and a non-zero value is returned.
 */
#define DARR_POP_AT(arr_p, idx, out) \
	_darr_pop_at((void **) (arr_p), idx, out)

/*
 * Remove element of dynamic array pointed to by arr_pat index idx.
 * Use free_fn to free the element's internal memory if free_fn is not NULL.
 */
#define DARR_DEL_AT(arr_p, idx) \
	_darr_del_at((void **) (arr_p), idx)

/*
 * Free all memory consumed by the dynamic array arr. Uses free_fn if set
 * to remove the memory of each element in the array. Before reusing the array,
 * it has to be prepared with darrprep() again.
 */
#define DARR_DESTROY(arr) \
	_darr_destroy((void *) (arr))

/***********************************************************
 * Don't use these functions, use the macros above instead *
 ***********************************************************/
size_t _darr_size(void *arr);

void (*_darr_free_fn(void *arr))(void *);

int _darr_append(void **arr, void *elem);

int _darr_pop_at(void **arr, size_t idx, void *out);

int _darr_del_at(void **arr, size_t idx);

int _darr_destroy(void *arr);

void * _darr_create(
		size_t elem_size,
		size_t preallocate,
		void (*free_fn)(void *));

#endif /* DARR_H */
