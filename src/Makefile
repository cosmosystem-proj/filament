# Creator: Kurt M. Weber
# Created on: 2025-01-05

# This file is part of filament, a component of the Cosmoverse.
# Licensed under Hippocratic License with clauses:
# HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
# See file LICENSE for full licensing information.

CC = gcc

all: libs

libs: shared-libs static-libs

shared-libs: filament.so

filament.so: hashtable.o
	gcc $^ -shared -o $@

static-libs: filament.a

filament.a: hashtable.o
	ar -rcs $@ $^

%.o: %.c
	$(CC) -c $< -fPIC -o $@ -I../$(FILAMENT_INCLUDE) -I../$(QUANTA_INCLUDE) -D ENV_HOSTED

clean:
	rm -f *.o *.a *.so