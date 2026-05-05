/**
 * @file    main.cpp
 * @brief   Advanced Circuit Analyzer — Recursive Equivalent Resistance Calculator
 *
 * @details This program computes the total equivalent resistance of arbitrarily
 *          nested series and parallel resistor networks.  The circuit topology
 *          is described with a simple Domain-Specific Language (DSL):
 *
 *          - **S** — begins a series sub-circuit
 *          - **P** — begins a parallel sub-circuit
 *          - **e** — terminates the current sub-circuit
 *          - Numeric values represent individual resistor values (in Ohms)
 *
 *          Sub-circuits may be nested to any depth.
 *
 *          ### Example inputs
 *          | Input                     | Meaning                                        | Result   |
 *          |---------------------------|------------------------------------------------|----------|
 *          | `S 10 20 e`               | 10Ω + 20Ω in series                            | 30 Ω     |
 *          | `P 10 20 e`               | 10Ω ∥ 20Ω in parallel                          | 6.667 Ω  |
 *          | `S 10 P 20 30 e e`        | 10Ω in series with (20Ω ∥ 30Ω)                 | 22 Ω     |
 *          | `S P 10 20 e 30 e`        | (10Ω ∥ 20Ω) in series with 30Ω                 | 36.667 Ω |
 *
 * @author  Abdlrhman (ID: 2300343)
 * @date    12 December 2024
 * @version 1.0
 *
 * @note    Compiled with: g++ -Wall -Wextra -std=c++17 -o circuit_analyzer 2300343.cpp
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>   // For numeric_limits (infinity check)

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  Forward Declarations
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief  Tokenizes the raw user input string into a vector of whitespace- /
 *         comma-separated tokens.
 *
 * @param  userInput  The single-line input string from the user.
 * @return A vector of string tokens (connection types, resistor values, end
 *         markers) extracted from @p userInput.
 *
 * @details Delimiters recognized: space (' ') and comma (',').
 *          Consecutive delimiters are treated as a single separator.
 */
vector<string> tokenizeInput(const string& userInput);

/**
 * @brief  Recursively evaluates the equivalent resistance of a sub-circuit
 *         described by the token list starting at @p index.
 *
 * @param  tokens  The complete list of tokens produced by tokenizeInput().
 * @param  index   [in/out] Current position in the token list.  On return the
 *                 index points to the token immediately after the closing 'e'.
 * @return The equivalent resistance (in Ohms) of the parsed sub-circuit.
 *
 * @throws Terminates the program with an error message and exit code 1 if:
 *         - The token list is exhausted unexpectedly (missing 'e').
 *         - An unrecognized connection type is encountered.
 *         - A series block has fewer than 1 resistor.
 *         - A parallel block has fewer than 2 resistors.
 *         - A resistor value is zero or negative.
 *         - Division by zero would occur in a parallel calculation.
 */
float calculateResistance(const vector<string>& tokens, size_t& index);

/**
 * @brief  Determines whether a token represents a valid numeric resistor value.
 *
 * @param  token  The string token to check.
 * @return true if the token starts with a digit or a decimal point; false
 *         otherwise.
 */
bool isNumericToken(const string& token);

// ─────────────────────────────────────────────────────────────────────────────
//  Main Entry Point
// ─────────────────────────────────────────────────────────────────────────────

/**
 * @brief  Program entry point.
 *
 * Reads a single line of circuit description from standard input, parses it
 * into tokens, computes the equivalent resistance via recursive descent, and
 * prints the result to standard output.
 *
 * @return 0 on success; the program calls exit(1) on malformed input.
 */
int main() {
    // Display usage instructions to guide the user
    cout << "=============================================" << endl;
    cout << "   Advanced Circuit Analyzer v2.0" << endl;
    cout << "=============================================" << endl;
    cout << "Enter a circuit description using:" << endl;
    cout << "  S  — Series connection" << endl;
    cout << "  P  — Parallel connection" << endl;
    cout << "  e  — End of sub-circuit" << endl;
    cout << "Example: S 10 P 20 30 e e" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Input: ";

    // Read the entire circuit description as a single line
    string userInput;
    getline(cin, userInput);

    // Tokenize the raw input into individual components
    vector<string> tokens = tokenizeInput(userInput);

    // Validate that input is not empty
    if (tokens.empty()) {
        cerr << "Error: Empty input. Please provide a circuit description." << endl;
        return 1;
    }

    // Initialize the parsing index at the beginning of the token list
    size_t index = 0;

    // Recursively compute the total equivalent resistance
    float totalResistance = calculateResistance(tokens, index);

    // Verify that all tokens were consumed (no trailing garbage)
    if (index != tokens.size()) {
        cerr << "Warning: Unexpected tokens after the circuit description were ignored." << endl;
    }

    // Display the computed result
    cout << "The total resistance = " << totalResistance << " Ohms" << endl;

    return 0;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Function Implementations
// ─────────────────────────────────────────────────────────────────────────────

vector<string> tokenizeInput(const string& userInput) {
    vector<string> tokens;      // Accumulates the extracted tokens
    string currentToken = "";   // Buffer for the token being built

    // Iterate over every character in the input string
    for (char c : userInput) {
        if (c == ' ' || c == ',') {
            // Delimiter encountered — flush the current token if non-empty
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken = "";  // Reset the buffer for the next token
            }
        } else {
            // Non-delimiter character — append to the current token
            currentToken += c;
        }
    }

    // Flush any remaining token after the loop (handles input without
    // a trailing delimiter)
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

bool isNumericToken(const string& token) {
    // A numeric token starts with a digit or a decimal point
    // (e.g., "10", "3.5", ".75")
    return !token.empty() && (isdigit(token[0]) || token[0] == '.');
}

float calculateResistance(const vector<string>& tokens, size_t& index) {
    // ── Guard: ensure the index is within bounds ──────────────────────────
    if (index >= tokens.size()) {
        cerr << "Error: Unexpected end of input — missing connection type or 'e' terminator." << endl;
        exit(1);
    }

    // ── Read the connection type token (S/s or P/p) ──────────────────────
    string connectionType = tokens[index++];
    float totalResistance = 0.0f;

    // =====================================================================
    //  SERIES connection: R_total = R1 + R2 + ... + Rn
    // =====================================================================
    if (connectionType == "S" || connectionType == "s") {
        int resistorCount = 0;  // Number of resistors/sub-circuits parsed

        // Consume tokens until the end marker 'e' is found
        while (true) {
            // Bounds check before accessing tokens[index]
            if (index >= tokens.size()) {
                cerr << "Error: Missing 'e' terminator for series connection." << endl;
                exit(1);
            }

            // End marker found — exit the loop
            if (tokens[index] == "e") {
                break;
            }

            if (isNumericToken(tokens[index])) {
                // Token is a resistor value — parse and accumulate
                float value = stof(tokens[index++]);
                if (value <= 0.0f) {
                    cerr << "Error: Resistor value must be positive (got " << value << ")." << endl;
                    exit(1);
                }
                totalResistance += value;
                resistorCount++;
            } else {
                // Token is a sub-circuit — recursively evaluate it
                totalResistance += calculateResistance(tokens, index);
                resistorCount++;
            }
        }

        // A series connection requires at least 1 resistor
        if (resistorCount < 1) {
            cerr << "Error: Series connection must contain at least 1 resistor." << endl;
            exit(1);
        }
    }
    // =====================================================================
    //  PARALLEL connection: 1/R_total = 1/R1 + 1/R2 + ... + 1/Rn
    // =====================================================================
    else if (connectionType == "P" || connectionType == "p") {
        float reciprocalSum = 0.0f;  // Accumulates 1/R for each branch
        int resistorCount = 0;       // Number of resistors/sub-circuits parsed

        // Consume tokens until the end marker 'e' is found
        while (true) {
            // Bounds check before accessing tokens[index]
            if (index >= tokens.size()) {
                cerr << "Error: Missing 'e' terminator for parallel connection." << endl;
                exit(1);
            }

            // End marker found — exit the loop
            if (tokens[index] == "e") {
                break;
            }

            if (isNumericToken(tokens[index])) {
                // Token is a resistor value — parse and add reciprocal
                float value = stof(tokens[index++]);
                if (value <= 0.0f) {
                    cerr << "Error: Resistor value must be positive (got " << value << ")." << endl;
                    exit(1);
                }
                reciprocalSum += 1.0f / value;
                resistorCount++;
            } else {
                // Token is a sub-circuit — recursively evaluate it
                float subResistance = calculateResistance(tokens, index);
                if (subResistance == 0.0f) {
                    cerr << "Error: Division by zero — a sub-circuit returned 0 Ohms "
                         << "inside a parallel connection." << endl;
                    exit(1);
                }
                reciprocalSum += 1.0f / subResistance;
                resistorCount++;
            }
        }

        // A parallel connection requires at least 2 branches
        if (resistorCount < 2) {
            cerr << "Error: Parallel connection must contain at least 2 resistors." << endl;
            exit(1);
        }

        // Guard against division by zero in the final reciprocal inversion
        if (reciprocalSum == 0.0f) {
            cerr << "Error: Reciprocal sum is zero — cannot compute parallel resistance." << endl;
            exit(1);
        }

        totalResistance = 1.0f / reciprocalSum;
    }
    // =====================================================================
    //  Unknown connection type
    // =====================================================================
    else {
        cerr << "Error: Unrecognized connection type '" << connectionType
             << "'. Expected 'S' (series) or 'P' (parallel)." << endl;
        exit(1);
    }

    // Advance past the 'e' end marker
    index++;

    return totalResistance;
}
