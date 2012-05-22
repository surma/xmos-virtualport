#include <stdint.h>
#include "types.h"
#include "internal_c.h"

void eport_update(expansion_port *ep) {
	update(ep->buffer, ep->strobe, ep->clk, ep->data, ep->type);
}

void eport_create_shift(expansion_port *port, unsigned int s, unsigned int c, unsigned int d) {
	int i;
	port->type = SHIFT;
	port->strobe = s;
	port->clk = c;
	port->data = d;
	for(i = 0; i < MAX_NUM_CHIPS; i++) {
		port->buffer[i] = 0;
	}
	eport_update(port);
}

void eport_create_port(expansion_port *port, unsigned int s) {
	int i;
	port->type = PORT;
	port->strobe = s;
	for(i = 0; i < MAX_NUM_CHIPS; i++) {
		port->buffer[i] = 0;
	}
	eport_update(port);
}

void eport_set_silent(expansion_port *port, int idx, int state) {
	uint8_t byte = idx >> 3;
	uint8_t bit = idx & 0x7;
	port->buffer[byte] = (port->buffer[byte] & ~(1<<bit)) | ((state&1) << bit);
}


void eport_set(expansion_port *port, int idx, int state) {
	eport_set_silent(port, idx, state);
	eport_update(port);
}


void epin_create(expansion_pin *pin, expansion_port *port, int idx) {
	pin->ep_ptr = (int)port;
	pin->idx = idx;
}

void epin_set(expansion_pin *pin) {
	eport_set((expansion_port*)pin->ep_ptr, pin->idx, 1);
}

void epin_unset(expansion_pin *pin) {
	eport_set((expansion_port*)pin->ep_ptr, pin->idx, 0);
}

void esubport_create(expansion_subport *subport, expansion_port *port, uint8_t start, uint8_t len) {
	subport->ep_ptr = (int)port;
	subport->start = start;
	subport->len = len;
}

void esubport_set(expansion_subport *subport, uint8_t v) {
	int i;
	expansion_port *port = (expansion_port*)subport->ep_ptr;
	for(i = 0; i < subport->len; i++) {
		if((v&1<<i) > 0) {
			eport_set_silent(port, subport->start+i, 1);
		} else {
			eport_set_silent(port, subport->start+i, 0);
		}
	}
	eport_update(port);
}

void esubport_pin_create(expansion_pin *pin, expansion_subport *subport, int idx) {
	if(idx >= subport->len) {
		return;
	}
	pin->ep_ptr = subport->ep_ptr;
	pin->idx = subport->start + idx;
}
