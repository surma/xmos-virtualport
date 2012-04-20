#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>

#define MAX_NUM_CHIPS 1

typedef struct {
	unsigned int strobe;
	unsigned int clk;
	unsigned int data;
	uint8_t buffer[MAX_NUM_CHIPS];
} expansion_port;

typedef struct {
	int ep_ptr;
	uint8_t idx;
} expansion_pin;

typedef struct {
	int ep_ptr;
	uint8_t start;
	uint8_t len;
} expansion_subport;
#endif // TYPES_H
