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

uint64 testvals[] = {4, 32, 128, 592, 395232, 23469449, 230320323};

bool test_ll_append() {
  filament_ll ll = filament_ll_factory();

  if (!ll) {
    return false;
  }

  filament_ll_append(ll, (void *)&testvals[0], sizeof(uint64));
  INDUCTION_SUBTEST("ll->start pointer set to a valid value",
                    (ll->start != NULL))
  INDUCTION_SUBTEST("ll->start data pointer correctly set",
                    (ll->start->data.data == &testvals[0]))
  INDUCTION_SUBTEST("ll->start data size correctly set",
                    ll->start->data.size = sizeof(uint64))

  filament_ll_append(ll, (void *)&testvals[1], sizeof(uint64));
  INDUCTION_SUBTEST("ll->start->next pointer set to a valid value",
                    (ll->start->next != NULL))
  INDUCTION_SUBTEST("ll->start->next data pointer correctly set",
                    (ll->start->next->data.data == &testvals[1]))
  INDUCTION_SUBTEST("ll->start->next data size correctly set",
                    ll->start->next->data.size = sizeof(uint64))

  filament_ll_append(ll, (void *)&testvals[2], sizeof(uint64));
  INDUCTION_SUBTEST("ll->start->next->next pointer set to a valid value",
                    (ll->start->next->next != NULL))
  INDUCTION_SUBTEST("ll->start->next->next data pointer correctly set",
                    (ll->start->next->next->data.data == &testvals[2]))
  INDUCTION_SUBTEST("ll->start->next->next data size correctly set",
                    ll->start->next->next->data.size = sizeof(uint64))
  return true;
}

bool test_ll_factory() {
  filament_ll ll;

  ll = filament_ll_factory();

  INDUCTION_SUBTEST("ll object allocated successfully", ll != NULL)
  INDUCTION_SUBTEST("ll start object null", (ll->start == NULL))

  return true;
}

bool test_ll_node_factory() {
  filament_ll_node node;

  node = filament_ll_node_factory();

  INDUCTION_SUBTEST("ll node allocated successfully", (node != NULL))
  INDUCTION_SUBTEST("node data initialized correctly",
                    ((node->data.data == NULL) && (node->data.size == 0)))
  INDUCTION_SUBTEST("node next initialized correctly", (node->next == NULL))
  return true;
}

bool test_ll_next() {
  size_t count = sizeof(testvals) / sizeof(testvals[0]);

  filament_ll ll = filament_ll_factory();

  for (uint64 i = 0; i < count; i++) {
    filament_ll_append(ll, &testvals[i], sizeof(testvals[i]));
  }

  uint64 j = 0;

  filament_ll_data *data;

  while (data = filament_ll_next(ll)) {
    printf("Value %lld is %lld, size %lld\n", j, *(uint64 *)(data->data),
           data->size);
    INDUCTION_SUBTEST("Values correct",
                      ((*(uint64 *)data->data == testvals[j]) &&
                       (data->size = sizeof(testvals[j]))))
    j++;
  }

  filament_ll ll2 = filament_ll_factory();
  INDUCTION_SUBTEST("Should return NULL on an empty list",
                    (filament_ll_next(ll2) == NULL))
  return true;
}

bool test_ll_rewind() {
  filament_ll ll = filament_ll_factory();

  INDUCTION_SUBTEST("pos should be NULL", (ll->pos == NULL))

  filament_ll_rewind(ll);

  INDUCTION_SUBTEST("pos should still be NULL after rewind on an empty list",
                    (ll->pos == NULL))

  size_t count = sizeof(testvals) / sizeof(testvals[0]);

  for (uint64 i = 0; i < count; i++) {
    filament_ll_append(ll, &testvals[i], sizeof(testvals[i]));
  }

  INDUCTION_SUBTEST("pos should equal start after data is appended",
                    (ll->pos == ll->start))

  filament_ll_next(ll);
  filament_ll_next(ll);
  filament_ll_next(ll);

  INDUCTION_SUBTEST("pos should NOT equal start after some next operations",
                    (ll->pos != ll->start))

  filament_ll_rewind(ll);
  INDUCTION_SUBTEST("pos should equal start after rewind operation",
                    (ll->pos == ll->start))

  return true;
}

BEGIN_TEST_SET
INDUCTION_TEST(test_ll_factory, "Test LL factory")
INDUCTION_TEST(test_ll_node_factory, "Test LL node factory")
INDUCTION_TEST(test_ll_append, "Test LL append")
INDUCTION_TEST(test_ll_next, "Test LL next")
INDUCTION_TEST(test_ll_rewind, "Test LL rewind")
END_TEST_SET