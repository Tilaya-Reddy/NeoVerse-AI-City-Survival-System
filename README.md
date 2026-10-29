# NeoVerse: AI City Survival System

A **C++ console application** that simulates the control room of a futuristic smart city. Engineers log in, report and process city events, raise emergency overrides, record sensor readings and run analytics, with all data saved to files between sessions.

Built for **Programming 622** to demonstrate STL containers, polymorphism, file I/O and algorithm analysis.

## Features

- **Login system** with three attempts before shutdown
- **Event queue (FIFO):** report city events and process them in the order they arrive
- **Emergency override stack (LIFO):** the most recent emergency is resolved first
- **Sensor readings and historical logs:** record daily energy usage, traffic density and population, and keep a running log
- **Polymorphic city systems:** power, transport, health and security systems all respond to the same `processEvent()` call in their own way
- **Analytics:** sort readings, find the highest and lowest energy usage, count critical alerts, search events by ID and print a system report
- **Persistence:** everything is saved on exit and reloaded on start; events can also be exported to CSV

## How it's organised

| Module - Responsibility |

| `CityComponent` - Abstract base class (ID, name, active flag) with a pure virtual `processEvent()` |

| `CitySystems`, `PowerSystem`, `TransportSystem`, `HealthSystem` and `SecuritySystem`, each overriding `processEvent()` |

| `CityData` - Sensor readings (`vector`) and historical logs (`list`), with save/load |

| `EventManager` - Event queue, emergency stack and processed-event history, with save/load |

| `Engineer` - Engineer account: ID, username, password, clearance level (Low / Medium / High) |

| `AuthSystem` - Stores engineers and handles login (linear search, plus a binary-search version) |

| `Analytics` - Sorting, min/max, counting and searching with STL algorithms, plus the system report |

| `FileManager` - Config file handling and CSV export |

## Build and run

**Requirements:** Windows with Visual Studio 2019 or newer and the *Desktop development with C++* workload.

1. Clone the repo.
2. Open the `.sln` file in Visual Studio.
3. Build and run with **Ctrl + F5**.
4. Log in. Demo engineer accounts are created automatically on first run (see `seedDemoEngineersIfNeeded` in the main source file).
5. Use the numbered menu. Option `0` saves everything and exits.

The program reads and writes its files in a `data/` folder next to where it runs: `engineers.dat`, `city_readings.dat`, `city_logs.dat`, `events.dat`, `config.txt` and `events_export.csv`. Create an empty `data` folder if it doesn't exist.

## Main menu

```
 1. Report a new city event
 2. Process next event in queue (FIFO)
 3. Raise an emergency override
 4. Resolve top emergency (LIFO)
 5. View event queue and emergency stack
 6. Add a sensor reading
 7. View sensor readings and historical logs
 8. Run city components (polymorphism demo)
 9. Run analytics (sort / find / min / max / count)
10. View system report
11. View config.txt
12. Export events to CSV
13. View registered engineers
 0. Save and exit
```

## Design decisions

| Structure - Used for & Why |

| `vector` - Sensor readings and processed-event history; fast appends and traversal, and works directly with STL algorithms such as `sort` and `min_element` |

| `list` - Historical logs and Cheap removal of the oldest entry from the front |

| `queue` - Pending city events and Events must be handled first-in, first-out |

| `stack` - Emergency overrides and the newest emergency must interrupt and be resolved first (last-in, first-out) |

## Complexity analysis

| Operation - Time & Notes |

| Add a sensor reading (`vector::push_back`) - O(1) amortised | 

| Remove oldest reading (`vector::erase(begin())`) - O(n), Every later element shifts down |

| Add / remove oldest log (`list`) - O(1) | 

| Display readings or logs - O(n), Single traversal |

| Queue push / pop, stack push / pop - O(1) | 

| Sort readings by energy usage (`sort`) - O(n log n), Needs the full ordered list |

| Highest / lowest energy usage (`max_element` / `min_element`) -  O(n), One pass is enough, so a full sort would be wasted work |

| Count critical alerts (`count_if`) - O(n), Every event must be checked once |

| Find an event by ID (`find`) - O(n), History is in time order, not ID order |

| Login (linear search) - O(n) | 

| Login (binary search) - O(log n), Requires engineers sorted by username |

## Known limitations

- Passwords are stored with a simple Caesar-style shift to demonstrate the idea of "stored, not plain text". This is **not real encryption**; a real system would use a salted hash such as bcrypt or Argon2.
- 
- Clearance levels are recorded and shown at login but do not restrict menu options.

## Licence

Student project, shared for learning and portfolio purposes.
