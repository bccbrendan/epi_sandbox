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

}} // EPI::BinaryTree
