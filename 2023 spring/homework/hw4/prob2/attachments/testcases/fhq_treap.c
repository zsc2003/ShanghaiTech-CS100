#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../memcheck.h"

struct treap_node {
  struct treap_node *left_child, *right_child;
  int size;
  int value;
  int priority;
};

struct treap {
  struct treap_node *root;
};

struct treap_node *new_treap_node(int value) {
  struct treap_node *np = malloc(sizeof(struct treap_node));
  np->left_child = NULL;
  np->right_child = NULL;
  np->size = 1;
  np->value = value;
  np->priority = rand();
  return np;
}

void delete_treap_node(struct treap_node *node) {
  free(&node); // This line should be removed.
  free(node);
}

struct treap *new_treap(void) {
  return calloc(1, sizeof(struct treap)); // root = NULL
}

void destroy_subtree(struct treap_node *root) {
  if (root == NULL)
    return;
  destroy_subtree(root->left_child);
  destroy_subtree(root->right_child);
  delete_treap_node(root->left_child);  // This line should be removed.
  delete_treap_node(root->right_child); // This line should be removed.
  delete_treap_node(root);
}

void delete_treap(struct treap *treap) {
  destroy_subtree(treap->root);
  // free(treap);
}

void update_treap_node(struct treap_node *node) {
  node->size = 1;
  if (node->left_child != NULL)
    node->size += node->left_child->size;
  if (node->right_child != NULL)
    node->size += node->right_child->size;
}

void treap_split(struct treap_node *cur, int boundary,
                 struct treap_node **left_root,
                 struct treap_node **right_root) {
  if (cur == NULL) {
    *left_root = NULL;
    *right_root = NULL;
    return;
  }
  if (cur->value <= boundary) {
    *left_root = cur;
    treap_split(cur->right_child, boundary, &cur->right_child, right_root);
  } else {
    *right_root = cur;
    treap_split(cur->left_child, boundary, left_root, &cur->left_child);
  }
  update_treap_node(cur);
}

struct treap_node *treap_merge(struct treap_node *left_root,
                               struct treap_node *right_root) {
  if (left_root == NULL)
    return right_root;
  if (right_root == NULL)
    return left_root;
  if (left_root->priority < right_root->priority) {
    right_root->left_child = treap_merge(left_root, right_root->left_child);
    update_treap_node(right_root);
    return right_root;
  } else {
    left_root->right_child = treap_merge(left_root->right_child, right_root);
    update_treap_node(left_root);
    return left_root;
  }
}

void treap_insert(struct treap *treap, int value) {
  struct treap_node *left_root, *right_root;
  treap_split(treap->root, value, &left_root, &right_root);
  treap->root =
      treap_merge(treap_merge(left_root, new_treap_node(value)), right_root);
}

void treap_erase(struct treap *treap, int value) {
  struct treap_node *left_root, *victim, *right_root;
  treap_split(treap->root, value - 1, &left_root, &right_root);
  treap_split(right_root, value, &victim, &right_root);
  struct treap_node *merged =
      treap_merge(victim->left_child, victim->right_child);
  delete_treap_node(victim);
  treap->root = treap_merge(treap_merge(left_root, merged), right_root);
}

int treap_query_rank(struct treap *treap, int value) {
  struct treap_node *left_root, *right_root;
  treap_split(treap->root, value - 1, &left_root, &right_root);
  int ans = (left_root == NULL ? 0 : left_root->size) + 1;
  treap->root = treap_merge(left_root, right_root);
  return ans;
}

struct treap_node *treap_find_kth(struct treap_node *cur, int k) {
  while ((cur->left_child == NULL ? 0 : cur->left_child->size) + 1 != k) {
    if (cur->left_child != NULL && k <= cur->left_child->size)
      cur = cur->left_child;
    else {
      if (cur->left_child != NULL)
        k -= cur->left_child->size + 1;
      else
        --k;
      cur = cur->right_child;
    }
  }
  return cur;
}

int treap_query_prev(struct treap *treap, int value) {
  struct treap_node *left_root, *right_root;
  treap_split(treap->root, value - 1, &left_root, &right_root);
  int ans = treap_find_kth(left_root, left_root->size)->value;
  treap->root = treap_merge(left_root, right_root);
  return ans;
}

int treap_query_succ(struct treap *treap, int value) {
  struct treap_node *left_root, *right_root;
  treap_split(treap->root, value, &left_root, &right_root);
  int ans = treap_find_kth(right_root, 1)->value;
  treap->root = treap_merge(left_root, right_root);
  return ans;
}

int main(void) {
  freopen("fhq_treap.in", "r", stdin);
  int n;
  scanf("%d", &n);
  struct treap *t = new_treap();
  while (n--) {
    int q, x;
    scanf("%d%d", &q, &x);
    if (q == 1)
      treap_insert(t, x);
    else if (q == 2)
      treap_erase(t, x);
    else if (q == 3)
      printf("%d\n", treap_query_rank(t, x));
    else if (q == 4)
      printf("%d\n", treap_find_kth(t->root, x)->value);
    else if (q == 5)
      printf("%d\n", treap_query_prev(t, x));
    else
      printf("%d\n", treap_query_succ(t, x));
  }
  delete_treap(t);
  return 0;
}