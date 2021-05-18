#include "rQuickSort.h"

void swap(u32 *a, u32 *b)
{
    u32 t = *a;
    *a = *b;
    *b = t;
}

u32 partition(u32 array[], u32 b[], int low, int high)
{

    int pivotIndex = rand() % (high - low + 1) + low;
    u32 pivot = array[pivotIndex];

    int i = (low - 1);

    swap(&array[pivotIndex], &array[high]);
    swap(&b[pivotIndex], &b[high]);
    pivotIndex = high;
    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {

            i++;

            swap(&array[i], &array[j]);
            swap(&b[i], &b[j]);
        }
    }

    swap(&array[i + 1], &array[pivotIndex]);
    swap(&b[i + 1], &b[pivotIndex]);
    return (i + 1);
}

void quickSort(u32 array[], u32 b[], int low, int high)
{
    if (low < high)
    {
        u32 pi = partition(array, b, low, high);
        quickSort(array, b, low, pi - 1);
        quickSort(array, b, pi + 1, high);
    }
}