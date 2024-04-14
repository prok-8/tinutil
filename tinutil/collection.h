/* SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later */

/**
 * @file collection.h
 * Simple functions and templates for querying and modifying stl collections.
 * Mostly convenience wrappers around stl functions.
 */

#pragma once

#include <algorithm>
#include <concepts>
#include <type_traits>

namespace tinutil {

/**
 * Checks if a collection contains an item.
 * Convenience wrapper around @c "std::find".
 * @tparam TItem Collection item type.
 * @tparam TItr Collection iterator type.
 * @param begin Begin iterator.
 * @param end End iterator.
 * @param item Item to check.
 * @return @c True, if item is found in the collection, @c false otherwise.
 */
template<typename TItem, typename TItr>
bool Contains(TItr begin, TItr end, const TItem item) {
	return std::find(begin, end, item) != end;
}

/**
 * Checks if a collections contains an item.
 * Convenience wrapper around @c "std::find".
 * @tparam TCollection Collection type.
 * @param collection Collection.
 * @param item Item to check.
* @return @c True, if item is found in the collection, @c false otherwise.
 */
template<typename TCollection>
bool Contains(const TCollection& collection, typename TCollection::const_reference item) {
	return Contains(collection.begin(), collection.end(), item);
}

/**
 * Finds the first item in the collection satisfying the predicate.
 * Convenience wrapper around @c "std::find_if".
 * @tparam TCollection Collection type.
 * @tparam TPredicate Predicate type.
 * @param collection Collection.
 * @param pred Predicate that must take a collection item and return @c bool.
 * @return Iterator, pointing to the found item.
 */
template<typename TCollection, typename TPredicate>
auto FindIf(TCollection& collection, TPredicate pred) {
	return std::find_if(collection.begin(), collection.end(), pred);
}

/**
 * Checks if all items in a collection satisfy a condition.
 * Convenience wrapper around @c "std::all_of".
 * @tparam TCollection Collection type.
 * @tparam TPredicate Predicate type.
 * @param collection Collection.
 * @param pred Predicate that must take a collection item and return @c bool.
 * @return @c True, if all items satisfy predicate, @c false otherwise.
 */
template<typename TCollection, typename TPredicate>
bool AllOf(TCollection& collection, TPredicate pred) {
	return std::all_of(collection.begin(), collection.end(), pred);
}

/**
 * Checks if any item in a collection satisfy a condition.
 * Convenience wrapper around @c "std::any_of".
 * @tparam TCollection Collection type.
 * @tparam TPredicate Predicate type.
 * @param collection Collection.
 * @param pred Predicate that must take a collection item and return @c bool.
 * @return @c True, if any item satisfies predicate, @c false otherwise.
 */
template<typename TCollection, typename TPredicate>
bool AnyOf(TCollection& collection, TPredicate pred) {
	return std::any_of(collection.begin(), collection.end(), pred);
}

/**
 * Erases all occurances of item in a collection.
 * Convenience wrapper around @c "std::erase".
 * @tparam TCollection Collection type.
 * @param collection Collection
 * @param item Item to erase.
 * @return Iterator folowing the erased element.
 */
template<typename TCollection>
auto Erase(TCollection& collection, typename TCollection::value_type item) {
	auto itr = std::find(collection.begin(), collection.end(), item);
	return collection.erase(itr);
}

/**
 * Inserts the item before the first item in the collection, which satisfies the compare function.
 * @tparam TCollection Collection type.
 * @tparam TCompare Compare function type.
 * @param collection Collection to insert into.
 * @param item Item to insert.
 * @param compareFn Function to compare the item with items in the collection.
 * It takes two arguments of collection's item type.
 * First argument is for the item to be inserted, second is for the item from the collection.
 * @return
 */
template<typename TCollection, typename TCompare>
typename TCollection::iterator InsertOrdered(TCollection& collection, typename TCollection::value_type item, TCompare compareFn) {
	auto it = FindIf(collection, [&](const typename TCollection::value_type& x) { return compareFn(item, x); });
	return collection.insert(it, item);
}

}