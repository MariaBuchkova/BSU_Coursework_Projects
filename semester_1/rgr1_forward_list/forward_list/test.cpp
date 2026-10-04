#include "catch.hpp"

#include "forward_list_impl.h"

#include <forward_list>
#include <list>
#include <type_traits>
#include <algorithm>
#include <sstream>


void CheckLists(const ForwardList& actual, const std::forward_list<int32_t>& expected) {
    ForwardList::ForwardListIterator actual_it = actual.begin();
    std::forward_list<int32_t>::const_iterator expected_it = expected.begin();
    for (; actual_it != actual.end() && expected_it != expected.cend();
         ++actual_it, ++expected_it) {
        REQUIRE(*actual_it == *expected_it);
    }
    CHECK((actual_it == actual.end() && expected_it == expected.cend()));
}


TEST_CASE("Fool", "[forward_list]") {
    INFO("Don't use std::forward_list or std::list, cheater!")
    STATIC_REQUIRE_FALSE(std::is_same_v<std::forward_list<int32_t>, ForwardList>);
    STATIC_REQUIRE_FALSE(std::is_base_of_v<std::forward_list<int32_t>, ForwardList>);
    STATIC_REQUIRE_FALSE(std::is_same_v<std::list<int32_t>, ForwardList>);
    STATIC_REQUIRE_FALSE(std::is_base_of_v<std::list<int32_t>, ForwardList>);
}


TEST_CASE("ForwardList has ctors", "[forward_list]") {
    STATIC_REQUIRE(std::is_default_constructible_v<ForwardList>);

    SECTION("Default ctor") {
        ForwardList a;
        REQUIRE(a.Size() == 0u);
        CheckLists(a, std::forward_list<int32_t>());
    }

    SECTION("User-defined ctor") {
        ForwardList a(10, 1);
        REQUIRE(a.Size() == 10u);
        CheckLists(a, std::forward_list<int32_t>(10, 1));
    }

    SECTION("Initializer list ctor") {
        ForwardList a{1, 2, 3, 4, 5};
        REQUIRE(a.Size() == 5u);
        CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 4, 5});
    }
}


TEST_CASE("Simple push/pop", "[forward_list]") {

    {
        ForwardList a{1};
        REQUIRE(a.Size() == 1u);
        REQUIRE(a.Front() == 1);
        CheckLists(a, std::forward_list<int32_t>{1});

        a.PushFront(2);
        REQUIRE(a.Size() == 2u);
        REQUIRE(a.Front() == 2);
        CheckLists(a, std::forward_list<int32_t>{2, 1});

        a.PopFront();
        REQUIRE(a.Size() == 1u);
        REQUIRE(a.Front() == 1);
        CheckLists(a, std::forward_list<int32_t>{1});
    }

    {
        ForwardList a{1, 2, 3, 1, 5, 1};
        CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 1, 5, 1});

        a.PopFront();
        a.PopFront();
        a.PopFront();
        CheckLists(a, std::forward_list<int32_t>{1, 5, 1});
    }
}


TEST_CASE("Advance push/pop", "[forward_list]") {
    {
        ForwardList a;
        for (int32_t i = 0; i < 100000; ++i) {
            a.PushFront(i);
        }
        for (int32_t i = 0; i < 99999; ++i) {
            a.PopFront();
        }
        CheckLists(a, std::forward_list<int32_t>{0});
        a.PopFront();
        CheckLists(a, std::forward_list<int32_t>());
    }

    {
        ForwardList a;
        for (int32_t i = 0; i < 100000; ++i) {
            a.PushFront(i);
            a.PopFront();
        }
        CheckLists(a, std::forward_list<int32_t>());
    }
}


TEST_CASE("Copying", "[forward_list]") {
    STATIC_REQUIRE(std::is_copy_constructible_v<ForwardList>);
    
    ForwardList a{1, 2, 3, 4, 5, 6, 7};
    CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6, 7});

    a = a;
    CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6, 7});

    ForwardList b = a;
    REQUIRE(b.Size() == 7u);
    REQUIRE(b.Front() == a.Front());
    REQUIRE(b.FindByValue(5));
    REQUIRE_FALSE(b.FindByValue(10));
    CheckLists(b, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6, 7});

    ForwardList c;
    c = b;
    REQUIRE(c.Size() == 7u);
    REQUIRE(c.Front() == a.Front());
    REQUIRE(c.FindByValue(5));
    REQUIRE_FALSE(c.FindByValue(10));
    CheckLists(c, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6, 7});
}


TEST_CASE("Clear", "[forward_list]") {
    ForwardList a;
    a.Clear();
    REQUIRE(a.Size() == 0u);
    CheckLists(a, std::forward_list<int32_t>());

    ForwardList b{1, 2, 3, 4, 5, 6};
    REQUIRE(b.Size() == 6u);
    CheckLists(b, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6});

    b.Clear();
    REQUIRE(a.Size() == 0u);
    CheckLists(a, std::forward_list<int32_t>());
}


TEST_CASE("Iterator basics", "[forward_list]") {
    // simple iterator tests
    ForwardList a{1, 2, 3, 4, 5, 6};

    ForwardList::ForwardListIterator it = a.begin();
    REQUIRE(*it == 1);
    REQUIRE(*(it.operator->()) == 1);
    ++it;
    REQUIRE(*it == 2);
    REQUIRE(*(it.operator->()) == 2);

    ForwardList::ForwardListIterator it2 = a.begin();
    it2++;
    REQUIRE(*it2 == 2);
    REQUIRE(*(it.operator->()) == 2);
    REQUIRE(it == it2);

    ForwardList::ForwardListIterator it3 = a.begin();
    REQUIRE(it != it3);
    REQUIRE(it2 != it3);
}


TEST_CASE("Modifications with iterators", "[forward_list]") {

    ForwardList a{1, 3, 5};
    *(a.begin().operator->()) = 3;
    *((++a.begin()).operator->()) = 4;

    CheckLists(a, std::forward_list<int32_t>{3, 4, 5});
    ForwardList::ForwardListIterator it = a.begin();
    ++it;
    REQUIRE(*it == 4);
}


TEST_CASE("Iterator loop", "[forward_list]") {

    ForwardList a{1, 2, 3, 4, 5, 6};

    ForwardList::ForwardListIterator it = a.begin();
    ++it;

    // std::copy test
    std::stringstream sstream;
    std::copy(it, a.end(), std::ostream_iterator<int32_t>(sstream));
    REQUIRE(sstream.str() == "23456");

    sstream.str("");

    // for-loop
    for (auto iter = a.begin(); iter != a.end(); ++iter) {
        sstream << *iter;
    }
    REQUIRE(sstream.str() == "123456");

    sstream.str("");

    // for-each
    for (int32_t item : a) {
        sstream << item;
    }
    REQUIRE(sstream.str() == "123456");

    CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6});
}


TEST_CASE("Remove(single elements)", "[forward_list]") {
    ForwardList a{1, 2, 3, 4, 5, 6};
    CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6});

    a.Remove(4);
    REQUIRE(a.Size() == 5u);
    REQUIRE(a.Front() == 1);
    CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 5, 6});

    a.Remove(1);
    REQUIRE(a.Size() == 4u);
    REQUIRE(a.Front() == 2);
    CheckLists(a, std::forward_list<int32_t>{2, 3, 5, 6});

    a.Remove(6);
    REQUIRE(a.Size() == 3u);
    REQUIRE(a.Front() == 2);
    CheckLists(a, std::forward_list<int32_t>{2, 3, 5});
}


TEST_CASE("Remove(repeated elements)", "[forward_list]")    {
    ForwardList a{1, 1, 1, 2, 5, 1, 8, 1};
    REQUIRE(a.Size() == 8u);
    CheckLists(a, std::forward_list<int32_t>{1, 1, 1, 2, 5, 1, 8, 1});

    a.Remove(1);
    REQUIRE(a.Size() == 3u);
    CheckLists(a, std::forward_list<int32_t>{2, 5, 8});
}


TEST_CASE("Output", "[forward_list]") {
    {
        ForwardList a;
        REQUIRE(a.Size() == 0u);
        CheckLists(a, std::forward_list<int32_t>{});

        std::stringstream sstream;
        a.Print(sstream);
        REQUIRE(sstream.str().empty());
    }

    {
        ForwardList a{6};
        REQUIRE(a.Size() == 1u);
        CheckLists(a, std::forward_list<int32_t>{6});

        std::stringstream sstream;
        a.Print(sstream);
        REQUIRE(sstream.str() == "6");
    }

    {
        ForwardList a{1, 2, 3, 4, 5, 6};
        REQUIRE(a.Size() == 6u);
        CheckLists(a, std::forward_list<int32_t>{1, 2, 3, 4, 5, 6});

        std::stringstream sstream;
        a.Print(sstream);
        REQUIRE(sstream.str() == "1 2 3 4 5 6");
    }
}
