#ifndef UNIT_MODEL_H
#define UNIT_MODEL_H

/**
 * @file unit_model.h
 * @brief Unit tests for the ModelImpl class.
 *
 * This file declares all unit test functions that exercise
 * ModelImpl's Singleton access, Factory methods, iterator methods, 
 * and execute(). Validation is performed by directly accessing 
 * protected attributes to ensure single-method isolation.
 */

/**
 * @brief Tests the Singleton instantiation and clear() method.
 */
void testModelSingletonAndClear();

/**
 * @brief Tests the Factory Method createSystem().
 */
void testModelCreateSystem();

/**
 * @brief Tests the generic Factory Method createFlow<T>().
 */
void testModelCreateFlow();

/**
 * @brief Tests the system iterators (beginSystems / endSystems).
 */
void testModelSystemIterators();

/**
 * @brief Tests the flow iterators (beginFlows / endFlows).
 */
void testModelFlowIterators();

/**
 * @brief Tests execute() using Mock objects.
 */
void testModelExecute();

/**
 * @brief Tests execute() with a flow that has a null origin.
 */
void testModelExecuteNullOrigin();

/**
 * @brief Tests execute() with a flow that has a null destination.
 */
void testModelExecuteNullDestination();

/**
 * @brief Aggregates and runs all ModelImpl unit tests.
 */
void runModelTests();

#endif