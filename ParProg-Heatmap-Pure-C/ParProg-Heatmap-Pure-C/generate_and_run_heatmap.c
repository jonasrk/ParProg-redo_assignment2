void* run_heatmap_tile(void* args){
	
	
		
	
	    struct heatmap_tile_args* this_args;
		this_args = args;

		int width = this_args->width;
		int height = this_args->height;
		int y = this_args->y;
		int thread = this_args->thread;
		double* heatmap = this_args->heatmap;
		double* last_round = this_args->last_round;
		long nprocs_max = this_args->nprocs_max;
		
		if (thread == 0){
    for (int x = 0; x < width; x++){
        double sum = 0;
        for (int row = -1; row < 2; row++){
            for (int col = -1; col < 2; col++){
                if (x+col >= 0 && x+col < width && y+row >= 0 && y+row < height){ //checks if cell is inside heatmap
                    sum += last_round[(x+col)*height+y+row];}}}
        heatmap[(x*height)+y] = sum/9.0;}
		
		}
	pthread_exit(heatmap);}


double* generate_and_run_heatmap(int width, int height, int rounds, int number_of_hotspots, int* hotspots, long nprocs_max){
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
			
			pthread_t thread_ids[nprocs_max];
			struct heatmap_tile_args these_args[nprocs_max];
			
			for (int thread = 0; thread < nprocs_max; thread++){
				
				struct heatmap_tile_args these_args[thread];
				these_args[thread].width = width;
				these_args[thread].height = height;
				these_args[thread].y = y;
				these_args[thread].thread = thread;
				these_args[thread].heatmap = heatmap;
				these_args[thread].last_round = last_round;
				these_args[thread].nprocs_max = nprocs_max;
				
				pthread_create(&thread_ids[thread], 
					                    NULL,
					                    run_heatmap_tile,
					                    &these_args[thread]);
				pthread_join(thread_ids[0], (void**)&heatmap);
				}
			
			}
				
				
				
				
        for (int hotspot = 0; hotspot < number_of_hotspots; hotspot++){
            if (round >= hotspots[hotspot*4+2] && round < hotspots[hotspot*4+3]){
                heatmap[(hotspots[hotspot*4]*height)+hotspots[hotspot*4+1]] = 1;}}
        last_round = heatmap;}
    
    return heatmap;}
	
