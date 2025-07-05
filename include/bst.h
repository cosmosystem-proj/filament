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
typedef struct filament_bst_node {
  uint64 key_len;
  uint64 val_len;
  void *key;
  void *val;

  filament_bst_node *left;
  filament_bst_node *right;
} filament_bst_node;

typedef struct filament_bst_raw {
  filament_bst_node *root;
} filament_bst_raw;

typedef filament_bst_raw *filament_bst;

#endif