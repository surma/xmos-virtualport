#include <stdint.h>
#include "types.h"
#include "update.h"
#include "lock/lock.h"

void vport_update(virtual_port *ep) {
	claim_lock(ep->lock);
	update(ep->buffer, ep->strobe, ep->clk, ep->data, ep->type);
	release_lock(ep->lock);
}

void vport_create_shift(virtual_port *port, unsigned int s, unsigned int c, unsigned int d) {
	int i;
	port->type = SHIFT;
	port->lock = create_lock();
	port->strobe = s;
	port->clk = c;
	port->data = d;
	for(i = 0; i < MAX_NUM_CHIPS; i++) {
		port->buffer[i] = 0;
	}
	vport_update(port);
}

void vport_create_port(virtual_port *port, unsigned int s) {
	int i;
	port->type = PORT;
	port->lock = create_lock();
	port->data = s;
	for(i = 0; i < MAX_NUM_CHIPS; i++) {
		port->buffer[i] = 0;
	}
	vport_update(port);
}

void vport_set_silent(virtual_port *port, int idx, int state) {
	uint8_t byte = idx >> 3;
	uint8_t bit = idx & 0x7;
	port->buffer[byte] = (port->buffer[byte] & ~(1<<bit)) | ((state&1) << bit);
}


void vport_set(virtual_port *port, int idx, int state) {
	vport_set_silent(port, idx, state);
	vport_update(port);
}


void vpin_create(virtual_pin *pin, virtual_port *port, int idx) {
	pin->ep_ptr = (int)port;
	pin->idx = idx;
}

void vpin_set(virtual_pin *pin) {
	vport_set((virtual_port*)pin->ep_ptr, pin->idx, 1);
}

void vpin_unset(virtual_pin *pin) {
	vport_set((virtual_port*)pin->ep_ptr, pin->idx, 0);
}

void vsubport_create(virtual_subport *subport, virtual_port *port, uint8_t start, uint8_t len) {
	subport->ep_ptr = (int)port;
	subport->start = start;
	subport->len = len;
}

void vsubport_set(virtual_subport *subport, uint8_t v) {
	int i;
	virtual_port *port = (virtual_port*)subport->ep_ptr;
	for(i = 0; i < subport->len; i++) {
		if((v&1<<i) > 0) {
			vport_set_silent(port, subport->start+i, 1);
		} else {
			vport_set_silent(port, subport->start+i, 0);
		}
	}
	vport_update(port);
}

void vsubport_pin_create(virtual_pin *pin, virtual_subport *subport, int idx) {
	if(idx >= subport->len) {
		return;
	}
	pin->ep_ptr = subport->ep_ptr;
	pin->idx = subport->start + idx;
}
