//SOLUTION
#include <algorithm>
#include <queue>
#include "binary_tree.h"

Binary_tree::Binary_tree()
{
    root = nullptr;
}

Binary_tree::Binary_tree(std::string root_data)
{
    root = new Node;
    root->data = root_data;
    root->left = nullptr;
    root->right = nullptr;
}

Binary_tree::Binary_tree(std::string root_data, Binary_tree left, Binary_tree right)
{
    root = new Node;
    root->data = root_data;
    root->left = left.root;
    root->right = right.root;
}

int Binary_tree::height(const Node *n) const
{
    if (n == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + std::max(height(n->left), height(n->right));
    }
}

int Binary_tree::height() const
{
    return height(root);
}

bool Binary_tree::empty() const
{
    return root == nullptr;
}

std::string Binary_tree::data() const
{
    return root->data;
}

Binary_tree Binary_tree::left() const
{
    Binary_tree result;
    result.root = root->left;
    return result;
}

Binary_tree Binary_tree::right() const
{
    Binary_tree result;
    result.root = root->right;
    return result;
}

void Binary_tree::addQuestion(std::string question,Binary_tree current, Binary_tree newTree)
{
    std::string temp = current.root->data;
    current.root->data = question;
    current.root->left = newTree.root;

    Node* newRight = new Node;
    newRight->data = temp;
    newRight->right = nullptr;
    newRight->left = nullptr;
    
    current.root->right = newRight;

}

