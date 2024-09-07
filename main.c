#include <stdio.h>
#include <stdlib.h>
#include "date.h"

#define ARRAY_SIZE 100
#define MIN_YEAR 1960
#define MAX_YEAR 2025

int main()
{
	Date dates[ARRAY_SIZE];

	seed_date_randomize();

	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		set_random_date_range(dates + i, MIN_YEAR, MAX_YEAR);
	}

	qsort(dates, ARRAY_SIZE, sizeof(Date), date_cmp);

	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		print_date(dates+i);
		putchar('\n');
	}

	getchar();
	return 0;
}


