#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<math.h>

#define SIZE 10000000

/*
 * Structure   : Node
 * -------------------------------
 *   Node of a binary tree
 *
 *   struct Node* left : Pointer to left subtree
 *   struct Node* right: Pointer to right subtree
 *   int data          : Value stored in node
 *   int numNodes      : Number of nodes in the subtree rooted by this node
 */
typedef struct Node {
    struct Node* left;
    struct Node* right;
    int data;
    int numNodes;
} Node;

/*
 * Function : getNumNodes
 * ---------------------------------
 * Function returns the number of nodes in the subtree rooted by the given node
 *
 *   Node* root: Given subtree
 * 
 *   returns   : Number of nodes in the subtree rooted by the given node
 */
int getNumNodes(Node* root) {
    if(root == NULL)
        return 0;

    return root->numNodes;
}

/*
 * Function : leftRotate
 * ---------------------------------
 * Perform left rotation about the given node
 *
 *   Node* root: Given subtree
 * 
 *   returns   : Left rotated subtree about the given node
 */
Node* leftRotate(Node* root) {
    if(root == NULL) 
        return root;

    Node* newRoot = root->right;
    Node* temp = newRoot->left;
    newRoot->left = root;
    root->right = temp;

    root->numNodes = getNumNodes(root->left) + getNumNodes(root->right) + 1;
    newRoot->numNodes = getNumNodes(newRoot->left) + getNumNodes(newRoot->right) + 1;
    return newRoot;
}

/*
 * Function : rightRotate
 * ---------------------------------
 * Perform right rotation about the given node
 *
 *   Node* root: Given subtree
 * 
 *   returns   : Right rotated subtree about the given node
 */
Node* rightRotate(Node* root) {
    if(root == NULL) 
        return NULL;

    Node* newRoot = root->left;
    Node* temp = newRoot->right;
    newRoot->right = root;
    root->left = temp;

    root->numNodes = getNumNodes(root->left) + getNumNodes(root->right) + 1;
    newRoot->numNodes = getNumNodes(newRoot->left) + getNumNodes(newRoot->right) + 1;
    return newRoot;
}

/*
 * Function : insert
 * ---------------------------------
 * Perform insert operation in a given Nearly Balanced Binary Search Tree keeping the nearly balanced property intact
 *
 *   Node* root: Nearly Balanced Binary Search Tree
 *   int x     : Value to be inserted
 * 
 *   returns   : Resulting Nearly Balanced Binary Search Tree after performing insert opeartion
 */
Node* insert(Node* root, int x) {
    if(root == NULL) {
        Node* newRoot = (Node*)malloc(sizeof(Node));
        *newRoot = (Node){.left = NULL, .right = NULL, .data = x, .numNodes = 1};
        return newRoot;
    }

    if(root->data == x)
        return root;
    else if(x < root->data) {
        root->left = insert(root->left, x);
    } else 
        root->right = insert(root->right, x);

    int leftNodes = getNumNodes(root->left);
    int rightNodes = getNumNodes(root->right);

    root->numNodes =  leftNodes + rightNodes + 1;

    if(leftNodes > ((3.0/4)*(root->numNodes))) {
        if(x < root->left->data)
            return rightRotate(root);                         // Case of single right rotation
        else {
            root->left = leftRotate(root->left);              // Case of left rotation followed by a right rotation
            return rightRotate(root);
        }
    } else if(rightNodes > ((3.0/4)*(root->numNodes))) {
        if(x > root->right->data)
            return leftRotate(root);                          // Case of single left rotation
        else {
            root->right = rightRotate(root->right);           // Case of right rotation followed by a left rotation
            return leftRotate(root);
        }
    }

    return root;
}

int main() {
    Node* root = NULL;

    clock_t start_t, end_t;
    double total_t;

    FILE* file1 = fopen("CumulativeTimeTillN.csv", "w+");
    FILE* file2 = fopen("TimeForNthInsertion.csv", "w+");

    fprintf(file1, "Total time for insertions from 1 to i, i\n");
    fprintf(file2, "Time for ith insertion, i\n");

    double cumulativeTime = 0;

    for (int i = 1; i <= (SIZE); i++) {
        start_t = clock();
        root = insert(root, i);
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        cumulativeTime += total_t;

        if(i % 50000 == 0)
            fprintf(file1, "%lf, %0.10lf\n", i*log2(i), cumulativeTime);
            
        if(i >= 1e5 && i <= 1e6)
            fprintf(file2, "%d, %0.10lf\n", i, total_t);
            
    }
    return 0;
}