/* Creator: Kurt M. Weber
 * Created on: 2025-07-05
 *
 * This file is part of filament, a component of the Cosmoverse.
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
 * See file LICENSE for full licensing information.
 */

#define _FILAMENT_BST_C
#define _FILAMENT_BST_TEST_C

#include "../include/bst.h"
#include "../induction/include/induction.h"
#include "../quanta/include/types.h"
#include <stdio.h>
#include <string.h>

uint8 test_keys[] = {5, 7, 8, 10, 3, 45, 9, 28};
uint16 test_vals[] = {2332, 60, 70, 44, 12993, 42, 593, 1003};

bool test_bst_factory() {
  filament_bst bst = filament_bst_factory();

  if (!bst) {
    return false;
  } else {
    return true;
  }
}

const char *test_bst_comparison_to_text(filament_bst_comparison val) {
  switch (val) {
  case FILAMENT_BST_EQUAL:
    return "EQUAL";
  case FILAMENT_BST_GREATERTHAN:
    return "GREATERTHAN";
  case FILAMENT_BST_LESSTHAN:
    return "LESSTHAN";
  }
}

bool test_bst_compare() {
  filament_bst_comparison result;

  {
    uint8 a = 1, b = 2;
    printf("One byte values, v1 = %hhd, v2 = %hhd, should return LESSTHAN...",
           a, b);

    result = filament_bst_compare(&a, sizeof(a), &b, sizeof(b));

    printf("%s\n", test_bst_comparison_to_text(result));
    if (result != FILAMENT_BST_LESSTHAN) {
      return false;
    }
  }

  {
    uint8 a = 2, b = 1;
    printf(
        "One byte values, v1 = %hhd, v2 = %hhd, should return GREATERTHAN...",
        a, b);

    result = filament_bst_compare(&a, sizeof(a), &b, sizeof(b));

    printf("%s\n", test_bst_comparison_to_text(result));
    if (result != FILAMENT_BST_GREATERTHAN) {
      return false;
    }
  }

  {
    uint8 a = 2, b = 2;
    printf("One byte values, v1 = %hhd, v2 = %hhd, should return EQUAL...", a,
           b);

    result = filament_bst_compare(&a, sizeof(a), &b, sizeof(b));

    printf("%s\n", test_bst_comparison_to_text(result));
    if (result != FILAMENT_BST_EQUAL) {
      return false;
    }
  }

  {
    uint16 a = 0x394A, b = 0x21D5;
    printf("Two byte values, v1 = %hd, v2 = %hd, should return LESSTHAN...", a,
           b);

    result = filament_bst_compare(&a, sizeof(a), &b, sizeof(b));

    printf("%s\n", test_bst_comparison_to_text(result));
    if (result != FILAMENT_BST_LESSTHAN) {
      return false;
    }
  }

  {
    uint16 a = 0x21D5, b = 0x394A;
    printf("Two byte values, v1 = %hd, v2 = %hd, should return GREATERTHAN...",
           a, b);

    result = filament_bst_compare(&a, sizeof(a), &b, sizeof(b));

    printf("%s\n", test_bst_comparison_to_text(result));
    if (result != FILAMENT_BST_GREATERTHAN) {
      return false;
    }
  }

  {
    uint16 a = 0x21D5, b = 0x21D5;
    printf("Two byte values, v1 = %hd, v2 = %hd, should return EQUAL...", a, b);

    result = filament_bst_compare(&a, sizeof(a), &b, sizeof(b));

    printf("%s\n", test_bst_comparison_to_text(result));
    if (result != FILAMENT_BST_EQUAL) {
      return false;
    }
  }

  {
    uint32 a = 0x21D5C38B;
    uint16 b = 0xC38B;
    printf("Four vs. two byte values, v1 = %d, v2 = %hd, should return "
           "GREATERTHAN...",
           a, b);

    result = filament_bst_compare(&a, sizeof(a), &b, sizeof(b));

    printf("%s\n", test_bst_comparison_to_text(result));
    if (result != FILAMENT_BST_GREATERTHAN) {
      return false;
    }
  }

  {
    uint16 a = 0xC38B;
    uint32 b = 0x21D5C38B;
    printf("Two vs. four byte values, v1 = %hd, v2 = %d, should return "
           "LESSTHAN...",
           a, b);

    result = filament_bst_compare(&a, sizeof(a), &b, sizeof(b));

    printf("%s\n", test_bst_comparison_to_text(result));
    if (result != FILAMENT_BST_LESSTHAN) {
      return false;
    }
  }
  return true;
}

bool test_bst_node_factory() {
  uint8 key = 65;
  uint64 val = 32532531;

  filament_bst_node *node =
      filament_bst_node_factory(&key, sizeof(key), &val, sizeof(val));

  INDUCTION_SUBTEST("Node creation", node)
  INDUCTION_SUBTEST("Key assigned properly", (node->key == &key))
  INDUCTION_SUBTEST("Key length assigned properly",
                    (node->key_len == sizeof(key)))
  INDUCTION_SUBTEST("Value assigned properly", (node->val == &val))
  INDUCTION_SUBTEST("Value length assigned properly",
                    (node->val_len == sizeof(val)))
  INDUCTION_SUBTEST("Left branch NULL", (!node->left))
  INDUCTION_SUBTEST("Right branch NULL", (!node->right))

  return true;
}

bool test_bst_insert() {

  filament_bst bst = filament_bst_factory();

  INDUCTION_SUBTEST(
      "Insert key 1",
      (filament_bst_insert(bst, &test_keys[0], sizeof(test_keys[0]),
                           &test_vals[0], sizeof(test_vals[0]))))

  INDUCTION_SUBTEST(
      "Insert key 2",
      (filament_bst_insert(bst, &test_keys[1], sizeof(test_keys[1]),
                           &test_vals[1], sizeof(test_vals[1]))))

  INDUCTION_SUBTEST(
      "Insert key 3",
      (filament_bst_insert(bst, &test_keys[2], sizeof(test_keys[2]),
                           &test_vals[2], sizeof(test_vals[2]))))

  INDUCTION_SUBTEST(
      "Insert key 4",
      (filament_bst_insert(bst, &test_keys[3], sizeof(test_keys[3]),
                           &test_vals[3], sizeof(test_vals[3]))))

  INDUCTION_SUBTEST(
      "Re-inserting key 1: should not be possible",
      (!filament_bst_insert(
          bst, &test_keys[0], sizeof(test_keys[0]), &test_vals[0],
          sizeof(test_vals[0])))) // note the negative--this call should
                                  // return false due to a duplicate key

  INDUCTION_SUBTEST(
      "Re-inserting key 2: should not be possible",
      (!filament_bst_insert(bst, &test_keys[1], sizeof(test_keys[1]),
                            &test_vals[1], sizeof(test_vals[1]))))

  INDUCTION_SUBTEST(
      "Re-inserting key 3: should not be possible",
      (!filament_bst_insert(bst, &test_keys[2], sizeof(test_keys[2]),
                            &test_vals[2], sizeof(test_vals[2]))))

  INDUCTION_SUBTEST(
      "Re-inserting key 4: should not be possible",
      (!filament_bst_insert(bst, &test_keys[3], sizeof(test_keys[3]),
                            &test_vals[3], sizeof(test_vals[3]))))

  return true;
}

bool test_bst_find() {
  size_t count = sizeof(test_keys) / sizeof(test_keys[0]);

  filament_bst bst = filament_bst_factory();

  if (!bst) {
    return false;
  }

  for (uint8 i = 0; i < count; i++) {
    filament_bst_insert(bst, &test_keys[i], sizeof(test_keys[i]), &test_vals[i],
                        sizeof(test_vals[i]));
  }

  for (uint8 i = 0; i < count; i++) {
    printf("Looking for key %hhu, should be %hu, is ", test_keys[i],
           test_vals[i]);
    uint16 *val =
        (uint16 *)(filament_bst_find(bst, &test_keys[i], sizeof(test_keys[i]))
                       .val);
    printf("%hu", *val);
    INDUCTION_SUBTEST("", (*val == test_vals[i]))
  }
  return true;
}

BEGIN_TEST_SET
INDUCTION_TEST(test_bst_factory, "Test BST factory")
INDUCTION_TEST(test_bst_compare, "Test BST comparison")
INDUCTION_TEST(test_bst_node_factory, "Test BST node factory")
INDUCTION_TEST(test_bst_insert, "Test BST insert")
INDUCTION_TEST(test_bst_find, "Test BST find")
END_TEST_SET