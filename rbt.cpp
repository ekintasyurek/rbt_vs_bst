// EB
// Implementing Red-Black Tree in C++

#include <iostream>

namespace RBT
{
  struct Node
  {
    int data;
    std::string name;
    Node *parent;
    Node *left;
    Node *right;
    int color;
  };
}

class RedBlackTree
{
private:
  RBT::Node *root;

  int heightHelper(RBT::Node *currentNode)
  {
    if (currentNode == nullptr)
    {
      return 0;
    }

    int leftHeight = heightHelper(currentNode->left);
    int rightHeight = heightHelper(currentNode->right);

    return std::max(leftHeight, rightHeight) + 1;
  }

  int totalNodesHelper(RBT::Node *currentNode)
  {
    if (currentNode == nullptr)
    {
      return 0;
    }

    return totalNodesHelper(currentNode->left) + totalNodesHelper(currentNode->right) + 1;
  }

  RBT::Node *searchHelper(RBT::Node *currentNode, int population)
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

  RBT::Node *minimum(RBT::Node *node)
  {
    while (node->left != nullptr)
    {
      node = node->left;
    }
    return node;
  }

  RBT::Node *maximum(RBT::Node *node)
  {
    while (node->right != nullptr)
    {
      node = node->right;
    }
    return node;
  }

  void inorderHelper(RBT::Node *currentNode, std::pair<std::string, int> orderedData[], int index)
  {
    if (currentNode != nullptr)
    {
      inorderHelper(currentNode->left, orderedData, index);
      orderedData[index++] = std::make_pair(currentNode->name, currentNode->data);
      inorderHelper(currentNode->right, orderedData, index);
    }
  }

  void preorderHelper(RBT::Node *currentNode, std::pair<std::string, int> orderedData[], int index)
  {
    if (currentNode != nullptr)
    {
      orderedData[index++] = std::make_pair(currentNode->name, currentNode->data);
      preorderHelper(currentNode->left, orderedData, index);
      preorderHelper(currentNode->right, orderedData, index);
    }
  }

  void postorderHelper(RBT::Node *currentNode, std::pair<std::string, int> orderedData[], int index)
  {
    if (currentNode != nullptr)
    {
      postorderHelper(currentNode->left, orderedData, index);
      postorderHelper(currentNode->right, orderedData, index);
      orderedData[index++] = std::make_pair(currentNode->name, currentNode->data);
    }
  }

  RBT::Node *insertHelper(RBT::Node *currentNode, RBT::Node *newNode)
  {
    if (currentNode == nullptr)
    {
      return newNode;
    }

    if (newNode->data < currentNode->data)
    {
      RBT::Node *leftChild = insertHelper(currentNode->left, newNode);
      currentNode->left = leftChild;
      leftChild->parent = currentNode;
    }
    else if (newNode->data >= currentNode->data)
    {
      RBT::Node *rightChild = insertHelper(currentNode->right, newNode);
      currentNode->right = rightChild;
      rightChild->parent = currentNode;
    }

    return currentNode;
  }

  void leftRotate(RBT::Node *x)
  {
    RBT::Node *y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
    {
      y->left->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == nullptr)
    {
      root = y;
    }
    else if (x == x->parent->left)
    {
      x->parent->left = y;
    }
    else
    {
      x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
  }

  void rightRotate(RBT::Node *y)
  {
    RBT::Node *x = y->left;
    y->left = x->right;

    if (x->right != nullptr)
    {
      x->right->parent = y;
    }
    x->parent = y->parent;

    if (y->parent == nullptr)
    {
      root = x;
    }
    else if (y == y->parent->left)
    {
      y->parent->left = x;
    }
    else
    {
      y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
  }

  void swapColors(int &a, int &b)
  {
    int temp = a;
    a = b;
    b = temp;
  }

  void insertFixup(RBT::Node *newNode)
  {
    RBT::Node *parent = nullptr;
    RBT::Node *grandparent = nullptr;

    while (newNode != root && newNode->color == 1 && newNode->parent->color == 1)
    {
      parent = newNode->parent;
      grandparent = parent->parent;

      if (parent == grandparent->left)
      {
        RBT::Node *uncle = grandparent->right;

        if (uncle != nullptr && uncle->color == 1)
        {
          grandparent->color = 1;
          parent->color = 0;
          uncle->color = 0;
          newNode = grandparent;
        }
        else
        {
          if (newNode == parent->right)
          {
            leftRotate(parent);
            newNode = parent;
            parent = newNode->parent;
          }

          rightRotate(grandparent);
          swapColors(parent->color, grandparent->color);
          newNode = parent;
        }
      }
      else
      {
        RBT::Node *uncle = grandparent->left;

        if (uncle != nullptr && uncle->color == 1)
        {
          grandparent->color = 1;
          parent->color = 0;
          uncle->color = 0;
          newNode = grandparent;
        }
        else
        {
          if (newNode == parent->left)
          {
            rightRotate(parent);
            newNode = parent;
            parent = newNode->parent;
          }

          leftRotate(grandparent);
          swapColors(parent->color, grandparent->color);
          newNode = parent;
        }
      }
    }

    root->color = 0;
  }

public:
  RedBlackTree()
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

  RBT::Node *searchTree(int population)
  {
    return searchHelper(root, population);
  }

  RBT::Node *successor(RBT::Node *node)
  {
    if (node->right != nullptr)
    {
      return minimum(node->right);
    }

    RBT::Node *successorNode = nullptr;
    RBT::Node *currentNode = root;

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

  RBT::Node *predecessor(RBT::Node *node)
  {
    if (node->left != nullptr)
    {
      return maximum(node->left);
    }

    RBT::Node *predecessorNode = nullptr;
    RBT::Node *currentNode = root;

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
    RBT::Node *newNode = new RBT::Node;
    newNode->data = population;
    newNode->name = city;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = nullptr;
    newNode->color = 1;

    if (root == nullptr)
    {
      root = newNode;
      root->color = 0;
    }
    else
    {
      insertHelper(root, newNode);
      insertFixup(newNode);
    }
  }

  // TODO
  void deleteNode(int population)
  {
  }

  int getHeight()
  {
    return heightHelper(root) - 1;
  }

  RBT::Node *getMaximum()
  {
    RBT::Node *currentNode = root;

    while (currentNode->right != nullptr)
    {
      currentNode = currentNode->right;
    }

    return currentNode;
  }

  RBT::Node *getMinimum()
  {
    RBT::Node *currentNode = root;

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