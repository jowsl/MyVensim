#ifndef UNIT_SYSTEM_H
#define UNIT_SYSTEM_H

/**
 * @file unit_system.h
 * @brief Unit tests for the SystemImpl class.
 *
 * This file declares all unit test functions that exercise
 * SystemImpl's constructor, copy constructor, assignment operator,
 * and getter/setter methods. Each test is strictly isolated to test
 * a single method, using a friend class to directly access and
 * validate internal state.
 */

/**
 * @brief Tests the default constructor of SystemImpl.
 * Verifies that a default-constructed system has an empty name and zero value
 * by directly reading protected attributes.
 */
void testSystemDefaultConstructor();

/**
 * @brief Tests the parameterized constructor of SystemImpl.
 * Verifies that name and value are correctly initialized
 * by directly reading protected attributes.
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
 * Verifies correct deep assignment and self-assignment safety,
 * directly validating internal attributes.
 */
void testSystemAssignmentOperator();

/**
 * @brief Tests setName() of SystemImpl.
 * Verifies that the name is correctly set by validating the protected attribute directly.
 */
void testSystemSetName();

/**
 * @brief Tests getName() of SystemImpl.
 * Verifies that the name is correctly retrieved after setting the protected attribute directly.
 */
void testSystemGetName();

/**
 * @brief Tests setValue() of SystemImpl.
 * Verifies that the value is correctly set, including negative and floating-point values,
 * by validating the protected attribute directly.
 */
void testSystemSetValue();

/**
 * @brief Tests getValue() of SystemImpl.
 * Verifies that the value is correctly retrieved after setting the protected attribute directly.
 */
void testSystemGetValue();

/**
 * @brief Aggregates and runs all SystemImpl unit tests.
 * Calls every individual test function and reports overall result.
 */
void runSystemTests();

#endif