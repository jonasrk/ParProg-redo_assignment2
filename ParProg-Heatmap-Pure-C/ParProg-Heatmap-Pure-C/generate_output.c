int generate_output(int argc, int number_of_coords, int* coords, int width, int height, double* heatmap){
    FILE *output_file;
    output_file = fopen("output.txt","w+");
    
    if (argc == 6){
        for (int coord = 0; coord < number_of_coords; coord++){
            fprintf(output_file, "%f\n", heatmap[coords[coord*2]*height+coords[coord*2+1]]);}}
    else {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++){
                if (heatmap[(x*height)+y] > 0.9) fprintf(output_file, "X");
                else {
                    int int_value = (int)((heatmap[(x*height)+y]+0.09)*10)/1;
                    fprintf(output_file, "%i", int_value);}}
            fprintf(output_file, "\n");}}
    fclose(output_file);
    
    return 0;}