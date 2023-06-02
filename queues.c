#include<stdio.h>
#include<stdlib.h>
#include<time.h>

 struct node
 {
   int data;
   struct node*next;
 };
 struct node*front=NULL;
 struct node*rear=NULL;
 void enQueue(FILE*fp,int t);
 void deQueue(FILE*fp);
 void random(int l,int h,int n);
int main()
{
   int l=5,h=80,n=7,t;
   random(l,h,n);
   int i,e=4,d=4;

   FILE*fp1=fopen("Queues.txt","r");
   FILE*fp2=fopen("log_enqueue.txt","w");
   FILE*fp3=fopen("log_dequeue.txt","w");
   clock_t start,stop;
   float time_r;
   start=clock();

   for(i=0;i<e;i++)
   {

       fscanf(fp1,"%d",&t);

       enQueue(fp2,t);

   }
   fclose(fp1);
   stop=clock();
   time_r=(float)(stop-start)/CLOCKS_PER_SEC;
   fprintf(fp2,"No. of operations for enQueue operations = %d\n Time taken for the enQueue operations = %f\n",e,time_r);
   start=clock();
   for(i=0;i<d;i++)
   {
       deQueue(fp3);
   }
   stop=clock();
   time_r=(float)(stop-start)/CLOCKS_PER_SEC;
   fprintf(fp3,"No. of operations for deQueue operations = %d\n Time taken for the deQueue operations = %f\n",d,time_r);

   fclose(fp2);
   fclose(fp3);
   return 0;
}
void random(int l,int h,int n)
{
    int i,r;
    FILE*fp=fopen("Queues.txt","w");
    for(i=0;i<n;i++)
    {
        r=rand()%(h-l)+l;
        fprintf(fp,"%d     ",r);
    }
    fclose(fp);
}
void enQueue(FILE*fp,int t)
{
    struct node*p=(struct node*)malloc(sizeof(struct node));
    p->data=t;
    p->next=NULL;
    if(front==NULL&&rear==NULL)
        front=rear=p;
    else
    {
        rear->next=p;
        rear=p;
    }
    fprintf(fp,"Enqueue %d\n",rear->data);
}
void deQueue(FILE*fp)
{
    if (front == NULL&&rear==NULL)
        {
        fprintf(fp,"\nUnderflow\n");

    }
    else
        {
        struct node * temp = front;
        int temp_data = front -> data;
        front = front ->next;
        free(temp);

        fprintf(fp,"Dequeue     %d\n",temp_data);
    }
}
