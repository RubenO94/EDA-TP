#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fileloader.h"
#include "constants.h"

LoadError load_antennas_from_file(const char* filename, ED_List* ed_list, int* rows, int* cols){
    FILE* file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];
    int y = 0;

    if (!file) return LOAD_ERR_FILE_NOT_FOUND;

    while (fgets(line, sizeof(line), file)) {
        int current_cols = 0;

        for (int x = 0; line[x] != '\0' && line[x] != '\n'; x++) {
            char ch = line[x];
            current_cols++;

            if (isalpha(ch)) {
                ED* new_node = create_ed(ch, x, y);
                insert_at_end(&ed_list, new_node);
            }
        }

        if (current_cols > *cols) {
            *cols = current_cols;
        }

        y++;
    }

    *rows = y;
    fclose(file);
    return LOAD_OK;
}
