# NeoVerse: AI City Survival System
PROGRAMMING 622 Assignment — Console-Based C++ Simulation

## 1. How to Run the Simulation

### Requirements
- A C++ compiler that supports C++17 (g++, clang++, or MSVC/Visual Studio all work)

### Build instructions (Linux / macOS / WSL / any g++ setup)
From the project's root folder:

```
g++ -std=c++17 -Wall -Iinclude src/*.cpp -o neoverse
./neoverse
```

### Build instructions (Windows, MinGW g++)
```
g++ -std=c++17 -Wall -Iinclude src\*.cpp -o neoverse.exe
neoverse.exe
```

### Build instructions (Visual Studio)
Create a new empty C++ console project, add all files from `src/` and `include/`
to the project, add `include/` to the project's Additional Include
Directories, and build/run as normal (Ctrl+F5).

The program creates a `data/` folder automatically (if it does not already
exist, create it manually next to the executable) where it stores:
- `engineers.dat`   — registered engineers and encrypted passwords
- `city_readings.dat` — sensor readings (vector data)
- `city_logs.dat`   — historical city logs (linked list data)
- `events.dat`      — full processed event history
- `config.txt`      — simulation configuration
- `events_export.csv` — created when you use the CSV export option

**Important:** run the program from the project's root folder (the folder
that contains `data/`), otherwise it will not find its data files.

## 2. Sample Login Credentials

On first run, three demo engineers are created automatically:

| Username  | Password    | Clearance |
|-----------|-------------|-----------|
| M_Reddy   | 223874      | High      |
| KB_Reddy  | 730145      | Medium    |
| T_Reddy   | 554865      | Low       |

These are saved (with encrypted passwords) to `data/engineers.dat` after
the first run, and reloaded automatically every time the program starts.

## 3. Explanation of Containers Used

| Container            | Used for                          | Why it was chosen |
|-----------------------|-----------------------------------|--------------------|
| `std::vector<Engineer>` | Registered engineers            | Small, fairly static list; fast index access for searching/printing. |
| `std::vector<SensorReading>` | Daily sensor readings       | Fast O(1) random access and O(1) amortised push_back; readings are read far more often than removed. |
| `std::list<std::string>` | Historical city logs           | Grows without bound over the city's lifetime; O(1) insertion/removal anywhere without shifting other elements, unlike a vector. |
| `std::queue<Event>`   | Incoming city events (FIFO)        | Events must be handled in the order they were reported. |
| `std::stack<EmergencyEvent>` | Emergency overrides (LIFO)  | The most recently raised emergency is treated as the most urgent. |
| `std::map<std::string,int>` | Tallying event types (reports) | Needed a quick way to count occurrences of each distinct event type. |

## 4. Big-O Decisions

### Section 1 — Login search
- `AuthSystem::login()` uses `std::find_if`, a **linear search, O(n)**. The
  engineer list is small and not sorted, so a simple scan is the most
  practical choice.
- `AuthSystem::binarySearchLogin()` is also included to demonstrate the
  **O(log n)** alternative: it first sorts a temporary copy of the vector by
  username, then uses `std::lower_bound` to binary-search it. Binary search
  is only worthwhile once the engineer list is sorted and large enough that
  O(log n) meaningfully beats O(n).

### Section 2 — City data containers
- `vector::push_back` → O(1) amortised. `vector::erase(begin())` (removing
  the oldest reading) → O(n), because every remaining element must shift
  left by one position.
- `list::push_back` → O(1). `list::pop_front` (removing the oldest log) →
  O(1), because a linked list only needs to relink two pointers, no shifting.
- Both containers need O(n) to traverse and display all their contents.

### Section 3 — Event processing
- `queue::push` / `queue::pop` → O(1) each.
- `stack::push` / `stack::pop` → O(1) each.
- Both are implemented as adapters over a `std::deque` by default, so there
  is no per-operation cost difference between them; the difference is purely
  in ORDER (FIFO vs LIFO), which is why one models normal events and the
  other models emergencies.

### Section 5 — STL algorithms
| Algorithm     | Complexity | Why chosen |
|---------------|------------|------------|
| `std::sort`   | O(n log n) | Needed a fully ordered list of readings, not just one extreme value. |
| `std::max_element` / `std::min_element` | O(n) | Only need a single extreme value, so a full sort would waste time. |
| `std::count_if` | O(n) | Must inspect every event once to test the "is this critical" condition. |
| `std::find_if` | O(n) worst case | Event history is stored in the order events happened, not sorted by ID, so a linear scan is required. |

## 5. Notes on Design (Section 4 — OOP)
`CityComponent` is an abstract base class (it has a pure virtual
`processEvent()` function, so it can never be instantiated directly).
`PowerSystem`, `TransportSystem`, `HealthSystem` and `SecuritySystem` all
inherit from it and each provide their own version of `processEvent()`.
In `main.cpp`, all four are stored as `CityComponent*` pointers in one
`std::vector`, and calling `comp->processEvent(...)` on each one runs a
DIFFERENT function depending on the real object type — this is runtime
polymorphism. Their destructors are also virtual, so deleting a
`CityComponent*` correctly runs the derived class's destructor first, then
the base class destructor (visible in the console output when the program
exits).

## 6. Project Structure

```
402504107 Programming Assignment/
├──# header files (.h), implementation files (.cpp), including main.cpp
├── data/               # created/used at runtime for persistence
├── README.md           # this file
```

## 7. Known Simplifications
- Password "encryption" is a simple Caesar-style character shift, used only
  to demonstrate the CONCEPT of not storing plain-text passwords, and is
  clearly documented as such in `Engineer.cpp` — it is not meant to be
  cryptographically secure.
- Response times for events are randomly generated (5–60 seconds) to give
  the analytics/report functions realistic-looking data to work with.
