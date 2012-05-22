#ifndef VIRTUALPORT_H
#define VIRTUALPORT_H

#include "types.h"

// Create a virtual port driving a shift register. s, c, d are 1-bit ports
// connected to strobe, clock and data of the shift register.
// Currently, a maximum of 32 pins (usually 4 8-bit shift registers)
// is supported.
void vport_create_shift(virtual_port& ep, out port s, out port c, out port d);
// Create a virtual port driving a hardware port.
void vport_create_port(virtual_port& ep, out port s);
// Change the state of the virtual port without forcing an update
// (i.e. only change the buffer).
void vport_set_silent(virtual_port& ep, int idx, int state);
// Set the state of the virutal port. Implies an update.
void vport_set(virtual_port& ep, int idx, int state);
// Refresh the state of the underlying model to represent the buffer.
void vport_update(virtual_port &ep);
// Extract a single pin from an virtual port.
void vpin_create(virtual_pin &pin, virtual_port &ep, int idx);
// Set a virtual pin.
void vpin_set(virtual_pin &pin);
// Unset a virtual pin.
void vpin_unset(virtual_pin &pin);
// Extract a range of pins (a subport) from an virtual port.
void vsubport_create(virtual_subport &subport, virtual_port &ep, uint8_t start, uint8_t len);
// Set the state of a virtual port.
void vsubport_set(virtual_subport &subport, uint8_t v);
// Extrac a single pin from a subport.
void vsubport_pin_create(virtual_pin &pin, virtual_subport &subport, int idx);

#endif // VIRTUALPORT_H
