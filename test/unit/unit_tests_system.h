#ifndef UNIT_TESTS_SYSTEM_H
#define UNIT_TESTS_SYSTEM_H

/**
 * @file unit_tests_system.h
 * @brief Unit tests for the System class.
 *
 * This file declares all unit test functions responsible for validating
 * the behavior of the System class, including construction, copy semantics,
 * assignment, and getter/setter methods.
 */

// ─── Constructor Tests ────────────────────────────────────────────────────────

/**
 * @brief Tests the default constructor of System.
 *
 * Verifies that a System created with no arguments initializes name to an
 * empty string and value to 0.0.
 */
void testSystemDefaultConstructor();

/**
 * @brief Tests the parameterized constructor of System.
 *
 * Verifies that a System created with explicit name and value stores them
 * correctly.
 */
void testSystemParameterizedConstructor();

/**
 * @brief Tests the copy constructor of System.
 *
 * Verifies that a System constructed from another System holds identical
 * name and value, and that modifying the copy does not affect the original.
 */
void testSystemCopyConstructor();

// ─── Assignment Operator Tests ────────────────────────────────────────────────

/**
 * @brief Tests the assignment operator of System.
 *
 * Verifies that assigning one System to another copies name and value
 * correctly.
 */
void testSystemAssignmentOperator();

/**
 * @brief Tests self-assignment of System.
 *
 * Verifies that assigning a System to itself leaves name and value unchanged.
 */
void testSystemSelfAssignment();

// ─── Getter / Setter Tests ────────────────────────────────────────────────────

/**
 * @brief Tests setName and getName of System.
 *
 * Verifies that a name set via setName is correctly returned by getName.
 */
void testSystemSetGetName();

/**
 * @brief Tests setValue and getValue of System.
 *
 * Verifies that a value set via setValue is correctly returned by getValue.
 */
void testSystemSetGetValue();

/**
 * @brief Tests setting the System value to zero.
 *
 * Verifies that the system correctly stores and returns the value 0.0.
 */
void testSystemSetValueZero();

/**
 * @brief Tests setting the System value to a negative number.
 *
 * Verifies that the system correctly stores and returns a negative value.
 */
void testSystemSetValueNegative();

// ─── Test Suite Entry Point ───────────────────────────────────────────────────

/**
 * @brief Runs all unit tests for the System class.
 *
 * This function calls every individual System test function and reports
 * overall success upon completion.
 */
void runSystemTests();

#endif // UNIT_TESTS_SYSTEM_H
