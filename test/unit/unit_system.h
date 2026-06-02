#ifndef UNIT_SYSTEM_H
#define UNIT_SYSTEM_H

/**
 * @file unit_system.h
 * @brief Unit tests for the SystemImpl class.
 *
 * This file declares all unit test functions that exercise
 * SystemImpl's constructor, copy constructor, assignment operator,
 * and getter/setter methods.
 */

/**
 * @brief Tests the default constructor of SystemImpl.
 * Verifies that a default-constructed system has an empty name and zero value.
 */
void testSystemDefaultConstructor();

/**
 * @brief Tests the parameterized constructor of SystemImpl.
 * Verifies that name and value are correctly initialized.
 */
void testSystemParameterizedConstructor();

/**
 * @brief Tests the copy constructor of SystemImpl.
 * Verifies that the copied system has the same name and value,
 * and that changes to the copy do not affect the original.
 */
void testSystemCopyConstructor();

/**
 * @brief Tests the assignment operator of SystemImpl.
 * Verifies correct deep assignment and self-assignment safety.
 */
void testSystemAssignmentOperator();

/**
 * @brief Tests setName() and getName() of SystemImpl.
 * Verifies that the name is correctly set and retrieved.
 */
void testSystemSetGetName();

/**
 * @brief Tests setValue() and getValue() of SystemImpl.
 * Verifies that the value is correctly set and retrieved, including
 * negative and floating-point values.
 */
void testSystemSetGetValue();

/**
 * @brief Aggregates and runs all SystemImpl unit tests.
 * Calls every individual test function and reports overall result.
 */
void runSystemTests();

#endif
