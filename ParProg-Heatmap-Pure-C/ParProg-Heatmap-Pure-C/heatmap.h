#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

struct heatmap_tile_args{
	
	int width, height, y, thread;
	long nprocs_max;
	double* heatmap;
	double* last_round;
	
};


