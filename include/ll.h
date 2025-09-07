/* Creator: Kurt M. Weber

 * Created on: 2025-09-02
 *
 * This file is part of filament, a component of the Cosmoverse.
 *
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR See file LICENSE for full
 * licensing information.
 */

#ifndef _FILAMENT_LL_H
#define _FILAMENT_LL_H

#include <quanta/include/types.h>

typedef struct filament_ll_data {
  void *data;
  size_t size;
} filament_ll_data;

#ifdef _FILAMENT_LL_PRIVATE
struct filament_ll_node {
  struct filament_ll_node *next;
  struct filament_ll_data data;
};

struct filament_ll {
  struct filament_ll_node *start;
  struct filament_ll_node *pos;
};

typedef struct filament_ll_node *filament_ll_node;

filament_ll_node filament_ll_node_factory();
#endif

typedef struct filament_ll *filament_ll;

void filament_ll_append(filament_ll ll, void *data, size_t size);
filament_ll filament_ll_factory();
filament_ll_data *filament_ll_next(filament_ll ll);
void filament_ll_rewind(filament_ll ll);

#endif
