#include "BinaryTree.h"
/**
 * Initializes the root and comparator.
 */
void BinaryTree_init(BinaryTree *tree, int (*comparator)(const void *, const void *)) {
    if (tree == NULL) return;
    tree->root = NULL;
    tree->size = 0;
    tree->comparator = comparator;
}

/**
 * Insertion is done by standard binary search. Default comparator is used
 * if comparator == NULL. Else, the special comparator is used.
 */
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
        /**
         * The following loop finds the place where the element should be.
         */
        while (curr != NULL) {
            prev = curr;
            // if curr->data < data, the if statement will be executed
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

/**
 * Finds an element in the tree using the default comparator. Does so by
 * standard binary search.
 */
void* BinaryTree_find(BinaryTree *tree, const void *data) {
    if (tree == NULL || data == NULL) return NULL;
    TreeNode *curr = tree->root;
    while (curr != NULL) {
        // if curr->data < data, the if statement will be executed
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

/**
 * Finds an element one in the binary tree two and returns 0 if found, -1 otherwise.
 */
int BinaryTree_findComparator(const void *one, const void *two) {
    BinaryTree *courses = (BinaryTree*)two;
    if (BinaryTree_find(courses, one) == NULL) return -1;
    return 0;
}

/**
 * Removes the data node assuming node is the root.
 */
TreeNode* BinaryTree_removeNode(BinaryTree *tree, TreeNode *node, void *data, void (*data_free)(void *)) {
    if (node == NULL || data == NULL) return NULL;
    // if statement executes if node->data < data
    if (tree->comparator(node->data, data) > 0) {
        node->left = BinaryTree_removeNode(tree, node->left, data, data_free);
    }
    else if (tree->comparator(node->data, data) < 0) {
        node->right = BinaryTree_removeNode(tree, node->right, data, data_free);
    }
    else {
        // The data was found
        TreeNode *temp;
        // If only one child
        if (node->left == NULL) {
            // Swap the child and delete the node
            temp = node->right;
            data_free(node->data);
            free(node);
            node = NULL;
            return temp;
        } else if (node->right == NULL) {
            // Swap the child and delete the node
            temp = node->left;
            data_free(node->data);
            free(node);
            node = NULL;
            return temp;
        } else {
            // Means there are two children
            temp = node->right;
            /*
             * Find the next biggest element.
             */
            while (temp->left != NULL) {
                temp = temp->left;
            }
            /*
             * Make the node point to the next biggest element and then remove it from the tree
             * so there's only 1 copy.
            */
            data_free(node->data);
            node->data = temp->data;
            node->right = BinaryTree_removeNode(tree, node->right, temp->data, dont_free);
        }
        // Node with 2 children
    }
    return node;
}

/**
 * Removes the node from the tree by calling removeNode starting at the root.
 */
void BinaryTree_remove(BinaryTree *tree, void *data, void (*data_free)(void *)) {
    if (tree == NULL || data == NULL) return;
    tree->root = BinaryTree_removeNode(tree, tree->root, data, data_free);
    tree->size--;
}

/**
 * Starts inorder traversal at the node and appends the value of the data
 * to the ArrayList
 */
void BinaryTree_serializeNode(TreeNode *node, ArrayList *list) {
    if (node == NULL) return;
    BinaryTree_serializeNode(node->left, list);
    ArrayList_push(list, node->data);
    BinaryTree_serializeNode(node->right, list);
}

/**
 * Serializes the tree to an instantiated Arraylist.
 */
void BinaryTree_serialize(BinaryTree *tree, ArrayList *data) {
    if (tree == NULL) return;
    BinaryTree_serializeNode(tree->root, data);
}

/**
 * Destructor for node. Performs in order traversal while calling data's destructor
 * and freeing the node itself.
 */
void BinaryTree_freeNode(TreeNode *node, void (*data_free)(void *)) {
    if (node == NULL) return;
    BinaryTree_freeNode(node->left, data_free);
    TreeNode *right = node->right;
    data_free(node->data);
    free(node);
    BinaryTree_freeNode(right, data_free);
}

/**
 * Frees the entire tree by calling freeNode starting at the root.
 */
void BinaryTree_free(BinaryTree *tree, void (*data_free)(void *)) {
    if (tree == NULL) return;
    BinaryTree_freeNode(tree->root, data_free);
    tree->root = NULL;
    tree->size = 0;
}

/**
 * Converts it to a string representation by first serializing then using
 * ArrayList_toString() to convert to string represntation.
 * Note: this is a common theme of iterating through BinaryTrees.
 * We create an ArrayList, inialize it, serialize the tree into that ArrayList,
 * then we perform our iteraive loop and destruct the ArrayList.
 */
void BinaryTree_toString(BinaryTree *tree, void (*data_toString)(const void *, char *), char *str) {
    if (tree == NULL) return;
    ArrayList *list = malloc(sizeof(ArrayList));
    ArrayList_init(list);
    BinaryTree_serialize(tree, list);
    ArrayList_toString(list, data_toString, str);
    ArrayList_free(list, dont_free);
    free(list);
}