# Creator: Kurt M. Weber
# Created on: 2025-02-06

# This file is part of filament, a component of the Cosmoverse.
# Licensed under Hippocratic License with clauses:
# HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
# See file LICENSE for full licensing information.

CC = gcc
DEPS = ../filament.so

all: test-hashtable test-bst

test-bst: test-bst.so
	../induction/induction ./test-bst.so

test-hashtable: test-hashtable.so
	../induction/induction ./test-hashtable.so

%.so: %.o
	$(CC) -shared -o $@ $^ -L ../src -l:filament.a

%.o: %.c
	$(CC) -g -c $< -fPIC -o $@ -I../$(FILAMENT_INCLUDE) -I../$(QUANTA_INCLUDE) -D ENV_HOSTED

clean:
	rm -f *.o *.a *.so