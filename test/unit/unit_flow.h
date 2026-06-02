#ifndef UNIT_FLOW_H
#define UNIT_FLOW_H

/**
 * @file unit_flow.h
 * @brief Unit tests for the FlowImpl class.
 *
 * This file declares all unit test functions that exercise
 * FlowImpl's constructor, copy constructor, assignment operator,
 * getter/setter methods, and the connect() method.
 *
 * Because FlowImpl::execute() is pure virtual, a minimal concrete
 * subclass (TestFlow) is used internally in the .cpp to instantiate
 * the class under test.
 */

/**
 * @brief Tests the default constructor of FlowImpl.
 * Verifies that a default-constructed flow has an empty name
 * and null origin/destination pointers.
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
 * and that changes to the copy do not affect the original's name.
 */
void testFlowCopyConstructor();

/**
 * @brief Tests the assignment operator of FlowImpl.
 * Verifies correct assignment and self-assignment safety.
 */
void testFlowAssignmentOperator();

/**
 * @brief Tests setName() and getName() of FlowImpl.
 * Verifies that the name is correctly set and retrieved.
 */
void testFlowSetGetName();

/**
 * @brief Tests setOrigin() / getOrigin() of FlowImpl.
 * Verifies that the origin system pointer is correctly stored and returned,
 * including setting it back to nullptr.
 */
void testFlowSetGetOrigin();

/**
 * @brief Tests setDestination() / getDestination() of FlowImpl.
 * Verifies that the destination system pointer is correctly stored and returned.
 */
void testFlowSetGetDestination();

/**
 * @brief Tests the connect() method of FlowImpl.
 * Verifies that connect() correctly sets both origin and destination
 * in a single call, including overwriting previous connections.
 */
void testFlowConnect();

/**
 * @brief Aggregates and runs all FlowImpl unit tests.
 * Calls every individual test function and reports overall result.
 */
void runFlowTests();

#endif
