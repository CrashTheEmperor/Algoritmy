/**
 * @file main_functions_cheat.c
 * @brief Cheat sheet for main functions from the sample code
 * @author Based on code samples
 */

/*************************************************************
 * STACK USAGE EXAMPLE
 *************************************************************/

/**
 * Example of loading stack data from a file 
 */
bool stack_init_file(struct TStack* aStack, FILE* aInputFile)
{
    if (aStack == NULL || aInputFile == NULL)
        return false;

    stack_init(aStack);
    int count;

    if (fscanf_s(aInputFile, "%d", &count) != 1)
        return false;

    for (size_t i = 0; i < count; i++)
    {
        int value;
        if (fscanf_s(aInputFile, "%d", &value) != 1)
        {
            stack_destroy(aStack);
            return false;
        }

        if (!stack_push(aStack, value))
        {
            stack_destroy(aStack);
            return false;
        }
    }

    return true;
}

/**
 * Main function demonstrating stack operations
 */
int stack_main_example(void)
{
    // Initialize stack
    struct TStack stack;
    stack_init(&stack);
    
    // Open input file
    FILE* inputfile = fopen("data.txt", "r");
    if (!inputfile)
    {
        printf("ERROR: Cannot open input file\n");
        return 1;
    }

    // Load stack from file
    if (!stack_init_file(&stack, inputfile))
    {
        printf("ERROR: Failed to initialize stack from file\n");
        fclose(inputfile);
        stack_destroy(&stack);
        return 2;
    }

    // Print stack contents using iterators
    printf("Stack contents:\n");
    struct TStackIterator iter = stack_iterator_begin(&stack);
    while (stack_iterator_is_valid(&iter))
    {
        printf("%d ", stack_iterator_value(&iter));
        stack_iterator_to_next(&iter);
    }
    printf("\n");

    // Pop and process elements
    int val;
    while (!stack_is_empty(&stack))
    {
        if (!stack_top(&stack, &val))
        {
            printf("Error: Failed to get top element\n");
            fclose(inputfile);
            stack_destroy(&stack);
            return 3;
        }

        printf("Popped value: %d\n", val);

        if (!stack_pop(&stack))
        {
            printf("Error: Failed to pop element\n");
            fclose(inputfile);
            stack_destroy(&stack);
            return 4;
        }

        // Check next value if stack not empty
        if (!stack_is_empty(&stack))
        {
            int val2;
            if (!stack_top(&stack, &val2))
            {
                printf("Error: Failed to get top element\n");
                fclose(inputfile);
                stack_destroy(&stack);
                return 5;
            }

            printf("Next value: %d\n", val2);
            
            if (val > val2)
                printf("\n");
        }
    }

    // Cleanup
    fclose(inputfile);
    stack_destroy(&stack);
    return 0;
}

/*************************************************************
 * QUEUE USAGE EXAMPLE 
 *************************************************************/

/**
 * Main function demonstrating queue operations with rotation
 */
int queue_main_example(void)
{
    // Initialize queue
    struct TQueue queue;
    queue_init(&queue);

    // Read characters until newline
    while (true) {
        char znak = getchar();
        if (znak == '\n')
            break;
        queue_push(&queue, znak);
    }

    // Get number of rotations
    int num;
    do {
        printf("Number of rotations: ");
        scanf("%d", &num);
    } while (num == 0);

    // Print initial queue contents
    for (struct TQueueIterator it = queue_iterator_begin(&queue); 
         queue_iterator_is_valid(&it); 
         queue_iterator_to_next(&it))
        printf("%c", queue_iterator_value(&it));
    printf("\n");
    
    // Perform rotations
    if (num > 0) {
        // Rotate right (move front to back)
        while (num != 0) {
            TQueueElement current;
            queue_front(&queue, &current);  // Get front element
            queue_pop(&queue);              // Remove from front
            queue_push(&queue, current);    // Push to back
            
            // Print current state after rotation
            for (struct TQueueIterator it = queue_iterator_begin(&queue); 
                 queue_iterator_is_valid(&it); 
                 queue_iterator_to_next(&it))
                printf("%c", queue_iterator_value(&it));
            printf("\n");
            
            num -= 1;
        }
    } else if (num < 0) {
        // Rotate left (move back to front)
        while (num != 0) {
            TQueueElement current;
            queue_back(&queue, &current);   // Get back element
            queue_pop_back(&queue);         // Remove from back
            queue_push_front(&queue, current); // Push to front
            
            // Print current state after rotation
            for (struct TQueueIterator it = queue_iterator_begin(&queue); 
                 queue_iterator_is_valid(&it); 
                 queue_iterator_to_next(&it))
                printf("%c", queue_iterator_value(&it));
            printf("\n");
            
            num += 1;
        }
    }

    // Cleanup
    queue_destroy(&queue);
    return 0;
}

/*************************************************************
 * PALINDROME DETECTOR USING STACK AND QUEUE
 *************************************************************/

/**
 * Main function demonstrating palindrome detection
 * Uses both stack and queue to compare characters
 */
int palindrome_main_example(int argc, char* argv[]) 
{
    // Initialize data structures
    struct TStack stack1;
    stack_init(&stack1);
    struct TQueue queue1;
    queue_init(&queue1);

    // Method 1: Read from stdin
    char arr[10000];
    scanf("%[^\n]%*c", arr);  // Read until newline
    
    // Process each character
    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == ' ' || arr[i] == '\0') {
            // Compare stack (reversed order) with queue (original order)
            struct TStackIterator StackIt = stack_iterator_begin(&stack1);
            struct TQueueIterator QueueIt = queue_iterator_begin(&queue1);
            bool palindrom = true;
            
            while (stack_iterator_is_valid(&StackIt) && queue_iterator_is_valid(&QueueIt)) {
                if (stack_iterator_value(&StackIt) == queue_iterator_value(&QueueIt)) {
                    stack_iterator_to_next(&StackIt);
                    queue_iterator_to_next(&QueueIt);
                } else {
                    palindrom = false;
                    break;
                }
            }
            
            // Print result
            printf("Word: '");
            for (struct TQueueIterator it = queue_iterator_begin(&queue1); 
                 queue_iterator_is_valid(&it); 
                 queue_iterator_to_next(&it))
                printf("%c", queue_iterator_value(&it));
            
            if (palindrom) {
                printf("' is a palindrome.\n");
            } else {
                printf("' is not a palindrome.\n");
            }
            
            // Reset for next word
            stack_destroy(&stack1);
            queue_destroy(&queue1);
            stack_init(&stack1);
            queue_init(&queue1);
        } else {
            // Store character in both stack and queue
            stack_push(&stack1, arr[i]);
            queue_push(&queue1, arr[i]);
        }
    }

    // Cleanup
    stack_destroy(&stack1);
    queue_destroy(&queue1);
    return 0;
}

/*************************************************************
 * SET OPERATIONS EXAMPLE
 *************************************************************/

/**
 * Example main function demonstrating set operations
 */
int set_main_example(void)
{
    // Initialize three sets
    struct TSet set1 = { 0 };
    struct TSet set2 = { 0 };
    struct TSet set3 = { 0 };
    set_init(&set1);
    set_init(&set2);
    set_init(&set3);

    // Run test plans on each set
    if (!testbench_run(&set1, 1, testplan))
    {
        puts("testplan 1 failed!!!");
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&set3);
        return 1;
    }
    
    if (!testbench_run(&set2, 1, testplan + 1))
    {
        puts("testplan 2 failed!!!");
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&set3);
        return 2;
    }
    
    if (!testbench_run(&set3, 1, testplan + 2))
    {
        puts("testplan 3 failed!!!");
        set_destroy(&set1);
        set_destroy(&set2);
        set_destroy(&set3);
        return 3;
    }

    // Print contents of each set
    printf("SET1: ");
    set_for_each(set_iterator_begin(&set1), print_value_by_iterator);
    printf("\n");

    printf("SET2: ");
    set_for_each(set_iterator_begin(&set2), print_value_by_iterator);
    printf("\n");
    
    printf("SET3: ");
    set_for_each(set_iterator_begin(&set3), print_value_by_iterator);
    printf("\n");

    // Test equality of sets
    if (set_equal(&set1, &set2))
    {
        printf("Set1 is equal to set2\n");
        printf("SET1: ");
        set_for_each(set_iterator_begin(&set1), print_value_by_iterator);
        printf("\n");

        printf("SET2: ");
        set_for_each(set_iterator_begin(&set2), print_value_by_iterator);
        printf("\n");
    }
    else
        printf("Set1 is not equal to set2\n");
    
    if (set_equal(&set1, &set3))
    {
        printf("Set1 is equal to set3\n");
        printf("SET1: ");
        set_for_each(set_iterator_begin(&set1), print_value_by_iterator);
        printf("\n");

        printf("SET3: ");
        set_for_each(set_iterator_begin(&set3), print_value_by_iterator);
        printf("\n");
    }
    else
        printf("Set1 is not equal to set3\n");
    
    // Test self-equality
    if (set_equal(&set1, &set1))
    {
        printf("Set1 is equal to itself\n");
    }
    else
        printf("Set1 is not equal to itself (error)\n");
    
    // Cleanup
    set_destroy(&set1);
    set_destroy(&set2);
    set_destroy(&set3);
    return 0;
}

/*************************************************************
 * SORTING ALGORITHMS EXAMPLE
 *************************************************************/

/**
 * Function to test sorting algorithms and collect statistics
 */
bool sort_testing(const char *aSortNameStr, void (*aSortFunc)(struct TVector *), const struct TVector *aOrigVector)
{
    // Clone the original vector for testing
    struct TVector vector = { 0 };
    if (!vector_clone(aOrigVector, &vector))
        return false;
    
    printf("\n------ %s ------\n", aSortNameStr);

    // Measure execution time
    struct timespec start_timespec = { 0 }, end_timespec = { 0 };
    timespec_get(&start_timespec, TIME_UTC);
    
    // Execute sorting algorithm
    (*aSortFunc)(&vector);
    
    timespec_get(&end_timespec, TIME_UTC);

    // Verify the sort was successful
    const bool is_sorted = vector_is_ascendantly_sorted(aOrigVector, &vector);
    printf("\nVector is %s\n", is_sorted ? "sorted. OK :-)" : "not sorted!!! FAIL :-(");
    printf("\nSorting time: %lf seconds.\n", difftimespec(end_timespec, start_timespec));

    // Print statistics about the sort
    vector_print_sortstats(&vector);
    vector_destroy(&vector);
    return is_sorted;
}

/**
 * Main function demonstrating sorting algorithms
 */
int sorting_main_example(void)
{
    // Initialize with random seed
    srand((unsigned int)time(NULL));

    // Load data from file
    struct TVector vector_orig = { 0 };
    FILE *fsrc = fopen("data_time.txt", "r");
    
    if (!fsrc)
        return 1;

    // Initialize vector from file
    bool initialized = vector_init_file(&vector_orig, fsrc);
    fclose(fsrc);
    if (!initialized)
        return 2;

    // Test different sorting algorithms
    sort_testing("Insert Sort", insert_sort, &vector_orig);
    sort_testing("Select Sort", select_sort, &vector_orig);
    sort_testing("Bubble Sort", bubble_sort, &vector_orig);
    sort_testing("Bubble Sort Optimized", bubble_sort_optimized, &vector_orig);
    sort_testing("Bubble Sort Optimized2", bubble_sort_optimized2, &vector_orig);
    sort_testing("Shaker Sort", shaker_sort, &vector_orig);

    // Test sorting by different keys (hours, minutes, seconds)
    puts("\n------ Test stability of multiple sorts:");
    
    // First sort by seconds (stable sort)
    vector_element_set_comparator(EBySeconds);
    insert_sort(&vector_orig);
    
    // Then sort by minutes (maintains order of equal minutes)
    vector_element_set_comparator(EByMinutes);
    insert_sort(&vector_orig);
    
    // Finally sort by hours (maintains order of equal hours)
    vector_element_set_comparator(EByHours);
    insert_sort(&vector_orig);
    
    // Print result
    vector_for_each(vector_iterator_begin(&vector_orig), print_element);
    printf("\n");

    // Save sorted vector to file
    fsrc = fopen("sorted_ascend_data_time.txt", "w");
    if (!fsrc)
    {
        vector_destroy(&vector_orig);
        return 3;
    }

    if (!vector_store_file(&vector_orig, fsrc))
    {
        fclose(fsrc);
        vector_destroy(&vector_orig);
        return 4;
    }
    fclose(fsrc);
    
    // Sort in descending order
    vector_element_set_comparator(EDescending);
    insert_sort(&vector_orig);
    
    // Save descending sorted vector to file
    fsrc = fopen("sorted_descend_data_time.txt", "w");
    if (!vector_store_file(&vector_orig, fsrc))
    {
        fclose(fsrc);
        vector_destroy(&vector_orig);
        return 4;
    }
    
    // Cleanup
    fclose(fsrc);
    vector_destroy(&vector_orig);
    return 0;
}

/*************************************************************
 * TIME VECTOR SORTING EXAMPLE
 *************************************************************/

/**
 * Example of vector containing time values
 */
struct TTime
{
    unsigned iHours;
    unsigned iMinutes;
    unsigned iSeconds;
};

/**
 * Vector comparator function for time values
 */
void vector_element_comparator(struct TVector* tVector)
{
    // Sort times by hours in ascending order
    if (compare_by == EAscending)
    {
        if (sorting_by == EByHours)
        {
            for (int i = 1; i < tVector->iSize; i++)
            {
                unsigned temp_hours = tVector->iValues[i].iHours;
                unsigned temp_minutes = tVector->iValues[i].iMinutes;
                unsigned temp_seconds = tVector->iValues[i].iSeconds;

                int j = i - 1;

                while (j >= 0 && tVector->iValues[j].iHours > temp_hours)
                {
                    tVector->iValues[j + 1].iHours = tVector->iValues[j].iHours;
                    tVector->iValues[j + 1].iMinutes = tVector->iValues[j].iMinutes;
                    tVector->iValues[j + 1].iSeconds = tVector->iValues[j].iSeconds;
                    j--;
                }

                tVector->iValues[j + 1].iHours = temp_hours;
                tVector->iValues[j + 1].iMinutes = temp_minutes;
                tVector->iValues[j + 1].iSeconds = temp_seconds;
            }
        }
        // Additional cases for minutes and seconds
        else if (sorting_by == EByMinutes)
        {
            // Similar insertion sort by minutes
            // (implementation omitted for brevity)
        }
        else if (sorting_by == EBySeconds)
        {
            // Similar insertion sort by seconds
            // (implementation omitted for brevity)
        }
    }
    // Could also add descending order case
}

/**
 * Main function for time vector sorting
 */
int time_vector_main(void)
{
    struct TVector vector_orig = { 0 };
    FILE* vstupni = fopen("data_time_vstupni.txt", "rt");
    FILE* vystupni = fopen("data_time_vystupni.txt", "w");

    if (vstupni == NULL)
    {
        printf("Cannot open input file!");
        return 1;
    }

    if (vector_init_file(&vector_orig, vstupni) == false)
    {
        printf("Error in vector_init_file!");
        return 100;
    }

    printf("Data before sorting:\n\n");
    print(&vector_orig);
    printf("\n");

    // Sort by hours in ascending order
    vector_element_set_comparator(EAscending, EByHours);
    vector_element_comparator(&vector_orig);

    printf("Data after ascending sort:\n\n");
    print(&vector_orig);

    if (vystupni == NULL)
    {
        printf("Cannot open output file!");
        return 2;
    }

    if (vector_store_file(&vector_orig, vystupni) == false)
    {
        printf("Error in vector_store_file!");
        return 200;
    }

    // Cleanup
    fclose(vstupni);
    fclose(vystupni);
    vector_destroy(&vector_orig);
    return 0;
}