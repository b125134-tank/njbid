#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_K 100

/*
    Merge two sorted arrays.

    a = first array
    b = second array
    n1 = size of first array
    n2 = size of second array
    result = merged array
*/
void mergeTwoArrays(int a[], int n1, int b[], int n2, int result[])
{
    int i = 0, j = 0, k = 0;

    while(i < n1 && j < n2)
    {
        if(a[i] <= b[j])
        {
            result[k++] = a[i++];
        }
        else
        {
            result[k++] = b[j++];
        }
    }

    while(i < n1)
    {
        result[k++] = a[i++];
    }

    while(j < n2)
    {
        result[k++] = b[j++];
    }
}


/*
    METHOD 1

    Merge first two arrays.
    Then merge the result with third array.
    Continue until all k arrays are merged.
*/
void method1(int **arrays, int k, int n)
{
    int currentSize = n;

    int *result = (int *)malloc(sizeof(int) * n * k);

    /* Copy first array */
    for(int i = 0; i < n; i++)
    {
        result[i] = arrays[0][i];
    }

    for(int i = 1; i < k; i++)
    {
        int newSize = currentSize + n;

        int *temp = (int *)malloc(sizeof(int) * newSize);

        mergeTwoArrays(
            result,
            currentSize,
            arrays[i],
            n,
            temp
        );

        free(result);

        result = temp;
        currentSize = newSize;
    }

    free(result);
}


/*
    METHOD 2

    Merge arrays pairwise.

    Round 1:
        A1 + A2
        A3 + A4
        ...

    Round 2:
        result1 + result2
        result3 + result4
        ...

    Continue until only one array remains.
*/
void method2(int **arrays, int k, int n)
{
    int currentK = k;
    int **current = arrays;

    while(currentK > 1)
    {
        int newK = (currentK + 1) / 2;

        int **next =
            (int **)malloc(sizeof(int *) * newK);

        int index = 0;

        for(int i = 0; i < currentK; i += 2)
        {
            if(i + 1 < currentK)
            {
                int *merged =
                    (int *)malloc(sizeof(int) * n * 2);

                mergeTwoArrays(
                    current[i],
                    n,
                    current[i + 1],
                    n,
                    merged
                );

                next[index++] = merged;
            }
            else
            {
                /*
                    If k is odd, copy the remaining array.
                */

                int *remaining =
                    (int *)malloc(sizeof(int) * n);

                for(int j = 0; j < n; j++)
                {
                    remaining[j] = current[i][j];
                }

                next[index++] = remaining;
            }
        }

        /*
            Free intermediate arrays.
        */

        if(current != arrays)
        {
            for(int i = 0; i < currentK; i++)
            {
                free(current[i]);
            }

            free(current);
        }

        current = next;
        currentK = newK;
    }

    /*
        Free final result.
    */

    if(current != arrays)
    {
        free(current[0]);
        free(current);
    }
}


int main()
{
    FILE *fp;

    fp = fopen("q3_merge.txt", "w");

    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    fprintf(fp,
        "# k Method1_O(nk^2) Method2_O(nklogk)\n");


    /*
        Use n = 10 as the size of every array.

        We vary k and record the theoretical
        growth of both methods.
    */

    int n = 10;

    for(int k = 2; k <= MAX_K; k++)
    {
        /*
            Method 1:

            n(2 + 3 + ... + k)

            = O(nk^2)
        */

        double method1Growth =
            n * (double)k * (k + 1) / 2.0;


        /*
            Method 2:

            There are log2(k) merging levels.

            Each level processes kn elements.

            Therefore:

            O(nklog2(k))
        */

        double method2Growth =
            n * k * log2(k);


        fprintf(fp,
            "%d %.4lf %.4lf\n",
            k,
            method1Growth,
            method2Growth);
    }

    fclose(fp);


    /*
        Create sample sorted arrays and
        execute both methods once.
    */

    int k = 4;

    int **arrays =
        (int **)malloc(sizeof(int *) * k);

    for(int i = 0; i < k; i++)
    {
        arrays[i] =
            (int *)malloc(sizeof(int) * n);

        for(int j = 0; j < n; j++)
        {
            arrays[i][j] =
                i * n + j;
        }
    }


    method1(arrays, k, n);
    method2(arrays, k, n);


    for(int i = 0; i < k; i++)
    {
        free(arrays[i]);
    }

    free(arrays);

    printf("q3_merge.txt created successfully.\n");

    return 0;
}