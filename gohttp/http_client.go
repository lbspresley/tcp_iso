package main

/*
#include <stdint.h>
#include <stdlib.h>
*/
import "C"

import (
	"context"
	"io"
	"net/http"
	"time"
	"unsafe"
)

//export GoHttpGet
func GoHttpGet(url *C.char, timeoutMs C.int) *C.char {
	goURL := C.GoString(url)
	if goURL == "" {
		return C.CString("ERROR: empty URL")
	}

	client := &http.Client{Timeout: time.Duration(timeoutMs) * time.Millisecond}
	ctx, cancel := context.WithTimeout(context.Background(), client.Timeout)
	defer cancel()

	req, err := http.NewRequestWithContext(ctx, http.MethodGet, goURL, nil)
	if err != nil {
		return C.CString("ERROR: " + err.Error())
	}

	resp, err := client.Do(req)
	if err != nil {
		return C.CString("ERROR: " + err.Error())
	}
	defer resp.Body.Close()

	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return C.CString("ERROR: " + err.Error())
	}

	return C.CString(string(body))
}

//export GoFree
func GoFree(ptr *C.char) {
	if ptr != nil {
		C.free(unsafe.Pointer(ptr))
	}
}

func main() {}
