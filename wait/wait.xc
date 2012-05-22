#include <platform.h>
#include "wait.h"

void wait(unsigned ticks) {
	timer t;
	unsigned time;

	t :> time;
	time += ticks;
	t when timerafter(time) :> void;
}
