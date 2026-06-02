/**
 * @file unit_tests_model.cpp
 * @brief Unit test implementations for the Model class.
 *
 * Because Flow::execute() is pure virtual, a concrete stub (StubFlow) is
 * defined locally with a fixed-percentage transfer rule so the Model's
 * execute() loop can be exercised without pulling in the functional-test
 * flow classes.
 *
 * Failures are reported via assert(); a passing test prints "OK" to stdout.
 */

#include "unit_tests_model.h"
#include "../../src/model.h"
#include "../../src/system.h"
#include "../../src/flow.h"

#include <cassert>
#include <iostream>
#include <cmath>

using namespace std;

// ─── Local Stub Subclass ──────────────────────────────────────────────────────

/**
 * @brief Concrete Flow that transfers a fixed percentage of the origin value.
 *
 * The transfer rate is specified at construction time (default 1 %).
 */
class FixedRateFlow : public Flow {
private:
    double rate;

public:
    FixedRateFlow(string name = "", double rate = 0.01)
        : Flow(name), rate(rate) {}

    double execute() override {
        if (getOrigin() != nullptr)
            return rate * getOrigin()->getValue();
        return rate; // constant injection when there is no origin
    }
};

// ─── Constructor Tests ────────────────────────────────────────────────────────

void testModelDefaultConstructor() {
    Model m;

    // Empty model: begin == end for both collections
    assert(m.beginSystems() == m.endSystems());
    assert(m.beginFlows()   == m.endFlows());

    cout << "  [Model] testModelDefaultConstructor              : OK" << endl;
}

void testModelCopyConstructor() {
    System s("sys", 10.0);
    FixedRateFlow f("flow");
    f.connect(&s, nullptr);

    Model original;
    original.add(&s);
    original.add(&f);

    Model copy(original);

    // Same pointers must appear in the copy
    assert(*copy.beginSystems() == &s);
    assert(*copy.beginFlows()   == &f);

    cout << "  [Model] testModelCopyConstructor                 : OK" << endl;
}

// ─── Assignment Operator Tests ────────────────────────────────────────────────

void testModelAssignmentOperator() {
    System s1("s1", 5.0);
    System s2("s2", 15.0);

    Model a;
    a.add(&s1);
    a.add(&s2);

    Model b;
    b = a;

    auto it = b.beginSystems();
    assert(*it == &s1); ++it;
    assert(*it == &s2); ++it;
    assert(it  == b.endSystems());

    cout << "  [Model] testModelAssignmentOperator              : OK" << endl;
}

void testModelSelfAssignment() {
    System s("self_sys", 3.0);
    Model m;
    m.add(&s);

    m = m; // must not crash or erase elements

    assert(*m.beginSystems() == &s);

    cout << "  [Model] testModelSelfAssignment                  : OK" << endl;
}

// ─── add() Tests ──────────────────────────────────────────────────────────────

void testModelAddSystem() {
    Model m;
    System s("only", 1.0);
    m.add(&s);

    auto it = m.beginSystems();
    assert(*it == &s);
    ++it;
    assert(it == m.endSystems());

    cout << "  [Model] testModelAddSystem                       : OK" << endl;
}

void testModelAddMultipleSystems() {
    Model m;
    System s1("s1", 10.0);
    System s2("s2", 20.0);
    System s3("s3", 30.0);

    m.add(&s1);
    m.add(&s2);
    m.add(&s3);

    int count = 0;
    for (auto it = m.beginSystems(); it != m.endSystems(); ++it)
        ++count;

    assert(count == 3);

    cout << "  [Model] testModelAddMultipleSystems              : OK" << endl;
}

void testModelAddFlow() {
    Model m;
    FixedRateFlow f("onlyFlow");
    m.add(&f);

    auto it = m.beginFlows();
    assert(*it == &f);
    ++it;
    assert(it == m.endFlows());

    cout << "  [Model] testModelAddFlow                         : OK" << endl;
}

void testModelAddMultipleFlows() {
    Model m;
    FixedRateFlow f1("f1");
    FixedRateFlow f2("f2");
    FixedRateFlow f3("f3");

    m.add(&f1);
    m.add(&f2);
    m.add(&f3);

    int count = 0;
    for (auto it = m.beginFlows(); it != m.endFlows(); ++it)
        ++count;

    assert(count == 3);

    cout << "  [Model] testModelAddMultipleFlows                : OK" << endl;
}

// ─── Iterator Tests ───────────────────────────────────────────────────────────

void testModelSystemIteratorsEmpty() {
    Model m;
    assert(m.beginSystems() == m.endSystems());

    cout << "  [Model] testModelSystemIteratorsEmpty            : OK" << endl;
}

void testModelFlowIteratorsEmpty() {
    Model m;
    assert(m.beginFlows() == m.endFlows());

    cout << "  [Model] testModelFlowIteratorsEmpty              : OK" << endl;
}

void testModelSystemIteratorsWithElements() {
    Model m;
    System s1("a", 1.0);
    System s2("b", 2.0);
    m.add(&s1);
    m.add(&s2);

    auto it = m.beginSystems();
    assert(*it == &s1); ++it;
    assert(*it == &s2); ++it;
    assert(it  == m.endSystems());

    cout << "  [Model] testModelSystemIteratorsWithElements     : OK" << endl;
}

void testModelFlowIteratorsWithElements() {
    Model m;
    FixedRateFlow f1("f1");
    FixedRateFlow f2("f2");
    m.add(&f1);
    m.add(&f2);

    auto it = m.beginFlows();
    assert(*it == &f1); ++it;
    assert(*it == &f2); ++it;
    assert(it  == m.endFlows());

    cout << "  [Model] testModelFlowIteratorsWithElements       : OK" << endl;
}

// ─── execute() Tests ──────────────────────────────────────────────────────────

void testModelExecuteSingleStep() {
    Model m;
    System src("src", 100.0);
    System dst("dst",   0.0);

    // 1 % flow: should transfer 1.0 (1 % of 100) in one step
    FixedRateFlow f("rate1pct", 0.01);
    f.connect(&src, &dst);

    m.add(&src);
    m.add(&dst);
    m.add(&f);

    m.execute(0, 1);

    // After 1 step: src = 99.0, dst = 1.0
    assert(fabs(src.getValue() - 99.0) < 1e-9);
    assert(fabs(dst.getValue() -  1.0) < 1e-9);

    cout << "  [Model] testModelExecuteSingleStep               : OK" << endl;
}

void testModelExecuteConservation() {
    Model m;
    System src("src", 200.0);
    System dst("dst",   0.0);

    FixedRateFlow f("conservation", 0.05);
    f.connect(&src, &dst);

    m.add(&src);
    m.add(&dst);
    m.add(&f);

    m.execute(0, 50);

    // Total value must be conserved (no external input or loss)
    double total = src.getValue() + dst.getValue();
    assert(fabs(total - 200.0) < 1e-9);

    cout << "  [Model] testModelExecuteConservation             : OK" << endl;
}

void testModelExecuteNullOrigin() {
    // A flow with no origin: acts as a source that injects a constant
    // (our stub returns rate when origin == nullptr)
    Model m;
    System dst("dst", 0.0);

    FixedRateFlow f("inject", 5.0); // injects 5.0 per step
    f.connect(nullptr, &dst);

    m.add(&dst);
    m.add(&f);

    m.execute(0, 3); // 3 steps → dst should be 15.0

    assert(fabs(dst.getValue() - 15.0) < 1e-9);

    cout << "  [Model] testModelExecuteNullOrigin               : OK" << endl;
}

void testModelExecuteNullDestination() {
    // A flow with no destination: acts as a sink that drains the origin
    Model m;
    System src("src", 100.0);

    FixedRateFlow f("drain", 0.10); // drains 10 % per step
    f.connect(&src, nullptr);

    m.add(&src);
    m.add(&f);

    // After 1 step: 100 - 0.10*100 = 90.0
    m.execute(0, 1);
    assert(fabs(src.getValue() - 90.0) < 1e-9);

    cout << "  [Model] testModelExecuteNullDestination          : OK" << endl;
}

// ─── Test Suite Entry Point ───────────────────────────────────────────────────

void runModelTests() {
    cout << "\n=== Model Unit Tests ===" << endl;

    testModelDefaultConstructor();
    testModelCopyConstructor();
    testModelAssignmentOperator();
    testModelSelfAssignment();
    testModelAddSystem();
    testModelAddMultipleSystems();
    testModelAddFlow();
    testModelAddMultipleFlows();
    testModelSystemIteratorsEmpty();
    testModelFlowIteratorsEmpty();
    testModelSystemIteratorsWithElements();
    testModelFlowIteratorsWithElements();
    testModelExecuteSingleStep();
    testModelExecuteConservation();
    testModelExecuteNullOrigin();
    testModelExecuteNullDestination();

    cout << "=== All Model tests passed! ===" << endl;
}
