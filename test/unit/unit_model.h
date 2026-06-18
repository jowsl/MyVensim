#ifndef UNIT_MODEL_H
#define UNIT_MODEL_H

/**
 * @brief Suíte de testes unitários da Interface Model usando sub-rogações (Mocks).
 */
void testModelRegistryAndClear();
void testModelCreateSystem();
void testModelCreateFlow();
void testModelSystemIterators();
void testModelFlowIterators();
void testModelExecute();
void testModelExecuteNullOrigin();
void testModelExecuteNullDestination();

void runModelTests();

#endif