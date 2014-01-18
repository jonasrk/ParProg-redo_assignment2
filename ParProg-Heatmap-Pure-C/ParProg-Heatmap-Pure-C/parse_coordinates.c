int parse_coordinates(const char* coord_file_name, int** coords){
    //count coordinates
    FILE *coord_file;
    coord_file = fopen (coord_file_name, "rt");
    int number_of_coords = 0;
    int ch;
    
    while (EOF != (ch=getc(coord_file)))
        if (ch=='\n') number_of_coords++;
    fclose(coord_file);
    
    // tokenize coords
    FILE *coord_file_again;
    coord_file_again = fopen (coord_file_name, "rt");
    *coords = malloc(sizeof(int)*number_of_coords*2);
    int coord_to_tokenize = -1;
    char line[80];
    
    while(fgets(line, 80, coord_file_again) != NULL){
        if (coord_to_tokenize > -1) {
            char s[64];
            strcpy(s, line);
            char* token = strtok(s, ",");
            int current_token = 0;
            while (token) {
                (*coords)[coord_to_tokenize*2+current_token] = atoi(token);
                token = strtok(NULL, ",");
                current_token++;}}
        coord_to_tokenize++;}
    fclose(coord_file_again);
    
    return number_of_coords;}