//CODE FOR SERIAL EXECUTION

#include<stdio.h> // header files
#include<time.h>
#include<malloc.h>


int main()
{
    int i,j,n;
    int limit,iter;

    //Initializing variables to use the clock
    clock_t starttime,endtime;
    double time_used;
    starttime=clock();

    printf("Enter the length of the box : ");
    scanf("%d",&n);
    printf("%d \n",n);
    double (*tempval)[n+1][n+1]=malloc(sizeof(double[2][n+1][n+1]));

    printf("Enter the limit for the number of iterations : ");
    scanf("%d",&limit);
    printf("%d \n",limit);


    // Initialization of the radiator and the rest of the values in a 3D array
    // Printing the original values
    for(i=0;i<n+1;i++)
        {
            for(j=0;j<n+1;j++){
                    if(j==n && i>(n*0.3) && i<=(n*0.7))
                    {
                        //Placing values for the area of the radiator
                        tempval[0][i][j]=100;
                        tempval[1][i][j]=100;
                    }
                    else
                    {
                        //Placing values for the other areas
                        tempval[0][i][j]=10;
                        tempval[1][i][j]=10;
                    }

                  printf("%.2f ",tempval[1][i][j]);
            }
            printf("\n");
        }
    system("pause");

    int flag,currval,nextval;

    for(iter=0;iter<limit;iter++){
        //Calculating values for the current as well as next values in order to calculate
        //the temperature of the points next to the boundary lines

        currval=iter%2;
        nextval=(iter+1)%2;

        for(i=1;i<n;i++){

            for(j=1;j<n;j++){
                tempval[currval][i][j]=0.25*(tempval[nextval][i-1][j]+tempval[nextval][i+1][j]+tempval[nextval][i][j-1]+tempval[nextval][i][j+1]);
            if(tempval[currval][i][j]!=tempval[nextval][i][j])
            {
                flag=1;
            }
            }
            if(flag==0)
                break;
        }
         //After calculation, the printing process of the same.
        printf("-----------------------------------------\n");
        for(i=0;i<n+1;i++){
            for(j=0;j<n+1;j++){
                printf("%.2f\t",tempval[currval][i][j]);
            }
            printf("\n");
        }

        printf("-----------------------------------------\n");


    }


    endtime=clock();

    //Time for execution
    printf("Number of Iterations %d",iter);
    time_used=(((double)endtime-starttime)/CLOCKS_PER_SEC);
    printf("\n Time taken : %f",time_used);


}
