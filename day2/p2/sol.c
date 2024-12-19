#include <stdio.h>
#include <stdlib.h>

int* remove_level(int *numbers, size_t *size, int index) {
    // Shift all elements after the index one position to the left
    for (int i = index; i < *size - 1; i++) {
        numbers[i] = numbers[i + 1];
    }

    // Resize the array to remove one element
    *size = *size - 1;
    numbers = realloc(numbers, (*size) * sizeof(int));
    if (numbers == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }

    return numbers;
}

// returns 1 if valid, 0 if not
int process_nums(int *numbers, size_t *size) {
    int which_way;
    int problems = 0;
    int i = 0; // Start from the beginning of the list

    while (i < *size - 1) { // Loop through the entire list
        int diff = numbers[i] - numbers[i + 1];

        // Determine if the sequence is increasing or decreasing
        if (i == 0) { // First pair of numbers
            if (numbers[0] < numbers[1]) {
                which_way = 1;  // increasing
            } else {
                which_way = 0;  // decreasing
            }
        }

        // Check if the sequence is still increasing or decreasing
        if (which_way == 1 && (numbers[i] > numbers[i + 1])) {
            problems++;
            // printf("Problem detected between %d and %d (increasing)\n", numbers[i], numbers[i + 1]);
            numbers = remove_level(numbers, size, i); // Remove the first of the two indices
            i = 0; // Reset index to 0 to recheck the entire list
            continue; // Recheck the list after removal
        }

        if (which_way == 0 && (numbers[i] < numbers[i + 1])) {
            problems++;
            // printf("Problem detected between %d and %d (decreasing)\n", numbers[i], numbers[i + 1]);
            numbers = remove_level(numbers, size, i); // Remove the first of the two indices
            i = 0; // Reset index to 0 to recheck the entire list
            continue; // Recheck the list after removal
        }

        // Check if the difference is too small or too large
        if (abs(diff) == 0 || abs(diff) > 3) {
            problems++;
            // printf("Problem with difference between %d and %d\n", numbers[i], numbers[i + 1]);
            numbers = remove_level(numbers, size, i); // Remove the first of the two indices
            i = 0; // Reset index to 0 to recheck the entire list
            continue; // Recheck the list after removal
        }

        // Move to the next pair of numbers
        i++;
    }

    // printf("problems: %d\n", problems);
    if (problems <= 1) {
        return 1;  // Valid
    } else {
        return 0;  // Invalid
    }
}

int main (void){

    /*
    1. read each line from file into a list (lots of lists...)
    
    2. enum through the list - if fail at any point, return 0, if true 1 (then add up trues in a counter!)
        2a. compare the first and second, second and third, and so on
        2b. so, 0 and 1, 1 and 2, 2 and 3
        2c. write a check func that does all important checks
            2c(a). if increasing, alwasy check that the rest are increasing
            2c(b). if decreasing, always check that the rest are decreasing
        2d. check the values are diff by at least 1 to 3
        

    3. ok cool 

    4. lets go!
    */

    // read into list, do checks, free and go again
    // open file for reading
    FILE * fp = fopen("test.txt", "r");
    if (fp == NULL){
        printf("Failed to open file.");
        return 1;
    }

    int *numbers = NULL;
    int valid = 0;
    char line[128];    
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        size_t count = 0;
        // list of numbers (NULL ptr/empty array)

        int num;
        char *ptr = line;

        while (sscanf(ptr, "%d", &num) == 1)
        {
            numbers = realloc(numbers, (count + 1) * sizeof(int));
            if (numbers == NULL){
                printf("realloc falied... or no number to add...");
                return 1;
            }

            numbers[count] = num;
            count++;

            while (*ptr && *ptr != ' ') ptr++;
            if (*ptr) ptr++;

        }
        // printf("number of ints: %d\n", count);
        // print arry just to see
        // for (int i = 0; i < count; i++){
        //     printf("%d ", numbers[i]);
        // }
        // do stuff with numbers list

        // pass ref to numbers list and size (count) to process nums
        valid += process_nums(numbers, &count);
        // printf("\n");
    }

    // free stuff!
    printf("valid: %d", valid);
    free(numbers);
    return 0;
}