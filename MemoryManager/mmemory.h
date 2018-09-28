#ifndef MEMORYMANAGER_MMEMORY_H
#define MEMORYMANAGER_MMEMORY_H

#include <stddef.h>

/************************************************************************
		������������ ������ �1

	�������� ������������ ������� ������ ��������� ������

 ************************************************************************/

#define LACK_OF_MEMORY -2;
#define INVALID_PARAMETERS -1;
#define SUCCESSFUL_IMPLEMENTATION 0;
#define UNKNOWN_ERROR 1;

typedef char* VA;				// ��� ����������� ����� �����

typedef struct Memory_block
{
	VA* va;
	size_t size;
} Memory_block;

typedef struct Node
{
	Memory_block* block;
	struct Node* next;
	struct Node* previous;
} Node;

typedef struct List {
	size_t size_memory;
	size_t size_free_memory;
	Node* head;
	Node* end;
} List;

/**
	@func	_malloc
	@brief	�������� ���� ������ ������������� �������

	@param	[out] ptr		������ �����
	@param	[in]  szBlock	������ �����

	@return	��� ������
	@retval	0	�������� ����������
	@retval	-1	�������� ���������
	@retval	-2	�������� ������
	@retval	1	����������� ������
 **/
int _malloc(VA* ptr, size_t szBlock);



/**
	@func	_free
	@brief	�������� ����� ������

	@param	[in] ptr		������ �����

	@return	��� ������
	@retval	0	�������� ����������
	@retval	-1	�������� ���������
	@retval	1	����������� ������
 **/
int _free(VA ptr);



/**
	@func	_read
	@brief	������ ���������� �� ����� ������

	@param	[in] ptr		������ �����
	@param	[in] pBuffer	������ ������ ���� ���������� ���������
	@param	[in] szBuffer	������ ������

	@return	��� ������
	@retval	0	�������� ����������
	@retval	-1	�������� ���������
	@retval	-2	������ �� ������� �����
	@retval	1	����������� ������
 **/
int _read(VA ptr, void* pBuffer, size_t szBuffer);



/**
	@func	_write
	@brief	������ ���������� � ���� ������

	@param	[in] ptr		�����c �����
	@param	[in] pBuffer	������ ������ ���� ���������� ���������
	@param	[in] szBuffer	������ ������

	@return	��� ������
	@retval	0	�������� ����������
	@retval	-1	�������� ���������
	@retval	-2	������ �� ������� �����
	@retval	1	����������� ������
 **/
int _write(VA ptr, void* pBuffer, size_t szBuffer);



/**
	@func	_init
	@brief	������������� ������ ��������� ������

	@param	[in] n		���������� �������
	@param	[in] szPage	������ ��������

	� �������� 1 � 2 ����� ����� ������ ������������� ��� n*szPage

	@return	��� ������
	@retval	0	�������� ����������
	@retval	-1	�������� ���������
	@retval	1	����������� ������
 **/
int _init(int n, int szPage);

Node* init_node(size_t size);
Memory_block* create_memory_block(VA va, size_t size);
Node* create_node(Memory_block *new_memory_block);

#endif