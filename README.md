# Philosophers
42 project to learn the basics of threads.

Eat, Sleep, Spaghetti, repeat. This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.
A variation on the [philosophers dining problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).




 **Allowed external functions**:
 
This is a school project and we were given limits on what we could use to create the program:

 memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock


## How to Test
To create the executable:
```sh
cd philo
make
```
To run the program:
```sh
./philo [Number of philosophers] [time to die] [time to eat] [time to sleep] Optional: [Number of times each philosopher must eat]
```

