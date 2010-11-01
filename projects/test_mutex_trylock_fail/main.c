#include <stdio.h>
#include <mutex.h>

#include <thread.h>
#include <flags.h>
#include <kernel.h>

mutex_t mutex;

void second_thread(void) {
    puts(" 2nd: trying to lock mutex...");
    mutex_trylock(&mutex);
    puts(" 2nd: done.");
}

tcb second_tcb;
char second_stack[8192];

int main(void)
{
    puts("main: locking mutex...");
    mutex_lock(&mutex);

    puts("main: creating thread...");
    int pid = thread_create(&second_tcb, second_stack, 8192, PRIORITY_MAIN-1, CREATE_STACKTEST, second_thread, "nr2");
    
    puts("main: thread created. Unlocking mutex...");
    mutex_unlock(&mutex, true);

    puts("main: mutex unlocked.");
}
