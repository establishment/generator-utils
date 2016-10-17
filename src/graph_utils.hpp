#pragma once

#include <cassert>

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using std::cerr;

struct UnsaturatedTreeNode {
    int node_index;
    int remaining_degree;

    ~UnsaturatedTreeNode() {
        delete next_node;
    }

    UnsaturatedTreeNode* next_node;
    UnsaturatedTreeNode(int node_index, int remaining_degree) 
        : node_index(node_index), remaining_degree(remaining_degree), next_node(nullptr) { }
};

struct IncrementalTree {
    int root;
    int num_nodes;
    int num_unsaturated_edges;
    std::vector<std::pair<int, int>> edges;
    UnsaturatedTreeNode* first_waiting_list_node;
    UnsaturatedTreeNode* last_waiting_list_node;

    IncrementalTree(int unsaturated_edges=0) 
        : root(0),
        num_nodes(1),
        num_unsaturated_edges(unsaturated_edges),
        first_waiting_list_node(new UnsaturatedTreeNode(root, num_unsaturated_edges)),
        last_waiting_list_node(first_waiting_list_node) { }

    IncrementalTree(const IncrementalTree& rhs) {
        *this = rhs;
    }

    IncrementalTree(IncrementalTree&& rhs) noexcept
        : root(rhs.root),
        num_nodes(rhs.num_nodes),
        num_unsaturated_edges(rhs.num_unsaturated_edges),
        edges(std::move(rhs.edges)),
        first_waiting_list_node(rhs.first_waiting_list_node),
        last_waiting_list_node(rhs.last_waiting_list_node) {
            rhs.first_waiting_list_node = nullptr;
            rhs.last_waiting_list_node = nullptr;
        }

    ~IncrementalTree() noexcept {
        delete first_waiting_list_node;
    }

    IncrementalTree& operator=(IncrementalTree&& rhs) noexcept {
        root = rhs.root;
        num_nodes = rhs.num_nodes;
        num_unsaturated_edges = rhs.num_unsaturated_edges;

        std::swap(edges, rhs.edges);
        std::swap(first_waiting_list_node, rhs.first_waiting_list_node);
        std::swap(last_waiting_list_node, rhs.last_waiting_list_node);

        return *this;
    }

    IncrementalTree& operator=(const IncrementalTree& rhs) {
        root = rhs.root;
        num_nodes = rhs.num_nodes;
        num_unsaturated_edges = rhs.num_unsaturated_edges;
        edges = rhs.edges;
        
        UnsaturatedTreeNode* first_node = rhs.first_waiting_list_node;

        first_waiting_list_node = new UnsaturatedTreeNode(first_node->node_index, first_node->remaining_degree);
        last_waiting_list_node = first_waiting_list_node;
        first_node = first_node->next_node;

        while (first_node != nullptr) {
            last_waiting_list_node->next_node = new UnsaturatedTreeNode(first_node->node_index, first_node->remaining_degree);
            last_waiting_list_node = last_waiting_list_node->next_node;
            first_node = first_node->next_node;
        }

        return *this;
   }

    IncrementalTree& Merge(const IncrementalTree& rhs) {
        return Merge(IncrementalTree(rhs));
    }

    IncrementalTree& Merge(IncrementalTree&& rhs) {
        if (rhs.num_nodes <= num_nodes) {
            int father = GetFreeNode();
            int oth = rhs.root + (num_nodes + root - rhs.root);
            edges.push_back({father, oth});

            for (int i = 0, limit = rhs.edges.size(); i < limit; i += 1) {
                auto edge = rhs.edges[i];
                edge.first += num_nodes + root - rhs.root;
                edge.second += num_nodes + root - rhs.root;
                edges.push_back(edge);
            }

            auto now = rhs.first_waiting_list_node;
            while (now != nullptr) {
                now->node_index += num_nodes + root - rhs.root;
                now = now->next_node;
            }
    
            /// root is the same
            num_nodes += rhs.num_nodes;
            num_unsaturated_edges += rhs.num_unsaturated_edges;
        } else {
            int new_root = rhs.root - num_nodes;

            /// copy edges
            for (auto edge : edges) {
                edge.first += new_root - root;
                edge.second += new_root - root;
                rhs.edges.push_back(edge);
            }
            std::swap(edges, rhs.edges);

            /// copy waiting list
            UnsaturatedTreeNode* first_node = first_waiting_list_node;
            while (first_node != nullptr) {
                first_node->node_index += new_root - root;
                first_node = first_node->next_node;
            }

            /// copy other values
            int father = GetFreeNode();
            int oth = rhs.root;
            edges.push_back({father, oth});

            root = new_root;
            num_nodes += rhs.num_nodes;
            num_unsaturated_edges += rhs.num_unsaturated_edges;
        }

        last_waiting_list_node->next_node = rhs.first_waiting_list_node;
        last_waiting_list_node = rhs.last_waiting_list_node;

        /// do not let destroctor to take away our precious list
        rhs.first_waiting_list_node = nullptr;
        rhs.last_waiting_list_node = nullptr;

        return *this;
    }

    IncrementalTree& InsertNode(int unsaturated_degree) {
        int father = GetFreeNode();
        int node = root + num_nodes;

        num_nodes += 1;
        num_unsaturated_edges += unsaturated_degree;
        
        edges.push_back({father, node});
        cerr << "Add Edge\t" << father << '\t' << node << '\n';
        last_waiting_list_node->next_node = new UnsaturatedTreeNode(node, unsaturated_degree);
        last_waiting_list_node = last_waiting_list_node->next_node;
        
        return *this;
    }

    IncrementalTree& FillWithLeaves() {
        while (num_unsaturated_edges) {
            InsertNode(0);
        }
        return *this;
    }

    std::vector<std::pair<int, int>> ToEdgeList(int start_node=1) const {
        int new_root = start_node;
        std::vector<std::pair<int, int>> final_edges;

        for (auto edge : edges) {
            edge.first += new_root - root;
            edge.second += new_root - root;
            final_edges.push_back(edge);
        }

        return final_edges;
    }

    void Debug() {
        auto now = first_waiting_list_node;
        while (now != nullptr) {
            cerr << now->node_index << '\t' << now->remaining_degree << '\n';
            now = now->next_node;
        }
        return;
    }

  private:
    int GetFreeNode() {
        assert(num_unsaturated_edges);
        num_unsaturated_edges -= 1;

        while (first_waiting_list_node != nullptr and first_waiting_list_node->remaining_degree == 0) {
            auto last_node = first_waiting_list_node;
            first_waiting_list_node = first_waiting_list_node->next_node;

            // delete only this
            last_node->next_node = nullptr;
            delete last_node;
        }

        if (first_waiting_list_node == nullptr) {
            assert(0);
        }

        first_waiting_list_node->remaining_degree -= 1;
        return first_waiting_list_node->node_index;
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
