#include "../darr.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

#define ARRAY_SIZE(x) \
	(sizeof (x) / sizeof ((x)[0]))

void test_int(void)
{
	int i, *arr, input[] = {
		1,
		10,
		2,
		512,
		19,
		88,
		1024
	}, arr_final[] = {
		1,
		2,
		19,
		88,
		1024
	};

	arr = DARR_CREATE (int, 1, NULL);

	for (i = 0; i < ARRAY_SIZE (input); ++i) {
		DARR_APPEND_RVAL (&arr, int, input[i]);
		assert(0 == memcmp(arr, input, i * sizeof (int)));
	}
	assert(ARRAY_SIZE (input) == DARR_SIZE (arr));

	assert(0 == DARR_POP_AT(&arr, 3, &i));

	assert(i == input[3]);

	assert(0 == DARR_DEL_AT (&arr, 1));

	assert(0 == memcmp(arr, arr_final, sizeof (arr_final)));

	assert(ARRAY_SIZE (arr_final) == DARR_SIZE (arr));

	DARR_DESTROY (arr);
}

void test_string(void)
{
	char **arr, *input[] = {
		"Lorem",
		"ipsum",
		"dolor",
		"sit",
		"amet"
	}, *arr_final[] = {
		"ipsum",
		"dolor",
		"sit",
	}, *tmp;
	int i, j;

	arr = DARR_CREATE (char *, 1, NULL);
	for (i = 0; i < ARRAY_SIZE (input); ++i) {
		assert(0 == DARR_APPEND (&arr, &input[i]));

		for (j = 0; j <= i; j++) {
			assert(0 == strcmp(arr[j], input[j]));
		}
	}

	assert(0 == DARR_POP_AT(&arr, 0, &tmp));

	assert(0 == strcmp(input[0], tmp));

	assert(0 == DARR_DEL_AT (&arr, 3));

	assert(0 == memcmp(arr, arr_final, sizeof (arr_final)));

	assert(ARRAY_SIZE (arr_final) == DARR_SIZE (arr));

	DARR_DESTROY (arr);
}

void test_struct(void)
{
	struct s {
		int i;
		char *s;
	};

	struct s input[] = {
		{.i = 1, .s = "Lorem"},
		{.i = 2, .s = "ipsum"},
		{.i = 3, .s = "dolor"},
		{.i = 4, .s = "sit"},
		{.i = 5, .s = "amit"},
	}, arr_final[] = {
		{.i = 2, .s = "ipsum"},
		{.i = 3, .s = "dolor"},
		{.i = 5, .s = "amit"},
	}, *arr, tmp;

	int i, j;

	arr = DARR_CREATE (struct s, 1, NULL);

	for (i = 0; i < ARRAY_SIZE (input); ++i) {
		assert(0 == DARR_APPEND (&arr, &input[i]));

		for (j = 0; j <= i; j++) {
			assert(0 == strcmp(arr[j].s, input[j].s));
			assert(arr[j].s == input[j].s);
			assert(arr[j].i == input[j].i);
		}
	}

	assert(0 == DARR_POP_AT(&arr, 0, &tmp));

	assert(tmp.s == input[0].s);
	assert(tmp.i == input[0].i);

	assert(0 == DARR_DEL_AT (&arr, 2));

	for (i = 0; i < ARRAY_SIZE (arr_final); ++i) {
		assert(arr[i].s == arr_final[i].s);
		assert(arr[i].i == arr_final[i].i);
		assert(0 == strcmp(arr[i].s, arr_final[i].s));
	}

	assert(ARRAY_SIZE (arr_final) == DARR_SIZE (arr));

	DARR_DESTROY (arr);
}

int main()
{
	test_int();
	test_string();
	test_struct();

	printf("All test were succesfull!\n");
}
