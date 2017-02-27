#pragma once
#include <memory>
#include <algorithm>

namespace EPI { namespace BinaryTree {

// forward decle for node_ptr
template <typename T>
struct Node;
 
template <typename T>
using node_ptr = std::unique_ptr<Node<T>>;

template <typename T>
struct Node {
    T data;
    node_ptr<T> left;
    node_ptr<T> right;
    Node<T>* parent;

    Node(T const& data, node_ptr<T> left, node_ptr<T> right)
        : data(data)
        , left(std::move(left))
        , right(std::move(right))
        , parent(nullptr)
    {}
};

template<typename T>
auto make_node(T const& value, node_ptr<T> lhs = nullptr, node_ptr<T> rhs = nullptr)
{
    auto node = std::make_unique<Node<T>>(value, std::move(lhs), std::move(rhs));
    if (node->left) { node->left->parent = node.get(); }
    if (node->right) { node->right->parent = node.get(); }
    return node;
}


// compiler can't deduce that I want a nullptr to be used as the node_ptr<T> lhs.
// so this function handles the case where a right child is provided but not a left.
template<typename T>
auto make_node(T const& value, std::nullptr_t lhs, node_ptr<T> rhs)
{
    auto node = std::make_unique<Node<T>>(value, std::move(lhs), std::move(rhs));
    if (node->right) { node->right->parent = node.get(); }
    return node;
}
template<typename T>
auto make_node(T const& value, node_ptr<T> lhs, std::nullptr_t rhs)
{
    auto node = std::make_unique<Node<T>>(value, std::move(lhs), std::move(rhs));
    if (node->left) { node->left->parent = node.get(); }
    return node;
}


template<typename T>
void TreeTraversal(const node_ptr<T>& root) {
    if (root) {
        // Preorder: process root before traversing left+right
        std::cout << "Preorder: " << root->data << std::endl;
        TreeTraversal(root->left);
        // Inorder: process left, root, right
        std::cout << "Inoder: " << root->data << std::endl;
        TreeTraversal(root->right);
        // Inorder: process left, right, root
        std::cout << "Postorder: " << root->data << std::endl;
     }
};

// Balanced
struct CheckBalanceSt {
    bool balanced;
    int height;
};

template<typename T>
CheckBalanceSt CheckBalance(const node_ptr<T>& tree) {
    if (tree) {
        auto left_balance = CheckBalance(tree->left);
        auto right_balance = CheckBalance(tree->right);
        auto balanced = 1 >= std::abs(left_balance.height - right_balance.height);
        balanced = balanced && left_balance.balanced && right_balance.balanced;
        auto my_height = 1 + std::max(left_balance.height, right_balance.height);
        return {balanced, my_height};
    } else {
        return {true, -1};
    }

}

template<typename T>
bool IsBalanced(const node_ptr<T>& tree) {
    return CheckBalance(tree).balanced;
}


// Symmetric
template<typename T>
bool IsSymmetric(const node_ptr<T>& tree) {
    return (!tree) || CheckSymmetric(tree->left, tree->right);
}

template<typename T>
bool CheckSymmetric(const node_ptr<T>& left, const node_ptr<T>& right) {
    if (left == nullptr && right == nullptr) {
        return true;
    }
    if (left != nullptr && right != nullptr) {
        return ((left->data == right->data)
            && CheckSymmetric(left->left, right->right)
            && CheckSymmetric(left->right, right->left));
    } else {
        return false;
    }
}

// Lowest Common Ancestor

template<typename T>
struct LCA_Status {
    int num_found;
    Node<T>* lca;
};

template<typename T>
LCA_Status<T> LCAHelper(const node_ptr<T>& subtree,
                     const node_ptr<T>& node0,
                     const node_ptr<T>& node1) {
    if (subtree == nullptr) {
        return {0, nullptr};
    }
    int num_found_here = (subtree == node0) ? 1 : 0;
    if (subtree == node1) {
        num_found_here++;
    }
    auto l_status = LCAHelper(subtree->left, node0, node1);
    if (l_status.lca != nullptr) {
        return l_status;
    }
    auto r_status = LCAHelper(subtree->right, node0, node1);
    if (r_status.lca != nullptr) {
        return r_status;
    } 
    auto num_found = l_status.num_found + r_status.num_found + num_found_here;
    auto maybe_lca = num_found == 2 ? subtree.get() : nullptr;
    return { num_found, maybe_lca };
}
 

template<typename T>
Node<T>* LCA(const node_ptr<T>& tree,
             const node_ptr<T>& node0,
             const node_ptr<T>& node1) {
    return LCAHelper(tree, node0, node1).lca;
}

template<typename T>
int GetDepth(const Node<T>* node) {
    if (node->parent == nullptr) {
        return 0;
    } else {
        return 1 + GetDepth(node->parent);
    }
}

template<typename T>
Node<T>* LCAWithParent(const node_ptr<T>& tree,
             const node_ptr<T>& node0,
             const node_ptr<T>& node1) {
    auto node0_iter = node0.get();
    auto node1_iter = node1.get();
    auto depth0 = GetDepth(node0_iter);
    auto depth1 = GetDepth(node1_iter);
     // bring the nodes to the same depth
    while (depth0 > depth1 && node0_iter->parent != nullptr) {
        node0_iter = node0_iter->parent;
        depth0--;
    }
    while (depth1 > depth0 && node1_iter->parent != nullptr) {
        node1_iter = node1_iter->parent;
        depth1--;
    }
    while (node0_iter->parent != node1_iter->parent) {
        node0_iter = node0_iter->parent;
        node1_iter = node1_iter->parent;
    }
    return node0_iter->parent;
}

template<typename T>
int SumRootToLeafHelper(const node_ptr<T>& subtree, int path_so_far) {
    auto path_including_here = (path_so_far << 1) + subtree->data;
    auto sum = 0;
    if (subtree->left) {
        sum += SumRootToLeafHelper(subtree->left, path_including_here);
    }
    if (subtree->right) {
        sum += SumRootToLeafHelper(subtree->right, path_including_here);
    }
    if (subtree->left == nullptr && subtree->right == nullptr) {
        sum = path_including_here;
    }
    return sum;
}

// SumRootToLeaf - compute the sum of the binary numbers representing
// the root-to-leaf paths
template<typename T>
int SumRootToLeaf(const node_ptr<T>& tree) {
    return SumRootToLeafHelper(tree, 0);
}

// HasPathSum
template<typename T>
bool HasPathSumHelper(const node_ptr<T>& subtree,
        int current_path_weight,
        int target_number) {
    if (!subtree) { return false; }
    auto weight = current_path_weight + subtree->data;
    if (!subtree->left && !subtree->right) {
        return weight == target_number;
    }
    if (HasPathSumHelper(subtree->left, weight, target_number)) {
        return true;
    }
    if (HasPathSumHelper(subtree->right, weight, target_number)) {
        return true;
    }
    return false;
}

template<typename T>
bool HasPathSum(const node_ptr<T>& root, int target_number) {
    return HasPathSumHelper(root, 0, target_number);
}

}} // EPI::BinaryTree
