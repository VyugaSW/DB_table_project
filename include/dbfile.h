#pragma once

#include "dbtable.h"
#include "notifyError.h"

#define DEFAULT_TB_PATH "data/data.txt" /**< Default path for reading/writing table data. */

/**
 * @brief Writes a table to a file.
 *
 * @param[in] table Pointer to the Table object to write.
 * @param[in] path  Path to the file where the table will be written.
 */
void table_fwrite(Table *table, const char *path);

/**
 * @brief Reads a table from a file.
 *
 * @param[out] table Pointer to the Table object where the data will be stored.
 * @param[in]  path  Path to the file from which the table will be read.
 */
void table_fread(Table *table, const char *path);