/* Creator: Kurt M. Weber
 * Created on: 2025-07-05
 *
 * This file is part of filament, a component of the Cosmoverse.
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
 * See file LICENSE for full licensing information.
 */

#include "../include/bst.h"
#include "../induction/include/induction.h"
#include "../quanta/include/types.h"
#include <stdio.h>
#include <string.h>

bool test_bst_factory() {
  filament_bst bst = filament_bst_factory();

  if (!bst) {
    return false;
  } else {
    return true;
  }
}

BEGIN_TEST_SET
INDUCTION_TEST(test_bst_factory, "Test BST factory")
END_TEST_SET