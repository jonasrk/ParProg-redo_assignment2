#include "heatmap.h"
#include "parse_coordinates.c"
#include "parse_and_count_hotspots.c"
#include "generate_and_run_heatmap.c"
#include "generate_output.c"

int main(int argc, const char * argv[]){
	
	long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
	  if (nprocs < 1)
	  {
	    fprintf(stderr, "Could not determine number of CPUs online:\n%s\n", 
	strerror (errno));
	    exit (EXIT_FAILURE);
	  }
	  
	long nprocs_max = sysconf(_SC_NPROCESSORS_CONF);
	  if (nprocs_max < 1)
	  {
	    fprintf(stderr, "Could not determine number of CPUs configured:\n%s\n", 
	strerror (errno));
	    exit (EXIT_FAILURE);
	  }
	  printf ("%ld of %ld processors online. Yay!\n",nprocs, nprocs_max);
	  
	  
	
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int rounds = atoi(argv[3]) + 1; //one extra round
    int number_of_coords = 0;
    int* coords = NULL;
    int* hotspots = NULL;
    
    if (argc == 6) number_of_coords = parse_coordinates(argv[5], &coords);
    int number_of_hotspots = parse_and_count_hotspots(argv[4], &hotspots);
	
	pthread_t thread_id;
	
	for (int thread = 0; thread < 1; thread++){
		
		
		
		
	
	struct heatmapParams thisParams;
	thisParams.width = width;
	thisParams.height = height;
	thisParams.rounds = rounds;
	thisParams.number_of_hotspots = number_of_hotspots;
	thisParams.hotspots = hotspots;
	
	pthread_create(&thread_id, 
	                    NULL,
	                    generate_and_run_heatmap,
	                    &thisParams);
	
	}
	double* heatmap;
	pthread_join(thread_id, (void**) &heatmap);
    generate_output(argc, number_of_coords, coords, width, height, heatmap);
    
    return 0;}

