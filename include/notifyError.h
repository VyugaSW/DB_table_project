#pragma once

/**
 * @brief Macro for logging error messages.
 *
 * This macro prints an error message to the standard error stream (`stderr`) in a formatted way.
 * The message includes the file name and line number where the error occurred, along with the
 * provided error message. The error message is displayed in red color for better visibility.
 *
 * @param[in] message The error message to log.
 *
 * Example usage:
 * @code
 * LOG_ERROR("Failed to allocate memory!");
 * @endcode
 *
 * Output:
 * @code
 * |!| Error in file example.c, line 10: Failed to allocate memory!
 * @endcode
 */
#define LOG_ERROR(message) fprintf(stderr, "\033[91m|!|\033[0m Error in file %s, line %d: %s\n", __FILE__, __LINE__, message)