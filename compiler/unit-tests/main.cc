#include <gtest/gtest.h>

char* g_ProgramName = const_cast<char*>("");

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
