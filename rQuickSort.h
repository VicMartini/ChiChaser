#include <stdint.h>
typedef uint32_t u32;

void swap(u32 *a, u32 *b);
u32 partition(u32 array[], u32 b[], int low, int high);
void quickSort(u32 array[], u32 b[], int low, int high);
