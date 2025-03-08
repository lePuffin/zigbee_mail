#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

// Main function that runs all tests
int main(int argc, const char** argv)
{
    // This runs the tests defined in the included test classes
    return CommandLineTestRunner::RunAllTests(argc, argv);
}