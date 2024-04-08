BUILD_INTERMEDIATE = build/intermediate
BUILD_CLIENT = $(BUILD_INTERMEDIATE)/client
BUILD_SERVER = $(BUILD_INTERMEDIATE)/server

CLIENT_SRC = client/src
SERVER_SRC = server/src

INCLUDE_CLIENT = client/include
INCLUDE_SERVER = server/include
CFLAGS = -Wall -Werror

all: client server

client: $(BUILD_CLIENT)/init.o $(BUILD_CLIENT)/show.o
	mkdir -p $(BUILD_CLIENT)
	gcc $(CFLAGS) -o build/$@ $(CLIENT_SRC)/client.c $^ -I $(INCLUDE_CLIENT)

$(BUILD_CLIENT)/init.o: $(CLIENT_SRC)/init.c | $(BUILD_CLIENT)
	gcc $(CFLAGS) -o $@ -c $< -I $(INCLUDE_CLIENT)

$(BUILD_CLIENT)/show.o: $(CLIENT_SRC)/show.c | $(BUILD_CLIENT)
	gcc $(CFLAGS) -o $@ -c $< -I $(INCLUDE_CLIENT)

server: 
	# TODO: Implement server build

$(BUILD_CLIENT) $(BUILD_SERVER):
	mkdir -p $@

clean:
	rm -rf build/*

.PHONY: all client server clean # This is to avoid conflicts with files named all, client, server, clean
