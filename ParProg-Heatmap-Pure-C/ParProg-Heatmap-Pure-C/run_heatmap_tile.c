void* run_heatmap_tile(void* args){
	struct heatmap_tile_args* this_args = args;
	for (int y = 0; y < this_args->height; y++) {
		if (y % this_args->nprocs_max == this_args->thread){
			for (int x = 0; x < this_args->width; x++){
	    		double sum = 0;
	    	    for (int row = -1; row < 2; row++){
	    	        for (int col = -1; col < 2; col++){
	    	            if (x+col >= 0 && x+col < this_args->width && y+row >= 0 && y+row < this_args->height){ //checks if cell is inside heatmap
	    	                sum += this_args->last_round[(x+col)*this_args->height+y+row];}}}
	    	        this_args->heatmap[(x*this_args->height)+y] = sum/9.0;}}}
	pthread_exit(NULL);}