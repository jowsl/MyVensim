/**
 * @file unit_tests_flow.cpp
 * @brief Unit test implementations for the Flow class.
 *
 * Because Flow::execute() is pure virtual, a minimal concrete stub
 * (StubFlow) is defined locally to allow instantiation and testing of all
 * non-virtual behaviour.  A second stub (PercentFlow) exercises the execute()
 * contract with a deterministic 10 % transfer rule.
 *
 * Failures are reported via assert(); a passing test prints "OK" to stdout.
 */

#include "unit_tests_flow.h"
#include "../../src/flow.h"
#include "../../src/system.h"

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

// ─── Local Stub Subclasses ────────────────────────────────────────────────────

/**
 * @brief Minimal concrete Flow used only to enable instantiation.
 *
 * execute() always returns 0.0 so it does not interfere with structural tests.
 */
class StubFlow : public Flow {
public:
    StubFlow(string name = "",
             System* origin      = nullptr,
             System* destination = nullptr)
        : Flow(name, origin, destination) {}

    double execute() override { return 0.0; }
};

/**
 * @brief Concrete Flow that transfers exactly 10 % of the origin value.
 *
 * Used to verify that execute() reads the origin system correctly and that
 * the returned amount can be applied to update system values.
 */
class PercentFlow : public Flow {
public:
    PercentFlow(string name = "") : Flow(name) {}

    double execute() override {
        if (getOrigin() != nullptr)
            return 0.10 * getOrigin()->getValue();
        return 0.0;
    }
};

// ─── Constructor Tests ────────────────────────────────────────────────────────

void testFlowDefaultConstructor() {
    StubFlow f;

    assert(f.getName()        == "");
    assert(f.getOrigin()      == nullptr);
    assert(f.getDestination() == nullptr);

    cout << "  [Flow] testFlowDefaultConstructor                : OK" << endl;
}

void testFlowParameterizedConstructor() {
    System src("src", 100.0);
    System dst("dst",   0.0);
    StubFlow f("myFlow", &src, &dst);

    assert(f.getName()        == "myFlow");
    assert(f.getOrigin()      == &src);
    assert(f.getDestination() == &dst);

    cout << "  [Flow] testFlowParameterizedConstructor          : OK" << endl;
}

void testFlowCopyConstructor() {
    System src("s", 50.0);
    System dst("d",  0.0);
    StubFlow original("orig", &src, &dst);

    StubFlow copy(original);

    assert(copy.getName()        == "orig");
    assert(copy.getOrigin()      == &src);
    assert(copy.getDestination() == &dst);

    // Modifying the copy must not affect the original
    copy.setName("copy");
    copy.setOrigin(nullptr);

    assert(original.getName()   == "orig");
    assert(original.getOrigin() == &src);

    cout << "  [Flow] testFlowCopyConstructor                   : OK" << endl;
}

// ─── Assignment Operator Tests ────────────────────────────────────────────────

void testFlowAssignmentOperator() {
    System src("s", 10.0);
    System dst("d",  0.0);
    StubFlow a("flowA", &src, &dst);
    StubFlow b;

    b = a;

    assert(b.getName()        == "flowA");
    assert(b.getOrigin()      == &src);
    assert(b.getDestination() == &dst);

    cout << "  [Flow] testFlowAssignmentOperator                : OK" << endl;
}

void testFlowSelfAssignment() {
    System src("s", 5.0);
    StubFlow f("self", &src, nullptr);

    f = f; // must not crash or corrupt state

    assert(f.getName()   == "self");
    assert(f.getOrigin() == &src);

    cout << "  [Flow] testFlowSelfAssignment                    : OK" << endl;
}

// ─── Getter / Setter Tests ────────────────────────────────────────────────────

void testFlowSetGetName() {
    StubFlow f;

    f.setName("river");
    assert(f.getName() == "river");

    f.setName("stream");
    assert(f.getName() == "stream");

    cout << "  [Flow] testFlowSetGetName                        : OK" << endl;
}

void testFlowSetGetOrigin() {
    StubFlow f;
    System s("pop", 200.0);

    f.setOrigin(&s);
    assert(f.getOrigin() == &s);

    f.setOrigin(nullptr);
    assert(f.getOrigin() == nullptr);

    cout << "  [Flow] testFlowSetGetOrigin                      : OK" << endl;
}

void testFlowSetGetDestination() {
    StubFlow f;
    System s("sink", 0.0);

    f.setDestination(&s);
    assert(f.getDestination() == &s);

    f.setDestination(nullptr);
    assert(f.getDestination() == nullptr);

    cout << "  [Flow] testFlowSetGetDestination                 : OK" << endl;
}

// ─── Connect Tests ────────────────────────────────────────────────────────────

void testFlowConnect() {
    StubFlow f;
    System src("src", 80.0);
    System dst("dst",  0.0);

    f.connect(&src, &dst);

    assert(f.getOrigin()      == &src);
    assert(f.getDestination() == &dst);

    cout << "  [Flow] testFlowConnect                           : OK" << endl;
}

void testFlowConnectNullptr() {
    StubFlow f("flow", nullptr, nullptr);

    f.connect(nullptr, nullptr);

    assert(f.getOrigin()      == nullptr);
    assert(f.getDestination() == nullptr);

    cout << "  [Flow] testFlowConnectNullptr                    : OK" << endl;
}

// ─── Execute Tests ────────────────────────────────────────────────────────────

void testFlowExecuteStub() {
    System src("src", 200.0);
    System dst("dst",   0.0);

    PercentFlow pf("percent");
    pf.connect(&src, &dst);

    // 10 % of 200.0 == 20.0
    double amount = pf.execute();
    assert(amount == 20.0);

    // Manually apply the transfer and verify system values
    src.setValue(src.getValue() - amount);
    dst.setValue(dst.getValue() + amount);

    assert(src.getValue() == 180.0);
    assert(dst.getValue() ==  20.0);

    cout << "  [Flow] testFlowExecuteStub                       : OK" << endl;
}

// ─── Test Suite Entry Point ───────────────────────────────────────────────────

void runFlowTests() {
    cout << "\n=== Flow Unit Tests ===" << endl;

    testFlowDefaultConstructor();
    testFlowParameterizedConstructor();
    testFlowCopyConstructor();
    testFlowAssignmentOperator();
    testFlowSelfAssignment();
    testFlowSetGetName();
    testFlowSetGetOrigin();
    testFlowSetGetDestination();
    testFlowConnect();
    testFlowConnectNullptr();
    testFlowExecuteStub();

    cout << "=== All Flow tests passed! ===" << endl;
}
