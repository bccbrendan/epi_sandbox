// SOURCE CODE FROM https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "binary_tree.h"

using namespace EPI::BinaryTree;
using namespace ::testing;

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
    // with parent pointers
    lca = EPI::BinaryTree::LCAWithParent(root, root->left->left, root->right->right);
    ASSERT_EQ(lca, root.get());
    lca = EPI::BinaryTree::LCAWithParent(root, root->left->left, root->left->right);
    ASSERT_EQ(lca, root->left.get());
}

// SumRootToLeaf -
TEST(TestingBinaryTree, SumRootToLeafSimple) {
    auto const root = make_node(1, make_node(0), make_node(1));
    ASSERT_EQ(SumRootToLeaf(root->right), 1);
    ASSERT_EQ(SumRootToLeaf(root), 5);
}

// SumRootToLeaf -
TEST(TestingBinaryTree, SumRootToLeaf) {
    auto const root = make_node(
        1,
        make_node(
            0,
            make_node(
                0,
                make_node(0),
                make_node(1)
            ),
            make_node(
                1,
                nullptr,
                make_node(
                    1,
                    make_node(0),
                    nullptr
                )
            )
        ),
        make_node(
            1,
            make_node(
                0,
                nullptr,
                make_node(
                    0,
                    make_node(
                        1,
                        nullptr,
                        make_node(1)
                    ),
                    make_node(0)
                )
            ),
            make_node(
                0,
                nullptr,
                make_node(0)
            )
        )
    );
    auto sum = SumRootToLeaf(root);
    ASSERT_EQ(sum, 0x8 + 0x9 + 0x16 + 0x33 + 0x18 + 0xc);
}

TEST(TestingBinaryTree, HasPathSum) {
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
    ASSERT_TRUE(HasPathSum(make_node(8), 8));
    ASSERT_TRUE(HasPathSum(root, 314 + 6 + 8));
    ASSERT_TRUE(HasPathSum(root, 314 + 6 + 8));
    ASSERT_TRUE(HasPathSum(root, 314 + 6 + 561 + 9));
    ASSERT_FALSE(HasPathSum(root, 314 + 6 + 561 + 1));
    ASSERT_FALSE(HasPathSum(root, 314 + 6 + 561 + 10));
    ASSERT_TRUE(HasPathSum(root, 314 + 6 + 561 + 3));
    ASSERT_TRUE(HasPathSum(root, 314 + 6 + 123));
}


TEST(TestingBinaryTree, InorderIterTest) {
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
    std::vector<int> results;
    for (auto it = root->begin(); it != root->end(); ++it) {
        results.push_back(*it);
    }
    ASSERT_THAT(results,
        ContainerEq(
            std::vector<int> { 8, 6, 9, 561, 3, 314, 561, 6, 123 }
    ));
}

