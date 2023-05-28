#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int n, i, j, temp;
  clock_t start, end;
  double cpu_time_used;

  printf("Enter the number of elements to be sorted: ");
  scanf("%d", &n);

  int arr[n];


  srand(time(NULL));


  printf("Generating %d random numbers...\n", n);
  for (i = 0; i < n; i++) {
    arr[i] = rand() % 100 + 1;
  }


  start = clock();


  for (i = 0; i < n-1; i++) {
    for (j = 0; j < n-i-1; j++) {
      if (arr[j] > arr[j+1]) {
        temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }


  end = clock();


  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;


  printf("Sorted array:\n");
  for (i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }


  FILE *fp;
  fp = fopen("sorted.txt", "w");

  if (fp == NULL) {
    printf("Unable to create file.\n");
    return 1;
  }

  fprintf(fp, "Sorted array:\n");
  for (i = 0; i < n; i++) {
    fprintf(fp, "%d ", arr[i]);
  }

  fprintf(fp, "\nTime taken to sort: %f seconds", cpu_time_used);

  fclose(fp);

  return 0;
}
