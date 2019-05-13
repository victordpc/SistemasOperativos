#include "barrier.h"
#include <errno.h>

#ifdef POSIX_BARRIER

/* Wrapper functions to use pthread barriers */

int sys_barrier_init(sys_barrier_t* barrier, unsigned int nthreads) {
	return pthread_barrier_init(barrier, NULL, nthreads);
}

int sys_barrier_destroy(sys_barrier_t* barrier) {
	return pthread_barrier_destroy(barrier);
}

int sys_barrier_wait(sys_barrier_t *barrier) {
	return pthread_barrier_wait(barrier);
}

#else

pthread_mutex_t mutex; /* Cerrojo para la barrera */
pthread_cond_t nHilos; /* Var condicion para los hilos */
int n_elementos; /*Numero de elementos en la barrera a comparar con n_MaxElem*/
int n_MaxElem;

/* Barrier initialization function */
int sys_barrier_init(sys_barrier_t *barrier, unsigned int nr_threads) {
	/* Initialize fields in sys_barrier_t
	 ... To be completed ....
	 */
	n_MaxElem = nr_threads;
	int resultado = 0;
	if ((resultado = pthread_mutex_init(&mutex, NULL) != 0))
		return resultado;
	if ((resultado = pthread_cond_init(&nHilos, NULL) != 0))
		return resultado;

	return 0;
}

/* Destroy barrier resources */
int sys_barrier_destroy(sys_barrier_t *barrier) {
	int resultado = 0;
	if ((resultado = pthread_mutex_destroy(&mutex) != 0))
		return resultado;
	if ((resultado = pthread_cond_destroy(&nHilos) != 0))
		return resultado;
	return 0;
}

/* Main synchronization operation */
int sys_barrier_wait(sys_barrier_t *barrier) {
	/* Implementation outline:
	 - Every thread arriving at the barrier adquires the lock and increments the nr_threads_arrived
	 counter atomically
	 * In the event this is not the last thread to arrive at the barrier, the thread
	 must block in the condition variable
	 * Otherwise...
	 1. Reset the barrier state in preparation for the next invocation of sys_barrier_wait() and
	 2. Wake up all threads blocked in the barrier
	 - Don't forget to release the lock before returning from the function

	 ... To be completed ....
	 */
	pthread_mutex_lock(&mutex);
	n_elementos++;

	if (n_elementos == n_MaxElem) {
		pthread_cond_broadcast(&nHilos);
		n_elementos=0;
	} else {
		while (n_elementos < n_MaxElem) {
			pthread_cond_wait(&nHilos, &mutex);
		}
	}

	pthread_mutex_unlock(&mutex);

	return 0;
}

#endif /* POSIX_BARRIER */
