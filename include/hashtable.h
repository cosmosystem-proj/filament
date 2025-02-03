/*
 * Creator: Kurt M. Weber
 * Created on: 2025-01-05
 *
 * This file is part of quanta, a component of the Cosmoverse.
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
 * See file LICENSE for full licensing information.
 */

#ifndef _FILAMENT_HASHTABLE_H
#define _FILAMENT_HASHTABLE_H

#include <quanta/include/types.h>

typedef uint64 filament_hash;
typedef bool (*filament_hashtable_cmp_callback)(void *, void *);

typedef struct _filament_hashtable_entry _filament_hashtable_entry;

typedef struct _filament_hashtable_entry {
  void *key;
  void *value;
  _filament_hashtable_entry *next;
} _filament_hashtable_entry;

typedef struct filament_hashtable {
  uint64 version;
  uint64 size;
  filament_hashtable_cmp_callback cmpfunc;
  _filament_hashtable_entry contents[];
} filament_hashtable;

#endif