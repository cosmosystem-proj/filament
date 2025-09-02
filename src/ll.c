/* Creator: Kurt M. Weber

 * Created on: 2025-09-02
 *
 * This file is part of filament, a component of the Cosmoverse.
 *
 * Licensed under Hippocratic License with clauses:
 * HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR See file LICENSE for full
 * licensing information.
 */

#define _FILAMENT_LL_C
#define _FILAMENT_LL_PRIVATE

#include <stdlib.h>

#include <ll.h>
#include <quanta/include/platform.h>

filament_ll filament_ll_factory() {
  struct filament_ll *ll;

  ll = malloc_wrapper(sizeof(struct filament_ll));
  if (!ll) {
    return NULL;
  }

  ll->start = NULL;

  return (filament_ll)ll;
}