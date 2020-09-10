#include "stats_lib.h";
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float maximum(float nums[], int n)
{
    float rtn = nums[0];
    for(int i = 1; i<n; i++){//go through all elements and set the highest equal to rtn
        if(nums[i]>rtn){
            rtn = nums[i];
        }
    }
    return rtn;
}


float minimum (float nums[], int n)
{
    float rtn = nums[0];
    for(int i = 1; i<n; i++){//go through all elements and set the lowest equal to rtn
        if(nums[i]<rtn){
            rtn = nums[i];
        }
    }
    return rtn;
}


float mean(float nums[], int n)
{
    float rtn = 0;
    for(int i = 0; i<n; i++){//sum all elements
        rtn += nums[i];
    }
    rtn = rtn/n;//divide by n
    return rtn;
}

float median(float nums[], int n)
{
    float temp;
    float rtn;
    int high;
    int low;
    for(int i=0; i<n; i++){//sort all elements
        for(int j=0; j<n-i-1; j++){
            if(nums[j]>nums[j+1]){
                temp = nums[j];
                nums[j]=nums[j+1];
                nums[j+1]=temp;
            }
        }
    }
    if(n%2==0){//conditions for when n is even or odd
        rtn = (nums[(n-1)/2]+nums[n/2])/2.0;
    }else{
        rtn = nums[n/2];
    }
    return rtn;

}

float variance(float nums[], int n)
{
  float mean = 0;
  float rtn;
    for(int i = 0; i<n; i++){
        mean += nums[i];
    }
    mean = mean/n;

    for(int i=0;i<n;i++){
        rtn += pow((nums[i]-mean),2);
    }
    rtn = rtn/(n-1);
    return rtn;
}

float standard_deviation(float nums[], int n)
{
    float mean = 0;
  float rtn;
    for(int i = 0; i<n; i++){
        mean += nums[i];
    }
    mean = mean/n;

    for(int i=0;i<n;i++){
        rtn += pow((nums[i]-mean),2);
    }
    rtn = rtn/(n-1);
    return sqrt(rtn);
}
