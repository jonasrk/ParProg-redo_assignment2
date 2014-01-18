int parse_and_count_hotspots(const char *hotspot_file_name, int** hotspots){
    // count hotspots
    FILE *hotspot_file;
    hotspot_file = fopen (hotspot_file_name, "rt");
    int number_of_hotspots = 0;
    int ch;
    
    while (EOF != (ch=getc(hotspot_file)))
        if (ch=='\n')
            number_of_hotspots++;
    fclose(hotspot_file);
    
    // tokenize hotspots
    FILE *hotspot_file_again;
    hotspot_file_again = fopen (hotspot_file_name, "rt");
    *hotspots = malloc(sizeof(int)*number_of_hotspots*4);
    int hotspot_to_tokenize = -1;
    char line[80];
    
    while(fgets(line, 80, hotspot_file) != NULL){
        if (hotspot_to_tokenize > -1) {
            char s[64];
            strcpy(s, line);
            char* token = strtok(s, ",");
            int current_token = 0;
            while (token) {
                (*hotspots)[hotspot_to_tokenize*4+current_token] = atoi(token);
                token = strtok(NULL, ",");
                current_token++;}}
        hotspot_to_tokenize++;}
    fclose(hotspot_file_again);
    
    return number_of_hotspots;}