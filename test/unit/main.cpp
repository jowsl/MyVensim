#ifndef MAIN_UNIT_TESTS
#define MAIN_UNIT_TESTS

/**
 * @file main.cpp
 * @brief Entry point for the unit test suite.
 *
 * Calls runAllUnitTests(), which in turn delegates to each
 * class-specific test runner: runSystemTests(), runFlowTests(),
 * and runModelTests().
 *
 * Build and run with:
 * @code
 *   make unit
 *   ./bin/unit_tests
 * @endcode
 */

#include "unit_system.h"
#include "unit_flow.h"
#include "unit_model.h"
#include <iostream>

using namespace std;

/**
 * @brief Aggregates and runs the complete unit test suite.
 *
 * Executes tests for SystemImpl, FlowImpl and ModelImpl in order.
 * Any failed assertion will terminate the process immediately via
 * assert(), clearly indicating which test caused the failure.
 */
void runAllUnitTests() {
    cout << "               Unit Test" << endl;

    runSystemTests();
    runFlowTests();
    runModelTests();

    cout << "         All unit tests passed!" << endl;
}

int main() {
    runAllUnitTests();
    return 0;
}

#endif
