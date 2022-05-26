#include <gtest/gtest.h>
extern "C" {
    #include "../text/_text.h"
    #include "../text/text.h"
    #include "../common.h"
}
// Demonstrate some basic assertions.

TEST(SaveTest, SavingText) {
    text txt1 = create_text();
    load(txt1, "test_file.txt");

    save(txt1, "out_file.txt");

    text txt2 = create_text();
    load(txt2, "out_file.txt");

    ASSERT_EQ(txt1->length, txt2->length);
    _node* cur1 = txt1->begin;
    _node* cur2 = txt2->begin;
    while(cur1 && cur2) {
        ASSERT_STREQ(cur1->contents, cur2->contents);
        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    free(txt1);
    free(txt2);
}

TEST(SaveTest, EmptyTxt) {
    text txt = create_text();
    testing::internal::CaptureStderr();
    save(txt, "fileoutput.txt");
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ("There are already no any lines in the text!\n", output); 
    free(txt);
}

TEST(McbTest, Rightness) { // essentially also an move_cursor test
    text txt = create_text();
    load(txt, "test_file.txt");

    _crsr crsr;
    crsr.line = txt->cursor->line;
    crsr.position = txt->cursor->position;

    testing::internal::CaptureStderr();
    mcb(txt);
    std::string output = testing::internal::GetCapturedStderr();

    _node* cur = txt->begin;
    while(cur) {
        for(int i = strlen(txt->cursor->line->contents); i >= 0; i--) {
            if (crsr.line->previous == txt->cursor->line) {
                if (crsr.position == 0 && txt->cursor->position == strlen(txt->cursor->line->contents)){
                    SUCCEED();
                } else if (crsr.position - txt->cursor->position == 1) {
                    SUCCEED();
                } else if (output == "Can't move cursor that direction\n" or  output == "No lines!!\n") {
                    SUCCEED();
                } else {
                    FAIL();
                }
            }
        }
        cur = cur->next;
    }
    free(txt);
}

TEST(RtTest, Rightness) { // essentially also an remove_last_line test
    text txt = create_text();
    load(txt, "test_file.txt");
    size_t len = 0 ;
    _node* cur = txt->begin;
    while (cur) {
        len++;
        cur = cur->next;
    }
    _node* end = txt->end;
    _node* new_end = txt->end->previous;
    rt(txt);
    ASSERT_EQ(txt->end, new_end);
    ASSERT_EQ(txt->end->next, (_node*)NULL);
    ASSERT_EQ(txt->length+1, len);
    free(txt);
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
