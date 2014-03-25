#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double** generate_and_run_heatmap(int width, int height, int rounds, int number_of_hotspots, int* hotspots);
int generate_output(int argc, int number_of_coords, int* coords, int width, int height, double* heatmap);
int parse_and_count_hotspots(const char *hotspot_file_name, int** hotspots);
int parse_coordinates(const char* coord_file_name, int** coords);