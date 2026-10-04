#define BOOST_TEST_MODULE CamonTest
#include <boost/test/included/unit_test.hpp>
#include "Header.h"
#include <vector>

BOOST_AUTO_TEST_CASE(BorderlineValues_3) {
    auto res = fun(3);
    BOOST_TEST(res.size() == 1);
    BOOST_TEST(res[0] == 3);
}

BOOST_AUTO_TEST_CASE(BorderlineValues_7) {
    auto res = fun(7);
    BOOST_TEST(res.size() == 2);
    BOOST_TEST(res[0] == 3);
    BOOST_TEST(res[1] == 7);
}

BOOST_AUTO_TEST_CASE(BorderlineValues_30) {
    auto res = fun(30);
    BOOST_TEST(res.size() == 2);
    BOOST_TEST(res[0] == 3);
    BOOST_TEST(res[1] == 7);
}

BOOST_AUTO_TEST_CASE(BorderlineValues_31) {
    auto res = fun(31);
    BOOST_TEST(res.size() == 3);
    BOOST_TEST(res[0] == 3);
    BOOST_TEST(res[1] == 7);
    BOOST_TEST(res[2] == 31);
}

BOOST_AUTO_TEST_CASE(BorderlineValues_127) {
    auto res = fun(127);
    BOOST_TEST(res.size() == 4);
    BOOST_TEST(res[0] == 3);
    BOOST_TEST(res[1] == 7);
    BOOST_TEST(res[2] == 31);
    BOOST_TEST(res[3] == 127);
}

BOOST_AUTO_TEST_CASE(BorderlineValues_128) {
    auto res = fun(128);
    BOOST_TEST(res.size() == 4);
    BOOST_TEST(res[0] == 3);
    BOOST_TEST(res[1] == 7);
    BOOST_TEST(res[2] == 31);
    BOOST_TEST(res[3] == 127);
}

BOOST_AUTO_TEST_CASE(ReturnEmptyVector) {
    BOOST_TEST(fun(1).empty());
    BOOST_TEST(fun(2).empty());
    BOOST_TEST(fun(0).empty());
    BOOST_TEST(fun(-100).empty());
}


BOOST_AUTO_TEST_CASE(Symmetry) {
    BOOST_TEST(fun(100) == fun(100));
    BOOST_TEST(fun(255) == fun(255));
}


BOOST_AUTO_TEST_CASE(LessThanN) {
    int n = 1000000;
    std::vector<int> result = fun(n);

    for (const auto& elem : result) {
        BOOST_TEST(elem <= n);
    }
}


BOOST_AUTO_TEST_CASE(SubsetProperty) {
    int less = 70;
    int big = 150;
    std::vector<int> resLess = fun(less);
    std::vector<int> resBig = fun(big);

    BOOST_TEST(resLess.size() <= resBig.size());

    for (size_t i = 0; i < resLess.size(); ++i) {
        BOOST_TEST(resLess[i] == resBig[i]);
    }
}


BOOST_AUTO_TEST_CASE(NoDuplicates) {
    std::vector<int> res = fun(1000);

    for (size_t i = 0; i < res.size(); ++i) {
        for (size_t j = i + 1; j < res.size(); ++j) {
            BOOST_TEST(res[i] != res[j]);
        }
    }
}

BOOST_AUTO_TEST_CASE(AscendingOrder) {
    std::vector<int> res = fun(1000);

    for (size_t i = 1; i < res.size(); ++i) {
        BOOST_TEST(res[i - 1] < res[i]);
    }
}