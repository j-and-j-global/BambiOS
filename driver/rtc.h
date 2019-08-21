/**
   drivers/rtc.h, James Condron 2019

   Interact with the realtime clock
 **/

/**
   t_time (tea time) represents the necessary information for representing
   the time from the RTC.

   (Ackshually, it'll do for any clock, and should we write a network clock this
   struct will be a decent jumping point for that)
**/
struct t_time {
  char seconds;          /* Seconds past the minute on the clock */
  char minutes;          /* Minutes on the hour */
  char hours;            /* Hours on the day */
  char day_of_week;      /* Day of the week, don't expect this to be any good (according to the docs) */
  char day_of_month;     /* Day of the month */
  char month;            /* Month of year, 0=January, 11=December */
  char year;             /* Two digit year- we always assume the century is the 21st */
  char century;          /* Century, should the CMOS know it. As above, defaults to 20 */

  /* The following are informational, largely used when filling the above */
  char twentyfour;       /* Whether the RTC is in 24 hour format, or not (the hours field above IS ALWAYS in 24 hour format) */
  char dst;              /* Whether the RTC thinks we're in daylight savings */
  char bin;              /* Whether the RTC returned data in binary (or BCD) */
};

/**
    Read the RTC and return the time it shows
**/
struct t_time rtc();

/**
   Convenience function, returning whether a given year is a leapyear or not
 **/
int leapyear(int);

/**
   Return the time shown on the RTC as seconds since 00:00:00 01/01/1970
 **/
unsigned long unixtime();

/**
   Given a Binary-coded decimal, mask off and return a straight up decimal of
   the value being encoded
 **/
char unbcd(char);


/* ------------------ */

static const unsigned char months[] = {
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const int leapseconds = 27;

/**
   The following are convenience definitions for time maths operations
 **/
#ifndef MINUTE_SECONDS
#define MINUTE_SECONDS 60
#endif

#ifndef HOUR_SECONDS
#define HOUR_SECONDS 60*MINUTE_SECONDS
#endif

#ifndef DAY_SECONDS
#define DAY_SECONDS 24*HOUR_SECONDS
#endif

#ifndef YEAR_SECONDS
#define YEAR_SECONDS 365*DAY_SECONDS
#endif
