/* Creator: Kurt M. Weber

 * Created on: 2025-09-02
 *
 * This file is part of filament, a component of the Cosmoverse.
 *
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR.  See file LICENSE for full
 * licensing information.
 */

#define _FILAMENT_LL_C
#define _FILAMENT_LL_PRIVATE
#define _FILAMENT_LL_TEST_C

#include "../include/ll.h"
#include "../induction/include/induction.h"

#include <stdio.h>
#include <string.h>

bool test_ll_factory() {
  filament_ll ll;

  ll = filament_ll_factory();

  INDUCTION_SUBTEST("ll object allocated successfully", ll != NULL)
  INDUCTION_SUBTEST("ll start object null", (ll->start == NULL))

  return true;
}

BEGIN_TEST_SET
INDUCTION_TEST(test_ll_factory, "Test LL factory")
END_TEST_SET