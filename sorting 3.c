#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void bubblesort(int n,int a[20]);
void insertionsort(int n,int a[20]);
void selectionsort(int n,int a[20]);
int main()
{
    FILE *fp1;
   // FILE *fp3;
   clock_t start,end;
   int n,a[20];
   int m;
   int k;
   int ch;
   float time;
   printf("enter the size of the array\n");
    scanf("%d",&n);
    printf("enter the elements in the array\n");
    int i;
    int f,l;
    printf("enter the higher and lower limit\n");
    scanf("%d%d",&f,&l);
    fp1=fopen("input.txt","w");
    //fp3=fopen("time.txt","w");
    for(i=0;i<n;i++)
    {
        a[i]=rand()%(l+f-1);
        fprintf(fp1,"%d ",a[i]);
        printf("%d ",a[i]);
    }
    while(1)
    {
        printf("menu\n");
        printf("bubblesort\n");
        printf("insertion sort\n");
        printf("selection sort\n");
        printf("enter your choice\n");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
            start=clock();
            bubblesort(n,a);
            end=clock();
            break;
            case 2:
            start=clock();
            insertionsort(n,a);
            end=clock();
            break;
            case 3:
            start=clock();
            selectionsort(n,a);
            end=clock();
            break;
            default:exit(0);
            break;
        }
        time=((float)(end-start))/CLOCKS_PER_SEC;
        printf("execution time %f\n",time);
    }
    fclose(fp1);
   // bubblesort(n,a);
    //insertionsort(n,a);
    //selectionsort(n,a);
    return 0;
}
void bubblesort(int n,int a[20])
{
    FILE *fp2;
    fp2=fopen("output.txt","w");
    int i,j,temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(a[j+1]<a[j])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    printf("sorted array\n");
    for(i=0;i<n;i++)
    {
        printf("%d ",a[i]);
        fprintf(fp2," %d ",a[i]);
    }
    fclose(fp2);
}
void insertionsort(int n,int a[20])
{
    FILE *fp2;
    int i,j,temp;
    fp2=fopen("output.txt","w");
    for(i=0;i<n;i++)
    {
        temp=a[i];
        for(j=i-1;j>=0&&a[j]>temp;j--)
             a[j+1]=a[j];
            a[j+1]=temp;

    }
    printf("sorted array\n");
    for(i=0;i<n;i++)
    {
        printf("%d ",a[i]);
        fprintf(fp2,"%d ",a[i]);
    }
    fclose(fp2);
}
void selectionsort(int n,int a[20])
{
    FILE *fp2;
    int i,j,temp;
    fp2=fopen("output.txt","w");
    for(i=0;i<n-1;i++)
    {
        int min=i;
        for(j=i+1;j<n;j++)
        {
            if(a[j]<a[min])
            min=j;
        }
        if(min!=i)
        {
            temp=a[i];
            a[i]=a[min];
            a[min]=temp;
        }
    }
    printf("sorted array\n");
    for(i=0;i<n;i++)
    {
        printf("%d ",a[i]);
        fprintf(fp2,"selection sort\n%d ",a[i]);
    }
    fclose(fp2);
}
