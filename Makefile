# Creator: Kurt M. Weber
# Created on: 2025-01-05

# This file is part of quanta, a component of the Cosmoverse.
# Licensed under Hippocratic License with clauses:
# HL3-CL-ECO-EXTR-FFD-MEDIA-MY-SUP-SV-TAL-USTA-XUAR
# See file LICENSE for full licensing information.

export FILAMENT_INCLUDE=./include
export QUANTA_INCLUDE=.

.PHONY: test

all: 
	cd src && make all
	cd induction && make all
	ln -sf src/filament.a filament.a
	ln -sf src/filament.so filament.so

test:
	cd test && make all

clean:
	cd src && make clean
	cd induction && make clean
	cd test && make clean
	rm -f *.o *.a *.so