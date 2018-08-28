#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


double twoDecs(double n)
{
    return (int)(n*100)/100.0;
}

char* Prob538(double target, int n)
{
    int i, j, closesti = 1, closestj = 1, iter = 0;
    double closest = 1;
    target/=100;        // to put in range 0 to 1

    //printf("\n%lf", target);

    for(i=1;i<=n;i++)
    {
        for(j=1;j<i;j++)
        {
            printf("\n %d/%d", j, i);

            if(i==1&&j==1)
                printf("WEIRD!");       //why isn't this triggering/isn't 1/1 being printed above?9


            if((fmod((double)i/j, 1)!=0 || j==1 )&&fabs(target - (double)j/i) < fabs(target - closest))
            {                                  //first condition to avoid checking (and changing answer to) redundant fractions like 2/4, 3/9
                printf("(New closest)");       //second condition to make sure first condition doesn't wrongly rule out fractions with 1 as
                                               //their numerator, such as 1/2, 1/3, etc.
                closestj = j;
                closesti = i;                   //still not perfect - 79.47% results in 8 in 10 instead of 4 in 5
                closest = (double)j/i;          //TODO: create/look for highest common factor function?
            }                                   //only catches cases where i is a whole number multiple of j

            iter++;
        }
    }

    int origJ = closestj, origI = closesti;
    printf("\nOriginal version took %d iterations  (%d in %d odds) \n", iter, closestj, closesti);

    iter=0, closest=1, j=1; //reset so that original algorithm's changes don't affect results

    bool tooLow;      //tooLow referring to the *current* value being lower than the target one
    double diff;

    for(i=1;i<=n;i++)
    {
        printf("\nOuter loop: %d/%d", j, i);

        diff = target - (double)j/i;

        tooLow = diff > 0 ? true : false;

        if ((fmod((double)i/j, 1)!=0 || j==1 )&&fabs(diff) < fabs(target - closest))
        {
            printf(" \t(New closest)");

            closestj = j;
            closesti = i;
            closest = (double) j / i;
        }





        while(tooLow&&i<10)     //&&i<10 to prevent cases where it gives the final fraction out of a higher number as a result,
                                //such as 73.66% giving 8 in 11 instead of 3 in 4
        {
           j++;   //j++ here instead of end of a for loop because even when it already went over the target,
           i++;            // it would still increment, meaning it would always increment one too many times            Is Comment still relevant?

            printf("\nInner Loop: %d/%d", j, i);

            diff = target - (double)j/i;

            tooLow = diff > 0 ? true : false;

            if((fmod((double)i/j, 1)!=0 || j==1 )&&fabs(diff) < fabs(target - closest))
            {
                printf(" \t(New closest)");

                closestj = j;
                closesti = i;
                closest = (double)j/i;
            }

            iter++;
        }

        iter++;

    }

    printf("\nAlternative  version took %d iterations\n", iter);

    if (origI!=closesti || origJ != closestj)
    {
        printf("\nERROR\nERROR\nERROR\nERROR\nERROR\nERROR\nERROR");
    }


    //TODO: Add final feature of expressing fractions that need more precision than a denominator of 10 can offer
    //e.g. 6.58% , 97.51%, not by extending the denominator of 10 to 11, 12 so on, but by testing neater denominators
    //of multiples of certain numbers, such as of 5s or 10s, which would give probabilities of 1 in 15, and 1 in 40
    //for the two examples mentioned

    unsigned int buffersize = 13 ;
    char* buffer = malloc(buffersize);

     snprintf(buffer, buffersize, "%d in %d odds", closestj, closesti);
     //printf("\n%d in %d odds", closestj, closesti);

    return buffer;
}

int main(void)
{
    srand((unsigned int)time(NULL));

    while(getchar())        //as opposed to running the whole program multiple times because then it wasn't random enough
    {
        int num = rand();

        printf("\nTime = %d", (unsigned int)time(NULL));
        printf("\nRand Num: %d", num);

        double newNum = (double) (num % 10000) / 100;       //to put in form xx.yy  e.g. 73.56%
        printf("\n%.2lf%%", newNum);

        printf("\n%s \n", Prob538(newNum, 10));
    }
    return 0;
}