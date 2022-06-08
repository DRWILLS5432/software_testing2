#include <gtest/gtest.h>
extern "C" {
    #include "../src/text/_text.h"
    #include "../src/text/text.h"
    #include "../src/common.h"
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
}

TEST(RtTest, EmptyTxt) { // essentially also an remove_last_line test
    text txt = create_text();
    testing::internal::CaptureStderr();
    rt(txt);
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ("This line doesn't exist\n", output); 
}

TEST(RtTest, NullTxt) { // essentially also an remove_last_line test
    testing::internal::CaptureStderr();
    rt(NULL);
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ("The text doesn't exist!\n", output); 
}

TEST(RtTest, CursorTest) { // essentially also an remove_last_line test
    text txt = create_text();
    load(txt, "test_file.txt");
    rt(txt);
    if (txt->cursor->line != txt->end && txt->cursor->position > strlen(txt->end->contents)) {
        FAIL();
    } else {
        SUCCEED();
    }
}

TEST(RtTest, OneLine) {
    text txt = create_text();
    load(txt, "oneliner.txt");
    rt(txt);
    if (txt->begin == NULL && txt->end == NULL && txt->cursor->line == NULL && txt->cursor->position == -1) {
        SUCCEED();
    } else {
        FAIL();
    }
}