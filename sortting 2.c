#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct node
{
    int data;
    struct node *next;
};
void random(struct node **, int, int, int);
void sort(struct node **, int);
int main()
{
    struct node *head = NULL;
    int l, h, n, i;
    char t;
    printf("enter range L-H and size\n");
    scanf("%d%d%d", &l, &h, &n);
    random(&head, l, h, n);
    sort(&head, n);
}
void random(struct node **head, int l, int h, int n)
{

    int i, r;
    FILE *fp;
    fp = fopen("input.txt", "w");
    for (i = 0; i < n; i++)
    {
        struct node *p;
        p = (struct node *)malloc(sizeof(struct node));
        p->data = rand() % (h - l) + l;
        p->next = *head;
        *head = p;
        fprintf(fp, "%d\t", p->data);
    }
    fclose(fp);
}

void sort(struct node **head, int n)
{
    struct node *top;
    struct node *bot;
    top = *head;
    clock_t start, stop;
    int i, j, x, min, test;
    char t;
    printf("sort method m,b,s,a(all)");
    scanf("%*c%c", &t);
    printf("enter no to be sorted");
    scanf("%d", &x);
    FILE *fp;
    FILE *tp;
    fp = fopen("output.txt", "w");
    tp = fopen("log.txt", "w");

    if (t == 's' || t == 'a')
    {
        start = clock();
        for (i = 0; i < x; i++)
        {
            min = top->data;
            bot = top;

            for (j = i; j < n; j++)
            {

                if (min > (bot->data))
                {
                    min = bot->data;
                    bot->data = top->data;
                    top->data = min;
                }
                bot = bot->next;
            }
            fprintf(fp, "%d\t", min);
            top = top->next;
        }
        fprintf(fp, "\n");
        stop = clock();
        float time_r = (float)(stop - start) / CLOCKS_PER_SEC;
        fprintf(tp, "selection  %d   %f sec\n", x, time_r);
    }

}
