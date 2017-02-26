// SOURCE CODE FROM https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption

#include <gtest/gtest.h>
#include "binary_tree.h"

using namespace EPI::BinaryTree;

TEST(TestingBinaryTree, IsBalancedNull) {
    std::unique_ptr<EPI::BinaryTree::Node<int>> empty;
    ASSERT_TRUE(IsBalanced(empty));
}

TEST(TestingBinaryTree, IsBalancedOne) {
    auto root = make_node(3);
    ASSERT_TRUE(IsBalanced(root));
}

TEST(TestingBinaryTree, IsBalancedOneGeneration) {
    auto const root = make_node(
        5,
        make_node(3),
        make_node(7)
    );
    ASSERT_TRUE(IsBalanced(root));
}

TEST(TestingBinaryTree, IsBalancedLeftLeftHeavy) {
    auto const root = make_node(
        5,
        make_node(
            3,
            make_node(2)
        )
    );
    ASSERT_FALSE(IsBalanced(root));
}

TEST(TestingBinaryTree, IsBalancedLeftRightHeavy) {
   auto const root = make_node(
        5, 
        make_node(
            3, 
            nullptr,
            make_node(2)
        ), 
        nullptr
    );    
    ASSERT_FALSE(IsBalanced(root));
}


TEST(TestingBinaryTree, IsBalancedRightRightHeavy) {
    auto const root = make_node(
        5, 
        nullptr,
        make_node(
            3, 
            make_node(2),
            nullptr
        )
    );    
    ASSERT_FALSE(IsBalanced(root));
}

TEST(TestingBinaryTree, IsBalancedRightLeftHeavy) {
    auto const root = make_node(
        5, 
        nullptr,
        make_node(
            3, 
            nullptr,
            make_node(2)
        )
    );    
    ASSERT_FALSE(IsBalanced(root));
}


TEST(TestingBinaryTree, IsBalancedCompleteTree) {
    auto const root = make_node(
        5, 
        make_node(
            3, 
            make_node(4),
            make_node(8)
        ),
        make_node(
            3, 
            make_node(7),
            make_node(2)
        )
    );    
    ASSERT_TRUE(IsBalanced(root));
}