/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

/**
 * @file util.h
 * Miscellaneous utility functions and templates.
 */

#include <variant>

namespace tinutil {

/**
 * Casts an enum to it's underlying type.
 * @tparam T Must be an enum type.
 * @param e Enum value.
 * @return auto Enum value, cast to enum's underlying type.
 */
template<typename T>
auto UnderlyingType(T e) {
	return static_cast<std::underlying_type_t<decltype(e)>>(e);
}

/**
 * Checks if a flag enum value has a flag.
 * If the value is checked against multiple flags,
 * the function returns @c true if at least one flag matches.
 * @tparam T Must be a flag enum type.
 * @param val Enum value.
 * @param flags Flags to check against.
 * @return @c True if at least one flag matches, @c false otherwise.
 */
template<typename T>
typename std::enable_if_t<std::is_enum_v<T>, bool> HasAnyFlag(T val, T flags) {
	return (UnderlyingType(val) & UnderlyingType(flags)) != 0;
}

/**
 * Checks if a value matches any of the other passed values.
 * @tparam First Type of the value to check.
 * @tparam T Variadic type for all the values to check against.
 * @param first Value to check.
 * @param t All values to check against.
 * @return @c True if the value matches any other value, @c false otherwise.
 */
template<typename First, typename ... T>
bool IsIn(First&& first, T&& ... t) {
    return ((first == t) || ...);
}

/**
 * Checks if a variant matches a value.
 * Returns @c false if the variant doesn't hold a value.
 * @tparam TVariant Variant type.
 * @tparam TAlternative Type of variant to check.
 * @param var Variant to check.
 * @param alt Value to check against.
 * @return @c True if variant holds a value that matches @p alt, @c false otherwise.
 */
template<typename TVariant, typename TAlternative>
bool VariantCompare(const TVariant& var, const TAlternative& alt) {
	return std::holds_alternative<TAlternative>(var) && std::get<TAlternative>(var) == alt;
}

}