#include <gtest/gtest.h>
extern "C" {
    #include "../text/_text.h"
    #include "../text/text.h"
    #include "../common.h"
}

TEST(ProcessBackward, Rightness) {
    size_t times = 0;
    text txt = create_text();
    load(txt, "test_file.txt");
    process_backward(txt, [](int idx, char*, int, void* data) {
        (*(size_t*)data)++;
        ASSERT_GE(idx, 0);
    }, (void*)&times);
    ASSERT_EQ(txt->length, times);
}

TEST(ProcessBackward, EmptyTxt) {
    text txt = create_text();
    testing::internal::CaptureStderr();
    process_backward(txt, [](int idx, char*, int, void* data) {}, NULL);
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ("There are already no any lines in the text!\n", output); 
}

TEST(MoveCursor, RightLineBegin) {
    text txt = create_text();
    load(txt, "test_file.txt");
    txt->cursor->position = 0;
    int opos = 0;
    _node* oline = txt->cursor->line;

    move_cursor(txt, RIGHT);
    ASSERT_EQ(txt->cursor->line, oline);
    ASSERT_EQ(txt->cursor->position, opos+1);
}

TEST(MoveCursor, RightLineEnd) { // also tests DOWN middle
    text txt = create_text();
    load(txt, "test_file.txt");
    txt->cursor->line = txt->cursor->line->previous;
    txt->cursor->position = strlen(txt->cursor->line->contents);

    int opos = txt->cursor->position;
    _node* oline = txt->cursor->line;

    move_cursor(txt, RIGHT);
    ASSERT_EQ(txt->cursor->line, oline->next);
    ASSERT_EQ(txt->cursor->position, 0);
} 

TEST(MoveCursor, DownLineMiddle) {
    text txt = create_text();
    load(txt, "test_file.txt");
    txt->cursor->line = txt->cursor->line->previous;
    txt->cursor->position = strlen(txt->cursor->line->contents);

    int opos = txt->cursor->position;
    _node* oline = txt->cursor->line;

    move_cursor(txt, DOWN);
    ASSERT_EQ(txt->cursor->line, oline->next);
    ASSERT_LE(txt->cursor->position, opos);
}

TEST(MoveCursor, DownLineEnd) {
    text txt = create_text();
    load(txt, "test_file.txt");

    int opos = txt->cursor->position;
    _node* oline = txt->cursor->line;

    testing::internal::CaptureStderr();
    move_cursor(txt, DOWN);
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ("Can't move cursor that direction\n", output); 
}

TEST(MoveCursor, UpLineMiddle) {
    text txt = create_text();
    load(txt, "test_file.txt");

    int opos = txt->cursor->position;
    _node* oline = txt->cursor->line;

    move_cursor(txt, UP);
    ASSERT_EQ(txt->cursor->line, oline->previous);
    ASSERT_LE(txt->cursor->position, opos);
}

TEST(MoveCursor, UpLineEnd) {
    text txt = create_text();
    load(txt, "test_file.txt");

    txt->cursor->position = 0;
    txt->cursor->line = txt->begin;

    testing::internal::CaptureStderr();
    move_cursor(txt, UP);
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ("Can't move cursor that direction\n", output); 
}