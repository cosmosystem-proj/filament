/* Creator: Kurt M. Weber
 * Created on: 2025-01-05
 *
 * This file is part of filament, a component of the Cosmoverse.
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
 * See file LICENSE for full licensing information.
 */

#include <bst.h>
#include <include/hashtable.h>
#include <quanta/include/platform.h>
#include <quanta/include/types.h>

/*
 * filament_hashtable *filament_hashtable_factory(uint64 size)
 * Creates, initializes, and returns a hash table object
 *
 * size - number of buckets in the hash table
 *
 * Must be destroyed with filament_hashtable_destroy()
 */

uint64 filament_hashtable_bucket_calc(filament_hash hash,
                                      filament_hashtable *table) {
  return hash % filament_hashtable_size(table);
}

filament_hashtable *filament_hashtable_factory(uint64 size, qword flags) {
  filament_hashtable *new = malloc_wrapper(
      sizeof(filament_hashtable) + ((size_t)size * sizeof(filament_bst)));

  // Return NULL on error
  if (!new) {
    return NULL;
  }

  new->size = size;
  new->version = 0;

  for (uint64 i = 0; i < size; i++) {
    new->contents[i] = filament_bst_factory();
  }

  return new;
}

bool filament_hashtable_insert(filament_hashtable *table, void *key,
                               size_t key_len, void *value, size_t value_len) {
  // ensure valid values
  if (!table || !key || !value || !key_len || !value_len) {
    return false;
  }

  filament_hash hash = filament_hashtable_hash(key, key_len);

  uint64 bucket = filament_hashtable_bucket_calc(hash, table);

  return filament_hashtable_bucket_put(table, bucket, key, key_len, value,
                                       value_len);
}

bool filament_hashtable_bucket_put(filament_hashtable *table, uint64 bucket,
                                   void *key, size_t key_len, void *value,
                                   size_t value_len) {

  if (bucket > table->size - 1) {
    return false;
  }

  if (!table->contents) {
    return false;
  }

  return filament_bst_insert(table->contents[bucket], key, key_len, value,
                             value_len);
}

uint64 filament_hashtable_size(filament_hashtable *table) {
  if (!table) {
    return 0;
  }

  return table->size;
}

void *filament_hashtable_search(filament_hashtable *table, void *key,
                                size_t key_len, size_t *value_len) {
  // value_len can be null if the caller does not need to know the length
  // return null if not found

  filament_hash hash = filament_hashtable_hash(key, key_len);

  uint64 bucket = filament_hashtable_bucket_calc(hash, table);
}

filament_hash filament_hashtable_hash(void *key, size_t len) {
  const qword c1 = 16840508717339396339UL;
  const qword c2 = 11061967308696050939UL;
  const qword c3 = 16747499861120173679UL;

  size_t padded_len = 0;

  // Copy the key into an internal buffer and pad it to a multiple of 8
  // bytes (64 bits)
  if ((len % 8) == 0) {
    padded_len = len;
  } else {
    padded_len = len + (8 - (len % 8));
  }

  byte *padded_key = malloc_wrapper(padded_len);

  if (!padded_key) {
    return 0;
  }

  for (uint64 i = 0; i < len; i++) {
    padded_key[i] = ((byte *)key)[i];
  }

  for (uint64 i = len; i < padded_len; i++) {
    padded_key[i] = '\0';
  }

  filament_hash hash = c1;

  for (uint64 i = 0; i < padded_len; i++) {
    hash *= c3;
    hash ^= ((padded_key)[i] ^= c2);
  }

  free_wrapper(padded_key);

  return hash;
}