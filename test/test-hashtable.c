/* Creator: Kurt M. Weber
 * Created on: 2025-02-06
 *
 * This file is part of filament, a component of the Cosmoverse.
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
 * See file LICENSE for full licensing information.
 */

#include "../include/hashtable.h"
#include "../induction/include/induction.h"
#include "../quanta/include/types.h"
#include <stdio.h>
#include <string.h>

bool test_hashing() {
  uint8 i = 0;
  for (i = 0; i <= 5; i++) {
    printf("Testing value %lli, hash = ", i);
    printf("%llx\n", filament_hashtable_hash(&i, 1));
  }

  {
    const char *key = "Liverpool club song";
    printf("Testing value %s, hash = ", key);
    printf("%llx\n", filament_hashtable_hash((void *)key, strlen(key) + 1));
  }

  {
    const char *key = "You'll Never Walk Alone";
    printf("Testing value %s, hash = ", key);
    printf("%llx\n", filament_hashtable_hash((void *)key, strlen(key) + 1));
  }

  return true;
}

bool test_hashtable_factory() {
  filament_hashtable *tbl;
  uint64 size = 256;
  uint64 version = 0;

  tbl = filament_hashtable_factory(size, 0);

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

  if (tbl->contents[0]) {
    printf("\tcontents[0] not null\n");
  }

  if (tbl->contents[size - 1]) {
    printf("\tcontents[%d] not null\n", size - 1);
  }

  return true;
}

bool test_hashtable_size() {
  filament_hashtable *table = filament_hashtable_factory(256, 0);

  if (!table) {
    printf("\tTable creation failed\n");
    return false;
  }

  if (filament_hashtable_size(table) != 256) {
    printf("Hashtable size not a match, should be %lli but is %lli\n", 256,
           table);
    return false;
  }

  return true;
}

bool test_insertion() {
  filament_hashtable *table = filament_hashtable_factory(256, 0);
  const char *key = "Liverpool club song";
  const char *value = "You'll Never Walk Alone";

  if (!filament_hashtable_insert(table, (void *)key, sizeof(key), (void *)value,
                                 sizeof(value))) {
    printf("\tInsertion failed\n");
    return false;
  }

  if (filament_hashtable_insert(table, (void *)key, sizeof(key), (void *)value,
                                sizeof(value))) {
    printf("\tDuplicate insertion succeeded, this should not happen\n");
    return false;
  }

  const char *key2 = "Everton club song";
  const char *value2 = "Forever Everton";

  if (!filament_hashtable_insert(table, (void *)key2, sizeof(key2),
                                 (void *)value2, sizeof(value2))) {
    printf("\tSecond insertion failed\n");
    return false;
  }

  return true;
}

bool test_finding() {
  filament_hashtable *table = filament_hashtable_factory(256, 0);

  const char *key = "Liverpool club song";
  const char *value = "You'll Never Walk Alone";

  if (!filament_hashtable_insert(table, (void *)key, sizeof(key), (void *)value,
                                 sizeof(value))) {
    printf("\tInsertion failed\n");
    return false;
  }

  const char *key2 = "Everton club song";
  const char *value2 = "Forever Everton";

  if (!filament_hashtable_insert(table, (void *)key2, sizeof(key2),
                                 (void *)value2, sizeof(value2))) {
    printf("\tSecond insertion failed\n");
    return false;
  }

  filament_hashtable_result r1 =
      filament_hashtable_find(table, (void *)key, sizeof(key));
  if (!r1.val || (strcmp(r1.val, value) != 0)) {
    printf("\tFirst find failed\n");
    return false;
  } else {
    printf("\tFound key %s, value %s\n", r1.key, r1.val);
  }

  filament_hashtable_result r2 =
      filament_hashtable_find(table, (void *)key2, sizeof(key2));
  if (!r2.val || (strcmp(r2.val, value2) != 0)) {
    printf("\tSecond find failed\n");
    return false;
  } else {
    printf("\tFound key %s, value %s\n", r2.key, r2.val);
  }

  filament_hashtable_result r3 = filament_hashtable_find(
      table, (void *)"Paint Your Wagon", sizeof("Paint Your Wagon"));
  if (r3.val) {
    printf("\tThird find succeeded and it should not have, key %s returned "
           "value %s\n",
           r3.key, r3.val);
    return false;
  }

  return true;
}

BEGIN_TEST_SET
INDUCTION_TEST(test_hashing, "Test hashing")
INDUCTION_TEST(test_hashtable_factory, "Hashtable factory test")
INDUCTION_TEST(test_hashtable_size, "Hashtable size retrieval test")
INDUCTION_TEST(test_insertion, "Insertion test")
INDUCTION_TEST(test_finding, "Finding test")
END_TEST_SET