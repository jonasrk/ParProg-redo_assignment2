all: main.o generate_and_run_heatmap.o generate_output.o parse_coordinates.o parse_and_count_hotspots.o
	gcc -std=c99 -o heatmap main.o generate_and_run_heatmap.o generate_output.o parse_coordinates.o parse_and_count_hotspots.o

main.o: main.c
	gcc -std=c99 -c main.c

generate_and_run_heatmap.o: generate_and_run_heatmap.c
	gcc -std=c99 -c generate_and_run_heatmap.c
	
generate_output.o: generate_output.c
	gcc -std=c99 -c generate_output.c

parse_coordinates.o: parse_coordinates.c
	gcc -std=c99 -c parse_coordinates.c
	
parse_and_count_hotspots.o: parse_and_count_hotspots.c
	gcc -std=c99 -c parse_and_count_hotspots.c
