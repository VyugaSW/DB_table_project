#pragma once

#include "notifyError.h"
#include <stdbool.h>

/**
 * @brief Structure representing a date.
 */
typedef struct Date {
    unsigned year;  /**< Year of the date. */
    unsigned day;   /**< Day of the date. */
    unsigned month; /**< Month of the date. */
} Date;

/**
 * @brief Initializes a new Date object.
 *
 * @param[in] year  The year of the date.
 * @param[in] month The month of the date.
 * @param[in] day   The day of the date.
 * @return Pointer to the newly created Date object, or NULL if initialization fails.
 */
Date *date_init(unsigned year, unsigned month, unsigned day);

/**
 * @brief Compares two dates.
 *
 * @param[in] date1 Pointer to the first date.
 * @param[in] date2 Pointer to the second date.
 * @return true if the first date is later than the second date, false otherwise.
 */
bool date_compare(Date *date1, Date *date2);

/**
 * @brief Creates a deep copy of a Date object.
 *
 * @param[in] date Pointer to the Date object to copy.
 * @return Pointer to the newly copied Date object, or NULL if copying fails.
 */
Date *date_copy(Date *date);

/**
 * @brief Converts a string in "DD.MM.YYYY" format to a Date object.
 *
 * @param[in] dateStr The string representing the date in "DD.MM.YYYY" format.
 * @return Pointer to the newly created Date object, or NULL if conversion fails.
 */
Date *date_stringToDate(const char* dateStr);