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

bool filament_bst_insert(filament_bst bst, void *key, size_t key_len, void *val,
                         size_t val_len) {

  // Make sure bst is a valid pointer
  // We check first so we don't waste cycles allocating then deallocating memory
  // for the node if it turns out we can't do anything with it
  if (!bst) {
    return false;
  }

  filament_bst_node *new =
      (filament_bst_node *)malloc_wrapper(sizeof(filament_bst_node));

  if (!new) {
    return false;
  }

  new->key = key;
  new->key_len = key_len;
  new->val = val;
  new->val_len = val_len;
  new->left = NULL;
  new->right = NULL;

  filament_bst_node *cur = bst->root;
  if (!cur) {
    bst->root = new;
    return true;
  }

  while (cur) {
    filament_bst_node *next;
    filament_bst_comparison cmp =
        filament_bst_compare(cur->key, cur->key_len, key, key_len);

    if (cmp == FILAMENT_BST_EQUAL) {
      free_wrapper(new);
      return false;
    }

    if (cmp == FILAMENT_BST_GREATERTHAN) {
      if (!cur->right) {
        cur->right = new;
        break;
      } else {
        cur = cur->right;
        continue;
      }
    }

    if (cmp == FILAMENT_BST_LESSTHAN) {
      if (!cur->left) {
        cur->left = new;
        break;
      } else {
        cur = cur->left;
        continue;
      }
    }
  }

  return true;
}