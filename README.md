    # Hospital Emergency Triage System

A console-based emergency room queue written in C using a binary min-heap.
It prioritizes patients by triage level and, for patients with the same priority,
uses arrival order as the tie-breaker.

## Features

- Admit a patient with an ID, name, age, and priority
- Automatically maintain treatment priority with a binary min-heap
- Treat the highest-priority patient next
- View the next patient without removing them
- Search for a patient by ID
- Change a patient's priority
- Discharge or remove a waiting patient
- Display all patients in treatment order
- Inspect the internal heap array

## Priority Levels

| Level | Priority | Meaning |
| ---: | :---: | :--- |
| 1 | Highest | Critical - immediate treatment |
| 2 | High | Emergency |
| 3 | Medium | Urgent |
| 4 | Low | Less urgent |
| 5 | Lowest | Non-urgent |

If multiple patients have the same priority, the patient who arrived first is
treated first.

## Repository Structure

```text
DSA-Assignment/
|-- main.c          # Menu loop and action handlers
|-- heap.c          # Min-heap implementation
|-- ui.c            # Input helper, Visuals
|-- heap.h          # Patient/Heap struct definition and Heap API
|-- ui.h            # UI API
|-- config.h        # Constants
|-- .gitignore
`-- README.md
```

## Requirements

- A C compiler such as GCC or MinGW
- A terminal that supports standard console input and output

On Windows, ANSI output is enabled automatically where supported. On Linux and
macOS, the source uses standard ANSI terminal colors.

## Build and Run

### Windows (MinGW or GCC)

```powershell
gcc main.c heap.c ui.c -o hospital-triage.exe
.\hospital-triage.exe
```

### Linux or macOS

```bash
gcc main.c heap.c ui.c -o hospital-triage
./hospital-triage
```

For stricter compiler checks:

```bash
gcc -Wall -Wextra -Wpedantic main.c heap.c ui.c -o hospital-triage
```

## Menu Options

```text
1. Admit new patient
2. Treat next patient
3. View next patient
4. Search patient by ID
5. Change patient priority
6. Remove patient from queue
7. Display all waiting patients
8. Display heap array
9. Exit
```

## Example Flow

1. Choose `1` to admit a patient.
2. Enter a unique ID, name, age, and a priority from `1` to `5`.
3. Choose `3` to preview who will be treated next.
4. Choose `2` to remove the highest-priority patient from the queue.
5. Choose `7` to view every waiting patient in treatment order.

## Data Structures and Complexity

- Queue storage: array-based binary heap
- Maximum queue size: 100 patients
- Insert: `O(log n)`
- Remove or treat next: `O(log n)`
- Update or search: `O(n)`
- View next patient: `O(1)`
- Display the entire treatment order: `O(n log n)`

The heap array stores patients in partial priority order. Displaying the queue
creates a copy and repeatedly removes the minimum patient, so it does not alter
the original queue.