#include <assert.h>
#include <stdlib.h>

typedef struct node node_t;

struct node {
    /*points at data*/
    void *data;
    /*pointers to next nodes | *left < *self, *right > *self */
    node_t *left;
    node_t *right;
};

typedef struct {
    /*ptr to first node*/
    node_t *root;
    /*ptr to comparison function: defines how nodes are sorted*/
    int (*cmp)(void*, void*);
} tree_t;

/******************************************************************************/

/*function prototypes */
tree_t *tree_make(int func(void*, void*));
int tree_isempty(tree_t *tree);
void *tree_search(tree_t *tree, void *key);
tree_t *tree_insert(tree_t *tree, void *value);
void tree_inorder(tree_t *tree, void process(void*));
void tree_free(tree_t *tree);
int tree_max_depth(tree_t *tree);
int tree_size(tree_t *tree);
int tree_isstick(tree_t *tree);

/******************************************************************************/

/*returns a pointer to the tree*/
tree_t
*tree_make(int func(void*, void*)) {
    tree_t *tree = NULL;
    /*assigns space to the tree (all are just pointers)*/
    tree = malloc(sizeof(*tree));
    assert(tree != NULL);

    /*tree is empty, so no root */
    tree->root = NULL;
    /*saves comparison function*/
    tree->cmp = func;

    /*returns a pointer to the tree*/
    return tree;
}

/******************************************************************************/

int
tree_isempty(tree_t *tree) {
    /*makes sure tree exists*/
    assert(tree!=NULL);
    /*a tree is empty if it has no nodes (so root is NULL) */
    return tree->root == NULL;
}

/******************************************************************************/

/*returns a pointer to the data that matches key, or NULL if it is not found*/
void
*tree_search(tree_t *tree, void *key) {
    assert(tree!=NULL);
    node_t *curr_node = tree->root;
    int outcome;

    /*loops until curr_node points at nothing*/
    while (curr_node) {
        /*key is less than current data, so if present it must be left*/
        if ((outcome=(*(tree->cmp))(key, curr_node->data)) < 0) {
            curr_node = curr_node->left;
        /*key is greater than current data, so if present it must be right*/
        } else if (outcome > 0) {
            curr_node = curr_node->right;
        /*data has been found*/
        } else {
            return curr_node->data;
        }
    }
    /*curr_node == NULL then key is not in the tree (return null ptr)*/
    return curr_node;
}

/******************************************************************************/

tree_t
*tree_insert(tree_t *tree, void *value) {
    assert(tree!=NULL);
    node_t *curr_node = NULL, *new_node, *next = tree->root;
    int outcome;

    while (next) {
        curr_node = next;
        /*value is less than current data, so insterted left */
        if ((outcome=(*(tree->cmp))(value, curr_node->data)) < 0) {
            next = curr_node->left;
        /*value is greater than current data, so inserted right*/
        } else if (outcome > 0) {
            next = curr_node->right;
        /*value is already in tree: tree returns unmodified*/
        } else {
            return tree;
        }
    }

    /*creates the new node holding the value to be inserted*/
    new_node = malloc(sizeof(*new_node));
    assert(new_node);
    new_node->data = value;
    new_node->left = new_node->right = NULL;

    /*tree has no nodes yet*/
    if (!curr_node) {
        tree->root = new_node;
    /*data should be inserted left*/
    } else if (outcome < 0) {
        curr_node->left = new_node;
    /*data should be inserted right */
    } else {
        curr_node->right = new_node;
    }
    return tree;
}

/******************************************************************************/

static void
r_tree_inorder(node_t *root, void process(void*)) {
    if (root) {
        r_tree_inorder(root->left, process);
        process(root->data);
        r_tree_inorder(root->right, process);
    }
}

/******************************************************************************/

void
tree_inorder(tree_t *tree, void process(void*)) {
    assert(tree!=NULL);
    r_tree_inorder(tree->root, process);
}

/******************************************************************************/

static void
r_tree_free(node_t *root) {
    if (root) {
        r_tree_free(root->left);
        r_tree_free(root->right);
        free(root);
    }
}

/******************************************************************************/

void
tree_free(tree_t *tree) {
    assert(tree!=NULL);
    r_tree_free(tree->root);
    free(tree);
}

/******************************************************************************/
static int r_tree_max_depth(node_t *root) {
    int d1, d2;

    if (root == NULL) {
        return 0;
    }

    d1 = r_tree_max_depth(root->left);
    d2 = r_tree_max_depth(root->right);

    if (d1 > d2) {
        return 1 + d1;
    } else {
        return 1 + d2;
    }
}
/******************************************************************************/
int tree_max_depth(tree_t *tree) {
    assert(tree != NULL);
    return r_tree_max_depth(tree->root);
}
/******************************************************************************/
static int r_tree_size(node_t *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + r_tree_size(root->left) + r_tree_size(root->right);
}

/******************************************************************************/
int tree_size(tree_t *tree) {
    assert(tree != NULL);
    return r_tree_size(tree->root);
}

/******************************************************************************/
static int r_tree_isstick(node_t *root) {
    if (root == NULL) {
        return 1;
    } else if (root->left && root->right) {
        return 0;
    } else {
        return r_tree_isstick(root->left) * r_tree_isstick(root->right);
    }
}

/******************************************************************************/
int tree_isstick(tree_t *tree) {
    assert(tree != NULL);
    return r_tree_isstick(tree);
}
