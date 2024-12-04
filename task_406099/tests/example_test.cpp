#include <gtest/gtest.h>
#include "../src/example.h"

TEST(ExampleTest, AddsTwoNumbers) {
    EXPECT_EQ(add_numbers(1, 2), 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}