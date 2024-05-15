# 🧮 Graph Algorithms Implementation - Continued Enhancement

**Author:** Vivian Umansky  
**Email:** Umanskyvivian@gmail.com

## Overview

Welcome back to the extension of my first CPP assignment! Building on the initial Graph class implementation, this assignment extends functionality to include arithmetic and comparison operators,applied directly to graph representations using adjacency matrices.

## Files

- **Graph.cpp**: Extends the initial `Graph` class by adding support for arithmetic and comparison operators.
- **Algorithms.cpp**: Integrates the extended graph functionalities with the graph algorithms implemented in the previous assignment.
- **Demo.cpp**: Demonstrates the new operator functionalities alongside the existing class methods.
- **Test.cpp**: Expanded to include tests for the new operators, ensuring robustness across various graph operations.
- **Main.cpp**: The entry point for running demonstrations and tests, showcasing the integrated capabilities of the updated Graph class.

## Extended Graph Operations

### Arithmetic Operators

- **Addition (`+`, `+=`)** and **Subtraction (`-`, `-=`)**: Support for direct and compound operations on graphs of the same dimension.
- **Unary Plus (`+`)** and **Negation (`-`)**: Unary operations to facilitate positive and negative forms of graphs.
- **Scalar Multiplication (`*`)**: Multiplies each edge weight by an integer scalar.
- **Graph Multiplication**: Defines matrix multiplication for graphs, producing a new graph as the result.
- **Post and Prefix Increment (`++`)** and **Decrement (`--`)**: Modifies all edge weights by incrementing or decrementing their values.

### Comparison Operators Details

#### Equality and Inequality (`==`, `!=`)

- **Equal (`==`)**: Two graphs G1 and G2 are considered equal if both have the same size (order of the adjacency matrix) and identical edge weights across the matrix. Equality is achieved only when every corresponding element (edge weight) in their adjacency matrices is the same.
- **Not Equal (`!=`)**: G1 and G2 are not equal if they differ in size or at least one corresponding edge weight in their adjacency matrices differs.

#### Relational Operators (`>`, `>=`, `<`, `<=`)

- **Greater (`>`) and Greater or Equal (`>=`)**: A graph G2 is considered greater than another graph G1 if:
  - **Subgraph Containment:** All elements of G1's adjacency matrix are contained within G2's adjacency matrix, implying G1 can be seen as a subgraph within G2 based on direct comparison of adjacency matrices.
  - **Edge Count Superiority:** If no direct subgraph relationship exists, G2 is greater if it has a higher total sum of edge compared to G1.
  - **Matrix Order Superiority:** If the sum of edge is identical, then G2 is considered greater if it has a larger adjacency matrix (higher order).

### Output Operator

- **Output (`<<`)**: Custom implementation for the logical display of graphs, showcasing the adjacency matrix and any pertinent graph properties.

## Integration with Previous Assignment

The `Algorithms.cpp` file from the previous assignment is updated to work seamlessly with the extended Graph class, ensuring that all algorithms operate correctly with the new operator functionalities.

## Code Division

The project is organized into distinct modules:

- **Graph.cpp**: Houses all graph representations and operator implementations.
- **Algorithms.cpp**: Focuses on algorithm implementations that utilize the new graph capabilities.
- **Demo.cpp**: Provides executable examples of how to use the extended graph class and its algorithms.
- **Test.cpp**: Ensures all new and existing functionalities perform as expected under various scenarios.
- **Main.cpp**: Central script for demonstrating project capabilities.

## Usage

Follow these steps to utilize this project:

1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Build the project using the provided Makefile: execute `make all` to compile and run tests and demos.

Ensure to check the integrity and functionality of the graph operations by running the comprehensive test suite included in the `Test.cpp` file.
