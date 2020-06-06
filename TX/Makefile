# Makefile auto generated using custom generator

CPPFLAGS=-c -Wextra -std=c++14 -O$(OPT) -g
CFLAGS=-c -Wextra -O$(OPT) -g
CPPC=g++
CC=gcc
INC= -I../libheg/include\

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
	@make SHELL=/bin/bash .//transmitter-out-$(OPT) OPT=$(OPT)

.//transmitter-out-$(OPT): ../build/objects/transmitter.o ../build/objects/HEGMap.o ../build/objects/BinayMessageBuilder.o ../build/objects/HEGLog.o ../build/objects/HEGEncoding.o
	$(CPPC) $(INC) -o $@ $^

../build/objects/transmitter.o: ./transmitter.cpp ../libheg/include/BinaryMessageBuilder.hpp ../libheg/include/HEGMap.hpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

../build/objects/HEGMap.o: ../libheg/src/HEGMap.cpp ../libheg/include/HEGMap.hpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

../build/objects/BinayMessageBuilder.o: ../libheg/src/BinayMessageBuilder.cpp ../libheg/include/BinaryMessageBuilder.hpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

../build/objects/HEGLog.o: ../libheg/src/HEGLog.cpp ../libheg/include/HEGLog.hpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

../build/objects/HEGEncoding.o: ../libheg/src/HEGEncoding.cpp ../libheg/include/HEGEncoding.hpp ../libheg/include/HEGDataTypes.hpp ../libheg/include/HEGLog.hpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

clean:
	rm -rf ../build .//transmitter-out-*
