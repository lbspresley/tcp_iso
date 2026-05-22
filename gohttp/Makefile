# Build Go HTTP client as c-shared and a C test harness

LIB_NAME=libgohttp.so
HEADER_NAME=libgohttp.h
TEST_BIN=test_gohttp

.PHONY: all lib test run clean

all: lib test

lib: $(LIB_NAME)

test: $(TEST_BIN)

$(LIB_NAME): http_client.go go.mod
	GO111MODULE=on go build -buildmode=c-shared -o $(LIB_NAME) http_client.go

$(TEST_BIN): $(LIB_NAME) test_gohttp.c
	$(CC) -O2 -Wall -Wextra -o $(TEST_BIN) test_gohttp.c -L. -lgohttp -Wl,-rpath,'$$ORIGIN'

# Example: make run URL=https://httpbin.org/get
run: $(TEST_BIN)
	LD_LIBRARY_PATH=. ./$(TEST_BIN) $(URL)

clean:
	$(RM) $(LIB_NAME) $(HEADER_NAME) $(TEST_BIN)
