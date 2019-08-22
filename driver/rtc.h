/**
   drivers/rtc.h, James Condron 2019

   Interact with the realtime clock
 **/

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
