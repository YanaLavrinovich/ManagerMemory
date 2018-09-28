#ifndef MEMORYMANAGER_MMEMORY_H
#define MEMORYMANAGER_MMEMORY_H

#include <stddef.h>

/************************************************************************
		Лабораторная работа №1

	Описание интерфейсных функций модели менеджера памяти

 ************************************************************************/

#define LACK_OF_MEMORY -2;
#define INVALID_PARAMETERS -1;
#define SUCCESSFUL_IMPLEMENTATION 0;
#define UNKNOWN_ERROR 1;

typedef char* VA;				// Тип описывающий адрес блока

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
	@brief	Выделяет блок памяти определенного размера

	@param	[out] ptr		адресс блока
	@param	[in]  szBlock	размер блока

	@return	код ошибки
	@retval	0	успешное выполнение
	@retval	-1	неверные параметры
	@retval	-2	нехватка памяти
	@retval	1	неизвестная ошибка
 **/
int _malloc(VA* ptr, size_t szBlock);



/**
	@func	_free
	@brief	Удаление блока памяти

	@param	[in] ptr		адресс блока

	@return	код ошибки
	@retval	0	успешное выполнение
	@retval	-1	неверные параметры
	@retval	1	неизвестная ошибка
 **/
int _free(VA ptr);



/**
	@func	_read
	@brief	Чтение информации из блока памяти

	@param	[in] ptr		адресс блока
	@param	[in] pBuffer	адресс буфера куда копируется инфомация
	@param	[in] szBuffer	размер буфера

	@return	код ошибки
	@retval	0	успешное выполнение
	@retval	-1	неверные параметры
	@retval	-2	доступ за пределы блока
	@retval	1	неизвестная ошибка
 **/
int _read(VA ptr, void* pBuffer, size_t szBuffer);



/**
	@func	_write
	@brief	Запись информации в блок памяти

	@param	[in] ptr		адресc блока
	@param	[in] pBuffer	адресс буфера куда копируется инфомация
	@param	[in] szBuffer	размер буфера

	@return	код ошибки
	@retval	0	успешное выполнение
	@retval	-1	неверные параметры
	@retval	-2	доступ за пределы блока
	@retval	1	неизвестная ошибка
 **/
int _write(VA ptr, void* pBuffer, size_t szBuffer);



/**
	@func	_init
	@brief	Инициализация модели менеджера памяти

	@param	[in] n		количество страниц
	@param	[in] szPage	размер страницы

	В варианте 1 и 2 общий объем памяти расчитывается как n*szPage

	@return	код ошибки
	@retval	0	успешное выполнение
	@retval	-1	неверные параметры
	@retval	1	неизвестная ошибка
 **/
int _init(int n, int szPage);

Node* init_node(size_t size);
Memory_block* create_memory_block(VA va, size_t size);
Node* create_node(Memory_block *new_memory_block);

#endif