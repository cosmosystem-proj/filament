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

  if (tbl->contents[0]) {
    printf("\tcontents[0] not null\n");
  }

  if (tbl->contents[size - 1]) {
    printf("\tcontents[%d] not null\n");
  }

  return true;
}

bool test_entry_factory() {
  const char *key = "Liverpool club song";
  const char *value = "You'll Never Walk Alone";

  filament_hashtable_entry *entry = filament_hashtable_entry_factory(
      (void *)key, strlen(key) + 1, (void *)value, strlen(value) + 1);

  if (!entry) {
    printf("\tFailed to allocate entry\n");
    return false;
  }

  if (strcmp(key, entry->key) != 0) {
    printf("\tKey not a match, should be %s but is %s\n", key, entry->key);
    return false;
  }

  if (entry->key_len != strlen(key) + 1) {
    printf("\tKey length not a match, should be %lli but is %lli\n",
           strlen(key) + 1, entry->key_len);
    return false;
  }

  if (strcmp(value, entry->value) != 0) {
    printf("\tValue not a match, should be %s but is %s\n", value,
           entry->value);
    return false;
  }

  if (entry->value_len != strlen(value) + 1) {
    printf("\tValue length not a match, should be %lli but is %lli\n",
           strlen(value) + 1, entry->value_len);
    return false;
  }

  if (entry->left) {
    printf("\tleft pointer not null\n");
    return false;
  }

  if (entry->right) {
    printf("\tright pointer not null\n");
  }

  return true;
}

bool test_hashtable_size() {
  filament_hashtable *table = filament_hashtable_factory(256);

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
  filament_hashtable *table = filament_hashtable_factory(256);
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

BEGIN_TEST_SET
INDUCTION_TEST(test_hashing, "Test hashing")
INDUCTION_TEST(test_hashtable_factory, "Hashtable factory test")
INDUCTION_TEST(test_entry_factory, "Entry factory test")
INDUCTION_TEST(test_hashtable_size, "Hashtable size retrieval test")
INDUCTION_TEST(test_insertion, "Insertion test")
END_TEST_SET