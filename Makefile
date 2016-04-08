.PHONY:all
all:udp_server udp_client

udp_server:udp_server.c
	gcc -o udp_server udp_server.c
udp_client:udp_client.c
	gcc -o udp_client udp_client.c

.PHONY:clean
clean:
	rm -rf udp_client udp_server
