#ifndef EXPANSION_PORT_H
#define EXPANSION_PORT_H

#include "types.h"

void eport_create(expansion_port& ep, out port s, out port c, out port d);
void eport_set_silent(expansion_port& ep, int idx, int state);
void eport_set(expansion_port& ep, int idx, int state);
void eport_update(expansion_port &ep);
void epin_create(expansion_pin &pin, expansion_port &ep, int idx);
void epin_set(expansion_pin &pin);
void epin_unset(expansion_pin &pin);
void esubport_create(expansion_subport &subport, expansion_port &ep, uint8_t start, uint8_t len);
void esubport_set(expansion_subport &subport, uint8_t v);
void esubport_pin_create(expansion_pin &pin, expansion_subport &subport, int idx);

#endif // EXPANSION_PORT_H
