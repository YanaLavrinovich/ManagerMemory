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
	Memory_block* block = (Memory_block*)malloc(sizeof(Memory_block));
	block->size = szBlock;
	block->va = ptr;

	if (list->head == NULL) {
		Node* node = (Node*)malloc(sizeof(Node));
		list->head = node;
		list->end = node;
		list->size_free_memory -= szBlock;
		node->next = NULL;
		node->previous = NULL;
		node->block = block;
		
		return SUCCESSFUL_IMPLEMENTATION;
	}
	else {
		Node* node = (Node*)malloc(sizeof(Node));
		node->block = block;
		node->next = NULL;
		node->previous = list->end;
		list->end->next = node;
		list->end = node;
		list->size_free_memory -= szBlock;
		return SUCCESSFUL_IMPLEMENTATION;
	}
}

int _free(VA ptr) {
	if (list == NULL) {
		return UNKNOWN_ERROR;
	}
	if (ptr == NULL) {
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
			
			//free(ptr);
			return SUCCESSFUL_IMPLEMENTATION;
		}
		current_node = current_node->next;
	}
	return UNKNOWN_ERROR;
}

void print_list() {
	Node* curr = list->head;
	while (curr != NULL) {
		printf("%c - %d ", curr->block->va, curr->block->size);
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
		if (curr->block->va == ptr && curr->block->size >= szBuffer) {
			memcpy(ptr, pBuffer, szBuffer);
			return SUCCESSFUL_IMPLEMENTATION;
		}
		else {
			return LACK_OF_MEMORY;
		}
		curr = curr->next;
	}

}