#ifndef MAIN_FUNCTIONAL_TESTS
#define MAIN_FUNCTIONAL_TESTS

#include "functional_tests.h"
#include "../../src/model.h"
#include "../../src/system.h"
#include "../../src/flow.h"

int main() {
    
    exponentialFunctionalTest();
    logisticalFunctionalTest();
    complexFunctionalTest();
    
    return 0;
}
#endif