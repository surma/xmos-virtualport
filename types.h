#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>
#include "../lock/lock.h"

#define MAX_NUM_CHIPS 4

typedef enum {
	SHIFT,
	PORT
} vport_type_t;

typedef struct {
	unsigned int strobe;
	unsigned int clk;
	unsigned int data;
	lock lock;
	uint8_t buffer[MAX_NUM_CHIPS];
	vport_type_t type;
} virtual_port;

typedef struct {
	int ep_ptr;
	uint8_t idx;
} virtual_pin;

typedef struct {
	int ep_ptr;
	uint8_t start;
	uint8_t len;
} virtual_subport;
#endif // TYPES_H
