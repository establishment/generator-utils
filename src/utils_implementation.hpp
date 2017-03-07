#pragma once

#include "utils.hpp"

#include <algorithm>
#include <vector>
#include <memory>

template <typename Type>
std::vector<Type> Range(Type left, Type right, Type step) {
    assert(step != static_cast<Type>(0));
    
    if (left == right) {
        return {};
    }

    std::vector<Type> result;

    if (step > static_cast<Type>(0)) {
        assert(left <= right);
        result.reserve((right - left) / step);
        for (Type itr = left; itr < right; itr += step) {
            result.push_back(itr);
        }
    } else {
        assert(left >= right);
        result.reserve((right - left) / step);
        for (Type itr = left; itr > right; itr += step) {
            result.push_back(itr);
        }
    }

    return result;
};

template <typename Type>
std::vector<Type> xRange(Type left, Type right, Type step) {
    return Range(left, static_cast<Type>(static_cast<Type>(1) + right), step);
}

template <typename Type>
std::vector<Type> Range(Type right) {
    return Range(static_cast<Type>(0), right, static_cast<Type>(1));
}

template <typename Type>
std::vector<Type> xRange(Type right) {
    return Range(static_cast<Type>(0), static_cast<Type>(static_cast<Type>(1) + right), static_cast<Type>(1));
}

template <typename Type>
std::vector<Type> Range(Type left, Type right) {
    return Range(left, right, static_cast<Type>(1));
}

template <typename Type>
std::vector<Type> xRange(Type left, Type right) {
    return Range(left, static_cast<Type>(static_cast<Type>(1) + right), static_cast<Type>(1));
}

// RandomShuffle
template <typename LinearIterator>
void RandomShuffle(LinearIterator begin, LinearIterator end) {
    int num_elements = std::distance(begin, end);
    for (int itr = 0; itr < num_elements; itr += 1) {
        int oth = rand() % (num_elements - itr) + itr;
        std::swap(*(begin + itr), *(begin + oth));
    }
}

template <typename Container>
Container& RandomShuffle(Container& container) {
    RandomShuffle(container.begin(), container.end());
    return container;
}

template <typename Container>
Container&& RandomShuffle(Container&& container) {
    RandomShuffle(container.begin(), container.end());
    return std::move(container);
}

// Sort
template <typename LinearIterator>
void Sort(LinearIterator begin, LinearIterator end) {
    std::sort(begin, end);
}

template <typename Container>
Container& Sort(Container& container) {
    std::sort(container.begin(), container.end());
    return container;
}

template <typename Container>
Container&& Sort(Container&& container) {
    std::sort(container.begin(), container.end());
    return std::move(container);
}

template <typename LinearIterator>
void Reverse(LinearIterator begin, LinearIterator end) {
    std::reverse(begin, end);
}

template <typename Container>
Container& Reverse(Container& container) {
    std::reverse(container.begin(), container.end());
    return container;
}

template <typename Container>
Container&& Reverse(Container&& container) {
    std::reverse(container.begin(), container.end());
    return std::move(container);
}

template <typename Container>
Container& Unique(Container& container) {
    Sort(container);
    container.resize(std::unique(container.begin(), container.end()) - container.begin());
    return container;
}

template <typename Container>
Container&& Unique(Container&& container) {
    Unique(container);
    return std::move(container);
}

