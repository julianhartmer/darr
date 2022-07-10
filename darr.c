#include "darr.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define container_of(ptr, type, member) \
	((type *) ((char *)(ptr) - offsetof(type, member)))

#define ARRAY2CONTAINER(arr) \
	(container_of (arr, darr_container, data))

#define CONTAINER2ARRAY(container) \
	(&(container)->data[0])

typedef struct {
	size_t capacity;                /* space capacity by the array */
	size_t elem_num;                /* number of entries of array in use */
	size_t elem_size;               /* size of the array type */
	void (*free_elem_fn)(void *);   /* function to free element memory */
	char data[];                    /* address of data is data in darr */
} darr_container;

static void resize(darr_container **container)
{
	darr_container *new_container = NULL;
	size_t new_capacity = (*container)->capacity;

	if ((*container)->capacity < (*container)->elem_num) {
		new_capacity = (*container)->capacity * 2;
	} else if ((*container)->capacity > (*container)->elem_num * 4) {
		new_capacity = (*container)->capacity / 2;
	}

	if (new_capacity != (*container)->capacity) {
		new_container = realloc(*container,
				sizeof (darr_container) + new_capacity * (*container)->elem_size);
		if (NULL != new_container) {
			(*container) = new_container;
			(*container)->capacity = new_capacity;
		}
	}
}

void * _darr_create(
		size_t elem_size,
		size_t preallocate,
		void (*free_fn)(void *))
{
	darr_container *container = malloc(sizeof (darr_container) + preallocate * elem_size);

	if (NULL == container)
		return NULL;

	container->capacity = preallocate;
	container->elem_num = 0;
	container->elem_size = elem_size;
	container->free_elem_fn = free_fn;
	
	return CONTAINER2ARRAY(container);
}

size_t _darr_size(void *arr)
{
	return (ARRAY2CONTAINER (arr))->elem_num;
}

void (*_darr_free_fn(void *arr))(void *)
{
	return (ARRAY2CONTAINER (arr))->free_elem_fn;
}

int _darr_append(void **arr, void *elem)
{
	darr_container *container = ARRAY2CONTAINER (*arr);
	size_t idx = container->elem_num;

	container->elem_num++;
	resize(&container);

	if (container->capacity < idx)
		return -1;

	memcpy(&container->data[idx * container->elem_size],
			elem, container->elem_size);

	*arr = CONTAINER2ARRAY(container);

	return 0;
}

int _darr_pop_at(void **arr, size_t idx, void *out)
{
	darr_container *container = ARRAY2CONTAINER (*arr);

	if (container->elem_num <= idx)
		return -1;

	memmove(out, &container->data[idx * container->elem_size],
			container->elem_size);
	memmove(&container->data[idx * container->elem_size],
			&container->data[(idx + 1) * container->elem_size],
			container->elem_size * (container->elem_num - (idx + 1)));
	container->elem_num--;
	
	resize(&container);

	*arr = CONTAINER2ARRAY (container);

	return 0;
}

int _darr_del_at(void **arr, size_t idx)
{
	darr_container *container = ARRAY2CONTAINER (*arr);

	if (container->elem_num <= idx)
		return -1;

	if (container->free_elem_fn)
		container->free_elem_fn(&container->data[idx * container->elem_size]);

	memmove(&container->data[idx * container->elem_size],
			&container->data[(idx + 1) * container->elem_size],
			container->elem_size * (container->elem_num - (idx + 1)));
	container->elem_num--;
	
	resize(&container);

	*arr = CONTAINER2ARRAY (container);

	return 0;
}

int _darr_destroy(void *arr)
{
	darr_container *container = ARRAY2CONTAINER (arr);

	if (container->free_elem_fn) {
		while (container->elem_num--) {
			container->free_elem_fn(&container->data[container->elem_num]);
		}
	}
	
	free(container);
	return 0;
}
