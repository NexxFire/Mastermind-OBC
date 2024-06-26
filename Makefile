# Compiler options
CC ?= gcc
CFLAGS = -Wall -Wextra -Iclient/include -Iserver/include -Ilib/libSocket -Ilib/libUtils -Ilib/libButton -Ilib/libLCD -Ilib/libLedMatrix -Ilib/libSegments -L$(PREFIX)/lib -I$(PREFIX)/include
LDFLAGS = -pthread -lncursesw
LDFLAGS_CLIENT = -lwiringPi -lwiringPiDev -lncursesw
PREFIX ?= /usr


# Directories
BUILD_DIR = build
INTER_DIR = $(BUILD_DIR)/intermediate
CLIENT_DIR = client
SERVER_DIR = server
LIBSOCKET_DIR = lib/libSocket
LIBUTILS_DIR = lib/libUtils
LIBBUTTON_DIR = lib/libButton
LIBLCD_DIR = lib/libLCD
LIBLEDMATRIX_DIR = lib/libLedMatrix
LIBSEGMENTS_DIR = lib/libSegments

# Files
CLIENT_SRCS = $(wildcard $(CLIENT_DIR)/src/*.c)
CLIENT_OBJS = $(patsubst $(CLIENT_DIR)/src/%.c,$(INTER_DIR)/%.o,$(CLIENT_SRCS))
SERVER_SRCS = $(wildcard $(SERVER_DIR)/src/*.c)
SERVER_OBJS = $(patsubst $(SERVER_DIR)/src/%.c,$(INTER_DIR)/%.o,$(SERVER_SRCS))
LIBSOCKET_SRCS = $(wildcard $(LIBSOCKET_DIR)/*.c)
LIBSOCKET_OBJS = $(patsubst $(LIBSOCKET_DIR)/%.c,$(INTER_DIR)/%.o,$(LIBSOCKET_SRCS))
LIBUTILS_SRCS = $(wildcard $(LIBUTILS_DIR)/*.c)
LIBUTILS_OBJS = $(patsubst $(LIBUTILS_DIR)/%.c,$(INTER_DIR)/%.o,$(LIBUTILS_SRCS))
LIBBUTTON_SRCS = $(wildcard $(LIBBUTTON_DIR)/*.c)
LIBBUTTON_OBJS = $(patsubst $(LIBBUTTON_DIR)/%.c,$(INTER_DIR)/%.o,$(LIBBUTTON_SRCS))
LIBLCD_SRCS = $(wildcard $(LIBLCD_DIR)/*.c)
LIBLCD_OBJS = $(patsubst $(LIBLCD_DIR)/%.c,$(INTER_DIR)/%.o,$(LIBLCD_SRCS))
LIBLEDMATRIX_SRCS = $(wildcard $(LIBLEDMATRIX_DIR)/*.c)
LIBLEDMATRIX_OBJS = $(patsubst $(LIBLEDMATRIX_DIR)/%.c,$(INTER_DIR)/%.o,$(LIBLEDMATRIX_SRCS))
LIBSEGMENTS_SRCS = $(wildcard $(LIBSEGMENTS_DIR)/*.c)
LIBSEGMENTS_OBJS = $(patsubst $(LIBSEGMENTS_DIR)/%.c,$(INTER_DIR)/%.o,$(LIBSEGMENTS_SRCS))


# Executables
CLIENT_EXECUTABLE = $(BUILD_DIR)/client
SERVER_EXECUTABLE = $(BUILD_DIR)/server

.PHONY: all clean client server

all: $(BUILD_DIR) client server

$(BUILD_DIR):
	mkdir -p $(INTER_DIR)

client: $(BUILD_DIR) $(CLIENT_EXECUTABLE)
	
server: $(BUILD_DIR) $(SERVER_EXECUTABLE)
	

$(CLIENT_EXECUTABLE): $(CLIENT_OBJS) $(LIBSOCKET_OBJS) $(LIBUTILS_OBJS) $(LIBBUTTON_OBJS) $(LIBLCD_OBJS) $(LIBLEDMATRIX_OBJS) $(LIBSEGMENTS_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDFLAGS_CLIENT) $^ -o $@

$(SERVER_EXECUTABLE): $(SERVER_OBJS) $(LIBSOCKET_OBJS) $(LIBUTILS_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(INTER_DIR)/%.o: $(CLIENT_DIR)/src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(INTER_DIR)/%.o: $(SERVER_DIR)/src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(INTER_DIR)/%.o: $(LIBSOCKET_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(INTER_DIR)/%.o: $(LIBUTILS_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(INTER_DIR)/%.o: $(LIBBUTTON_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(INTER_DIR)/%.o: $(LIBLCD_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(INTER_DIR)/%.o: $(LIBLEDMATRIX_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(INTER_DIR)/%.o: $(LIBSEGMENTS_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@



clean:
	rm -rf $(BUILD_DIR)
