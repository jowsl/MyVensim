/**
 * @file unit_tests_system.cpp
 * @brief Unit test implementations for the System class.
 *
 * Each function exercises one specific aspect of the System class.
 * Failures are reported via assert(); a passing test prints "OK" to stdout.
 */

#include "unit_tests_system.h"
#include "../../src/system.h"

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

// ─── Constructor Tests ────────────────────────────────────────────────────────

void testSystemDefaultConstructor() {
    System s;

    assert(s.getName()  == "");
    assert(s.getValue() == 0.0);

    cout << "  [System] testSystemDefaultConstructor            : OK" << endl;
}

void testSystemParameterizedConstructor() {
    System s("reservoir", 42.5);

    assert(s.getName()  == "reservoir");
    assert(s.getValue() == 42.5);

    cout << "  [System] testSystemParameterizedConstructor      : OK" << endl;
}

void testSystemCopyConstructor() {
    System original("source", 99.0);
    System copy(original);

    // Values must match
    assert(copy.getName()  == "source");
    assert(copy.getValue() == 99.0);

    // Modifying copy must NOT affect original
    copy.setName("copy");
    copy.setValue(1.0);

    assert(original.getName()  == "source");
    assert(original.getValue() == 99.0);

    cout << "  [System] testSystemCopyConstructor               : OK" << endl;
}

// ─── Assignment Operator Tests ────────────────────────────────────────────────

void testSystemAssignmentOperator() {
    System a("alpha", 10.0);
    System b;

    b = a;

    assert(b.getName()  == "alpha");
    assert(b.getValue() == 10.0);

    cout << "  [System] testSystemAssignmentOperator            : OK" << endl;
}

void testSystemSelfAssignment() {
    System s("self", 7.7);

    s = s; // must not crash or corrupt state

    assert(s.getName()  == "self");
    assert(s.getValue() == 7.7);

    cout << "  [System] testSystemSelfAssignment                : OK" << endl;
}

// ─── Getter / Setter Tests ────────────────────────────────────────────────────

void testSystemSetGetName() {
    System s;

    s.setName("ocean");
    assert(s.getName() == "ocean");

    // Overwrite with a new name
    s.setName("lake");
    assert(s.getName() == "lake");

    cout << "  [System] testSystemSetGetName                    : OK" << endl;
}

void testSystemSetGetValue() {
    System s;

    s.setValue(3.14);
    assert(s.getValue() == 3.14);

    // Overwrite with another value
    s.setValue(2.71);
    assert(s.getValue() == 2.71);

    cout << "  [System] testSystemSetGetValue                   : OK" << endl;
}

void testSystemSetValueZero() {
    System s("zero", 50.0);

    s.setValue(0.0);
    assert(s.getValue() == 0.0);

    cout << "  [System] testSystemSetValueZero                  : OK" << endl;
}

void testSystemSetValueNegative() {
    System s("negative", 10.0);

    s.setValue(-25.0);
    assert(s.getValue() == -25.0);

    cout << "  [System] testSystemSetValueNegative              : OK" << endl;
}

// ─── Test Suite Entry Point ───────────────────────────────────────────────────

void runSystemTests() {
    cout << "\n=== System Unit Tests ===" << endl;

    testSystemDefaultConstructor();
    testSystemParameterizedConstructor();
    testSystemCopyConstructor();
    testSystemAssignmentOperator();
    testSystemSelfAssignment();
    testSystemSetGetName();
    testSystemSetGetValue();
    testSystemSetValueZero();
    testSystemSetValueNegative();

    cout << "=== All System tests passed! ===" << endl;
}
