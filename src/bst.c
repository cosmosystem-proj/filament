/* Creator: Kurt M. Weber
 * Created on: 2025-01-05
 *
 * This file is part of filament, a component of the Cosmoverse.
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
 * See file LICENSE for full licensing information.
 */

#define _FILAMENT_BST_C

#include <include/bst.h>
#include <quanta/include/platform.h>
#include <quanta/include/types.h>
#include <quanta/include/util.h>

filament_bst_comparison filament_bst_compare(void *v1, size_t v1_len, void *v2,
                                             size_t v2_len);

filament_bst_comparison filament_bst_compare(void *v1, size_t v1_len, void *v2,
                                             size_t v2_len) {
  // Return FILAMENT_BST_GREATERTHAN if v1 > v2, FILAMENT_BST_EQUAL if v1 = v2,
  // FILAMENT_BST_LESSTHAN if v1 < v2

  // Pay careful attention to how this is explained, on little-endian systems
  // it may produce counterintuitive results.  Because it works from lowest to
  // highest address doing byte-byte comparisons, it won't necessarily give the
  // same result as a straightforward numerical comparison would.

  size_t shortest = MIN((v1_len), (v2_len));

  // byte-by-byte comparison of the two values presented to us

  for (size_t i = 0; i < shortest; i++) {
    if (((byte *)v1)[i] > ((byte *)v2)[i]) {
      return FILAMENT_BST_GREATERTHAN;
    } else if (((byte *)v1)[i] < ((byte *)v2)[i]) {
      return FILAMENT_BST_LESSTHAN;
    }
  }

  // if we've gotten to this point, then if the two values are of the same
  // length then they're also equal
  if (v1_len == v2_len) {
    return FILAMENT_BST_EQUAL;
  }

  // If their lengths are unequal, but their values from 0...shortest bytewise
  // are equal, then we report the longer one as the greater--so if v1 is longer
  // than v2, return >, otherwise return <
  if (v1_len > v2_len) {
    return FILAMENT_BST_GREATERTHAN;
  } else {
    return FILAMENT_BST_LESSTHAN;
  }
}

filament_bst filament_bst_factory() {
  filament_bst_raw *new =
      (filament_bst_raw *)malloc_wrapper(sizeof(filament_bst_raw));

  // return NULL on error
  if (!new) {
    return (filament_bst)NULL;
  }

  new->root = (filament_bst_node *)NULL;

  return new;
}

filament_bst_result filament_bst_find(filament_bst bst, void *key, size_t len) {
  filament_bst_result res = {.key = 0, .key_len = 0, .val = 0, .val_len = 0};
  filament_bst_node *cur = NULL;

  if (!bst) {
    return res;
  }

  cur = bst->root;

  while (cur) {
    filament_bst_comparison cmp =
        filament_bst_compare(key, len, cur->key, cur->key_len);

    switch (cmp) {
    case FILAMENT_BST_EQUAL:
      res.key = cur->key;
      res.key_len = cur->key_len;
      res.val = cur->val;
      res.val_len = cur->val_len;
      return res;
    case FILAMENT_BST_LESSTHAN:
      cur = cur->left;
      break;
    case FILAMENT_BST_GREATERTHAN:
      cur = cur->right;
      break;
    }
  }

  return res;
}

bool filament_bst_insert(filament_bst bst, void *key, size_t key_len, void *val,
                         size_t val_len) {

  // Make sure bst is a valid pointer
  // We check first so we don't waste cycles allocating then deallocating memory
  // for the node if it turns out we can't do anything with it
  if (!bst) {
    return false;
  }

  filament_bst_node *cur = bst->root;
  filament_bst_node **curptr = &(bst->root);

  while (cur) {
    filament_bst_node *next = NULL;
    filament_bst_comparison cmp =
        filament_bst_compare(key, key_len, cur->key, cur->key_len);

    switch (cmp) {
    case FILAMENT_BST_EQUAL:
      return false;
    case FILAMENT_BST_GREATERTHAN:
      curptr = &(cur->right);
      cur = cur->right;
      break;
    case FILAMENT_BST_LESSTHAN:
      curptr = &(cur->left);
      cur = cur->left;
      break;
    }
  }

  filament_bst_node *new =
      filament_bst_node_factory(key, key_len, val, val_len);
  if (!new) {
    return false;
  }
  *curptr = new;

  return true;
}

filament_bst_node *filament_bst_node_factory(void *key, size_t key_len,
                                             void *val, size_t val_len) {
  filament_bst_node *node = malloc_wrapper(sizeof(filament_bst_node));

  if (!node) {
    return NULL;
  }

  node->key = key;
  node->key_len = key_len;
  node->val = val;
  node->val_len = val_len;
  node->left = NULL;
  node->right = NULL;

  return node;
}