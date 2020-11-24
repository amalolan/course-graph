#include "BinaryTree.h"
void BinaryTree_init(BinaryTree *tree, int (*comparator)(const void *, const void *)) {
    if (tree == NULL) return;
    tree->root = NULL;
    tree->size = 0;
    tree->comparator = comparator;
}

void BinaryTree_insert(BinaryTree *tree, void *data, int (*comparator)(const void *, const void *)) {
    if (comparator == NULL) comparator = tree->comparator;
    if (tree == NULL || data == NULL) return;
    TreeNode *node = malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    if (tree->size == 0) {
        tree->root = node;
    } else {
        TreeNode* curr = tree->root;
        TreeNode* prev;

        while (curr != NULL) {
            prev = curr;
            if (comparator(curr->data, data) > 0) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }

        if (comparator(prev->data, data) > 0) {
            prev->left = node;
        } else if (comparator(prev->data, data) < 0) {
            prev->right = node;
        } else {
            printf("Error: Already in the tree\n.");
        }

    }
    tree->size++;
}

void* BinaryTree_find(BinaryTree *tree, const void *data) {
    if (tree == NULL || data == NULL) return NULL;
    TreeNode *curr = tree->root;
    while (curr != NULL) {
        if (tree->comparator(curr->data, data) > 0) {
            curr = curr->left;
        } else if (tree->comparator(curr->data, data) < 0) {
            curr = curr->right;
        } else {
            return curr->data;
        }
    }
    return NULL;
}

int BinaryTree_findComparator(const void *one, const void *two) {
    BinaryTree *courses = (BinaryTree*)two;
    if (BinaryTree_find(courses, one) == NULL) return -1;
    return 0;
}

TreeNode* BinaryTree_removeNode(BinaryTree *tree, TreeNode *node, void *data, void (*data_free)(void *)) {
    if (node == NULL || data == NULL) return NULL;
    if (tree->comparator(node->data, data) > 0) {
        node->left = BinaryTree_removeNode(tree, node->left, data, data_free);
    }
    else if (tree->comparator(node->data, data) < 0) {
        node->right = BinaryTree_removeNode(tree, node->right, data, data_free);
    }
    else {
        TreeNode *temp;
        if (node->left == NULL) {
            temp = node->right;
            data_free(node->data);
            free(node);
            node = NULL;
            return temp;
        } else if (node->right == NULL) {
            temp = node->left;
            data_free(node->data);
            free(node);
            node = NULL;
            return temp;
        } else {
            temp = node->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            data_free(node->data);
            node->data = temp->data;
            node->right = BinaryTree_removeNode(tree, node->right, temp->data, dont_free);
        }
        // Node with 2 children
    }
    return node;
}

void BinaryTree_remove(BinaryTree *tree, void *data, void (*data_free)(void *)) {
    if (tree == NULL || data == NULL) return;
    tree->root = BinaryTree_removeNode(tree, tree->root, data, data_free);
    tree->size--;
}


void BinaryTree_serializeNode(TreeNode *node, ArrayList *data) {
    if (node == NULL) return;
    BinaryTree_serializeNode(node->left, data);
    ArrayList_push(data, node->data);
    BinaryTree_serializeNode(node->right, data);
}

void BinaryTree_serialize(BinaryTree *tree, ArrayList *data) {
    if (tree == NULL) return;
    BinaryTree_serializeNode(tree->root, data);
}

void BinaryTree_freeNode(TreeNode *node, void (*data_free)(void *)) {
    if (node == NULL) return;
    BinaryTree_freeNode(node->left, data_free);
    TreeNode *right = node->right;
    data_free(node->data);
    free(node);
    BinaryTree_freeNode(right, data_free);
}

void BinaryTree_free(BinaryTree *tree, void (*data_free)(void *)) {
    if (tree == NULL) return;
    BinaryTree_freeNode(tree->root, data_free);
    tree->root = NULL;
    tree->size = 0;
}

void BinaryTree_toString(BinaryTree *tree, void (*data_toString)(const void *, char *), char *str) {
    if (tree == NULL) return;
    ArrayList *list = malloc(sizeof(ArrayList));
    ArrayList_init(list);
    BinaryTree_serialize(tree, list);
    ArrayList_toString(list, data_toString, str);
    ArrayList_free(list, dont_free);
    free(list);
}