double* generate_and_run_heatmap(int width, int height, int rounds, int number_of_hotspots, int* hotspots){
    // generate heatmap
    double* heatmap;
    double* last_round = malloc(sizeof(double)*width*height);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++){
            last_round[(x*height)+y] = 0;}}
    
    // run heatmap
    for (int round = 0; round < rounds; round++) {
        heatmap = malloc(sizeof(double)*width*height);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++){
                double sum = 0;
                for (int row = -1; row < 2; row++){
                    for (int col = -1; col < 2; col++){
                        if (x+col >= 0 && x+col < width && y+row >= 0 && y+row < height){ //checks if cell is inside heatmap
                            sum += last_round[(x+col)*height+y+row];}}}
                heatmap[(x*height)+y] = sum/9.0;}}
        for (int hotspot = 0; hotspot < number_of_hotspots; hotspot++){
            if (round >= hotspots[hotspot*4+2] && round < hotspots[hotspot*4+3]){
                heatmap[(hotspots[hotspot*4]*height)+hotspots[hotspot*4+1]] = 1;}}
        last_round = heatmap;}
    
    return heatmap;}