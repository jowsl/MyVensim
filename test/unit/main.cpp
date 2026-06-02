/**
 * @file main.cpp
 * @brief Entry point for the MyVensim unit-test suite.
 *
 * This file calls the top-level runner for each class under test.
 * Each runner groups all unit tests for one class, executing them in
 * sequence and printing a summary line on success.
 *
 * To add tests for a new class:
 *  1. Create unit_tests_<class>.h / .cpp following the existing pattern.
 *  2. Include the header here.
 *  3. Call its run<Class>Tests() function inside main().
 */

#include "unit_tests_system.h"
#include "unit_tests_flow.h"
#include "unit_tests_model.h"

#include <iostream>

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "   MyVensim - Unit Test Suite" << endl;
    cout << "========================================" << endl;

    runSystemTests();
    runFlowTests();
    runModelTests();

    cout << "\n========================================"  << endl;
    cout << "   All unit tests passed successfully!"     << endl;
    cout << "========================================"   << endl;

    return 0;
}
