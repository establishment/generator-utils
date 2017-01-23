#pragma once

#include "random.hpp"

#include <iostream>

#include <cassert>

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

// Random utils
template<>
int Rand<int>() {
    return rand();
};

template<>
long long Rand<long long>() {
    return 1LL * rand() * RAND_MAX + rand();
};

template<>
int Rand<int>(int left, int right) {
    if (left == right) { return 0; }
    long long x = 1LL * rand() * RAND_MAX + rand();
    x %= (long long)right - left;
    x += left;
    return x;
};

template<>
int xRand<int>(int left, int right) {
    return Rand(left, right + 1);
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
long long xRand<long long>(long long left, long long right) {
    return Rand(left, right + 1);       
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
    long double x = Rand<long double>(std::log2(left), std::log2(right));
    Type r = std::pow(2.0, x);
    assert(left <= r);
    assert(r < right);
    return r;
}

template<typename Type>
Type xRandLog(Type left, Type right) {
    return RandLog(left, right + (Type)1);
}

template<typename Type>
Type RandLogScaled(Type left, Type right) {
    return RandLog<Type>((Type)1, right - left + (Type)1) + (left - 1);
}

template<typename Type>
Type xRandLogScaled(Type left, Type right) {
    return RandLog<Type>((Type)1, right - left + (Type)2) + (left - 1);
}

template<typename Type>
std::vector<Type> UniqueNumbers(Type left, Type right, int num_elements, const std::function<bool(Type)>& valid_number) {
    assert(right - left >= num_elements);
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
std::vector<Type> xUniqueNumbers(Type left, Type right, int num_elements, const std::function<bool(Type)>& valid_number) {
    return UniqueNumbers(left, right + 1, num_elements, valid_number);
};



template<typename Type>
std::vector<Type> UniqueNumbers(Type right, int num_elements, const std::function<bool(Type)>& valid_number) {
    return UniqueNumbers<Type>((Type)0, right, num_elements, valid_number);
};

template<typename Type>
std::vector<Type> xUniqueNumbers(Type right, int num_elements, const std::function<bool(Type)>& valid_number) {
    return UniqueNumbers<Type>((Type)0, right + (Type)1, num_elements, valid_number);
};



template<typename Type>
std::vector<Type> UniqueNumbers(Type left, Type right, int num_elements) {
    return UniqueNumbers<Type>(left, right, num_elements, [](Type) -> bool { return true; });
};

template<typename Type>
std::vector<Type> xUniqueNumbers(Type left, Type right, int num_elements) {
    return UniqueNumbers<Type>(left, right + (Type)1, num_elements, [](Type) -> bool { return true; });
};



template<typename Type>
std::vector<Type> UniqueNumbers(Type right, int num_elements) {
    return UniqueNumbers<Type>((Type)0, right, num_elements, [](Type) -> bool { return true; });
};

template<typename Type>
std::vector<Type> xUniqueNumbers(Type right, int num_elements) {
    return UniqueNumbers<Type>((Type)0, right + (Type)1, num_elements, [](Type) -> bool { return true; });
};



std::vector<int> Partition::Uniform(int num_elements, int num_buckets, int min_val) {
//    std::cerr << ">>>>>\t" << num_elements << '\t' << num_buckets << '\t' << min_val << '\t' << num_elements + num_buckets - 1 << '\n';
    num_elements -= num_buckets * min_val;
    
    std::vector<int> delimiters = UniqueNumbers((int)0, num_elements + num_buckets - 1, num_buckets - 1);

//    std::cerr << "1\t" << delimiters.size() << '\n';

    std::sort(delimiters.begin(), delimiters.end());
    
//    std::cerr << "2\t" << delimiters.size() << '\n';
    delimiters.push_back(num_elements + num_buckets - 1);
//    std::cerr << "Size:\t" << delimiters.size() << '\t' << "Capacity:\t" << delimiters.capacity() << '\n';

    delimiters.insert(delimiters.begin(), -1);
    
//    std::cerr << "2.5\t" << delimiters.size() << '\n';

//    delimiters.insert(delimiters.end(), num_elements + num_buckets - 1);
    
//    std::cerr << "3\n";

    std::vector<int> sizes;

    for (int i = 1; i <= num_buckets; i += 1) {
        sizes.push_back(delimiters[i] - delimiters[i - 1] - 1 + min_val);
    }

//    std::cerr << "<<<<<\n";
    return sizes;
};

std::vector<int> RandomPermutation(int num_elements, int start_element) {
    std::vector<int> permutation(num_elements);
    int sum = start_element;
    
    for (auto& itr : permutation) {
        itr = sum;
        sum += 1;
    }

    random_shuffle(permutation.begin(), permutation.end());
    return permutation;
}

UniqueWordGenerator::UniqueWordGenerator(std::function<int()> word_len_generator, const std::vector<char>& sigma =
        {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'})
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
