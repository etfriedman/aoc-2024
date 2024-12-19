#include <stdio.h>
#include <stdlib.h>

// returns 1 if valid, 0 if not
int process_nums(int *numbers, size_t size) {
    int which_way;
    if (numbers[0] < numbers[1]) {
        which_way = 1;  // increasing
    } else {
        which_way = 0;  // decreasing
    }

    for (int i = 0, j = 1; i < size - 1 && j < size; i++, j++) {
        // printf("i, j: %d %d, values: %d, %d\n", i, j, numbers[i], numbers[j]);
        int diff = numbers[i] - numbers[j];

        // Check if the sequence is still increasing or decreasing
        if (which_way == 1 && (numbers[i] > numbers[j])) {
            return 0;  // should only increase
        } 
        if (which_way == 0 && (numbers[i] < numbers[j])) {
            return 0;  // should only decrease
        }
        if (abs(diff) == 0 || abs(diff) > 3) {
            return 0;  // difference should not be 0 or greater than 3
        }
    }
    // printf("good!\n");
    return 1;
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
    FILE * fp = fopen("list.txt", "r");
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
        valid += process_nums(numbers, count);
        // printf("\n");
    }

    // free stuff!
    printf("valid: %d", valid);
    free(numbers);
    return 0;
}