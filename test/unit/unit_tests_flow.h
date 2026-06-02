#ifndef UNIT_TESTS_FLOW_H
#define UNIT_TESTS_FLOW_H

/**
 * @file unit_tests_flow.h
 * @brief Unit tests for the Flow class.
 *
 * This file declares all unit test functions responsible for validating
 * the behavior of the Flow class, including construction, copy semantics,
 * assignment, getter/setter methods, the connect helper, and the pure-virtual
 * execute() contract via a concrete stub subclass.
 */

// ─── Constructor Tests ────────────────────────────────────────────────────────

/**
 * @brief Tests the default constructor of Flow.
 *
 * Verifies that a Flow constructed with no arguments has an empty name and
 * null origin/destination pointers.
 */
void testFlowDefaultConstructor();

/**
 * @brief Tests the parameterized constructor of Flow.
 *
 * Verifies that name, origin, and destination supplied at construction time
 * are stored correctly.
 */
void testFlowParameterizedConstructor();

/**
 * @brief Tests the copy constructor of Flow.
 *
 * Verifies that a Flow constructed from another Flow shares the same name
 * and pointer values, and that altering the copy does not change the original.
 */
void testFlowCopyConstructor();

// ─── Assignment Operator Tests ────────────────────────────────────────────────

/**
 * @brief Tests the assignment operator of Flow.
 *
 * Verifies that assigning one Flow to another copies name, origin, and
 * destination correctly.
 */
void testFlowAssignmentOperator();

/**
 * @brief Tests self-assignment of Flow.
 *
 * Verifies that assigning a Flow to itself leaves all attributes unchanged.
 */
void testFlowSelfAssignment();

// ─── Getter / Setter Tests ────────────────────────────────────────────────────

/**
 * @brief Tests setName and getName of Flow.
 *
 * Verifies that the name stored via setName is correctly returned by getName.
 */
void testFlowSetGetName();

/**
 * @brief Tests setOrigin and getOrigin of Flow.
 *
 * Verifies that the origin pointer stored via setOrigin is correctly returned
 * by getOrigin.
 */
void testFlowSetGetOrigin();

/**
 * @brief Tests setDestination and getDestination of Flow.
 *
 * Verifies that the destination pointer stored via setDestination is correctly
 * returned by getDestination.
 */
void testFlowSetGetDestination();

// ─── Connect Tests ────────────────────────────────────────────────────────────

/**
 * @brief Tests the connect() method of Flow.
 *
 * Verifies that connect() sets both origin and destination in a single call.
 */
void testFlowConnect();

/**
 * @brief Tests connecting a Flow to null pointers.
 *
 * Verifies that calling connect() with nullptr for both arguments is accepted
 * and results in null origin and destination.
 */
void testFlowConnectNullptr();

// ─── Execute Tests ────────────────────────────────────────────────────────────

/**
 * @brief Tests the execute() method via a concrete stub Flow.
 *
 * Uses a simple stub subclass (transfers 10 % of the origin value) to verify
 * that execute() returns the expected amount and that the value propagates
 * when applied manually.
 */
void testFlowExecuteStub();

// ─── Test Suite Entry Point ───────────────────────────────────────────────────

/**
 * @brief Runs all unit tests for the Flow class.
 *
 * This function calls every individual Flow test function and reports
 * overall success upon completion.
 */
void runFlowTests();

#endif // UNIT_TESTS_FLOW_H
