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

    Node(T const& data, node_ptr<T> left, node_ptr<T> right)
        : data(data)
        , left(std::move(left))
        , right(std::move(right))
    {}
};

template<typename T>
auto make_node(T const& value, node_ptr<T> lhs = nullptr, node_ptr<T> rhs = nullptr)
{
    return std::make_unique<Node<T>>(value, std::move(lhs), std::move(rhs));    
}

// compiler can't deduce that I want a nullptr to be used as the node_ptr<T> lhs.
// so this function handles the case where a right child is provided but not a left.
template<typename T>
auto make_node(T const& value, std::nullptr_t lhs, node_ptr<T> rhs)
{
    return std::make_unique<Node<T>>(value, std::move(lhs), std::move(rhs));    
}
template<typename T>
auto make_node(T const& value, node_ptr<T> lhs, std::nullptr_t rhs)
{
    return std::make_unique<Node<T>>(value, std::move(lhs), std::move(rhs));    
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


}} // EPI::BinaryTree
