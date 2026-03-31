philosophers/ └── philo/ ├── Makefile # Build configuration ├── philosopher.h # Header file with data structures ├── main.c # Entry point and initialization ├── routines.c # Philosopher thread routines ├── actions.c # Eating, sleeping, thinking actions ├── current_time.c # Time tracking utilities └── ft_atoi.c # String to integer conversion

Code

## Features

**Thread-Safe Synchronization** - Uses pthread mutexes to protect shared resources (forks)
**Deadlock Prevention** - Implements proper fork acquisition and release strategies
**Configurable Parameters** - Command-line arguments for number of philosophers and timing
**Death Detection** - Monitors philosopher state and stops simulation if someone dies
**Meal Counting** - Optional tracking of meals eaten per philosopher
**Timestamp Logging** - Tracks state changes with millisecond precision

## Prerequisites

- **GCC** or compatible C compiler
- **POSIX-compliant system** (Linux, macOS, BSD)
- **pthread library** (typically included by default)
- **make** (for building)

## Installation

Clone the repository:
```bash
git clone https://github.com/somaya-Hassoune/philosophers.git
cd philosophers/philo
Build the project:

bash
make
Clean build artifacts:

bash
make clean
Usage
Command Syntax
bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
Parameters
| Parameter | Description | Unit |
|-----------|-------------|------|
| `number_of_philosophers` | Number of philosophers (and forks) | count |
| `time_to_die` | Time a philosopher can survive without eating | milliseconds |
| `time_to_eat` | Time required for a philosopher to eat | milliseconds |
| `time_to_sleep` | Time a philosopher sleeps after eating | milliseconds |
| `number_of_meals` | (Optional) Meals each philosopher must eat to stop | count |
Examples
Basic simulation with 5 philosophers:

bash
./philo 5 800 200 200
Philosophers must eat 10 meals each:

bash
./philo 4 410 200 200 10
Single philosopher (special case):

bash
./philo 1 800 200 200
Implementation Details
Key Components
1. Data Structures (philosopher.h)

t_program: Stores philosopher state, fork references, and timing parameters
Maintains dead flag, meal count, and thread synchronization primitives
2. Initialization (main.c)

Allocates memory for philosophers and mutexes (forks)
Initializes each philosopher with fork references
Creates thread pool for concurrent execution
3. Philosopher Routines (routines.c)

philo_routine(): Main loop for eating, sleeping, thinking
dead_routine(): Monitors philosopher state and enforces death condition
one_philo(): Special handler for single philosopher edge case
4. Actions (actions.c)

Fork acquisition with deadlock prevention
Eating, sleeping, and thinking state transitions
Thread-safe output logging
5. Time Management (current_time.c)

Millisecond-precision timestamp tracking
Relative timing based on simulation start time
Synchronization Strategy
Code
┌─────────────────────────────────┐
│     Fork (Mutex #1..N)          │
│  Protects actual fork resources │
└─────────────────────────────────┘
         ↕
┌─────────────────────────────────┐
│     Death Mutex (Mutex #0)      │
│  Protects death flag            │
└─────────────────────────────────┘
         ↕
┌─────────────────────────────────┐
│     Meal Mutex (Mutex #N+1)     │
│  Protects meal counter          │
└─────────────────────────────────┘
Example Output
Code
0 1 has taken a fork
0 1 is eating
0 2 has taken a fork
0 2 has taken a fork
0 2 is eating
0 2 is sleeping
0 1 is sleeping
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
...
Each line shows:

Timestamp (milliseconds since start)
Philosopher ID (1 to N)
Action (has taken a fork, is eating, is sleeping, is thinking, died)
Performance Considerations
Lock Contention: Higher philosopher count increases fork competition
Timing Parameters: Carefully tune time values to observe different behaviors:
Very short death time can cause starvation
Short eat/sleep times increase context switching overhead
Author
somaya-Hassoune - Implementation of the Dining Philosophers Problem

License
This project is open source and available for educational purposes.
