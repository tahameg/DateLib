/**
 * @file date.h
 * @brief Header file for date manipulation functions.
 *
 * This file provides functions for setting, getting, and manipulating dates. It includes
 * functionality for creating dates, comparing them, calculating differences, and more.
 */

#ifndef DATE_H
#define DATE_H

/**
 * @struct Date
 * @brief A structure to represent a date.
 *
 * The `Date` structure holds the day, month, and year of a date.
 */
typedef struct Date{
    int m_mday; /**< Day of the month (1-31) */
    int m_month; /**< Month of the year (1-12) */
    int m_year; /**< Year (e.g., 2024) */
} Date;

/**
 * @brief Set a date with specified day, month, and year.
 *
 * @param[out] out Pointer to a `Date` structure to be initialized.
 * @param[in] day Day of the month (1-31).
 * @param[in] mon Month of the year (1-12).
 * @param[in] year Year (e.g., 2024).
 *
 * @return Pointer to the initialized `Date` structure, or NULL if the date is invalid.
 */
Date * set_date(Date *out, int day, int mon, int year);

/**
 * @brief Set a date from a string in the format "dd-mm-yyyy".
 *
 * @param[out] out Pointer to a `Date` structure to be initialized.
 * @param[in] str String representing the date in "dd-mm-yyyy" format.
 *
 * @return Pointer to the initialized `Date` structure, or NULL if the date is invalid.
 */
Date * set_date_by_string(Date *out, const char* str);

/**
 * @brief Set the date to today's date.
 *
 * @param[out] out Pointer to a `Date` structure to be initialized with today's date.
 *
 * @return Pointer to the initialized `Date` structure.
 */
Date * set_todays_date(Date *out);

/**
 * @brief Set the year of the given date.
 *
 * @param[in,out] inout Pointer to a `Date` structure to be updated.
 * @param[in] y New year value.
 *
 * @return Pointer to the updated `Date` structure.
 */
Date * set_year(Date *inout, int y);

/**
 * @brief Set the month of the given date.
 *
 * @param[in,out] inout Pointer to a `Date` structure to be updated.
 * @param[in] m New month value (1-12).
 *
 * @return Pointer to the updated `Date` structure.
 */
Date * set_month(Date *inout, int m);

/**
 * @brief Set the day of the month of the given date.
 *
 * @param[in,out] inout Pointer to a `Date` structure to be updated.
 * @param[in] md New day of the month (1-31).
 *
 * @return Pointer to the updated `Date` structure.
 */
Date * set_month_day(Date *inout, int md);

/**
 * @brief Seed the random number generator for date randomization.
 */
void seed_date_randomize();

/**
 * @brief Set a random date within the specified range of years.
 *
 * @param[in,out] inout Pointer to a `Date` structure to be initialized with a random date.
 * @param[in] min_year Minimum year value.
 * @param[in] max_year Maximum year value.
 *
 * @return Pointer to the initialized `Date` structure.
 */
Date * set_random_date_range(Date *inout, int min_year, int max_year);

/**
 * @brief Get the year from a `Date` structure.
 *
 * @param[in] in Pointer to a `Date` structure.
 *
 * @return The year from the `Date` structure.
 */
int get_year(const Date *in);

/**
 * @brief Get the month from a `Date` structure.
 *
 * @param[in] in Pointer to a `Date` structure.
 *
 * @return The month from the `Date` structure (1-12).
 */
int get_month(const Date *in);

/**
 * @brief Get the day of the week for the given date.
 *
 * @param[in] in Pointer to a `Date` structure.
 *
 * @return The day of the week as an integer (0-6, where 0 is Sunday).
 */
int get_weekday(const Date *in);

/**
 * @brief Get the day of the month from a `Date` structure.
 *
 * @param[in] in Pointer to a `Date` structure.
 *
 * @return The day of the month from the `Date` structure.
 */
int get_month_day(const Date *in);

/**
 * @brief Get the year day (day of the year) from a `Date` structure.
 *
 * @param[in] in Pointer to a `Date` structure.
 *
 * @return The day of the year from the `Date` structure.
 */
int get_year_day(const Date *in);

/**
 * @brief Compare two dates.
 *
 * @param[in] p1 Pointer to the first `Date` structure.
 * @param[in] p2 Pointer to the second `Date` structure.
 *
 * @return A negative value if `p1` is earlier than `p2`, zero if they are equal, and a positive value if `p1` is later than `p2`.
 */
int date_cmp(const void *restrict p1, const void *restrict p2);

/**
 * @brief Calculate the difference in days between two dates.
 *
 * @param[in] d1 Pointer to the first `Date` structure.
 * @param[in] d2 Pointer to the second `Date` structure.
 *
 * @return The number of days between `d1` and `d2`. A positive value indicates `d2` is after `d1`.
 */
int get_date_diff(const Date *restrict d1, const Date *restrict d2);

/**
 * @brief Get the date that is `n` days after the given date.
 *
 * @param[out] out Pointer to a `Date` structure to be initialized with the new date.
 * @param[in] in Pointer to the original `Date` structure.
 * @param[in] n Number of days to add.
 *
 * @return Pointer to the initialized `Date` structure.
 */
Date * n_days_after(Date *restrict out, const Date *restrict in, int n);

/**
 * @brief Read a date from standard input.
 *
 * @param[out] out Pointer to a `Date` structure to be initialized with the input date.
 *
 * @return Pointer to the initialized `Date` structure.
 */
Date * scan_date(Date *out);

/**
 * @brief Print a `Date` structure in a human-readable format.
 *
 * @param[in] in Pointer to a `Date` structure to be printed.
 */
void print_date(const Date *in);

#endif // DATE_H
