#ifndef UNIT_FLOW_H
#define UNIT_FLOW_H

/**
 * @file unit_flow.h
 * @brief Unit tests for the FlowImpl class.
 *
 * This file declares all unit test functions that exercise
 * FlowImpl's constructor, copy constructor, assignment operator,
 * getter/setter methods, and the connect() method. Each test validates
 * a single method at a time, using a friend class to directly access
 * protected attributes.
 *
 * Because FlowImpl::execute() is pure virtual, a minimal concrete
 * subclass (TestFlow) is used internally in the .cpp to instantiate
 * the class under test.
 */

/**
 * @brief Tests the default constructor of FlowImpl.
 * Verifies that a default-constructed flow has an empty name
 * and null origin/destination pointers via direct attribute access.
 */
void testFlowDefaultConstructor();

/**
 * @brief Tests the parameterized constructor of FlowImpl.
 * Verifies that name, origin, and destination are correctly initialized.
 */
void testFlowParameterizedConstructor();

/**
 * @brief Tests the copy constructor of FlowImpl.
 * Verifies that the copied flow shares the same pointer values,
 * and that changes to the copy do not affect the original.
 */
void testFlowCopyConstructor();

/**
 * @brief Tests the assignment operator of FlowImpl.
 * Verifies correct assignment and self-assignment safety.
 */
void testFlowAssignmentOperator();

/**
 * @brief Tests setName() of FlowImpl.
 * Verifies that the name is correctly set by checking the protected attribute directly.
 */
void testFlowSetName();

/**
 * @brief Tests getName() of FlowImpl.
 * Verifies that the name is correctly retrieved after setting the protected attribute directly.
 */
void testFlowGetName();

/**
 * @brief Tests setOrigin() of FlowImpl.
 * Verifies that the origin system pointer is correctly stored by checking the protected attribute directly.
 */
void testFlowSetOrigin();

/**
 * @brief Tests getOrigin() of FlowImpl.
 * Verifies that the origin system pointer is correctly returned after setting the protected attribute directly.
 */
void testFlowGetOrigin();

/**
 * @brief Tests setDestination() of FlowImpl.
 * Verifies that the destination system pointer is correctly stored by checking the protected attribute directly.
 */
void testFlowSetDestination();

/**
 * @brief Tests getDestination() of FlowImpl.
 * Verifies that the destination system pointer is correctly returned after setting the protected attribute directly.
 */
void testFlowGetDestination();

/**
 * @brief Tests the connect() method of FlowImpl.
 * Verifies that connect() correctly sets both origin and destination
 * in a single call, checking the protected attributes directly.
 */
void testFlowConnect();

/**
 * @brief Aggregates and runs all FlowImpl unit tests.
 * Calls every individual test function and reports overall result.
 */
void runFlowTests();

#endif