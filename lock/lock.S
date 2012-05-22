#include <xs1.h>

.extern create_lock
.globl create_lock.nstackwords
.linkset create_lock.nstackwords, 0
.globl create_lock
.text
create_lock:
	getr      r0, XS1_RES_TYPE_LOCK
	retsp     0

.extern claim_lock
.globl claim_lock.nstackwords
.linkset claim_lock.nstackwords, 0
.globl claim_lock
.text
claim_lock:
	in      r0, res[r0]
	retsp   0

.extern release_lock
.globl release_lock.nstackwords
.linkset release_lock.nstackwords, 0
.globl release_lock
.text
release_lock:
	out      res[r0], r0
	retsp    0


.extern free_lock
.globl free_lock.nstackwords
.linkset free_lock.nstackwords, 0
.globl free_lock
.text
free_lock:
	freer      res[r0]
	retsp      0

