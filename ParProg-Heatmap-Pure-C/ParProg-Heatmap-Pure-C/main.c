#include "heatmap.h"

int main(int argc, const char * argv[]){
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int rounds = atoi(argv[3]) + 1; //one extra round
    int number_of_coords = 0;
    int* coords = NULL;
    int* hotspots = NULL;
    
    if (argc == 6) number_of_coords = parse_coordinates(argv[5], &coords);
    int number_of_hotspots = parse_and_count_hotspots(argv[4], &hotspots);
    double** heatmap = generate_and_run_heatmap(width, height, rounds, number_of_hotspots, hotspots);
    generate_output(argc, number_of_coords, coords, width, height, *heatmap);
    
    if(coords != NULL) free(coords);
    if(hotspots != NULL) free(hotspots);
    if(*heatmap != NULL) free(*heatmap);
    
    return 0;}

