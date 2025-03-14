#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "date.h"
#include "notifyError.h"

/**
 * @brief Enumeration for comparison criteria.
 */
typedef enum ECmp_by {
    ID = 0,      /**< Compare by book ID. */
    NAME,        /**< Compare by book name. */
    PRICE,       /**< Compare by book price. */
    BOOK_DATE    /**< Compare by book date. */
} ECmp_by;

/**
 * @brief Structure representing a book.
 */
typedef struct Book {
    size_t id;    /**< Unique identifier for the book. */
    char *name;   /**< Name of the book. */
    Date *date;   /**< Pointer to the book's date. */
    double price; /**< Price of the book. */
} Book;

/**
 * @brief Initializes a new book.
 *
 * @param[in] name  The name of the book.
 * @param[in] date  Pointer to the book's date.
 * @param[in] price The price of the book.
 * @return Pointer to the newly created Book object, or NULL if initialization fails.
 */
Book *init_book(char *name, Date *date, double price);

/**
 * @brief Compares two books based on the specified criteria.
 *
 * @param[in] book1       Pointer to the first book.
 * @param[in] book2       Pointer to the second book.
 * @param[in] compare_by  The criteria to compare the books by (ID, NAME, PRICE, or BOOK_DATE).
 * @return true if the first book is greater than the second based on the criteria, false otherwise.
 */
bool compare_books(Book *book1, Book *book2, ECmp_by compare_by);

/**
 * @brief Creates a deep copy of a book.
 *
 * @param[in] book  Pointer to the book to copy.
 * @return Pointer to the newly copied Book object, or NULL if copying fails.
 */
Book *copy_book(Book *book);

/**
 * @brief Frees the memory allocated for a book.
 *
 * @param[in] book  Pointer to the book to free.
 */
void free_book(Book *book);