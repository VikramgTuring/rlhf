class MyTest : ::testing::Test
{
  protected:
    // Because we call GTEST_CHECK_LEAKS_INIT(),
    // members defined earlier than the constructor
    // will be leak-checked.
    const std::string sentence = "quick brown fox";
    MyClassUnderTest obj_;

    void SetUp() override { 
        // Add any test setup logic here
    }
    void TearDown() override { 
        // Add any test teardown logic here 
    }

    TEST(MyTest, MemoryLeakTest) {
        // Your test code goes here
    }
};