#include <stdio.h>
#include <stdlib.h>
#include "stats_lib.h";
#include "stats_lib.c";

float maximum(float nums[], int n);

int main()
{
    FILE *fp;
   float nums[1000];
   float data;
   int i = 0;
   int size = 0;
   float print;

   fp = fopen("Lab1data.txt", "r");//opens the text document in read mode
   int rv = fscanf(fp, "%f", &data);//scan document element

   while (!feof(fp) && i < 1000){//loops through to scan all parts of the document into the array
        nums[i++] = data;
        rv = fscanf(fp, "%f", &data);
        size++;
   }
        nums[i++] = data;//have to repeat the loop one more time as it misses the last element of the document
        rv = fscanf(fp, "%f", &data);
        size++;

   fclose(fp);//closes the text document

   print = maximum(nums, size);
   printf("1.\tMaximum: %.0f\n", print);

   print = minimum(nums, size);
   printf("2.\tMinimum: %.0f\n", print);

   print = mean(nums, size);
   printf("3.\tMean: %.2f\n", print);

   print = median(nums, size);
   printf("4.\tMedian: %.2f\n", print);

   print = variance(nums, size);
   printf("5.\tVariance: %.2f\n", print);

   print = standard_deviation(nums, size);
   printf("6.\tStandard Deviation: %.2f", print);

    return 0;
}
