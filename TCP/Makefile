.PHONY: all server client clean update

all:
	make -C tcp-server
	make -C tcp-client

server:
	make -C tcp-server

client:
	make -C tcp-client

clean:
	make clean -C tcp-client
	make clean -C tcp-server

update:
	tcp-server/makeMakefile.sh
	tcp-client/makeMakefile.sh