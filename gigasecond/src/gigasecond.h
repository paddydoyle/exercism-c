#ifndef GIGASECOND_H
#define GIGASECOND_H

#include <math.h>
#include <sys/types.h>

#define GIGASECOND pow(10, 9)

time_t gigasecond_after(const time_t);

#endif
