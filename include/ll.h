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

#ifdef _FILAMENT_LL_PRIVATE
struct filament_ll_node {
  struct filament_ll_node *next;
  void *data;
};

struct filament_ll {
  struct filament_ll_node *start;
};
#endif

typedef struct filament_ll *filament_ll;

#endif
