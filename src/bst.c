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