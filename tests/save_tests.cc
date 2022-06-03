#include <gtest/gtest.h>
extern "C" {
    #include "../text/_text.h"
    #include "../text/text.h"
    #include "../common.h"
}

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
}

TEST(SaveTest, EmptyTxt) {
    text txt = create_text();
    testing::internal::CaptureStderr();
    save(txt, "out_file.txt");
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ("There are already no any lines in the text!\n", output); 
}

TEST(SaveTest, UnabilityToSave) {
    text txt = create_text();
    load(txt, "test_file.txt"); 
    testing::internal::CaptureStderr();
    save(txt, "no_access.txt");    
    std::string output = testing::internal::GetCapturedStderr();
    ASSERT_EQ("The file no_access.txt cannot be opened\n", output); 
}