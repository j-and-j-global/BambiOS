/**
   std/time.h, James Condron 2019

   Represent, and interact with, the time
 **/

/**
   t_time (tea time) represents the necessary information for representing
   the time.
**/
struct t_time {
  char seconds;          /* Seconds past the minute on the clock */
  char minutes;          /* Minutes on the hour */
  char hours;            /* Hours on the day */
  char day_of_week;      /* Day of the week, don't expect this to be any good if coming from the RTC (according to the docs) */
  char day_of_month;     /* Day of the month */
  char month;            /* Month of year, 0=January, 11=December */
  char year;             /* Two digit year- we always assume the century is the 21st */
  char century;          /* Century, should we know it. As above, defaults to 20 */
  char *zoneoffset;       /* Timezone Offset; defaults to +00:00, which designates UTC */

  /* The following are informational, largely used when filling the above from the CMOS RTC */
  char twentyfour;       /* Whether the RTC is in 24 hour format, or not (the hours field above IS ALWAYS in 24 hour format) */
  char dst;              /* Whether the RTC thinks we're in daylight savings */
  char bin;              /* Whether the RTC returned data in binary (or BCD) */
};


/**
   iso8601_ish returns the time as a sort of iso8601 formatted timestamp.

   Fields where the value is less than 0 may come back padded with a leading 0, or may not
 **/
char *iso8601_ish(struct t_time, char*);
