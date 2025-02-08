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

bool test_hashing() {
  uint8 i = 0;
  for (i = 0; i <= 5; i++) {
    printf("Testing value %lli, hash = ", i);
    printf("%llx\n", filament_hashtable_hash(&i, 1));
  }

  return true;
}

bool test_hashtable_factory() {
  filament_hashtable *tbl;
  uint64 size = 256;
  uint64 version = 0;

  tbl = filament_hashtable_factory(size);

  if (!tbl) {
    printf("\tAllocation failed\n");
    return false;
  }

  if (tbl->size != size) {
    printf("\tSizing failed, requested is %lli but actual is %lli\n", size,
           tbl->size);
    return false;
  }

  if (tbl->version != version) {
    printf("\tVersion failed, correct is %lli but actual is %lli\n", version,
           tbl->version);
    return false;
  }

  return true;
}

BEGIN_TEST_SET
INDUCTION_TEST(test_hashing, "Test hashing")
INDUCTION_TEST(test_hashtable_factory, "Hashtable factory test")
END_TEST_SET