/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

#include "tinutil/util.h"

#include <type_traits>
#include "gtest/gtest.h"

enum class TestEnum {
	kElem1 = 0,
	kElem2,
	kElem3,
};

enum class TestFlagEnum {
	kFlag1 = 1 << 0,
	kFlag2 = 1 << 1,
	kFlag3 = 1 << 2,
	kFlag4 = 1 << 4,
};

template<typename First, typename ... T>
auto CombineFlags(First&& first, T&& ... t) {
    return static_cast<First>(std::underlying_type_t<First>(first) | (static_cast<std::underlying_type_t<First>>(t) | ...));
}

TEST(Util, UnderlyingType) {
	auto x = tinutil::UnderlyingType(TestEnum::kElem1);
	EXPECT_EQ(x, 0);
}

TEST(Util, HasAnyFlag) {
	TestFlagEnum e = CombineFlags(TestFlagEnum::kFlag1, TestFlagEnum::kFlag2);
	EXPECT_TRUE(tinutil::HasAnyFlag(e, TestFlagEnum::kFlag1));
	EXPECT_FALSE(tinutil::HasAnyFlag(e, TestFlagEnum::kFlag3));
	EXPECT_TRUE(tinutil::HasAnyFlag(e, CombineFlags(TestFlagEnum::kFlag1, TestFlagEnum::kFlag3)));
	EXPECT_FALSE(tinutil::HasAnyFlag(e, CombineFlags(TestFlagEnum::kFlag3, TestFlagEnum::kFlag4)));
}

TEST(Util, IsIn) {
	EXPECT_TRUE(tinutil::IsIn(1, 5, 4, 1, 6));
	EXPECT_FALSE(tinutil::IsIn(1, 5, 4, 2, 6));
}

TEST(Util, VariantCompare) {
	std::variant<int, float, bool> v = 12;
	EXPECT_TRUE(tinutil::VariantCompare(v, 12));
	EXPECT_FALSE(tinutil::VariantCompare(v, 15));
	EXPECT_FALSE(tinutil::VariantCompare(v, false));
}