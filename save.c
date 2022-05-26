#include <stdio.h>
#include "common.h"
#include "text/text.h"

/* void (*process)(int index, char *contents, int cursor, void *data),*/
static void saveline(int idx, char *contents, int cursor, void *data);

/**
 * @brief Сохраняет файл
 * 
 * @param txt абстракция файла
 * @param filename название файла
 */

void save(text txt, char* filename) {
    FILE* f;
    if ((f = fopen(filename, "w")) == NULL) {
        printf("The file %s cannot be opened\n", filename);
        return;
    }

    process_forward(txt, saveline, f);
    fclose(f);
}

static void saveline(int idx, char *contents, int cursor, void *data) {
    UNUSED(idx);
    UNUSED(cursor);
    
    fprintf((FILE*)data, "%s\n", contents);
}