#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_coordinates(const char* coord_file_name, int* coords){

    int number_of_coords = 0;
    
    FILE *coord_file;
    coord_file = fopen (coord_file_name, "rt");
    
    //count coordinates
    int ch;
    while (EOF != (ch=getc(coord_file)))
        if (ch=='\n')
            number_of_coords++;
    fclose(coord_file);
    
    coords = malloc(sizeof(int)*number_of_coords*2);
    
    // tokenize coords
    int coord_to_tokenize = -1;
    FILE *coord_file_again;
    coord_file_again = fopen (coord_file_name, "rt");
    char line[80];
    while(fgets(line, 80, coord_file_again) != NULL){
        if (coord_to_tokenize > -1) {
            char s[64];
            strcpy(s, line);
            char* token = strtok(s, ",");
            int current_token = 0;
            while (token) {
                coords[coord_to_tokenize*number_of_coords+current_token] = atoi(token);
                token = strtok(NULL, ",");
                current_token++;
            }
        }
        coord_to_tokenize++;
    }
    fclose(coord_file_again);
    
    return number_of_coords;
    
}

int main(int argc, const char * argv[])
{
    
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int rounds = atoi(argv[3]) + 1; //one extra round
    int number_of_coords;
    int* coords = NULL;
    
    // if 5 arguments are given -> parse the coordinate file
    if (argc == 6) number_of_coords = parse_coordinates(argv[5], coords);
    
    // parse and count hotspots
    const char *hotspot_file_name = argv[4];
    
    // count hotspots
    FILE *hotspot_file;
    hotspot_file = fopen (hotspot_file_name, "rt");
    int number_of_hotspots = 0;
    int ch;
    while (EOF != (ch=getc(hotspot_file)))
        if (ch=='\n')
            number_of_hotspots++;
    fclose(hotspot_file);
    int hotspots[number_of_hotspots][4];
    
    // tokenize hotspots
    
    int hotspot_to_tokenize = -1;
    FILE *hotspot_file_again;
    hotspot_file_again = fopen (hotspot_file_name, "rt");
    char line[80];
    while(fgets(line, 80, hotspot_file) != NULL){
        if (hotspot_to_tokenize > -1) {
            char s[64];
            strcpy(s, line);
            char* token = strtok(s, ",");
            int current_token = 0;
            while (token) {
                hotspots[hotspot_to_tokenize][current_token] = atoi(token);
                token = strtok(NULL, ",");
                current_token++;
            }
        }
        hotspot_to_tokenize++;
    }
    fclose(hotspot_file_again);
    
    // generate heatmap
    
    double* heatmap = malloc(sizeof(double)*width*height);
    double* last_round = malloc(sizeof(double)*width*height);
    double* last_round_copy = malloc(sizeof(double)*width*height);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++){
            last_round[(x*height)+y] = 0;
            last_round_copy[(x*height)+y] = 0;
            heatmap[(x*height)+y] = 0;
            for (int hotspot = 0; hotspot < number_of_hotspots; hotspot++){
                if (hotspots[hotspot][0] == x && hotspots[hotspot][1] == y && 0 >= hotspots[hotspot][2] && 0 < hotspots[hotspot][3]){
                    heatmap[(x*height)+y] = 1;
                }
            }
        }
    }
    
    // run heatmap
    
    for (int round = 0; round < rounds; round++) {
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++){
                double temp;
                temp = heatmap[(x*height)+y];
                double sum = 0;
                for (int row = -1; row < 2; row++){
                    for (int col = -1; col < 2; col++){
                        if (x+col >= 0 && x+col < width && y+row >= 0 && y+row < height){
                            sum += last_round[(x+col)*height+y+row];}}}
                heatmap[(x*height)+y] = sum/9.0;
                last_round_copy[(x*height)+y] = temp;
                for (int hotspot = 0; hotspot < number_of_hotspots; hotspot++){
                    if (hotspots[hotspot][0] == x && hotspots[hotspot][1] == y && round >= hotspots[hotspot][2] && round < hotspots[hotspot][3]){
                        heatmap[(x*height)+y] = 1;}}
            }
        }
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++){
                last_round[(x*height)+y] = heatmap[(x*height)+y];}}
    }
    
    // Generate output file
    
    FILE *output_file;
    output_file = fopen("output.txt","w+");
    
    if (argc == 6){
        for (int coord = 0; coord < number_of_coords; coord++){
            fprintf(output_file, "%f\n", heatmap[coords[coord*number_of_coords]*height+coords[coord*number_of_coords+1]]);
        }
    } else {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++){
                if (heatmap[(x*height)+y] > 0.9) fprintf(output_file, "X");
                else {
                    int int_value = (int)((heatmap[(x*height)+y]+0.09)*10)/1;
                    fprintf(output_file, "%i", int_value);
                }
            }
            fprintf(output_file, "\n");
        }
    }
    fclose(output_file);
    
    return 0;
}

