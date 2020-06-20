#include "resistor_color.h"

resistor_band_t color_array[] = {
	BLACK, BROWN, RED, ORANGE, YELLOW,
	GREEN, BLUE, VIOLET, GREY, WHITE
};

unsigned int color_code(resistor_band_t color) {
	return color;
}

unsigned int* colors() {
	return color_array;
}
