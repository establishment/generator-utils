#pragma once

#include <vector>

// [WARNING] Does not yield
// just like python's range
// returns a std::vector with numbers from [left, right) eg: [left, left + step, left + 2 * step)
template <typename Type>
std::vector<Type> Range(Type left, Type right, Type step);

template <typename Type>
std::vector<Type> Range(Type left, Type right);

// [Range] with left=0, step=1
template <typename Type>
std::vector<Type> Range(Type right);

template <typename Type>
std::vector<Type> xRange(Type left, Type right, Type step);

template <typename Type>
std::vector<Type> xRange(Type left, Type right);

template <typename Type>
std::vector<Type> xRange(Type right);

// good deterministic random shuffle
template <typename LinearIterator>
void RandomShuffle(LinearIterator begin, LinearIterator end);

template <typename Container>
Container& RandomShuffle(Container& container);

template <typename Container>
Container&& RandomShuffle(Container&& container);

// Sort
template <typename LinearIterator>
void Sort(LinearIterator begin, LinearIterator end);

template <typename Container>
Container& Sort(Container& container);

template <typename Container>
Container&& Sort(Container&& container);

// Reverse
template <typename LinearIterator>
void Reverse(LinearIterator begin, LinearIterator end);

template <typename Container>
Container& Reverse(Container& container);

template <typename Container>
Container&& Reverse(Container&& container);

// Unique - sort, unique, resize, return
template <typename Container>
Container& Unique(Container& container);

template <typename Container>
Container&& Unique(Container&& container);

#include "utils_implementation.hpp"
