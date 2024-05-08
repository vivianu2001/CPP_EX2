#include <iostream>

// Declaration of functions from other modules
void runDemo();
int runTests();

int main(int argc, char **argv)
{
    std::cout << "Running demo..." << std::endl;
    runDemo(); // Run the demo functionality

    std::cout << "\nRunning tests..." << std::endl;
    int testResult = runTests(); // Run tests and capture the result

    return testResult; // Return the result of the tests as the program's exit code
}