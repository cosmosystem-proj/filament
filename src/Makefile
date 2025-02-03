# Creator: Kurt M. Weber
# Created on: 2025-01-05

# This file is part of quanta, a component of the Cosmoverse.
# Licensed under Hippocratic License with clauses:
# HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
# See file LICENSE for full licensing information.

CC = gcc

all: filament.a

filament.a: hashtable.o
	ar -r filament.a hashtable.o

%.o: %.c
	$(CC) -c $< -o $@ -I../$(FILAMENT_INCLUDE) -I../$(QUANTA_INCLUDE) -D ENV_HOSTED

clean:
	rm -f *.o *.a