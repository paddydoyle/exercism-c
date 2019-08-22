#ifndef DARTS_H
#define DARTS_H

#include <stdint.h>

typedef struct coordinate {
	double x, y;
} coordinate_t;

typedef struct score_map {
	double min_radius;
	uint8_t score;
} score_map_t;


uint8_t score(coordinate_t landing_position);

#endif
