#include "mmemory.h"
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdio.h>


List* list;


int _init(int n, int szPage) {
	if (n < 0 || szPage < 0) {
		return INVALID_PARAMETERS;
	}
	if (list != NULL) {
		free(list);
	}
	int size_memory = n * szPage;
	list = (List*)malloc(sizeof(List));
	if (list == NULL) {
		return UNKNOWN_ERROR;
	}
	list->size_memory = size_memory;
	list->size_free_memory = size_memory;
	list->head = NULL;
	return SUCCESSFUL_IMPLEMENTATION;
}

int _malloc(VA* ptr, size_t szBlock) {
	if (ptr == NULL || szBlock == 0) {
		return INVALID_PARAMETERS;
	}
	if (list == NULL) {
		return UNKNOWN_ERROR;
	}
	if (list->size_free_memory < szBlock) {
		return LACK_OF_MEMORY;
	}
	if (list->head == NULL) {
		Node* new_node = init_node(szBlock);
		list->head = new_node;
		list->end = new_node;
		list->size_free_memory -= szBlock;
		new_node->next = NULL;
		new_node->previous = NULL;
		*ptr = new_node->block->va;
		
		return SUCCESSFUL_IMPLEMENTATION;
	}
	else {
		Node* new_node = init_node(szBlock);
		new_node->next = NULL;
		new_node->previous = list->end;
		list->end->next = new_node;
		list->end = new_node;
		list->size_free_memory -= szBlock;
		*ptr = new_node->block->va;
		return SUCCESSFUL_IMPLEMENTATION;
	}
}

int _free(VA ptr) {
	if (list == NULL) {
		return UNKNOWN_ERROR;
	}
	if (ptr == NULL || get_node(list, ptr) == NULL) {
		return INVALID_PARAMETERS;
	}
	Node* current_node = list->head;
	while (current_node != NULL) {
		if (current_node->block->va == ptr) {
			list->size_free_memory += current_node->block->size;
			if (current_node->previous) {
				current_node->previous->next = current_node->next;
			}
			if (current_node->next) {
				current_node->next->previous = current_node->previous;
			}
			if (!current_node->previous) {
				list->head = current_node->next;
			}
			free(current_node);
			
			free(ptr);
			return SUCCESSFUL_IMPLEMENTATION;
		}
		current_node = current_node->next;
	}
	return UNKNOWN_ERROR;
}

void print_list() {
	Node* curr = list->head;
	while (curr != NULL) {
		printf("%c - %d ", &(curr->block->va), curr->block->size);
		curr = curr->next;
	}
}

int _write(VA ptr, void* pBuffer, size_t szBuffer) {
	if (list == NULL) {
		return UNKNOWN_ERROR;
	}
	if (ptr == NULL || pBuffer == NULL || szBuffer < 0) {
		return INVALID_PARAMETERS;
	}
	Node* curr = list->head;
	while (curr != NULL) {
		if (curr->block->va == ptr) {
			if (curr->block->size >= szBuffer) {
				memcpy(ptr, pBuffer, szBuffer);
				return SUCCESSFUL_IMPLEMENTATION;
			}
			else {
				return LACK_OF_MEMORY;
			}
		}
		curr = curr->next;
	}
}

Node* init_node(size_t size) {
	VA va = (VA)malloc(size * sizeof(VA));
	Node* new_node = create_node(create_memory_block(va, size));
	return new_node;
}

Memory_block* create_memory_block(VA va, size_t size) {
	Memory_block* new_memory_block = (Memory_block*)malloc(sizeof(Memory_block));
	new_memory_block->va = va;
	new_memory_block->size = size;
	return new_memory_block;
}

Node* create_node(Memory_block *new_memory_block) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->block = new_memory_block;
	return new_node;
}

Node *get_node(List *list, VA va) {
	Node *current_node = list->head;
	while (current_node != NULL) {
		if (current_node->block->va == va) {
			return current_node;
		}
		current_node = current_node->next;
	}
	return NULL;
}