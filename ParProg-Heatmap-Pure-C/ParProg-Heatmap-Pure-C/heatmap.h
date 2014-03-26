#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

struct heatmap_tile_args{
	
	int width, height, y;
	double* heatmap;
	double* last_round;
	
};


