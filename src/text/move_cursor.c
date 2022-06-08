#include "_text.h"
#include <string.h>

void move_cursor(text txt, direction dir) {
    if (txt == NULL) {
        fprintf(stderr, "No text\n");
        return;
    }

    if (txt->length == 0 || (txt->begin == NULL && txt->end == NULL)) {
        fprintf(stderr, "No lines in the text\n");
        return;
    }

    size_t len;
    switch(dir) {
        case LEFT:
        if(txt->cursor->position != 0){
            txt->cursor->position -= 1;
            return;
        } else if (txt->cursor->line->previous != NULL) {
            txt->cursor->position = MAXLINE + 2;
        }
        case UP:
        if (txt->cursor->line->previous != NULL) {
            len = strlen(txt->cursor->line->previous->contents);
            if(len < txt->cursor->position) {
                txt->cursor->position = len;
            }
            txt->cursor->line = txt->cursor->line->previous;
            return;
        }
        break;
        case RIGHT:
        len = strlen(txt->cursor->line->contents);
        if(txt->cursor->position < len) {
            txt->cursor->position += 1;
            return;
        } else if (txt->cursor->line->next != NULL) {
            txt->cursor->position = 0;
        }
        case DOWN:
        if (txt->cursor->line->next != NULL) {
            len = strlen(txt->cursor->line->next->contents);
            if(len < txt->cursor->position) {
                txt->cursor->position = len;
            }
            txt->cursor->line = txt->cursor->line->next;
            return;
        }
        break;
    }
    fprintf(stderr, "Can't move cursor that direction\n");
}