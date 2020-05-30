# Makefile auto generated using custom generator

CPPFLAGS=-c -Wextra -std=c++14 -O$(OPT) -g
CFLAGS=-c -Wextra -O$(OPT) -g
CPPC=g++
CC=gcc
INC=
.PHONY: all clean check-directory make-opt check-opt-value

all: check-directory

check-directory:
	@[ -d "build/objects" ] || mkdir -p build/objects
	@[ -d "build" ] || mkdir -p build
	@make SHELL=/bin/bash check-opt-value OPT=$(OPT)

check-opt-value:
	@[ "$(OPT)" == "" ] && make SHELL=/bin/bash make-opt OPT=0 || make SHELL=/bin/bash make-opt OPT=$(OPT)

make-opt:
	@if [ ! -f "build/.out-$(OPT)" ]; then \
		rm -rf build/*; \
		mkdir -p build/objects; \
		touch build/.out-$(OPT); \
	fi
	@make SHELL=/bin/bash prj-out-$(OPT) OPT=$(OPT)

prj-out-$(OPT): build/objects/receiver.o
	$(CPPC) $(INC) -o $@ $^

build/objects/receiver.o: ./receiver.cpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

clean:
	rm -rf build prj-out-*
