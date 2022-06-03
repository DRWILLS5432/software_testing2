/**
 * remove_all.c -- реализует функцию очистки текста
 *
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "_text.h"

void remove_last_line(text txt)
{
    /* Проверяем, имеется ли текст */
    if (txt == NULL) {
        fprintf(stderr, "The text doesn't exist!\n");
        return;
    }    
    
    /* Если список изначально пуст, делать ничего не надо */
    if (txt->length == 0) {
        fprintf(stderr, "This line doesn't exist\n");
        return;
    }

    /* Текст ненулевой длины должен содержать хотя бы одну строку */
    assert(txt->begin != NULL && txt->end != NULL);
    node* save = txt->end;

    if (save->previous != NULL) {
        txt->end = save->previous;
        txt->end->next = NULL;
        if (txt->cursor->line == save) {
            txt->cursor->line = txt->end;
            txt->cursor->position = strlen(txt->end->contents);
        }
    } else {
        txt->begin = NULL;
        txt->end = NULL;
        txt->cursor->line = NULL;
        txt->cursor->position = -1;
    }

    txt->length -= 1;
    free(save);
}
