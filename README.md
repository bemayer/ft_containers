# ft_containers
Reimplementation of C++ Standard Template Library Containers in C++98

## Overview
This project involves reimplementing several core containers from the C++ Standard Template Library (STL) using the C++ 98 standard. The goal is to gain an in-depth understanding of data structures, memory management, and template programming in C++. By reconstructing these containers, the project provides insights into their internal operations, which is essential for writing efficient and robust code.

## Features
- **Vector**: Dynamic array with automatic resizing.
- **Stack**: LIFO (Last-In-First-Out) data structure built on top of the vector.
- **Map**: Associative array implemented using a red-black tree.
- **Set**: Collection of unique keys, also implemented with a red-black tree.
- **Iterator Implementations**: Custom iterators that comply with standard iterator traits.
- **Utility Components**: Reimplementation of components like pair, make_pair, and other helper functions.

## Implementation Highlights
- **C++98 Compliance**: Ensures compatibility with older systems by adhering strictly to the C++98 standard.
- **Templates and Generics**: Extensive use of template programming to create flexible and reusable code.
- **Exception Safety**: Robust error handling to maintain container integrity.
- **Algorithm Efficiency**: Optimized data structures for performance comparable to their standard counterparts.
- **Testing**: Comprehensive tests to validate behavior against the standard STL containers.

## Motivation
Rewriting these containers was an opportunity to:
- **Understand Internal Mechanics**: Learn how standard containers manage memory, handle exceptions, and optimize for performance.
- **Enhance Problem-Solving Skills**: Tackle complex programming challenges related to data structure implementation.
- **Explore Template Programming**: Deepen understanding of templates and their powerful capabilities in C++.

## How to Build and Test

### Prerequisites
- A C++ compiler that supports C++98 (e.g., GCC 3.4+, Clang).
- `make` utility installed on your system.


### Cloning the Repository
```bash
git clone https://github.com/bemayer/ft_containers.git
cd ft_containers
```

### Building
Compile the containers and any test files, and execute them using the provided Makefile:
```bash
make test
```
