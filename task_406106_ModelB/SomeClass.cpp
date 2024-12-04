#include <gtest/gtest.h>

// Example class with a potential memory leak
class SomeClass {
public:
    SomeClass() {
        data = new int[1024]; // Potential memory leak if not deallocated
    }
    ~SomeClass() {
        // Remember to delete this memory
        delete[] data;
    }

private:
    int* data;
};

TEST(MyTestFixture, TestSomething) {
    {
        SomeClass obj; // Node constructor is called here 
        // Test logic here
    }
    // Object goes out of scope here, and its destructor is called if destruction happens then no leak will be detected
    EXPECT_TRUE(::testing::UnitTest::GetInstance()->leak_detection_enabled());
}