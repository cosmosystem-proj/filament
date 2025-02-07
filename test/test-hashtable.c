/* Creator: Kurt M. Weber
 * Created on: 2025-02-06
 *
 * This file is part of quanta, a component of the Cosmoverse.
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
 * See file LICENSE for full licensing information.
 */

#include <stdio.h>
#include "../include/hashtable.h"
#include "../induction/include/induction.h"
#include "../quanta/include/types.h"

bool test() {
  uint8 i = 0;
  for (i = 0; i <= 5; i++) {
    printf("Testing value %lli, hash = ", i);
    printf("%llx\n", filament_hashtable_hash(&i, 1));
  }

  return true;
}

BEGIN_TEST_SET
INDUCTION_TEST(test, "Test test")
END_TEST_SET