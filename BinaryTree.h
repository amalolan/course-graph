#ifndef COURSE_GRAPH_BINARYTREE_H
#define COURSE_GRAPH_BINARYTREE_H

#include "stdbool.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "Util.h"
#include "ArrayList.h"

/**
 * Node that wraps data for the BinaryTree. Generic void * pointer used.
 */
typedef struct TreeNode_struct {
    void *data;
    struct TreeNode_struct *left;
    struct TreeNode_struct *right;
} TreeNode;

/**
 * BinarySearchTree. Comparisons are done usually using the default comparator.
 * Inserts sometimes override the default comparator with a special comparator.
 */
typedef struct BinaryTree_struct {
    int (*comparator)(const void *, const void *);
    TreeNode *root;
    size_t size;
} BinaryTree;

/**
 * Initializes the BinaryTree
 * @param tree BinaryTree object
 * @param comparator The default comparator for the tree. Inserts, finds, and deletions are based on this.
 */
void BinaryTree_init(BinaryTree *tree, int (*comparator)(const void *, const void *));

/**
 *
 * @param tree the BinaryTree
 * @param data the universal pointer
 * @param comparator comparator to override default. Useful in certain cases.
 */
void BinaryTree_insert(BinaryTree *tree, void *data, int (*comparator)(const void *, const void *));

/**
 * Finds the element in the tree based on the default comparator.
 * @param tree the BinaryTree to search in
 * @param data the element to look for
 * @return The element found in the tree (note based on the comparator this could be a different type)
 */
void* BinaryTree_find(BinaryTree *tree, const void *data);

/**
 * Finds the element but acts as a comparator. So returns 0 on find, -1 on miss.
 * Useful when doing a 1D search without iterating over possibilities.
 * Can be used in conjunction with ArrayList_find or LinkedList_find with no extra iteration
 * @param one the data to find
 * @param two the BinaryTree to search in
 * @return 0 if found, -1 otherwise
 */
int BinaryTree_findComparator(const void *one, const void *two);

/**
 * Serializes everything starting from the node as the root.
 * Recursive calls allow tree to be serialized if started at root.
 * @param node The node to start serialization at
 * @param list the list to append to
 */
void BinaryTree_serializeNode(TreeNode *node, ArrayList *list);

/**
 * Converts BinaryTree into an ArrayList in sorted order.
 * Useful for traversals as don't need to repeat recursive calls to nodes.
 * Takes O(n), so using serialize then for loop is same time complexity.
 * @param tree The tree to serialize
 * @param data the list to append to
 */
void BinaryTree_serialize(BinaryTree *tree, ArrayList *data);

/**
 * Removes node from the BinaryTree assuming the node is the root. Returns the new root.
 * This implementation works recursively, thus to remove a node from the tree
 * we can simply call this function starting at the root.
 * Data is found using the default comparator.
 * @param tree The BinaryTree the nodes are in
 * @param node The node assumed to be the root for this call to removeNode()
 * @param data The data to remove.
 * @param data_free The destructor for data.
 * @return The new root
 */
TreeNode* BinaryTree_removeNode(BinaryTree *tree, TreeNode *node, void *data, void (*data_free)(void *));

/**
 * Removes the data from the BinaryTree using the default comparator.
 * @param tree The tree to remove from
 * @param data the data to remove
 * @param data_free the destructor for the data
 */
void BinaryTree_remove(BinaryTree *tree, void *data, void (*data_free)(void *));

/**
 * Converts the BinaryTree into a string representation. Does so by using the
 * serializing function. Note, str needs to be allocated and existing data will
 * be overwritten.
 * @param tree The tree to convert to string
 * @param data_toString The method to convert the data into strings
 * @param str The string to store it in.
 */
void BinaryTree_toString(BinaryTree *tree, void (*data_toString)(const void *, char *), char *str);

/**
 *
 * @param node Destructor to free individual nodes
 * @param data_free Destructor for the data
 */
void BinaryTree_freeNode(TreeNode *node, void (*data_free)(void *));

/**
 * Destructor
 * @param tree BinaryTree to destruct
 * @param data_free Destructor for the data
 */
void BinaryTree_free(BinaryTree *tree, void (*data_free)(void *));

#endif //COURSE_GRAPH_BINARYTREE_H
