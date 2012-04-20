#include <xs1.h>
#include <platform.h>
#include <stdint.h>
#include "types.h"
#include "../misc/wait.h"

void update(uint8_t buffer[], out port strobe, out port clk, out port data) {
	int i, d;
	strobe <: 0;
	for(i = MAX_NUM_CHIPS*8-1; i >= 0; i--) {
		if ((buffer[i>>3] & (1<<(i&7))) > 0) {
			d = 1;
		} else {
			d = 0;
		}
		data <: d;
		wait(10);
		clk <: 1;
		wait(10);
		clk <: 0 ;
		wait(10);
	}
	strobe <: 1;
}
