/**
   cmos.h, James Condron 2019

   Handle i/o for CMOS- including RTC
 **/

/**
   read_from_cmos returns the value the cmos holds for a given cmos address.

   It is the caller's responsibility to ensure the cmos is ready, using cmos_ready
 **/
unsigned char read_from_cmos(char);

/**
   cmos_ready returns !0 for whether the cmos is ready, and 0 for when it isn't
 **/
int cmos_ready();

/**
   cmos_clock_updating returns 1 if the cmos clock is in the middle of updating

   If it is, then the time we're about to read is not likely to be correct, especially
   if all of the time registers have not updated (which this tells us is not the case)
 **/
int cmos_clock_updating();

/**
   cmos_status_a returns the value at register 0x0A
 **/
unsigned char cmos_status_a();

/**
   cmos_status_b returns the value at register 0x0B
 **/
unsigned char cmos_status_b();


#ifndef CMOS_ADDRESS
#define CMOS_ADDRESS 0x70
#endif

#ifndef CMOS_DATA
#define CMOS_DATA 0x71
#endif
