#ifndef LOCK_H
#define LOCK_H

typedef unsigned lock;

lock create_lock();
void claim_lock(lock l);
void release_lock(lock l);
void free_lock(lock l);

#endif //LOCK_H
