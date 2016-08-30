#pragma once

#include <cassert>
#include <cstdlib>

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

template<typename Type>
std::vector<Type> UniqueNumbers(Type left, Type right, Type num_elements, const std::function<bool(Type)>& valid_number) {
    assert(left <= right);

    std::unordered_map<Type, bool> selected_numbers;

    std::vector<Type> result;
    result.reserve(num_elements);

    while (num_elements > 0) {
        int element = std::rand() % (right - left) + left;
        if (not selected_numbers[element] and valid_number(element)) {
            selected_numbers[element] = true;
            result.push_back(element);
            num_elements -= 1;
        }
    }

    return result;
};

template<typename Type>
std::vector<Type> UniqueNumbers(Type right, Type num_elements, const std::function<bool(int)>& valid_number) {
    return UniqueNumbers<Type>(0, right, num_elements, valid_number);
};

template<typename Type>
std::vector<Type> UniqueNumbers(Type left, Type right, Type num_elements) {
    assert(right - left >= num_elements);
    return UniqueNumbers<Type>(left, right, num_elements, [](Type) -> bool { return true; });
};

template<typename Type>
std::vector<Type> UniqueNumbers(Type right, Type num_elements) {
    assert(right >= num_elements);
    return UniqueNumbers<Type>(0, right, num_elements, [](Type) -> bool { return true; });
};

template <typename Type>
std::vector<Type> Range(Type left, Type right, Type step) {
    assert(step != 0);

    if (left == right) {
        return {};
    }

    std::vector<Type> result;

    if (step > 0) {
        assert(left <= right);
        result.reserve((right - left - 1) / step);
        for (Type itr = left; itr < right; itr += step) {
            result.push_back(itr);
        }
    } else {
        assert(left >= right);
        for (Type itr = left; itr > right; itr += step) {
            result.push_back(itr);
        }
    }

    return result;
};

template <typename Type>
std::vector<Type> Range(Type right) {
    return Range(0, right, 1);
}

std::vector<int> Partition::Uniform(int num_elements, int num_buckets, int min_val) {
    num_elements -= num_buckets * min_val;

    std::vector<int> delimiters = UniqueNumbers(0, num_elements + num_buckets - 1, num_buckets - 1);

    std::sort(delimiters.begin(), delimiters.end());

    delimiters.insert(delimiters.begin(), -1);
    delimiters.insert(delimiters.end(), num_elements + num_buckets - 1);

    std::vector<int> sizes;

    for (int i = 1; i <= num_buckets; i += 1) {
        sizes.push_back(delimiters[i] - delimiters[i - 1] - 1 + min_val);
    }

    return sizes;
};

// Random utils

template<>
int Rand<int>() {
    return rand();
}

template<>
long long Rand<long long>() {
    return 1LL * rand() * RAND_MAX + rand();
}

template<>
int Rand<int>(int left, int right) {
    if (left == right) { return 0; }
    long long x = 1LL * rand() * RAND_MAX + rand();
    x %= (long long)(right - left);
    x += left;
    return x;
}

template<>
long long Rand<long long>(long long left, long long right) {
    if (left == right) { return 0; }
    long long x = 1LL * rand() * RAND_MAX + rand();
    x %= (right - left);
    x += left;
    return x;
}

template<>
double Rand<double>(double left, double right) {
    long double x = (1.0 * rand() * RAND_MAX + rand()) / RAND_MAX / RAND_MAX;
    x *= (right - left);
    x += left;
    return (double)x;
}

template<>
long double Rand<long double>(long double left, long double right) {
    long double x = (1.0 * rand() * RAND_MAX + rand()) / RAND_MAX / RAND_MAX;
    x *= (right - left);
    x += left;
    return x;
}

template<typename Type>
Type RandLog(Type left, Type right) {
    double x = Rand<double>(std::log2(left), std::log2(right));
    Type r = std::pow(2, x);
    assert(left <= r);
    assert(r < right);
    return r;
}

std::vector<int> RandomPermutation(int num_elements, int start_element) {
    auto permutation = Range(start_element, num_elements + start_element);
    RandomShuffle(permutation);
    return permutation;
}

template <typename LinearIterator>
void RandomShuffle(LinearIterator begin,LinearIterator end) {
    int num_elements = std::distance(begin, end);
    for (int itr = 0; itr < num_elements; itr += 1) {
        int oth = rand() % (num_elements - itr) + itr;
        std::swap(*(begin + itr), *(begin + oth));
    }
};

template<typename Container>
void RandomShuffle(Container& container) {
    RandomShuffle(container.begin(), container.end());
};

UniqueWordGenerator::UniqueWordGenerator(std::function<int()> word_len_generator, const std::vector<char>& sigma)
        : word_len_generator(word_len_generator), sigma(sigma) { }

std::string UniqueWordGenerator::RandomString() {
    while (1) {
        int len = word_len_generator();
        std::string x(len, ' ');
        for (int i = 0; i < len; i += 1) {
            x[i] = sigma[rand() % sigma.size()];
        }

        if (selected[x] == false) {
            selected[x] = true;
            return x;
        }
    }
}
