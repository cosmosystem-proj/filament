/*
 * Creator: Kurt M. Weber
 * Created on: 2025-01-05
 *
 * This file is part of filament, a component of the Cosmoverse.
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
 * See file LICENSE for full licensing information.
 */

#ifndef _FILAMENT_BST_H
#define _FILAMENT_BST_H

#include <quanta/include/types.h>

typedef struct filament_bst_node filament_bst_node;
typedef struct filament_bst_node {
  size_t key_len;
  size_t val_len;
  void *key;
  void *val;

  filament_bst_node *left;
  filament_bst_node *right;
} filament_bst_node;

typedef struct filament_bst_raw {
  filament_bst_node *root;
} filament_bst_raw;

typedef enum filament_bst_comparison {
  FILAMENT_BST_LESSTHAN,
  FILAMENT_BST_EQUAL,
  FILAMENT_BST_GREATERTHAN
} filament_bst_comparison;

typedef struct filament_bst_result {
  void *val;
  size_t len;
} filament_bst_result;

typedef filament_bst_raw *filament_bst;

filament_bst filament_bst_factory();
bool filament_bst_insert(filament_bst bst, void *key, size_t key_len, void *val,
                         size_t val_len);

#ifdef _FILAMENT_BST_C
filament_bst_comparison filament_bst_compare(void *v1, size_t v1_len, void *v2,
                                             size_t v2_len);
filament_bst_node *filament_bst_node_factory(void *key, size_t key_len,
                                             void *val, size_t val_len);
#endif

#endif