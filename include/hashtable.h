/*
 * Creator: Kurt M. Weber
 * Created on: 2025-01-05
 *
 * This file is part of filament, a component of the Cosmoverse.
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
 * See file LICENSE for full licensing information.
 */

#ifndef FILAMENT_HASHTABLE_H
#define FILAMENT_HASHTABLE_H

#include <bst.h>
#include <quanta/include/types.h>

typedef uint64 filament_hash;
typedef bool (*filament_hashtable_cmp_callback)(void *, void *);

typedef struct filament_hashtable {
  uint64 version;
  uint64 size; // size is 1-based, so max index of bucket is size-1!
  filament_hashtable_cmp_callback cmpfunc;
  // filament_hashtable_entry *contents[];
  filament_bst contents[];
} filament_hashtable;

typedef filament_bst_result filament_hashtable_result;

// we do this so we can test stuff in clang-repl without it complaining because
// functions aren't name-mangled
#ifdef __cplusplus
extern "C" {
#endif

filament_hashtable *filament_hashtable_factory(uint64 size, qword flags);
filament_hashtable_result filament_hashtable_find(filament_hashtable *table,
                                                  void *key, size_t key_len);
filament_hash filament_hashtable_hash(void *key, size_t len);
uint64 filament_hashtable_size(filament_hashtable *table);
bool filament_hashtable_bucket_put(filament_hashtable *table, uint64 bucket,
                                   void *key, size_t key_len, void *value,
                                   size_t value_len);
bool filament_hashtable_insert(filament_hashtable *table, void *key,
                               size_t key_len, void *value, size_t value_len);

#ifdef __cplusplus
}
#endif

#endif