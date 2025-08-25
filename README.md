# 🍝 Philosophers

A concurrency challenge in disguise — build a dining simulation using threads and mutexes, where philosophers fight (peacefully) for forks and try not to starve.

Welcome to **Philosophers** — a 42 project that dives into the core of multithreading, resource sharing, and deadlock avoidance.

---

## 🚀 Project Overview

**philosophers** is part of the 42 school curriculum. The goal: simulate the classic **Dining Philosophers Problem** — a concurrency problem that illustrates synchronization issues and how to avoid them.

🍴 Philosophers sit at a table with forks between them
💤 They think, eat, and sleep
⏳ But if they can’t eat in time… they die

---

## ⚙️ Simulation Rules

Each philosopher:

* Thinks
* Picks up two forks (mutexes)
* Eats (for a specified time)
* Sleeps
* Repeats

The simulation ends when:

* A philosopher dies (doesn't eat in time)
* Or all philosophers have eaten a specified number of times (optional)

---

## 🧠 Key Concepts Covered

* POSIX threads (`pthread_create`, `pthread_join`)
* Mutexes for shared resource protection
* Thread synchronization and race condition prevention
* Avoiding deadlocks and starvation
* Handling timing and precision in C
* Clean and safe memory/thread management

---

## 🛠️ Technologies

* **Language:** C
* **OS:** Linux
* **Multithreading:** POSIX Threads
* **No external libraries**

---

## 📦 How to Use

Clone the repo:

```bash
git clone https://github.com/your-username/philosophers.git
cd philosophers
```

Compile:

```bash
make
```

Run:

```bash
./philo 5 800 200 200
```

**Arguments:**

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200 3
```

---

## 🧪 Bonus Features

* 🔍 Deadlock prevention strategies
* 🕓 High-precision sleep function
* 🧹 Clean exit and memory deallocation
* ⚰️ Death detection without race conditions

---

## 🧠 Challenges Faced

* Accurate time management — `usleep()` isn't always enough
* Detecting deaths without delay
* Preventing race conditions with mutexes
* Ensuring clean and safe thread termination
* Avoiding deadlocks with minimal locking strategies

## 🔁 Sample Output

```bash
0 1 is thinking
1 2 is thinking
2 1 has taken a fork
3 1 has taken a fork
4 1 is eating
5 2 has taken a fork
6 2 has taken a fork
7 2 is eating
...
```

---

## 💡 Lessons Learned

* Concurrency is hard — timing bugs are sneaky.
* Deadlocks aren't always obvious, until your whole sim freezes.
* Threads are powerful but need strict discipline.
* Proper logging and monitoring are crucial for debugging multi-threaded apps.
