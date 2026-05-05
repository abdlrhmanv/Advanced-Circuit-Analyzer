<div align="center">

# ⚡ Advanced Circuit Analyzer

**Recursive Equivalent Resistance Calculator**

A C++ command-line tool that computes the total equivalent resistance of arbitrarily complex electrical circuits using a recursive descent parser and a custom Domain-Specific Language (DSL).

*Capstone Project — Computer Programming · Level 2 · Semester 1*

</div>

---

## 👨‍💻 About Me

I'm **Abdlrhman Ismail**, a Senior Computer Engineering student at **Ain Shams University (ASU)**. This project was developed as my Capstone Project for the Computer Programming course, demonstrating proficiency in recursive algorithms, DSL design, and robust C++ software engineering.

---

## 📂 Repository Structure

```
Advanced-Circuit-Analyzer/
├── main.cpp                                    # Source code (fully documented, Doxygen-style)
├── Advanced Circuit Analyzer Project.cbp       # Code::Blocks project file
├── .gitignore                                  # Git ignore rules
└── README.md                                   # ← You are here
```

---

## 🔧 How It Works

Users describe circuit topologies using a simple **Domain-Specific Language (DSL)**:

| Token | Meaning |
|:-----:|---------|
| `S`   | Begin a **series** sub-circuit |
| `P`   | Begin a **parallel** sub-circuit |
| `e`   | End the current sub-circuit |
| `N`   | A numeric **resistor value** (in Ohms) |

Sub-circuits can be **nested to any depth**, allowing representation of real-world circuits of any complexity.

### 📐 Formulas

| Connection | Formula |
|------------|---------|
| **Series** | `R_total = R₁ + R₂ + … + Rₙ` |
| **Parallel** | `1/R_total = 1/R₁ + 1/R₂ + … + 1/Rₙ` |

---

## 📋 Examples

| Input | Circuit Description | Result |
|-------|---------------------|--------|
| `S 10 20 e` | 10Ω + 20Ω in series | **30 Ω** |
| `P 10 20 e` | 10Ω ∥ 20Ω in parallel | **6.667 Ω** |
| `S 10 P 20 30 e e` | 10Ω in series with (20Ω ∥ 30Ω) | **22 Ω** |
| `S P 10 20 e 30 e` | (10Ω ∥ 20Ω) in series with 30Ω | **36.667 Ω** |

---

## 🛡️ Error Handling

The program validates all input and gracefully handles:

| Scenario | Behavior |
|----------|----------|
| Missing `e` terminator | Clear error message (no crash) |
| Zero or negative resistor values | Rejected with descriptive error |
| Invalid connection type | Reports the unrecognized token |
| Empty input | Prompts user for valid input |
| Trailing / malformed tokens | Warning issued |

---

## 🛠️ Tech Stack & Tools

| Category | Tools |
|----------|-------|
| **Language** | C++17 🔧 |
| **Algorithm** | Recursive Descent Parsing |
| **Key Concepts** | Tokenization · Recursion · DSL Design · Circuit Analysis |
| **Documentation** | Doxygen-style comments |
| **IDE** | Code::Blocks |
| **Compiler** | GCC (g++) |
| **Version Control** | Git & GitHub |

---

## 🚀 Getting Started

```bash
# 1. Clone the repository
git clone git@github.com:abdlrhmanv/Advanced-Circuit-Analyzer.git
cd Advanced-Circuit-Analyzer

# 2. Compile
g++ -Wall -Wextra -std=c++17 -o circuit_analyzer main.cpp

# 3. Run
./circuit_analyzer
```

You will see a prompt — enter your circuit description:

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

---

## 📬 Contact

Always happy to chat about Software Engineering, AI, or Mathematics — feel free to reach out!

| | |
|---|---|
| 📧 **Email** | abdlrhmanv@icloud.com |
| 💼 **LinkedIn** | [Abdlrhman Ismail](https://linkedin.com/in/abdlrhmanv) |
| 🐙 **GitHub** | [@abdlrhmanv](https://github.com/abdlrhmanv) |

---

<div align="center">

Made with ❤️ by **Abdlrhman Ismail**

*December 2024*

</div>
