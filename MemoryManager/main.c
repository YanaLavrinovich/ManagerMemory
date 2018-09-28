#include <stdio.h>  
#include <assert.h>
#include <malloc.h>
#include "mmemory.h"

void init_invalid_parameters() {
	int err;
	err = _init(-1, -15);
	assert(-1 == err);
}

void init_successful_implementation() {
	int err;
	err = _init(1, 25);
	assert(0 == err);
}

void malloc_invalid_parameters() {
	int err;
	_init(1, 10);
	err = _malloc(NULL, 10);
	assert(-1 == err);
}

void malloc_lack_of_memory() {
	int err;
	VA va1;
	VA va2;
	_init(1, 10);
	_malloc(&va1, 10);
	err = _malloc(&va2, 1);
	assert(-2 == err);
}

void free_invalid_parameters() {
	int err;
	VA va1 = (VA)malloc(sizeof(VA));
	_init(1, 10);
	err = _free(va1);
	assert(-1 == err);
}

void free_centre_success() {
	int err;
	VA va1;
	VA va2;
	VA va3;
	_init(1, 15);
	_malloc(&va1, 5);
	_malloc(&va2, 5);
	_malloc(&va3, 5);
	_free(va1);
	_free(va3);
	err = _free(va2);
	assert(0 == err);
}

void free_right_success() {
	int err;
	VA va1;
	VA va2;
	_init(1, 10);
	_malloc(&va1, 5);
	_malloc(&va2, 5);
	_free(va1);
	err = _free(va2);
	assert(0 == err);
}

void free_left_success() {
	int err;
	VA va1;
	VA va2;
	_init(1, 10);
	_malloc(&va1, 5);
	_malloc(&va2, 5);
	_free(va2);
	err = _free(va1);
	assert(0 == err);
}

void free_one_block_success() {
	int err;
	VA va1;
	_init(1, 10);
	_malloc(&va1, 10);
	err = _free(va1);
	assert(0 == err);
}

void write_invalid_parameters() {
	int err;
	VA va1;
	_init(1, 10);
	_malloc(&va1, 10);
	err = _write(NULL, NULL, 10);
	assert(-1 == err);
}

void write_lack_of_memory() {
	int err;
	VA va1;
	char* write_buffer = "write";
	_init(1, 10);
	_malloc(&va1, 5);
	err = _write(va1, write_buffer, 6);
	assert(-2 == err);
}

void write_successful_implementation() {
	int err;
	VA va1;
	char* write_buffer = "write";
	_init(1, 10);
	_malloc(&va1, 5);
	err = _write(va1, write_buffer, 5);
	assert(0 == err);
}



void init_test() {
	init_invalid_parameters();
	init_successful_implementation();
}

void malloc_test() {
	malloc_invalid_parameters();
	malloc_lack_of_memory();
	//malloc_with_memory_remaining();
	//malloc_without_memory_remaining();
}

void free_test() {
	free_invalid_parameters();
	free_centre_success();
	free_right_success();
	free_left_success();
	free_one_block_success();
}

void write_test() {
	write_invalid_parameters();
	write_lack_of_memory();
	write_successful_implementation();
}

int main(void)                
{
	init_test();
	malloc_test();
	free_test();
	write_test();
	//_free(va2);
	//char* buf = 'ddd';
	//_write(&va1, buf, 3);
	//print_list();
	//printf("%c", va);   

	//system("pause");
	return 0;
}