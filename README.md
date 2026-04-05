# Philosophers (philo)

A multithreaded **Dining Philosophers** simulator written in C with POSIX threads (`pthread`). Each philosopher runs in its own thread, shares forks modeled as mutexes, and coordinates eating, sleeping, and thinking while a monitor thread watches for starvation (death) and optional completion when everyone has eaten enough.

## Requirements

- A C compiler (`cc` by default)
- POSIX threads (`-pthread`)
- `make` (optional but recommended; the provided `Makefile` targets Unix-style shells for `clean`)

## Project layout

| Path | Role |
|------|------|
| `philo/Makefile` | Builds the `philo` binary with `-Wall -Wextra -Werror -pthread` |
| `philo/philo.h` | Shared types: `t_philo`, `t_main_struct`, and function declarations |
| `philo/main.c` | Entry: argument check, allocation, init, thread creation, joins, teardown |
| `philo/arg_error_check.c` | CLI validation: digit-only args, count, ranges (e.g. philosopher count 1–200) |
| `philo/assignment.c` | Parses parameters into `t_main_struct`, allocates philosopher and fork arrays |
| `philo/init_destroy_mutex.c` | Initializes and destroys fork mutexes plus `message`, `stop`, and `meal` mutexes |
| `philo/create_philo.c` | Wires each philosopher to left/right forks (circular table), spawns threads |
| `philo/time_functions.c` | Millisecond timestamps (`gettimeofday`) and `ft_msleep` |
| `philo/routine.c` | Per-philosopher loop: fork order, eat/sleep/think, death checks, single-philosopher case |
| `philo/saying_act.c` | Timestamped, mutex-protected logging for actions |
| `philo/dead_control.c` | Monitor thread: detects death by `time_to_die`, optional “all ate N times” stop |

## Build

From the `philo` directory:

```bash
make
```

This produces an executable named `philo`.

To rebuild from scratch:

```bash
make re
```

## Usage

```text
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- **5 arguments** — simulation runs until someone dies (or indefinitely if timings allow).
- **6 arguments** — stops when every philosopher has eaten at least `number_of_times_each_philosopher_must_eat` meals.

All numeric arguments must be positive integers (and philosopher count is validated up to 200). Arguments must contain digits only (no stray signs or spaces in the number strings beyond what `ft_atoi` accepts for the leading part).

Example:

```bash
./philo 5 800 200 200
./philo 4 410 200 200 5
```

## Behavior (implementation highlights)

- **Forks** — One mutex per fork; philosophers `i` uses fork `i` and fork `(i + 1) % N` as left/right (circular table).
- **Deadlock reduction** — Even IDs lock left-then-right; odd IDs lock right-then-left. Odd threads also start with a short delay so pairs do not always contend in lockstep.
- **Meals** — `last_meal_time` and `total_meal_number` are updated under `meal_mutex` where needed; the monitor reads them to decide death and “everyone full” conditions.
- **Stopping** — `stop_mutex` and `stop_control` coordinate shutdown: death sets a distinct state so a death message can print; optional meal completion sets another state so threads exit cleanly.
- **Output** — `message_mutex` (and coordination with `stop_mutex`) keeps lines from interleaving and respects the stop flag after a philosopher dies.
- **One philosopher** — Special path: only one fork exists logically; the philosopher waits `time_to_die` and dies (classic edge case).

## Clean

```bash
make clean   # removes the `philo` binary (per Makefile)
```

## Author

School 42 project structure and headers (ecakdemi).
