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
  uint8 key_1 = 5;
  uint16 val_1 = 2332;

  filament_bst bst = filament_bst_factory();

  INDUCTION_SUBTEST(
      "Insert key 1",
      (filament_bst_insert(bst, &key_1, sizeof(key_1), &val_1, sizeof(val_1))))

  uint8 key_2 = 7;
  uint16 val_2 = 69;

  INDUCTION_SUBTEST(
      "Insert key 2",
      (filament_bst_insert(bst, &key_2, sizeof(key_2), &val_2, sizeof(val_2))))

  uint8 key_3 = 7;
  uint16 val_3 = 70;

  INDUCTION_SUBTEST("Insert key 3",
                    (!filament_bst_insert(
                        bst, &key_3, sizeof(key_3), &val_3,
                        sizeof(val_3)))) // note the negative--this call should
                                         // return false due to a duplicate key

  uint8 key_4 = 3;
  uint16 val_4 = 70;

  INDUCTION_SUBTEST(
      "Insert key 4",
      (filament_bst_insert(bst, &key_4, sizeof(key_4), &val_4, sizeof(val_4))))

  uint8 key_5 = 18;
  uint16 val_5 = 44;

  INDUCTION_SUBTEST(
      "Insert key 5",
      (filament_bst_insert(bst, &key_5, sizeof(key_5), &val_5, sizeof(val_5))))

  return true;
}

BEGIN_TEST_SET
INDUCTION_TEST(test_bst_factory, "Test BST factory")
INDUCTION_TEST(test_bst_compare, "Test BST comparison")
INDUCTION_TEST(test_bst_node_factory, "Test BST node factory")
INDUCTION_TEST(test_bst_insert, "Test BST insert")
END_TEST_SET