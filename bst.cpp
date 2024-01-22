// EB
// Implementing Binary Search Tree in C++

#include <iostream>

namespace BST
{
  struct Node
  {
    int data;
    std::string name;
    Node *parent;
    Node *left;
    Node *right;
  };
}

class BinarySearchTree
{
private:
  BST::Node *root;

  BST::Node *insertHelper(BST::Node *currentNode, BST::Node *newNode)
  {
    if (currentNode == nullptr)
    {
      return newNode;
    }

    if (newNode->data < currentNode->data)
    {
      currentNode->left = insertHelper(currentNode->left, newNode);
    }
    else if (newNode->data >= currentNode->data)
    {
      currentNode->right = insertHelper(currentNode->right, newNode);
    }

    return currentNode;
  }

  int heightHelper(BST::Node *currentNode)
  {
    if (currentNode == nullptr)
    {
      return 0;
    }

    int leftHeight = heightHelper(currentNode->left);
    int rightHeight = heightHelper(currentNode->right);

    return std::max(leftHeight, rightHeight) + 1;
  }

  int totalNodesHelper(BST::Node *currentNode)
  {
    if (currentNode == nullptr)
    {
      return 0;
    }

    return totalNodesHelper(currentNode->left) + totalNodesHelper(currentNode->right) + 1;
  }

  BST::Node *searchHelper(BST::Node *currentNode, int population)
  {
    if (currentNode == nullptr || currentNode->data == population)
    {
      return currentNode;
    }

    if (population < currentNode->data)
    {
      return searchHelper(currentNode->left, population);
    }
    else
    {
      return searchHelper(currentNode->right, population);
    }
  }

  BST::Node *minimum(BST::Node *node)
  {
    while (node->left != nullptr)
    {
      node = node->left;
    }
    return node;
  }

  BST::Node *maximum(BST::Node *node)
  {
    while (node->right != nullptr)
    {
      node = node->right;
    }
    return node;
  }

  BST::Node *deleteHelper(BST::Node *currentNode, int population)
  {
    if (currentNode == nullptr)
    {
      return nullptr;
    }

    if (population < currentNode->data)
    {
      currentNode->left = deleteHelper(currentNode->left, population);
    }
    else if (population > currentNode->data)
    {
      currentNode->right = deleteHelper(currentNode->right, population);
    }
    else
    {
      if (currentNode->left == nullptr)
      {
        BST::Node *temp = currentNode->right;
        delete currentNode;
        return temp;
      }
      else if (currentNode->right == nullptr)
      {
        BST::Node *temp = currentNode->left;
        delete currentNode;
        return temp;
      }

      BST::Node *temp = minimum(currentNode->right);
      currentNode->data = temp->data;
      currentNode->right = deleteHelper(currentNode->right, temp->data);
    }

    return currentNode;
  }

  void inorderHelper(BST::Node *currentNode, std::pair<std::string, int> orderedData[], int index)
  {
    if (currentNode != nullptr)
    {
      inorderHelper(currentNode->left, orderedData, index);
      orderedData[index++] = std::make_pair(currentNode->name, currentNode->data);
      inorderHelper(currentNode->right, orderedData, index);
    }
  }

  void preorderHelper(BST::Node *currentNode, std::pair<std::string, int> orderedData[], int index)
  {
    if (currentNode != nullptr)
    {
      orderedData[index++] = std::make_pair(currentNode->name, currentNode->data);
      preorderHelper(currentNode->left, orderedData, index);
      preorderHelper(currentNode->right, orderedData, index);
    }
  }

  void postorderHelper(BST::Node *currentNode, std::pair<std::string, int> orderedData[], int index)
  {
    if (currentNode != nullptr)
    {
      postorderHelper(currentNode->left, orderedData, index);
      postorderHelper(currentNode->right, orderedData, index);
      orderedData[index++] = std::make_pair(currentNode->name, currentNode->data);
    }
  }

public:
  BinarySearchTree()
  {
    root = nullptr;
  }

  void preorder(std::pair<std::string, int> orderedData[], int index)
  {
    preorderHelper(root, orderedData, index);
  }

  void inorder(std::pair<std::string, int> orderedData[], int index)
  {
    inorderHelper(root, orderedData, index);
  }

  void postorder(std::pair<std::string, int> orderedData[], int index)
  {
    postorderHelper(root, orderedData, index);
  }

  BST::Node *searchTree(int population)
  {
    BST::Node *result = searchHelper(root, population);
    return result;
  }

  BST::Node *successor(BST::Node *node)
  {
    if (node->right != nullptr)
    {
      return minimum(node->right);
    }

    BST::Node *successorNode = nullptr;
    BST::Node *currentNode = root;

    while (currentNode != nullptr)
    {
      if (node->data < currentNode->data)
      {
        successorNode = currentNode;
        currentNode = currentNode->left;
      }
      else if (node->data > currentNode->data)
      {
        currentNode = currentNode->right;
      }
      else
      {
        break;
      }
    }

    return successorNode;
  }

  BST::Node *predecessor(BST::Node *node)
  {
    if (node->left != nullptr)
    {
      return maximum(node->left);
    }

    BST::Node *predecessorNode = nullptr;
    BST::Node *currentNode = root;

    while (currentNode != nullptr)
    {
      if (node->data > currentNode->data)
      {
        predecessorNode = currentNode;
        currentNode = currentNode->right;
      }
      else if (node->data > currentNode->data)
      {
        currentNode = currentNode->left;
      }
      else
      {
        break;
      }
    }

    return predecessorNode;
  }

  void insert(std::string city, int population)
  {
    BST::Node *newNode = new BST::Node;
    newNode->data = population;
    newNode->name = city;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = nullptr;

    if (root == nullptr)
    {
      root = newNode;
    }
    else
    {
      insertHelper(root, newNode);
    }
  }

  void deleteNode(int population)
  {
    root = deleteHelper(root, population);
  }

  int getHeight()
  {
    return heightHelper(root) - 1;
  }

  BST::Node *getMaximum()
  {
    BST::Node *currentNode = root;

    while (currentNode->right != nullptr)
    {
      currentNode = currentNode->right;
    }

    return currentNode;
  }

  BST::Node *getMinimum()
  {
    BST::Node *currentNode = root;

    while (currentNode->left != nullptr)
    {
      currentNode = currentNode->left;
    }

    return currentNode;
  }

  int getTotalNodes()
  {
    return totalNodesHelper(root);
  }
};