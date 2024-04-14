/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

#include "tinutil/collection.h"

#include <vector>
#include "gtest/gtest.h"

TEST(Collection, Contains1) {
    std::vector<int> v{1, 2, 3, 4};
    EXPECT_TRUE(tinutil::Contains(v.begin() + 1, v.end() - 1, 2));
    EXPECT_FALSE(tinutil::Contains(v.begin() + 1, v.end() - 1, 1));
}

TEST(Collection, Contains2) {
    std::vector<int> v{1, 2, 3, 4};
    EXPECT_TRUE(tinutil::Contains(v, 2));
    EXPECT_FALSE(tinutil::Contains(v, 10));
}

TEST(Collection, FindIf) {
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    EXPECT_TRUE(tinutil::FindIf(v, [](int x){ return x > 3; }) == v.begin() + 3);
}

TEST(Collection, AllOf) {
    std::vector<int> v{1, 2, 3, 4, 5};
    EXPECT_TRUE(tinutil::AllOf(v, [](int x){ return x < 10; }));
    EXPECT_FALSE(tinutil::AllOf(v, [](int x) { return x < 4; }));
}

TEST(Collection, AnyOf) {
    std::vector<int> v{1, 2, 3, 4, 5};
    EXPECT_TRUE(tinutil::AnyOf(v, [](int x){ return x > 3; }));
    EXPECT_FALSE(tinutil::AnyOf(v, [](int x){ return x > 10; }));
}

TEST(Collection, Erase) {
    std::vector<int> v{1, 2, 3, 4, 5};
    auto result = tinutil::Erase(v, 2);
    EXPECT_EQ(result, v.begin() + 1);
    EXPECT_EQ(v, (std::vector<int>{1, 3, 4, 5}));
}

TEST(Collection, InsertOrdered) {
    std::vector<int> v{1, 2, 4, 5};
    auto result = tinutil::InsertOrdered(v, 3, [](int a, int b){ return a < b; });
    EXPECT_EQ(result, v.begin() + 2);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 4, 5}));
}