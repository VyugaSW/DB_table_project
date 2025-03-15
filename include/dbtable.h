#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "notifyError.h"
#include "book.h"

#define TABLE_SIZE_MAX 20000      /**< Maximum allowed size of the table. */
#define TABLE_INITIAL_SIZE 50     /**< Initial size of the table. */

/**
 * @brief Structure representing a table of books.
 */
typedef struct Table {
    Book **books_arr; /**< Array of pointers to Book objects. */
    size_t size;      /**< Current allocated size of the table. */
    size_t count;     /**< Current number of books in the table. */
} Table;

/**
 * @brief Initializes a new Table object.
 *
 * @return Pointer to the newly created Table object, or NULL if initialization fails.
 */
Table *table_init();

/**
 * @brief Adds a book to the table.
 *
 * @param[in,out] table Pointer to the Table object.
 * @param[in]     book  Pointer to the Book object to add.
 */
void table_addElement(Table *table, Book *book);

/**
 * @brief Resizes the table to a new size.
 *
 * @param[in,out] table    Pointer to the Table object.
 * @param[in]     new_size The new size for the table.
 * 
 * @returns True if memory was allocated. False if something went wrong.
 */
bool table_resize(Table *table, size_t new_size);

/**
 * @brief Deletes a book from the table by its ID.
 *
 * @param[in,out] table Pointer to the Table object.
 * @param[in]     id    The ID of the book to delete.
 */
void table_delElement(Table *table, size_t id);

/**
 * @brief Frees the memory allocated for the table and its books.
 *
 * @param[in] table Pointer to the Table object to free.
 */
void table_free(Table *table);

/**
 * @brief Prints the contents of the table.
 *
 * @param[in] books_arr Array of pointers to Book objects.
 * @param[in] count     Number of books in the array.
 */
void table_print(const Book **books_arr, size_t count);

/**
 * @brief Sorts the books in the table based on the specified criteria.
 *
 * @param[in,out] table      Pointer to the Table object.
 * @param[in]     flag       If true, sorts in ascending order; otherwise, sorts in descending order.
 * @param[in]     compare_by The criteria to sort the books by (ID, NAME, PRICE, or BOOK_DATE).
 */
void table_sort(Table *table, bool flag, ECmp_by compare_by);