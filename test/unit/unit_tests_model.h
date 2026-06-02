#ifndef UNIT_TESTS_MODEL_H
#define UNIT_TESTS_MODEL_H

/**
 * @file unit_tests_model.h
 * @brief Unit tests for the Model class.
 *
 * This file declares all unit test functions responsible for validating
 * the behavior of the Model class, including construction, copy semantics,
 * assignment, adding elements, iterator access, and the execute() simulation
 * loop.
 */

// ─── Constructor Tests ────────────────────────────────────────────────────────

/**
 * @brief Tests the default constructor of Model.
 *
 * Verifies that a newly constructed Model has no Systems and no Flows
 * (i.e., beginSystems() == endSystems() and beginFlows() == endFlows()).
 */
void testModelDefaultConstructor();

/**
 * @brief Tests the copy constructor of Model.
 *
 * Verifies that a Model constructed from another contains the same Systems
 * and Flows (by pointer), and that structural changes to the copy do not
 * affect the original.
 */
void testModelCopyConstructor();

// ─── Assignment Operator Tests ────────────────────────────────────────────────

/**
 * @brief Tests the assignment operator of Model.
 *
 * Verifies that assigning one Model to another copies the System and Flow
 * pointer lists correctly.
 */
void testModelAssignmentOperator();

/**
 * @brief Tests self-assignment of Model.
 *
 * Verifies that assigning a Model to itself does not corrupt its internal
 * System or Flow lists.
 */
void testModelSelfAssignment();

// ─── add() Tests ──────────────────────────────────────────────────────────────

/**
 * @brief Tests adding a single System to the Model.
 *
 * Verifies that after one add(System*) call, the Model iterators span
 * exactly one element equal to the added pointer.
 */
void testModelAddSystem();

/**
 * @brief Tests adding multiple Systems to the Model.
 *
 * Verifies that multiple add(System*) calls accumulate correctly and that
 * all pointers are accessible via the system iterators.
 */
void testModelAddMultipleSystems();

/**
 * @brief Tests adding a single Flow to the Model.
 *
 * Verifies that after one add(Flow*) call, the Model iterators span exactly
 * one element equal to the added pointer.
 */
void testModelAddFlow();

/**
 * @brief Tests adding multiple Flows to the Model.
 *
 * Verifies that multiple add(Flow*) calls accumulate correctly and that
 * all pointers are accessible via the flow iterators.
 */
void testModelAddMultipleFlows();

// ─── Iterator Tests ───────────────────────────────────────────────────────────

/**
 * @brief Tests system iterators on an empty Model.
 *
 * Verifies that beginSystems() == endSystems() when no System has been added.
 */
void testModelSystemIteratorsEmpty();

/**
 * @brief Tests flow iterators on an empty Model.
 *
 * Verifies that beginFlows() == endFlows() when no Flow has been added.
 */
void testModelFlowIteratorsEmpty();

/**
 * @brief Tests system iterators after adding elements.
 *
 * Verifies that iterating from beginSystems() to endSystems() visits every
 * added System pointer in insertion order.
 */
void testModelSystemIteratorsWithElements();

/**
 * @brief Tests flow iterators after adding elements.
 *
 * Verifies that iterating from beginFlows() to endFlows() visits every
 * added Flow pointer in insertion order.
 */
void testModelFlowIteratorsWithElements();

// ─── execute() Tests ──────────────────────────────────────────────────────────

/**
 * @brief Tests the execute() method with a simple exponential transfer.
 *
 * Uses a single-step run (time 0 to 1) and validates that the system values
 * are updated by exactly the amount returned by execute().
 */
void testModelExecuteSingleStep();

/**
 * @brief Tests the execute() method for multiple steps.
 *
 * Runs the model for several steps and verifies that the total value
 * (origin + destination) is conserved across all iterations.
 */
void testModelExecuteConservation();

/**
 * @brief Tests the execute() method with a null-origin Flow.
 *
 * Verifies that a Flow with no origin only adds to the destination without
 * attempting to modify a null pointer.
 */
void testModelExecuteNullOrigin();

/**
 * @brief Tests the execute() method with a null-destination Flow.
 *
 * Verifies that a Flow with no destination only subtracts from the origin
 * without attempting to modify a null pointer.
 */
void testModelExecuteNullDestination();

// ─── Test Suite Entry Point ───────────────────────────────────────────────────

/**
 * @brief Runs all unit tests for the Model class.
 *
 * This function calls every individual Model test function and reports
 * overall success upon completion.
 */
void runModelTests();

#endif // UNIT_TESTS_MODEL_H
