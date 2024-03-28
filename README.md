# Simple Integer Calculator in C++

This repository implements a basic integer calculator program written in C++. It supports essential arithmetic operations and evaluates mathematical expressions entered in infix notation.

## Features:
- Performs calculations on integers.
- Evaluates infix expressions following PEMDAS (Parentheses, Exponents, Multiplication and Division, Addition and Subtraction) order of operations.
- Provides a step-by-step breakdown of expression conversion (infix to postfix) for transparency.

## Getting Started:

### Prerequisites:
Ensure you have a C++ compiler installed (e.g., GCC, Clang).

### Clone or Download:
Clone this repository using Git:

git clone https://github.com/<your-username>/simple-integer-calculator.git

or download the ZIP file.

### Build:
Navigate to the project directory in your terminal and run `make`. This will compile the program and generate an executable named `calc`.

## Usage:

To execute the calculator and evaluate an expression:

```bash
./calc "<expression>"
```
**Do not use spaces between values in the expression.**

### Example:

```bash
./calc "(3+2)*5"
```
**Use code with caution.**

The program will display the breakdown of expression conversion and the final calculated value.

## Output:

The program provides clear output, including:

- Expression Breakdown: Shows the conversion process from infix to postfix notation for better understanding.
- Calculated Value: Returns the final result of the evaluated expression.

## Developed by:

Ben Berton (for C++ class)

## Additional Notes:

- To remove generated object files after compilation, use `make clean`.
- For more advanced mathematical operations or real-number calculations, consider extending the program's capabilities.

## License:

(Specify the license you wish to use, e.g., MIT, Apache 2.0).
