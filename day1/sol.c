#include <stdio.h>
#include <stdlib.h>


int main(void) {

    // open file for reading
    FILE * fp = fopen("test.txt", "r");
    if (fp == NULL){
        printf("Failed to open file.");
        return 1;
    }
    printf("Creating lists...\n");
    // create three lists (dis1, dis2, diff)
    int dis1[512];
    int dis2[512];
    int diff[512];
    // populate
    char line[32];
    while (fgets(line, sizeof(line), fp) != NULL){
        // printf("Line: %s", line);
        int count = 0;
        int var1, var2;
        sscanf(line, "%d %d", &var1, &var2);
        // printf("Values: %d, %d\n",var1, var2);
        // dis1[count] = atoi(var1);
        // dis2[count] = atoi(var2);

        count += 1;

    }
    for(int i = 0; i < sizeof(dis1); i++){
        printf("%d", dis1[i]);
    }
    // algorithm + populate diff...

    // sum

    // return and print sum

    return 0;
}