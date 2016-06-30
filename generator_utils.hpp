#pragma once

#include <functional>
#include <vector>

template<typename T>
T Rand();

std::vector<int> RandomPermutation(int num_elements, int start_element=0);

// good deterministic random shuffle
template <typename LinearIterator>
void RandomShuffle(LinearIterator begin,LinearIterator end);

template<typename Container>
void RandomShuffle(Container& container);



// returns a std::vector containing (num_elements) unique numbers from [left, right) which return true for valid_number()
// Complexity
//  Let [good] = number of valid elements from [right, left) and [bad] number of non valid elements from [right, left)
//  Memory O(num_elements)
//  Time O(unordered_map_lookup * (good + bad) * (HarmonicNumber(good) - HarmonicNumber(good - num_elements))
//  eg: for bad=0, num_elements=good / 2 it's ~ O(unordered_map_lookup * num_elements * ln(2))
std::vector<int> UniqueNumbers(int left, int right, int num_elements, const std::function<bool(int)>& valid_number);

// returns a std::vector containing (num_elements) unique numbers from [0, right) which return true for valid_number()
std::vector<int> UniqueNumbers(int right, int num_elements, const std::function<bool(int)>& valid_number);

// returns a std::vector containing (num_elements) unique numbers from [left, right)
std::vector<int> UniqueNumbers(int left, int right, int num_elements);

// returns a std::vector containing (num_elements) unique numbers from [0, right)
std::vector<int> UniqueNumbers(int right, int num_elements);



// [WARNING] Does not yield
// just like python's range
// returns a std::vector with numbers from [left, right) eg: [left, left + step, left + 2 * step)
std::vector<int> Range(int left, int right, int step=1);

// [Range] with left=0, step=1
std::vector<int> Range(int right);



// splits [num_elements] into [num_buckets]
struct Partition {
    // a random split, from all C(num_elements + num_buckets - 1, num_buckets - 1) for min_val = 0
    static std::vector<int> Uniform(int num_elements, int num_buckets, int min_val);
};

#include "generator_utils_implementation.hpp"