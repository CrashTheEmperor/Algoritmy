{
TEST_MESSAGE("Vlozeni elementu: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9")
TEST_OPERATION(set_insert)
TEST_INPUTS( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9 )
TEST_OUTPUT( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 )
//TEST_LIST_OPERATIONS
//TEST_REPORT_BEFORE
//TEST_REPORT_AFTER
TEST_PRINT_MEMORY_STATS
},

{
TEST_MESSAGE("Test pritomnosti elementu: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9")
TEST_OPERATION(set_is_element_of)
TEST_INPUTS( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9 )
TEST_OUTPUT( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 )
//TEST_LIST_OPERATIONS
//TEST_REPORT_BEFORE
//TEST_REPORT_AFTER
},

{
TEST_MESSAGE("Odebrani elementu: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9")
TEST_OPERATION(set_erase)
TEST_INPUTS( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9 )
TEST_OUTPUT( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 )
//TEST_LIST_OPERATIONS
//TEST_REPORT_BEFORE
//TEST_REPORT_AFTER
TEST_PRINT_MEMORY_STATS
},
