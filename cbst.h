#ifndef BST_H
#define BST_H

#include "../ctree/ctree.h"

#define INIT_BST(NAME, TYPE, CMPFN, COPYFN, PRINTFN)                          \
INIT_TREE(NAME, TYPE, CMPFN, COPYFN, PRINTFN)                                 \
                                                                              \
extern tree_##NAME bst_##NAME##_insert(TYPE e, tree_##NAME t);                \
extern tree_##NAME bst_##NAME##_delete(TYPE e, tree_##NAME t);                \
                                                                              \
tree_##NAME bst_##NAME##_insert(TYPE e, tree_##NAME t){                       \
  tree_##NAME l = t;                                                          \
                                                                              \
  if (tree_##NAME##_isEmpty(t))                                               \
    return tree_##NAME##_cons(e,tree_##NAME##_new(), tree_##NAME##_new());    \
                                                                              \
  while(!tree_##NAME##_isEmpty(t)) {                                          \
    TYPE f = tree_##NAME##_root(t);                                           \
    if((CMPFN)(&e, &f) <= 0){                                                 \
      if(tree_##NAME##_isEmpty(tree_##NAME##_left(t))) {                      \
        t->left =                                                             \
          tree_##NAME##_cons(e, tree_##NAME##_new(), tree_##NAME##_new());    \
        t = tree_##NAME##_left(t);                                            \
      }                                                                       \
      t = tree_##NAME##_left(t);                                              \
    } else {                                                                  \
      if (tree_##NAME##_isEmpty(tree_##NAME##_right(t))){                     \
        t->right =                                                            \
          tree_##NAME##_cons(e, tree_##NAME##_new(), tree_##NAME##_new());    \
        t = tree_##NAME##_right(t);                                           \
      }                                                                       \
      t = tree_##NAME##_right(t);                                             \
    }                                                                         \
  }                                                                           \
  return l;                                                                   \
}                                                                             \
                                                                              \
tree_##NAME bst_##NAME##_delete(TYPE e, tree_##NAME t) {                      \
  tree_##NAME l = t, pl = NULL, pr = NULL, next = NULL;                       \
  while(!tree_##NAME##_isEmpty(t) &&                                          \
        (CMPFN)(&e, &(t->value)) != 0) {                                      \
    if((CMPFN)(&e, &(t->value)) < 0) {                                        \
      pl = t;                                                                 \
      pr = tree_##NAME##_new();                                               \
      t = tree_##NAME##_left(t);                                              \
    }                                                                         \
    else {                                                                    \
      pl = tree_##NAME##_new();                                               \
      pr = t;                                                                 \
      t = tree_##NAME##_right(t);                                             \
    }                                                                         \
  }                                                                           \
                                                                              \
  if (tree_##NAME##_isEmpty(t))                                               \
    return l;                                                                 \
                                                                              \
  if (tree_##NAME##_isEmpty(tree_##NAME##_left(t)) &&                         \
      tree_##NAME##_isEmpty(tree_##NAME##_right(t))) {                        \
    if (t == l) {                                                             \
      free(t);                                                                \
      return tree_##NAME##_new();                                             \
    }                                                                         \
    if (!tree_##NAME##_isEmpty(pl)){                                          \
      free(pl->left);                                                         \
      pl->left = tree_##NAME##_new();                                         \
    } else {                                                                  \
      free(pr->right);                                                        \
      pr->right = tree_##NAME##_new();                                        \
    }                                                                         \
  }                                                                           \
                                                                              \
  else if (tree_##NAME##_isEmpty(tree_##NAME##_left(t)) &&                    \
           !tree_##NAME##_isEmpty(tree_##NAME##_right(t))) {                  \
    if (t == l) {                                                             \
      pl = tree_##NAME##_right(t);                                            \
      free(t);                                                                \
      return pl;                                                              \
    }                                                                         \
    next = tree_##NAME##_right(t);                                            \
    free(t);                                                                  \
  }                                                                           \
                                                                              \
  else if (!tree_##NAME##_isEmpty(tree_##NAME##_left(t)) &&                   \
    tree_##NAME##_isEmpty(tree_##NAME##_right(t))) {                          \
    if (t == l) {                                                             \
      pl = tree_##NAME##_left(t);                                             \
      free(t);                                                                \
      return pl;                                                              \
    }                                                                         \
    next = tree_##NAME##_left(t);                                             \
    free(t);                                                                  \
  }                                                                           \
                                                                              \
  else if (!tree_##NAME##_isEmpty(tree_##NAME##_left(t)) &&                   \
           !tree_##NAME##_isEmpty(tree_##NAME##_right(t))) {                  \
    pr = t;                                                                   \
    pl = tree_##NAME##_new();                                                 \
    next = tree_##NAME##_right(t);                                            \
    while (!tree_##NAME##_isEmpty(tree_##NAME##_left(next))) {                \
      pr = tree_##NAME##_new();                                               \
      pl = next;                                                              \
      next = tree_##NAME##_left(next);                                        \
    }                                                                         \
    t->value = tree_##NAME##_root(next);                                      \
    if (!tree_##NAME##_isEmpty(tree_##NAME##_right(next))) {                  \
      tree_##NAME tmp = tree_##NAME##_right(next);                            \
      free(next);                                                             \
      next = tmp;                                                             \
    }                                                                         \
    else {                                                                    \
      free(next);                                                             \
      next = tree_##NAME##_new();                                             \
    }                                                                         \
  }                                                                           \
  if (!tree_##NAME##_isEmpty(pl)) {                                           \
    pl->left = next;                                                          \
  } else {                                                                    \
    pr->right = next;                                                         \
  }                                                                           \
  return l;                                                                   \
}
#endif /* BST_H */
