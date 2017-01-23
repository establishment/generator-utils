#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

/**** Basic Rand Utils ****/
template<typename Type=int>
Type Rand();

template<typename Type=int>
Type xRand();

template<typename Type>
Type Rand(Type left, Type right);

template<typename Type>
Type xRand(Type left, Type right);

// returns random numbers from [left, right), number i having the chx = 1/i
template<typename Type>
Type RandLog(Type left, Type right);

template<typename Type>
Type xRandLog(Type left, Type right);

// returns random numbers from [left, right)
// Maps [left, right) to [1, right - left + 1) and calls RandLog
template<typename Type>
Type RandLogScaled(Type left, Type right);

template<typename Type>
Type xRandLogScaled(Type left, Type right);

/**** Unique Numbers ****/
// returns a std::vector containing (num_elements) unique numbers from [left, right) which return true for valid_number()
// Complexity
//  Let [good] = number of valid elements from [right, left) and [bad] number of non valid elements from [right, left)
//  Memory O(num_elements)
//  Time O(unordered_map_lookup * (good + bad) * (HarmonicNumber(good) - HarmonicNumber(good - num_elements))
//  eg: for bad=0, num_elements=good / 2 it's ~ O(unordered_map_lookup * num_elements * ln(2))
template<typename Type>
std::vector<Type> UniqueNumbers(Type left, Type right, int num_elements, const std::function<bool(Type)>& valid_number);

template<typename Type>
std::vector<Type> xUniqueNumbers(Type left, Type right, int num_elements, const std::function<bool(Type)>& valid_number);

// returns a std::vector containing (num_elements) unique numbers from [0, right) which return true for valid_number()
template<typename Type>
std::vector<Type> UniqueNumbers(Type right, int num_elements, const std::function<bool(Type)>& valid_number);

template<typename Type>
std::vector<Type> xUniqueNumbers(Type right, int num_elements, const std::function<bool(Type)>& valid_number);

// returns a std::vector containing (num_elements) unique numbers from [left, right)
template<typename Type>
std::vector<Type> UniqueNumbers(Type left, Type right, int num_elements);

template<typename Type>
std::vector<Type> xUniqueNumbers(Type left, Type right, int num_elements);

// returns a std::vector containing (num_elements) unique numbers from [0, right)
template<typename Type>
std::vector<Type> UniqueNumbers(Type right, int num_elements);

template<typename Type>
std::vector<Type> xUniqueNumbers(Type right, int num_elements);

// equivalent to UniqueNumbers(start_element, num_elements + start_element);
std::vector<int> RandomPermutation(int num_elements, int start_element);

/**** Patitioning ****/
// splits [num_elements] into [num_buckets]
struct Partition {
    // a random split, from all C(num_elements + num_buckets - 1, num_buckets - 1) for min_val = 0
    static std::vector<int> Uniform(int num_elements, int num_buckets, int min_val);
};

/**** Strings ****/
class UniqueWordGenerator {
  public:
    UniqueWordGenerator(std::function<int(void)> word_len_generator, const std::vector<char>& sigma);

    std::string RandomString();

  private:
    std::function<int(void)> word_len_generator;
    std::vector<char> sigma;
    std::map<std::string, bool> selected;
};

#include "random_implementation.hpp"
