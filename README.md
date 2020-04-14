# philosophers
C is a language that runs on one thread by default, which means that the code will only run one instruction at a time. In some cases you'll need to do multiple instructions at a time, a graphical interface for instance, will not stop when it performs an action related to a button's click. That's what we call multithreading, not to be confused with asynchronous operations that can be performed in only one thread that does multiple tasks.
A thread is a task that runs linked to a process. A process we can have multiple threads and threads can run other threads and so on.
By default a process runs on a single thread. Each thread is new tasks that can be run indefinitely and in parallel to the other threads.
1 process contains multiple threads. 

Le principal avantage des threads par rapport aux processus, c'est la facilité et la rapidité de leur création. En effet, tous les threads d'un même processus partagent le même espace d'adressage, et donc toutes les variables. Mémoire partagée.
Cela évite donc l'allocation de nouveaux espaces lors de la création, la création d'un thread est environ cent fois plus rapide que celle d'un processus.
Au-delà de la création, la superposition de l'exécution des activités dans une même application (1 application = 1 processus) permet une importante accélération quant au fonctionnement de cette dernière.
La communication entre les threads est plus aisée que celle entre les processus, pour lesquels on doit utiliser des pipes.

#Mutex :
Doing multiple operations on one target at the same time is very dangerous. If three threads want to write a single file at the same time, it would be a problem because a hard drive can't go as fast as a CPU does. In this case we should lock the other threads in order to not overload the hard drive with tasks that can corrupt the file. Mutex can be used to lock the other threads.
phthread_join() n'est relatif qu'au current thread, donc à moins de faire un join dans THREAD1 pour THREAD2, si on reste dans le main thread, on utilise les mutex.

pthread_mutex_lock() verrouille le mutex. 
- Si le mutex est déverrouillé, il devient verrouillé et est possédé par le thread appelant et pthread_mutex_lock() rend la main immédiatement. 
- Si le mutex est déjà verrouillé par un autre thread, pthread_mutex_lock suspend le thread appelant jusqu'à ce que le mutex soit déverrouillé.
- Si le mutex est déjà verrouillé par le thread appelant, le comportement de pthread_mutex_lock() dépend du type de mutex. Voir le man.

#Semaphores
The semaphores be controlled by any thread. The notion of ownership is not present in the case of a semaphore, so they can be locked and unlocked by any part of the program.

#Compilation : 
gcc -lpthread main.c (for Unix)

#ressources : 
- https://dev.to/quantumsheep/basics-of-multithreading-in-c-4pam
- https://openclassrooms.com/en/courses/1513891-la-programmation-systeme-en-c-sous-unix/1514567-les-threads 
