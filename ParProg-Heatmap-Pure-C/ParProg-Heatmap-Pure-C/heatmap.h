#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

struct heatmapParams {
    int width, height, rounds, number_of_hotspots;
	int* hotspots;
};