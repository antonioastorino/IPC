# Makefile auto generated using custom generator

CPPFLAGS=-c -Wextra -std=c++14 -O$(OPT) -g
CFLAGS=-c -Wextra -O$(OPT) -g
CPPC=g++
CC=gcc
INC= -I../lib\

.PHONY: all clean check-directory make-opt check-opt-value

all: check-directory

check-directory:
	@[ -d "../build/objects" ] || mkdir -p ../build/objects
	@[ -d "./" ] || mkdir -p ./
	@make SHELL=/bin/bash check-opt-value OPT=$(OPT)

check-opt-value:
	@[ "$(OPT)" == "" ] && make SHELL=/bin/bash make-opt OPT=0 || make SHELL=/bin/bash make-opt OPT=$(OPT)

make-opt:
	@if [ ! -f "../build/.out-$(OPT)" ]; then \
		rm -rf ../build/*; \
		mkdir -p ../build/objects; \
		touch ../build/.out-$(OPT); \
	fi
	@make SHELL=/bin/bash .//receiver-out-$(OPT) OPT=$(OPT)

.//receiver-out-$(OPT): ../build/objects/receiver.o ../build/objects/test.o
	$(CPPC) $(INC) -o $@ $^

../build/objects/receiver.o: ./receiver.cpp ../lib/test.hpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

../build/objects/test.o: ../lib/test.cpp ../lib/test.hpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

clean:
	rm -rf ../build .//receiver-out-*
