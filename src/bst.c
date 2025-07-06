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

filament_bst_comparison filament_bst_compare(void *v1, size_t v1_len, void *v2,
                                             size_t v2_len);

filament_bst_comparison filament_bst_compare(void *v1, size_t v1_len, void *v2,
                                             size_t v2_len) {}

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
  }

  return true;
}