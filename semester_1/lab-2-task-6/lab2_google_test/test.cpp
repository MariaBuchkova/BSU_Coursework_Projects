#include "pch.h"
#include "../lab-2-task-6/Header.h"

TEST(CamonTest, BorderlineValues) {
    EXPECT_EQ(fun(3), (std::vector<int>{3}));
    EXPECT_EQ(fun(7), (std::vector<int>{3, 7}));
    EXPECT_EQ(fun(31), (std::vector<int>{3, 7, 31}));
    EXPECT_EQ(fun(127), (std::vector<int>{3, 7, 31, 127}));
}
TEST(CamonTest, RerurnEmptyVector) {
    EXPECT_TRUE(fun(1).empty());
    EXPECT_TRUE(fun(2).empty());
    EXPECT_TRUE(fun(0).empty());
    EXPECT_TRUE(fun(-100).empty());
}

TEST(CamonTest, Symmetry) {
    EXPECT_EQ(fun(100), fun(100));
    EXPECT_EQ(fun(255), fun(255));
}

TEST(CamonTest, NoDuplicates) {
    std::vector<int> res = fun(1000);

    for (size_t i = 0; i < res.size(); ++i) {
        for (size_t j = i + 1; j < res.size(); ++j) {
            EXPECT_NE(res[i], res[j]);
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}