#include "darts.h"
#include <math.h>

const score_map_t SCORES[4] = {
	{10, 0},
	{5, 1},
	{1, 5},
	{0, 10}
};

uint8_t score(coordinate_t landing_position) {
	uint8_t i, n_scores;
	double distance;

	distance = sqrt(landing_position.x * landing_position.x +
		landing_position.y * landing_position.y);

	// Save re-calculating each time through the loop.
	n_scores = sizeof(SCORES) / sizeof(score_map_t);

	for (i=0; i<n_scores; i++) {
		if (distance > SCORES[i].min_radius) {
			return SCORES[i].score;
		}
	}

	// Special case for dead center: the last score
	return SCORES[n_scores-1].score;
}
