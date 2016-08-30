#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>



// returns a std::vector containing (num_elements) unique numbers from [left, right) which return true for valid_number()
// Complexity
//  Let [good] = number of valid elements from [right, left) and [bad] number of non valid elements from [right, left)
//  Memory O(num_elements)
//  Time O(unordered_map_lookup * (good + bad) * (HarmonicNumber(good) - HarmonicNumber(good - num_elements))
//  eg: for bad=0, num_elements=good / 2 it's ~ O(unordered_map_lookup * num_elements * ln(2))
template<typename Type=int>
std::vector<Type> UniqueNumbers(Type left, Type right, Type num_elements, const std::function<bool(Type)>& valid_number);

// returns a std::vector containing (num_elements) unique numbers from [0, right) which return true for valid_number()
template<typename Type=int>
std::vector<Type> UniqueNumbers(Type right, Type num_elements, const std::function<bool(int)>& valid_number);

// returns a std::vector containing (num_elements) unique numbers from [left, right)
template<typename Type=int>
std::vector<Type> UniqueNumbers(Type left, Type right, Type num_elements);

// returns a std::vector containing (num_elements) unique numbers from [0, right)
template<typename Type=int>
std::vector<Type> UniqueNumbers(Type right, Type num_elements);



// [WARNING] Does not yield
// just like python's range
// returns a std::vector with numbers from [left, right) eg: [left, left + step, left + 2 * step)
template <typename Type=int>
std::vector<Type> Range(Type left, Type right, Type step=1);

// [Range] with left=0, step=1
template <typename Type=int>
std::vector<Type> Range(Type right);



// splits [num_elements] into [num_buckets]
struct Partition {
    // a random split, from all C(num_elements + num_buckets - 1, num_buckets - 1) for min_val = 0
    static std::vector<int> Uniform(int num_elements, int num_buckets, int min_val);
};

// Random Utils below :)

template<typename Type>
Type Rand();

template<typename Type=int>
Type Rand(Type left, Type right);

// returns random numbers from [left, right), number i having the chx = 1/i
template<typename Type=int>
Type RandLog(Type left, Type right);


std::vector<int> RandomPermutation(int num_elements, int start_element=0);

// good deterministic random shuffle
template <typename LinearIterator>
void RandomShuffle(LinearIterator begin,LinearIterator end);

template<typename Container>
void RandomShuffle(Container& container);

class UniqueWordGenerator {
  public:
    UniqueWordGenerator(std::function<int(void)> word_len_generator, const std::vector<char>& sigma=Range<char>('a', 'z'+1));

    std::string RandomString();

  private:
    std::function<int(void)>& word_len_generator;
    std::vector<char> sigma;
    std::map<std::string, bool> selected;
};

#include "generator_utils_implementation.hpp"
