#include <gtest/gtest.h>
#include <sys/file.h>
extern "C" {
    #include "../src/text/_text.h"
    #include "../src/text/text.h"
    #include "../src/common.h"
}

TEST(McbTest, LineEnd) { // essentially also an move_cursor test
    text txt = create_text();

    txt->length = 1;

    _node* nd = new _node();

    nd->previous = NULL;
    nd->next = NULL;
    nd->contents[0] = 'a'; 
    nd->contents[1] = 'b'; 
    nd->contents[2] = 'c';
    nd->contents[3] = 'd'; 
    nd->contents[4] = '\0';
//                cursor pos 4 is here:^
    txt->begin = nd;
    txt->end = nd;

    txt->cursor = new _crsr();

    txt->cursor->line = nd;
    txt->cursor->position = 4;

    mcb(txt);
    ASSERT_EQ(txt->cursor->position, 3);
}

TEST(McbTest, LineMiddle) { // essentially also an move_cursor test
    text txt = create_text();
    
    txt->length = 1;

    _node* nd = new _node();

    nd->previous = NULL;
    nd->next = NULL;
    nd->contents[0] = 'a'; 
    nd->contents[1] = 'b'; 
    nd->contents[2] = 'c';
    nd->contents[3] = 'd'; 
    nd->contents[4] = '\0';
//       cursor pos 2 is here:^
    txt->begin = nd;
    txt->end = nd;

    txt->cursor = new _crsr();

    txt->cursor->line = nd;
    txt->cursor->position = 2;

    mcb(txt);
    ASSERT_EQ(txt->cursor->position, 1);
}

TEST(McbTest, LineStart) { // essentially also an move_cursor test
    text txt = create_text();

    _node* nd = new _node();
    _node* nd1 = new _node();

    txt->length = 2;

    nd->previous = NULL;
    nd->next = nd1;
    nd->contents[0] = 'a'; 
    nd->contents[1] = 'b'; 
    nd->contents[2] = 'c';
    nd->contents[3] = 'd'; 
    nd->contents[4] = '\0';
// cursor pos 0    :^

    nd1->previous = nd;
    nd1->next = NULL;
    nd1->contents[0] = 'a'; 
    nd1->contents[1] = 'b'; 
    nd1->contents[2] = 'c';
    nd1->contents[3] = 'd'; 
    nd1->contents[4] = '\0';

    txt->begin = nd;
    txt->end = nd1;

    txt->cursor = new _crsr();

    txt->cursor->line = nd1;
    txt->cursor->position = 0;

    mcb(txt);
    ASSERT_EQ(txt->cursor->position, 4);
    ASSERT_EQ(txt->cursor->line, nd);
}

TEST(McbTest, EmptyTxt) {
    text txt = create_text();
    testing::internal::CaptureStderr();
    mcb(txt);
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ("No lines in the text\n", output); 
}

TEST(McbTest, NullTxt) { // essentially also an remove_last_line test
    testing::internal::CaptureStderr();
    mcb(NULL);
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ("No text\n", output); 
}

