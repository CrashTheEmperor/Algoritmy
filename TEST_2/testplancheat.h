/**
 * @file testplan_cheat.h
 * @brief Template for creating test plans for ADT operations
 * @author Your Name
 * @version 1.0
 */

 #ifndef TESTPLAN_CHEAT_H
 #define TESTPLAN_CHEAT_H
 
 /**
  * Test plan structure for testing data structures. Define tests using the macros below.
  * Each test should be enclosed in curly braces {} and added to the testplan array.
  *
  * Example:
  * const struct TTestPlan testplan[] = {
  *   {
  *     TEST_MESSAGE("Test description")
  *     TEST_OPERATION(function_name)
  *     TEST_INPUTS(value1, value2, value3)
  *     TEST_OUTPUT(expected1, expected2, expected3)
  *     TEST_REPORT_AFTER
  *   },
  *   // More tests...
  * };
  */
 
 /**
  * Required test plan macros:
  */
 
 // Define the function to test
 #define TEST_OPERATION(aFunc) .iOperation = { .iFuncStr = #aFunc, .iFunc = (TTestFunc*)(aFunc) },
 
 // Define input values for testing (comma separated)
 #define TEST_INPUTS(...) .iInputs = { .iSize = ITEMS_OF((const TTestFuncInput[]) TEST_BRACED_INIT_LIST(__VA_ARGS__)), .iValues = TEST_BRACED_INIT_LIST(__VA_ARGS__) },
 
 // Define expected output values (comma separated)
 #define TEST_OUTPUT(...) .iOutput = { .iSize = ITEMS_OF((const TTestFuncOutput[]) TEST_BRACED_INIT_LIST(__VA_ARGS__)), .iValue = TEST_BRACED_INIT_LIST(__VA_ARGS__) },
 
 /**
  * Optional test plan macros:
  */
 
 // Add a description message to the test
 #define TEST_MESSAGE(aStr) .iMessage = (aStr),
 
 // Print detailed list of operations before testing
 #define TEST_LIST_OPERATIONS .iListOperations = true,
 
 // Print data structure contents before test
 #define TEST_REPORT_BEFORE .iReportBefore = true,
 
 // Print data structure contents after test
 #define TEST_REPORT_AFTER .iReportAfter = true,
 
 // Print memory allocation statistics after test
 #define TEST_PRINT_MEMORY_STATS .iMemoryStats = true,
 
 #endif /* TESTPLAN_CHEAT_H */