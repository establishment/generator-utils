#pragma once

#include <cassert>
#include <cstdlib>

#include <functional>
#include <unordered_map>
#include <vector>

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

std::vector<int> UniqueNumbers(int left, int right, int num_elements, const std::function<bool(int)>& valid_number) {
    assert(left <= right);

    std::unordered_map<int, bool> selected_numbers;

    std::vector<int> result;
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

std::vector<int> UniqueNumbers(int right, int num_elements, const std::function<bool(int)>& valid_number) {
    return UniqueNumbers(0, right, num_elements, valid_number);
};

std::vector<int> UniqueNumbers(int left, int right, int num_elements) {
    assert(right - left <= num_elements);
    return UniqueNumbers(left, right, num_elements, [](int) -> bool { return true; });
};

std::vector<int> UniqueNumbers(int right, int num_elements) {
    assert(right <= num_elements);
    return UniqueNumbers(0, right, num_elements, [](int) -> bool { return true; });
};

std::vector<int> Range(int left, int right, int step) {
    assert(step != 0);

    if (left == right) {
        return {};
    }

    std::vector<int> result;

    if (step > 0) {
        assert(left <= right);
        result.reserve((right - left - 1) / step);
        for (int itr = left; itr < right; itr += step) {
            result.push_back(itr);
        }
    } else {
        assert(left >= right);
        for (int itr = left; itr > right; itr += step) {
            result.push_back(itr);
        }
    }

    return result;
};

std::vector<int> Range(int right) {
    return Range(0, right, 1);
}


std::vector<int> TreeFromDegree(std::vector<int> degrees) {
    RandomShuffle(degrees);

    std::vector<int> in_degree({degrees.back()});
    std::vector<int> fathers;
    degrees.pop_back();

    std::vector<int> available_nodes({0});

    auto add_node = [&](int father, int degree) -> int {
        in_degree.push_back(degree);
        if (degree != 0) {
            available_nodes.push_back((int)in_degree.size() - 1);
        }
        fathers.push_back(father);
        return (int)in_degree.size() - 1;
    };

    auto get_random_node = [&]() -> int {
        int index = rand() % available_nodes.size();
        int node = available_nodes[index];
        in_degree[node] -= 1;
        if (in_degree[node] == 0) {
            std::swap(available_nodes[index], available_nodes.back());
            available_nodes.pop_back();
        }
        return node;
    };

    auto random_path_num = [&]() -> int {
        if (degrees.size() < 3) {
            return degrees.size();
        } else {
            int mx = degrees.size() / log2(degrees.size() + 1);
            mx = std::max(mx, 1);
            return rand() % mx + 1;
        }
    };

    while (degrees.size()) {
        int new_num = random_path_num();
        int start = get_random_node();
        int last_node = start;
        for (int i = 0; i < new_num; i += 1) {
            if (i + 1 != new_num) {
                degrees.back() -= 1;
            }

            int node = add_node(last_node, degrees.back());
            degrees.pop_back();
            last_node = node;
        }
    }

    while (not available_nodes.empty()) {

        int father = get_random_node();
        add_node(father, 0);
    }

    return fathers;
};

std::vector<int> Partition::Uniform(int num_elements, int num_buckets, int min_val) {
    num_elements -= num_buckets * min_val;

    std::vector<int> delimiters = UniqueNumbers(0, num_elements + num_buckets - 1, num_buckets - 1);

    sort(delimiters.begin(), delimiters.end());

    delimiters.insert(delimiters.begin(), -1);
    delimiters.insert(delimiters.end(), num_elements + num_buckets - 1);

    std::vector<int> sizes;

    for (int i = 1; i <= num_buckets; i += 1) {
        sizes.push_back(delimiters[i] - delimiters[i - 1] - 1 + min_val);
    }

    return sizes;
};