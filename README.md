# ⚡ Advanced Circuit Analyzer

A C++ command-line tool that computes the **total equivalent resistance** of arbitrarily complex electrical circuits using a **recursive descent parser**.

## 🔧 How It Works

Users describe circuit topologies using a simple **Domain-Specific Language (DSL)**:

| Token | Meaning |
|-------|---------|
| `S`   | Begin a **series** sub-circuit |
| `P`   | Begin a **parallel** sub-circuit |
| `e`   | End the current sub-circuit |
| `N`   | A numeric **resistor value** (in Ohms) |

Sub-circuits can be **nested to any depth**, allowing representation of real-world circuits of any complexity.

## 📐 Formulas

- **Series:** `R_total = R₁ + R₂ + ... + Rₙ`
- **Parallel:** `1/R_total = 1/R₁ + 1/R₂ + ... + 1/Rₙ`

## 📋 Examples

| Input | Circuit Description | Result |
|-------|-------------------|--------|
| `S 10 20 e` | 10Ω + 20Ω in series | **30 Ω** |
| `P 10 20 e` | 10Ω ∥ 20Ω in parallel | **6.667 Ω** |
| `S 10 P 20 30 e e` | 10Ω in series with (20Ω ∥ 30Ω) | **22 Ω** |
| `S P 10 20 e 30 e` | (10Ω ∥ 20Ω) in series with 30Ω | **36.667 Ω** |

## 🚀 Build & Run

### Prerequisites
- **g++** (GCC) with C++17 support

### Compile
```bash
g++ -Wall -Wextra -std=c++17 -o circuit_analyzer main.cpp
```

### Run
```bash
./circuit_analyzer
```

You will see a prompt. Enter your circuit description:
```
=============================================
   Advanced Circuit Analyzer v2.0
=============================================
Enter a circuit description using:
  S  — Series connection
  P  — Parallel connection
  e  — End of sub-circuit
Example: S 10 P 20 30 e e
---------------------------------------------
Input: S 10 P 20 30 e e
The total resistance = 22 Ohms
```

## 🛡️ Error Handling

The program validates all input and handles:
- ✅ Missing `e` terminators (no crash)
- ✅ Zero or negative resistor values
- ✅ Invalid connection type descriptors
- ✅ Empty input
- ✅ Trailing/malformed tokens

## 🏗️ Project Structure

```
Advanced Circuit Analyzer Project/
├── main.cpp                                    # Source code
├── Advanced Circuit Analyzer Project.cbp       # Code::Blocks project file
├── .gitignore                                  # Git ignore rules
└── README.md                                   # This file
```

## 📝 Technical Details

- **Language:** C++17
- **Algorithm:** Recursive descent parsing
- **Key Concepts:** Tokenization, recursion, DSL design, electrical circuit analysis
- **Documentation:** Doxygen-style comments throughout

## 👤 Author

**Abdlrhman** (ID: 2300343)

## 📄 License

This project is part of a university capstone project (Computer Programming — Level 2, Semester 1).
