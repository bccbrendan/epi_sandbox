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


TEST(TestingBinaryTree, IsSymmetricA) {
    auto const root = make_node(
        314, 
        make_node(
            6, 
            nullptr,
            make_node(
                2,
                nullptr,
                make_node(3)
            )
        ),
        make_node(
            6, 
            make_node(
                2,
                make_node(3),
                nullptr
            ),
            nullptr
        )
    );    
    ASSERT_TRUE(IsSymmetric(root));
}


TEST(TestingBinaryTree, IsSymmetricB) {
    auto const root = make_node(
        314, 
        make_node(
            6, 
            nullptr,
            make_node(
                561,
                nullptr,
                make_node(3)
            )
        ),
        make_node(
            6, 
            make_node(
                2,
                make_node(1),
                nullptr
            ),
            nullptr
        )
    );    
    ASSERT_FALSE(IsSymmetric(root));
}
TEST(TestingBinaryTree, IsSymmetricC) {
    auto const root = make_node(
        314, 
        make_node(
            6, 
            nullptr,
            make_node(
                561,
                nullptr,
                make_node(3)
            )
        ),
        make_node(
            6, 
            make_node(561),
            nullptr
        )
    );    
    ASSERT_FALSE(IsSymmetric(root));
}


TEST(TestingBinaryTree, LCA) {
    auto const root = make_node(
        314, 
        make_node(
            6, 
            make_node(8),
            make_node(
                561,
                make_node(9),
                make_node(3)
            )
        ),
        make_node(
            6, 
            make_node(561),
            make_node(123)
        )
    );    
    auto lca = EPI::BinaryTree::LCA(root, root->left->left, root->right->right);
    ASSERT_EQ(lca, root.get());
    lca = EPI::BinaryTree::LCA(root, root->left->left, root->left->right);
    ASSERT_EQ(lca, root->left.get());
 }

