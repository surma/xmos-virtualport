#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>

#define MAX_NUM_CHIPS 1

typedef enum {
	SHIFT,
	PORT
} eport_type_t;

typedef struct {
	unsigned int strobe;
	unsigned int clk;
	unsigned int data;
	uint8_t buffer[MAX_NUM_CHIPS];
	eport_type_t type;
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
