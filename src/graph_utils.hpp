#pragma once

#include <cassert>

#include <queue>
#include <vector>

struct IncrementalTree {
    int root, num_elements, remaining_children_degree;
    std::vector<int>* _free_children_degree;
    std::vector<std::vector<int>>* _children;
    std::queue<int>* _waiting_list;

    IncrementalTree(int degree) : root(0), num_elements(1), remaining_children_degree(degree),
                                  _free_children_degree(new std::vector<int>(1, degree)),
                                  _children(new std::vector<std::vector<int>>(1)),
                                  _waiting_list(new std::queue<int>) {
        if (degree) {
            _waiting_list->push(0);
        }
    }

    ~IncrementalTree() {
        delete _free_children_degree;
        delete _children;
        delete _waiting_list;
    }

    IncrementalTree(const IncrementalTree& rhs) {
        *this = rhs;
    }

    IncrementalTree& operator=(const IncrementalTree& rhs) {
        delete _free_children_degree;
        delete _children;
        delete _waiting_list;

        root = rhs.root;
        num_elements = rhs.num_elements;
        remaining_children_degree = rhs.remaining_children_degree;

        _free_children_degree = new std::vector<int>(*(rhs._free_children_degree));
        _children = new std::vector<std::vector<int>>(*(rhs._children));
        _waiting_list = new std::queue<int>(*(rhs._waiting_list));

        return *this;
    }

    // need to refactor this
    IncrementalTree& Merge(IncrementalTree&& rhs) {
        Merge(rhs);
        return *this;
    }
    IncrementalTree& Merge(IncrementalTree& rhs) {
        if (num_elements >= rhs.num_elements) {
            int nod = this->GetNextFather();
            rhs.PrepareForMove(num_elements);
            (*_children)[nod].push_back(rhs.root);

            for (auto& itr : *(rhs._children)) {
                _children->emplace_back(std::move(itr));
            }
            for (auto& itr : *(rhs._free_children_degree)) {
                _free_children_degree->emplace_back(std::move(itr));
            }


            num_elements += rhs.num_elements;
            remaining_children_degree += rhs.remaining_children_degree;
        } else {
            int nod = this->GetNextFather();
            PrepareForMove(rhs.num_elements);
            (*_children)[nod].push_back(rhs.root);

//            cerr << "COPY THIS INTO RHS\n";

            for (auto& itr : *_children) {
                rhs._children->emplace_back(std::move(itr));
            }
            for (auto& itr : *_free_children_degree) {
                rhs._free_children_degree->emplace_back(std::move(itr));
            }

            num_elements += rhs.num_elements;
            remaining_children_degree += rhs.remaining_children_degree;

            swap(_children, rhs._children);
            swap(_free_children_degree, rhs._free_children_degree);
        }

        PopFather();
        return *this;
    }

    IncrementalTree& PrepareForMove(int offset) {
        root += offset;
        for (auto& list : *_children) {
            for (auto& node : list) {
                node += offset;
            }
        }
        std::queue<int>* new_waiting_list(new std::queue<int>);
        while (not _waiting_list->empty()) {
            new_waiting_list->push(offset + _waiting_list->front());
            _waiting_list->pop();
        }

        delete _waiting_list;
        _waiting_list = new_waiting_list;
        return *this;
    }

    int GetNextFather() {
        return _waiting_list->front();
    }

    void NextValidFather() {
//        cerr << "NextValidFather\n";
        if (_waiting_list->empty()) {
            return;
        }

        int nod = _waiting_list->front();
        if ((*_free_children_degree)[nod] == 0) {
            _waiting_list->pop();
            for (auto itr : Children(nod)) {
                _waiting_list->push(itr);
            }
            NextValidFather();
        }
    }

    void PopFather() {
        NextValidFather();
        int nod = _waiting_list->front();
        assert((*_free_children_degree)[nod] > 0);

        (*_free_children_degree)[nod] -= 1;
        remaining_children_degree -= 1;
    }

    std::vector<int>& Children(int nod) {
        return (*_children)[nod];
    }

    IncrementalTree& InsertNode(int degree) {
        int father = GetNextFather();
        _free_children_degree->push_back(degree);
        _children->push_back({});
        (*_children)[father].push_back(num_elements);

        remaining_children_degree += degree;
        num_elements += 1;

        PopFather();
        return *this;
    }

    IncrementalTree& FillWithLeaves() {
        while (remaining_children_degree) {
            InsertNode(0);
        }
        return *this;
    }

    std::vector<std::pair<int, int>> ToEdgeList(int start_node=1) {
        std::vector<std::pair<int, int>> edges;
        for (int a = 0; a < num_elements; a += 1) {
            for (auto itr : (*_children)[a]) {
                edges.push_back({a + start_node, itr + start_node});
            }
        }

        return edges;
    }
};

// something something in the month of may
// bitches love my penis cuz it's really big

//std::vector<int> TreeFromDegree(std::vector<int> degrees) {
//    RandomShuffle(degrees);
//
//    std::vector<int> in_degree({degrees.back()});
//    std::vector<int> fathers;
//    degrees.pop_back();
//
//    std::vector<int> available_nodes({0});
//
//    auto add_node = [&](int father, int degree) -> int {
//        in_degree.push_back(degree);
//        if (degree != 0) {
//            available_nodes.push_back((int)in_degree.size() - 1);
//        }
//        fathers.push_back(father);
//        return (int)in_degree.size() - 1;
//    };
//
//    auto get_random_node = [&]() -> int {
//        int index = rand() % available_nodes.size();
//        int node = available_nodes[index];
//        in_degree[node] -= 1;
//        if (in_degree[node] == 0) {
//            std::swap(available_nodes[index], available_nodes.back());
//            available_nodes.pop_back();
//        }
//        return node;
//    };
//
//    auto random_path_num = [&]() -> int {
//        if (degrees.size() < 3) {
//            return degrees.size();
//        } else {
//            int mx = degrees.size() / log2(degrees.size() + 1);
//            mx = std::max(mx, 1);
//            return rand() % mx + 1;
//        }
//    };
//
//    while (degrees.size()) {
//        int new_num = random_path_num();
//        int start = get_random_node();
//        int last_node = start;
//        for (int i = 0; i < new_num; i += 1) {
//            if (i + 1 != new_num) {
//                degrees.back() -= 1;
//            }
//
//            int node = add_node(last_node, degrees.back());
//            degrees.pop_back();
//            last_node = node;
//        }
//    }
//
//    while (not available_nodes.empty()) {
//
//        int father = get_random_node();
//        add_node(father, 0);
//    }
//
//    return fathers;
//};
