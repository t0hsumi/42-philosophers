# Philosophers

This is a project to work on a variant of
[Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) and learn the basics of multi-threading with a mutex.


## Overview

- One or more philosophers sit at a round table.
  There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively **eat**, **think** or **sleep**.
    - while they are eating, they are not thinking or sleeping;
    - while thinking, they are not sleeping or eating;
    - and, of course, while sleeping, they are not eating or thinking.
- There are as many forks as philosophers on the table.
- Each philosopher takes his right and left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table
  and start sleeping. Once awake, they start thinking again.

## Global rules

Create the program `philo`.

This program takes the following arguments from the command line.
- number_of_philosophers: The number of philosophers and also the number of forks.
- time_to_die[ms]: If a philosopher didn’t start eating time_to_die[ms] since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat[ms]: The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- time_to_sleep[ms]: The time a philosopher will spend sleeping.
- number_of_times_each_philosophers_must_eat (optional):
  If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

This program output any state change of philosopher which must be formatted as follows:
- *timestamp*[ms] **X** has taken a fork
- *timestamp*[ms] **X** is eating
- *timestamp*[ms] **X** is sleeping
- *timestamp*[ms] **X** is thinking
- *timestamp*[ms] **X** died
  
  Replace *timestamp* with the current timestamp in milliseconds and **X** with the philosopher id.

Any state change should not be mixed up with another.

### misc
- I can use `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`,
  `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`,
  `pthread_mutex_lock` and `pthread_mutex_lock`, and other normal libc functions are forbidden.
- In no way can it quit abruptly.
  (segmentation fault, bus error, double free, etc).
- All heap allocated memory space must be properly freed when necessary.
  No leaks will be tolerated.
- Global variables are forbidden.
- All code must conform to the [42 Norm](https://github.com/42School/norminette).

## Usage

Clone this repository and run `make`, and make the executable file `philo`.

This program is used as follows:

```bash
./philo number_of_philosophers \
  time_to_die time_to_eat time_to_sleep \
	[number_of_times_each_philosophers_must_eat]
```

[This repository](https://github.com/nafuka11/philosophers-visualizer) illustrates what each philosopher does each time.

## Approach

The approach is simple. Look at the command line argument, initialize the table (whose contents are written in [header file](./includes/philosophers.h)), and then start the simulation. There are two points to note.
- printf() itself is a thread-safe function, so any logs aren't mixed up with another. However, to output logs in chronological order and not to output any log if a philosopher died, I used mutex in the output part (see [print_actions()](https://github.com/tohsumi1205/42-philosophers/blob/main/srcs/utils.c#L29) for more detail).
- In order not to output any log if a philosopher died, I must implement an observer thread that checks if each philosopher is dead continuously.

## Author

[Twitter](https://twitter.com/t76_1205)

## Licence

[MIT](./LICENSE)