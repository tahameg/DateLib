#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "date.h"

#define PUBLIC
#define PRIVATE static

#define IS_LEAP_YEAR(y) (((y) % 400) == 0) || ((((y) % 100) != 0) && (((y) % 4) == 0))
#define M_DAYS(y, m) mdays_lookup[IS_LEAP_YEAR(y) == 0 ? 0 : 1][m]
#define YEAR(d) (d)->m_year
#define MON(d) (d)->m_month
#define MDAY(d) (d)->m_mday

PRIVATE const int mdays_lookup[2][12] = {
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

PRIVATE const char* const months[13] = {
		"", "Ocak", "Subat", "Mart", "Nisan", "Mayis", "Haziran", "Temmuz", "Agustos", "Eylul", "Ekim", "Kasim", "Aralik"
};

PRIVATE const char* const wdays[7] = {
		"Pazar", "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi"
};

PRIVATE int is_valid_date(int mday, int mon, int year);
PRIVATE int day_of_the_week(int y, int m, int d);

PUBLIC Date * set_date(Date * out, int mday, int mon, int year)
{
	if(!is_valid_date(mday, mon, year)) return NULL;
	YEAR(out) = year;
	MON(out) = mon;
	MDAY(out) = mday;
	return out;
}


PUBLIC Date * set_date_by_string(Date *out, const char* str)
{
	//date format: dd-mm-yyyy
	int mday = atoi(str);
	int month = atoi(str+3);
	int year = atoi(str+6);
	return set_date(out, mday, month, year);
}


PUBLIC Date * set_todays_date(Date *out)
{
	time_t current_time;
	time(&current_time);

	struct tm* lt;
	lt = localtime(&current_time);
	set_date(out, lt->tm_mday, lt->tm_mon+1, lt->tm_year + 1900);
	return out;
}

PUBLIC void seed_date_randomize()
{
	srand(time(NULL));
}

PUBLIC Date * set_random_date_range(Date *inout, int min_year, int max_year)
{
	if(max_year - min_year < 0)
	{
		fprintf(stderr, "max_year cannot be smaller than min_year!\n");
		exit(-1);
	}

	YEAR(inout) = min_year + rand() % (max_year - min_year);
	MON(inout) = 1 + rand() % 12;
	MDAY(inout) = 1 + rand() % M_DAYS(YEAR(inout), MON(inout));

	return inout;
}

PUBLIC Date * set_year(Date *inout, int y)
{
	return set_date(inout, MDAY(inout), MON(inout), y);
}

PUBLIC Date * set_month(Date *inout, int m)
{
	return set_date(inout, MDAY(inout), m, YEAR(inout));
}


PUBLIC Date * set_month_day(Date *inout, int md)
{
	return set_date(inout, md, MON(inout), YEAR(inout));
}

PUBLIC int get_year(const Date *in)
{
	return YEAR(in);
}

// Returns the actual month of the year: 1: January, 2: February etc.
PUBLIC int get_month(const Date *in)
{
	return  MON(in);
}

PUBLIC int get_weekday(const Date *in)
{
	return day_of_the_week(MDAY(in), MON(in), YEAR(in));
}

PUBLIC int get_month_day(const Date *in)
{
	return  MDAY(in);
}

PUBLIC int get_year_day (const Date *in)
{
	return YEAR(in);
}


PUBLIC int date_cmp(const void *restrict p1, const void *restrict p2)
{
	const Date* d1 = (Date*) p1;
	const Date* d2 = (Date*) p2;
	if(YEAR(d1) !=  YEAR(d2)) return YEAR(d1) - YEAR(d2);
	if(MON(d1) !=  MON(d2)) return MON(d1) - MON(d2);
	if(MDAY(d1) != MDAY(d2)) return MDAY(d1) - MDAY(d2);
	return 0;
}

PUBLIC int get_date_diff(const Date *restrict d1, const Date *restrict d2)
{
	struct tm tm1 = {0}, tm2 = {0};

	tm1.tm_mday  = MDAY(d1);
	tm1.tm_mon = MON(d1) - 1;
	tm1.tm_year = YEAR(d1) - 1900;

	tm2.tm_mday  = MDAY(d2);
	tm2.tm_mon = MON(d2) - 1;
	tm2.tm_year = YEAR(d2) - 1900;

	time_t t1 = mktime(&tm1);
	time_t t2 = mktime(&tm2);

	if(t1 < 0 || t2 < 0)
	{
		fprintf(stderr, "Dates could not be parsed into time.\n");
		exit(-1);
	}

	return (int)((t2 - t1) / (60 * 60 * 24));
}



PUBLIC Date * n_days_after(Date *restrict  out, const Date *restrict in, int n)
{
	struct tm tm1 = {0};
	struct tm* tmp1;

	tm1.tm_mday = MDAY(in);
	tm1.tm_mon = MON(in) - 1;
	tm1.tm_year = YEAR(in) - 1900;

	time_t t1 = mktime(&tm1);

	t1 = t1 + (n * 60 * 60 * 24);

	tmp1 = localtime(&t1);

	MDAY(out) = tmp1->tm_mday;
 	MON(out) = tmp1->tm_mon + 1;
	YEAR(out) = tmp1->tm_year + 1900;

	return out;
 }


PUBLIC Date * scan_date(Date *out)
{
	char input[50];
	scanf("%s", input);
	return set_date_by_string(out, input);
}

PUBLIC void print_date(const Date *in)
{
	printf("%d %s %d, %s", in->m_mday, months[in->m_month], in->m_year, wdays[get_weekday(in)]);
}

PRIVATE int is_valid_date(int mday, int mon, int year){
	if(mon < 1 || mon > 12) return 0;
	if(mday < 1 || mday > M_DAYS(year, mon)) return 0;
	return 1;
}

PRIVATE int day_of_the_week(int d, int m, int y)
{
    // array with leading number of days values
    int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

    // if month is less than 3 reduce year by 1
    if (m < 3)
        y -= 1;

    return ((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7);
}
