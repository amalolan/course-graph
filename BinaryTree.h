#ifndef COURSE_GRAPH_BINARYTREE_H
#define COURSE_GRAPH_BINARYTREE_H

#include "stdbool.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "Util.h"
#include "ArrayList.h"

typedef struct TreeNode_struct {
    void *data;
    struct TreeNode_struct *left;
    struct TreeNode_struct *right;
} TreeNode;

typedef struct BinaryTree_struct {
    int (*comparator)(const void *, const void *);
    TreeNode *root;
    size_t size;
} BinaryTree;


void BinaryTree_init(BinaryTree *tree, int (*comparator)(const void *, const void *));
void BinaryTree_insert(BinaryTree *tree, void *data, int (*comparator)(const void *, const void *));
void* BinaryTree_find(BinaryTree *tree, const void *data);
int BinaryTree_findComparator(const void *one, const void *two);
void BinaryTree_serializeNode(TreeNode *node, ArrayList *data);
void BinaryTree_serialize(BinaryTree *tree, ArrayList *data);
TreeNode* BinaryTree_removeNode(BinaryTree *tree, TreeNode *node, void *data, void (*data_free)(void *));
void BinaryTree_remove(BinaryTree *tree, void *data, void (*data_free)(void *));
void BinaryTree_toString(BinaryTree *tree, void (*data_toString)(const void *, char *), char *str);

void BinaryTree_freeNode(TreeNode *node, void (*data_free)(void *));
void BinaryTree_free(BinaryTree *tree, void (*data_free)(void *));

#endif //COURSE_GRAPH_BINARYTREE_H
