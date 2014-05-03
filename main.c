#include "stdio.h"

#define YEAR_TO_DAYS(y) ((y)*365 + (y)/4 - (y)/100 + (y)/400)

int main()
{
	unsigned long unixtime;
	unsigned int year, month, day, hour, minute, second;
	printf("Unix timestamp: ");
	scanf("%u", &unixtime);

	second = unixtime % 60;
	unixtime /= 60;
	
	minute = unixtime % 60;	
	unixtime /= 60;

	hour = unixtime % 24;
	unixtime /= 24;

    /* unixtime is now days since 01/01/1970 UTC
     * Rebaseline to the Common Era */
	unixtime += 719499;

    /* Roll forward looking for the year.  This could be done more efficiently
     * but this will do.  We have to start at 1969 because the year we calculate here
     * runs from March - so January and February 1970 will come out as 1969 here.
     */
	for (year = 1969; unixtime > YEAR_TO_DAYS(year + 1) + 30; year++);

    /* OK we have our "year", so subtract off the days accounted for by full years. */
	unixtime -= YEAR_TO_DAYS(year);

    /* unixtime is now number of days we are into the year (remembering that March 1
     * is the first day of the "year" still). */

    /* Roll forward looking for the month.  1 = March through to 12 = February. */
	for (month = 1; month < 12 && unixtime > 367*(month+1)/12; month++);

    /* Subtract off the days accounted for by full months */
	unixtime -= 367*month/12;

    /* unixtime is now number of days we are into the month */

    /* Adjust the month/year so that 1 = January, and years start where we
     * usually expect them to. */
	month += 2;
	if (month > 12) {
		month -= 12;
		year++;
	}
	day = unixtime;
	printf("\n\n %d/%d/%d - %d:%d:%d\n", day, month, year, hour, minute, second);
}

