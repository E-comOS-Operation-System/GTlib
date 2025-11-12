# Formal Verification Guide

## Installation

### macOS
```bash
brew install frama-c
```

### Linux
```bash
apt-get install frama-c
# or
opam install frama-c
```

## Verification Methods

### 1. Using WP Plugin (Deductive Verification)
```bash
./verify.sh
```

### 2. Manual Verification of Single File
```bash
frama-c -wp -wp-rte src/window.c -cpp-extra-args="-Iinclude -Isrc"
```

### 3. Generate Verification Report
```bash
frama-c -wp -wp-rte -wp-out report src/window.c -cpp-extra-args="-Iinclude -Isrc"
```

## ACSL Specification

- `requires`: Precondition (must hold before function call)
- `ensures`: Postcondition (must hold after function returns)
- `\valid(p)`: Pointer p points to valid memory
- `\freed(p)`: Pointer p has been freed
- `\result`: Function return value

## Verification Goals

- Memory safety (no null pointer dereference, no buffer overflow)
- Function contract correctness
- Runtime error detection
