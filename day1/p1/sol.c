#include <stdio.h>
#include <stdlib.h>


int* remove_smallest(int *arr, size_t *size, int min_index){
	size_t new_size = *size - 1; 
	size_t write_index = 0;

	// copy all elements except the smallest to the new array
	for(size_t i = 0; i < *size; i++){
		// if not min index (smallest num), include it
		if(i != min_index){
			arr[write_index] = arr[i];
			write_index++;
		}
	}

	// int new_arr_len = write_index;
	// realloc array... does this work..??
	// must
	// int *new_arr = NULL;  
    // printf("old_size: %d new_size: %d\n", *ssize, new_size);
    if (new_size == 0){
        arr == NULL;
    } else {
	    arr = realloc(arr, new_size * sizeof(int));
	    // if (arr == NULL && sizeof(arr) != 0){
		//     printf("Finished.");
	    // }
    }

	*size = new_size;

	return arr;
}

int find_smallest(int *arr, size_t *size){
	// assume first is smallest
	int min = arr[0];
	int min_index = 0;
	for (size_t i = 0; i < *size; i++){
		if(arr[i] < min){
			min = arr[i];
			min_index = i;
		}
	}
	arr = remove_smallest(arr, size, min_index);

	return min;
}


int main(void) {

    // open file for reading
    FILE * fp = fopen("list.txt", "r");
    if (fp == NULL){
        printf("Failed to open file.");
        return 1;
    }
    // printf("Creating lists...\n");
    // create three lists (dis1, dis2, diff)
    // int dis1[1] = {0};
    // int dis2[1] = {0};
    // int diff[1] = {0};
    // alloc int arrays, starting at 1
    size_t size = 0;
    int *dis1 = NULL; 
    int *dis2 = NULL; 
    int *diff = NULL;
    // dis1 = (int*)calloc(size, sizeof(int));
    // dis2 = (int*)calloc(size, sizeof(int));
    // diff = (int*)calloc(size, sizeof(int));

    // populate
    char line[32];
	int count = 0;
    // counter / size needed for array, realloc to count before adding elements
    while (fgets(line, sizeof(line), fp) != NULL){
        // printf("Line: %s", line);
    	
        int var1, var2;
        sscanf(line, "%d %d", &var1, &var2);
        // printf("Values: %d, %d\n",var1, var2);
        // realloc array to add new elements
        size++;
        dis1 = realloc(dis1, size * sizeof(int));
        dis2 = realloc(dis2, size * sizeof(int));
        diff = realloc(diff, size * sizeof(int));

        dis1[count] = var1;
        dis2[count] = var2;

        // printf("List1 value %d: %d\n", count, dis1[count]);
        // printf("List2 value %d: %d\n", count, dis2[count]);
    	count++;
    }
    // algorithm + populate diff...
    // int smallest_dif1 = find_smallest(dis1, size);
    // printf("Smallest: %d", smallest_dif1);

    size_t arr1_size = size;
    size_t arr2_size = size;


    for (int i = 0; i < size; i++){
    	// get two smallesta
    	// set new arr size to update when changing arrays
    	// goes until... arrays are empty?

        if (arr1_size == 0){
            printf("Finished findings diffs...");
            break;
        } else {

    
    	int dis1_smallest = find_smallest(dis1, &arr1_size);
    	int dis2_smallest = find_smallest(dis2, &arr2_size);
    	// printf("two smallest: %d and %d", dis1_smallest, dis2_smallest);
    	int difference = dis1_smallest - dis2_smallest;
    	difference = abs(difference);
    	// printf("diff = %d\n", difference);
    	diff[i] = difference;
    	// diff[i] =
        } 
    }

    int sum = 0;
    for (int i = 0; i < size; i++){
    	sum += diff[i];
    }


    // printf("%d", sizeof(dis1));
    // for(int i = 0; i<size;i++){
    // 	printf("dis1: %d, dis2: %d\n", dis1[i], dis2[i]);
    // }
    // sum

    // return and print sum

    printf("sum of diff:\n %d", sum);
    free(dis1);
    free(dis2);
    free(diff);
    return 0;
}