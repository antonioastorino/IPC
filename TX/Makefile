# Makefile auto generated using custom generator

CPPFLAGS=-c -Wextra -std=c++14 -O$(OPT) -g
CFLAGS=-c -Wextra -O$(OPT) -g
CPPC=g++
CC=gcc
INC= -I../../HEG/include\
 -I../include\

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

../build/objects/transmitter.o: ./transmitter.cpp ../../HEG/include/BinaryMessageBuilder.hpp ../../HEG/include/HEGMap.hpp ../include/IPCConstants.hpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

../build/objects/HEGMap.o: ../../HEG/src/HEGMap.cpp ../../HEG/include/HEGMap.hpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

../build/objects/BinayMessageBuilder.o: ../../HEG/src/BinayMessageBuilder.cpp ../../HEG/include/BinaryMessageBuilder.hpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

../build/objects/HEGLog.o: ../../HEG/src/HEGLog.cpp ../../HEG/include/HEGLog.hpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

../build/objects/HEGEncoding.o: ../../HEG/src/HEGEncoding.cpp ../../HEG/include/HEGEncoding.hpp ../../HEG/include/HEGDataTypes.hpp ../../HEG/include/HEGLog.hpp 
	$(CPPC) $(INC) $(CPPFLAGS) $< -o $@

clean:
	rm -rf ../build .//transmitter-out-*
