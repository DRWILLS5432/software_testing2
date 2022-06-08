#include "_text.h"
#include <string.h>

void move_cursor_left(text txt) {
    size_t len;
    if (txt->begin == NULL || txt->length == 0) {
        fprintf(stderr, "No lines!!\n");
        return;
    }
    if(txt->cursor->position != 0){
        txt->cursor->position -= 1;
        return;
    } else {
        if (txt->cursor->line->previous != NULL) {
            len = strlen(txt->cursor->line->previous->contents);
            if(len < txt->cursor->position) {
                txt->cursor->position = len;
            }
            txt->cursor->line = txt->cursor->line->previous;
            return;
        }
    }
    fprintf(stderr, "Can't move cursor that direction\n");
}