#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<math.h>

#define SIZE 10000000      // Number of values to be inserted

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

Node* treeNodes[SIZE];     // Globally declared Array to store pointers to tree nodes while rebuilding
int count = 0;             // Globally declared count variable to store the number of elements in treeNodes array

Node* imbalancedNode = NULL;  // This shall store the pointer to node where imbalance occurs while insertion
Node* parent = NULL;          // This shall be the parent of imbalanceNode
bool imbalanceFlag = false;   // Boolean flag to detect if imbalance is detected at any point

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
 * Function : storeInorder
 * ----------------------------------------
 * Stores the inorder traversal of a given BST in 'treeNodes' array
 * 
 *   Node* root: Root of given BST
 * 
 */
void storeInorder(Node* root) {
    if(root != NULL) {
        storeInorder(root->left);
        treeNodes[count++] = root;
        storeInorder(root->right);
    }
}

/*
 * Function : inorderArrayToBalancedBST
 * ----------------------------------------
 * This function uses pointers to nodes stored in 'treeNodes' array in sorted order of keys and builds a
 * perfectly balanced BST
 * 
 *   int start: Start of 'treeNodes' array
 *   int end  : End of 'treeNodes' array
 * 
 *   returns   : Resulting prefectly balanced binary search tree
 */
Node* inorderArrayToBalancedBST(int start, int end) {
    if(start > end)
        return NULL;

    int mid = start + (end - start)/2;
    Node* root = treeNodes[mid];                             // Make the middle of the array as current root
    root->left = inorderArrayToBalancedBST(start, mid-1);    // Store left half elements in left subtree
    root->right = inorderArrayToBalancedBST(mid+1, end);     // Store right half elements in right subtree
    root->numNodes = getNumNodes(root->left) + getNumNodes(root->right) + 1;
    return root;
}

/*
 * Function : rebuildTree
 * ----------------------------------------
 * Rebuilds a BST to perfectly balanced BST    printf("Hyyyy\n");
 * 
 *   Node* root: Root of the BST to be rebuilt
 * 
 *   returns   : Resulting prefectly balanced binary search tree after rebuilding 
 */
Node* rebuildTree(Node* root) {
    count = 0;                                          // Set count to 0 to start storing tree nodes in array 
    storeInorder(root);                                 // Store the inorder traversal of tree in 'treeNodes' array
    return inorderArrayToBalancedBST(0, count-1);       // Build perfectly balanced BST out of the array
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
        return root;            // If key already exists, no need to insert again
    else if(x < root->data) {
        root->left = insert(root->left, x);
    } else 
        root->right = insert(root->right, x);

    int leftNodes = getNumNodes(root->left);
    int rightNodes = getNumNodes(root->right);

    root->numNodes =  leftNodes + rightNodes + 1;
    
    // We are following the approach of rebuilding the tree rooted at the top most imbalance node
    // This is more efficient than rebuilding at every imbalance node along the height from bottom to top
    if((leftNodes > (3.0/4)*(root->numNodes)) || (rightNodes > (3.0/4)*(root->numNodes))) {  // If imbalance occurs
        imbalancedNode = root;                                                               // at any node, store  
        imbalanceFlag = true;                                                                // the node and set flag 
        return root;                                                                         // to true
    }

    if(imbalanceFlag == true) {           // If imbalanceFlag is true, store the current node as parent of imbalance 
        parent = root;                    // node and set imbalanceFlag to false
        imbalanceFlag = false;
    }                                            

    return root;
}

int main() {
    Node* root = NULL;

    clock_t start_t, end_t;
    double total_t;

    FILE* file1 = fopen("CumulativeTimeTillN.csv", "w+");
    FILE* file2 = fopen("TimeForNthInsertion.csv", "w+");

    double cumulativeTime = 0;             // Cumulative time of insertion from 1 to N

    for(int i=1;i<=(SIZE);i++) {
        start_t = clock();

        root = insert(root, i);

        if(!imbalanceFlag && imbalancedNode != NULL) {           // If imbalance is detected at a node other than root
            if(imbalancedNode->data < parent->data) {
                parent->left = rebuildTree(imbalancedNode);
            } else {
                parent->right = rebuildTree(imbalancedNode);
            }
            imbalancedNode = NULL;
            parent = NULL;
        } else if(imbalanceFlag && root == imbalancedNode) {    // If root is the imbalanced node
            root = rebuildTree(root);
            imbalanceFlag = false;
            imbalancedNode = NULL;
            parent = NULL;
        }

        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

        cumulativeTime += total_t;

        if(i % 50000 == 0)
            fprintf(file1, "%lf, %0.10lf\n", i*log2(i), cumulativeTime);
            
        if(i >= 1e5 && i <= 1e6)
            fprintf(file2, "%lf, %0.10lf\n", log2(i), total_t);
    }
}