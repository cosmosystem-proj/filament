/* Creator: Kurt M. Weber
 * Created on: 2025-01-05
 *
 * This file is part of quanta, a component of the Cosmoverse.
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
 * See file LICENSE for full licensing information.
 */

#include <quanta/include/platform.h>
#include <quanta/include/types.h>
#include <include/hashtable.h>

/*
 * filament_hashtable *filament_hashtable_factory(uint64 size)
 * Creates, initializes, and returns a hash table object
 *
 * size - number of buckets in the hash table
 *
 * Must be destroyed with filament_hashtable_destroy()
 */

filament_hashtable *filament_hashtable_factory(uint64 size) {
  filament_hashtable *new =
      malloc_wrapper(sizeof(filament_hashtable) +
                     ((size_t)size * sizeof(_filament_hashtable_entry)));

  // Return NULL on error
  if (!new) {
    return NULL;
  }

  new->size = size;
  new->version = 0;

  for (uint64 i = 0; i < size; i++) {
    new->contents[i].key = NULL;
    new->contents[i].value = NULL;
    new->contents[i].next = NULL;
  }

  return new;
}

filament_hash filament_hashtable_hash(void *key, size_t len) {
  const qword c1 = 16840508717339396339UL;
  const qword c2 = 11061967308696050939UL;

  size_t padded_len = 0;

  // Copy the key into an internal buffer and pad it to a multiple of 8
  // bytes (64 bits)
  if ((len % 8) == 0) {
    padded_len = len;
  } else {
    padded_len = len + (8 - (len % 8));
  }

  byte *padded_key = malloc_wrapper(len + (len % 8));

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

  for (uint64 i = 0; i < padded_len; i += 8) {
    hash ^= (((qword *)padded_key)[i] ^= c2);
  }

  return hash;
}