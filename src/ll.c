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

#include <stdlib.h>

#include <ll.h>
#include <quanta/include/platform.h>
#include <quanta/include/types.h>

void filament_ll_append(filament_ll ll, void *data, size_t size) {
  filament_ll_node node = filament_ll_node_factory();
  filament_ll_node cur;

  if (!node) {
    return;
  }

  node->data.data = data;
  node->data.size = size;

  if (!(ll->start)) {
    ll->start = node;
    ll->pos = ll->start;
  } else {
    cur = ll->start;
    while (cur->next) {
      cur = cur->next;
    }
    cur->next = node;
  }

  return;
}

filament_ll filament_ll_factory() {
  struct filament_ll *ll;

  ll = malloc_wrapper(sizeof(struct filament_ll));
  if (!ll) {
    return NULL;
  }

  ll->start = NULL;
  ll->pos = NULL;

  return (filament_ll)ll;
}

filament_ll_data *filament_ll_next(filament_ll ll) {
  if (!ll->pos) {
    return NULL;
  } else {
    filament_ll_data *rv = &(ll->pos->data);
    ll->pos = ll->pos->next;
    return rv;
  }
}

filament_ll_node filament_ll_node_factory() {
  struct filament_ll_node *llnode;

  llnode = malloc_wrapper(sizeof(struct filament_ll_node));
  if (!llnode) {
    return NULL;
  }

  llnode->next = NULL;
  llnode->data.data = NULL;
  llnode->data.size = 0;

  return (filament_ll_node)llnode;
}

void filament_ll_rewind(filament_ll ll) {
  if (ll && ll->start) {
    ll->pos = ll->start;
  }

  return;
}