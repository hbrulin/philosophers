#include <pthread.h>

#include <unistd.h>
#include <stdio.h>

void wait(void)
{
    sleep(2); //pour les projets, utiliser usleep : La fonction usleep() suspend l'exécution du programme appelant durant (au moins) usec microsecondes.

    printf("Done.\n");
}

int main(void)
{
    pthread_t thread; //thread descriptor
    int err;

    err = pthread_create(&thread, NULL, wait, NULL); 
	/*Le nouveau thread exécute la fonction wait en lui passant arg4 
	comme premier argument. Le nouveau thread s'achève soit explicitement 
	en appelant pthread_exit(3), ou implicitement lorsque la fonction 
	wait s'achève.*/

    if (err)
    {
        printf("An error occured: %d", err);
        return 1;
    }

    printf("Waiting for the thread to end...\n");

    pthread_join(thread, NULL); // link the current thread process to another thread.
	//It makes the program stops in order to wait for the end of the selected thread. sinon return 0 avant exec du thread.
	//Mais le thread créé s'exécute dès la création. phthread_join ne sert qu'à attendre.

    printf("Thread ended.\n");    

    return 0;
}