#ifndef UNIT_MODEL_H
#define UNIT_MODEL_H

/**
 * @file unit_model.h
 * @brief Unit tests for the ModelImpl class.
 *
 * This file declares all unit test functions that exercise
 * ModelImpl's constructor, copy constructor, assignment operator,
 * add() methods, iterator methods, and execute().
 *
 * Because FlowImpl::execute() is pure virtual, a minimal concrete
 * subclass (ModelTestFlow) is used internally in the .cpp.
 */

/**
 * @brief Tests the default constructor of ModelImpl.
 * Verifies that a freshly constructed model has empty systems
 * and flows collections.
 */
void testModelDefaultConstructor();

/**
 * @brief Tests the copy constructor of ModelImpl.
 * Verifies that the copied model references the same system and
 * flow pointers, and that the original is not modified afterwards.
 */
void testModelCopyConstructor();

/**
 * @brief Tests the assignment operator of ModelImpl.
 * Verifies correct assignment including self-assignment safety.
 */
void testModelAssignmentOperator();

/**
 * @brief Tests add(System*) of ModelImpl.
 * Verifies that systems are correctly appended to the internal collection.
 */
void testModelAddSystem();

/**
 * @brief Tests add(Flow*) of ModelImpl.
 * Verifies that flows are correctly appended to the internal collection.
 */
void testModelAddFlow();

/**
 * @brief Tests the system iterators (beginSystems / endSystems) of ModelImpl.
 * Verifies that iteration covers exactly the added systems in insertion order.
 */
void testModelSystemIterators();

/**
 * @brief Tests the flow iterators (beginFlows / endFlows) of ModelImpl.
 * Verifies that iteration covers exactly the added flows in insertion order.
 */
void testModelFlowIterators();

/**
 * @brief Tests execute() with a simple exponential flow.
 * Verifies that after 100 steps the system values match the
 * expected acceptance criteria (same as the functional test).
 */
void testModelExecuteExponential();

/**
 * @brief Tests execute() with a flow that has a null origin.
 * Verifies that the model does not crash and only updates
 * the destination system.
 */
void testModelExecuteNullOrigin();

/**
 * @brief Tests execute() with a flow that has a null destination.
 * Verifies that the model does not crash and only updates
 * the origin system.
 */
void testModelExecuteNullDestination();

/**
 * @brief Aggregates and runs all ModelImpl unit tests.
 * Calls every individual test function and reports overall result.
 */
void runModelTests();

#endif
