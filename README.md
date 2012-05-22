virtualports are an abstraction to simplify manipulating GPIO pins on the [XMOS](http://xmos.com) architecture.

A virtualport is backed by either an actual hardware port or by 3 pins driving a shift register, effectively enabling arbitrary sized GPIO ports.

virtualports are thread safe. Multiple virtualports can be backed by the same hardware port and still be shared across multiple threads without the risk of raising resource exceptions.

Example
=======

	#include <xs1.h>
	#include "xmos-virtualport/virtualport.h"
	#include "xmos-virtualport/wait/wait.h"

	out port leds = XS1_PORT_8A;

	void counter(virtual_subport& leds) {
		int i = 0;
		while(1) {
			i = (i+1)%16;
			vsubport_set(leds, i);
			wait(50000000);
		}
	}

	void shifter(virtual_subport& leds) {
		int i = 1;
		while(1) {
			i = (i << 1) | (i >> 3);
			vsubport_set(leds, i);
			wait(50000000);
		}
	}

	int main() {
		virtual_port p;
		virtual_subport led1, led2;

		vport_create_port(p, leds);
		vsubport_create(led1, p, 0, 4);
		vsubport_create(led2, p, 4, 4);

		par {
			counter(led1);
			shifter(led2);
		}
	}

License
=======

MIT/X license.
