#pragma once
#include <memory>
#include <algorithm>
#include "binary_tree.h"
#include <cassert>      // assert
#include <cstddef>      // ptrdiff_t
#include <iterator>     // iterator
#include <type_traits>  // remove_cv
#include <utility>      // swap
#include <stack>



namespace EPI { namespace BinaryTree {

template <typename T>
struct Node;
 

// ForwardIterator for Inorder traversal
template
<
    class Type,
    class UnqualifiedType = std::remove_cv_t<Type>
>
class ForwardIterator 
    : public std::iterator<std::forward_iterator_tag,
                           UnqualifiedType,
                           std::ptrdiff_t,
                           Type*,
                           Type&>
{
    Node<UnqualifiedType>* itr;
    std::stack<Node<UnqualifiedType>*> node_stack;

    friend Node<Type>;

    explicit ForwardIterator(Node<UnqualifiedType>* nd) 
        : itr(nd),
        node_stack()
    { 
        DescendIterLeft(itr);
    }

    // get to the left-most node, recording as we go
    void DescendIterLeft(Node<UnqualifiedType>* node) {
        while (node && node->left) {
            node_stack.push(node);
            node = node->left.get();
        }
        itr = node;
     }

public:

    ForwardIterator()   // Default construct gives end.
        : itr(nullptr) 
          , node_stack()
    {
    }

    void swap(ForwardIterator& other) noexcept
    {
        using std::swap;
        swap(itr, other.itr);
        swap(node_stack, other.node_stack);
    }

    ForwardIterator& operator++ () // Pre-increment
    {
        if (itr->right) {
            // move right if we can
            DescendIterLeft(itr->right.get());
        } else {
            // otherwise, move up
            if (!node_stack.empty()) {
                itr = node_stack.top();
                node_stack.pop();
            } else {
                // or end
                itr = nullptr;
            }
        }
        return *this;
    }

    ForwardIterator operator++ (int) // Post-increment
    {
        assert(itr != nullptr && "Out-of-bounds iterator increment!");
        ForwardIterator tmp(*this);
        (*this)++;
        return tmp; 
    }

    // two-way comparison: v.begin() == v.cbegin() and vice versa
    template<class OtherType>
    bool operator == (const ForwardIterator<OtherType>& rhs) const
    {
        return itr == rhs.itr;
    }

    template<class OtherType>
    bool operator != (const ForwardIterator<OtherType>& rhs) const
    {
        return itr != rhs.itr;
    }

    Type& operator* () const
    {
        assert(itr != nullptr && "Invalid iterator dereference!");
        return itr->data;
    }

    Type& operator-> () const
    {
        assert(itr != nullptr && "Invalid iterator dereference!");
        return itr->data;
    }

    // One way conversion: iterator -> const_iterator
    operator ForwardIterator<const Type>() const
    {
        return ForwardIterator<const Type>(itr);
    }
};

}} // EPI::BinaryTree


