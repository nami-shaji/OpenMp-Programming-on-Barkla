//CODE FOR PARALLEL EXECUTION
#include<stdio.h> /* header files*/
#include<time.h>
#include<malloc.h>
#include<math.h>

/*For Openmp*/
#include<omp.h>

int main()
{
    int i,j,n=64;
    int limit=100,iter;


   //Initializing variables to use the clock
    clock_t starttime,endtime;
    double time_used;



    double (*temp)[n + 1][n + 1] = malloc( sizeof(double[2][n + 1][n + 1]));



    /* Initialization of the radiator and the rest of the values in a 3D array
		Printing the original values*/

     for(i=0;i<n+1;i++)
        {
            for(j=0;j<n+1;j++){
                    if(j==n && i>(n*0.3) && i<=(n*0.7))
                    {
                        /*Placing values for the area of the radiator*/
                        temp[0][i][j]=100;
                        temp[1][i][j]=100;
                    }
                    else
                    {
                        /*Placing values for the other areas*/
                        temp[0][i][j]=10;
                        temp[1][i][j]=10;
                    }
            }

        }


   /*Calculation of the start time*/
     starttime=clock();

    int flag=0;
    int currval,nextval;

    for(iter=0;iter<limit;iter++){


        /*Calculating values for the current as well as next values in order to calculate
          the temperature of the points next to the boundary lines*/
        currval=iter%2;
        nextval=(iter+1)%2;


        /*Assuming that steady state is achieved*/
        flag=0;

        #pragma omp parallel for schedule(dynamic) private(i,j)

        for(i=1;i<n;i++){

            for(j=1;j<n;j++){
                temp[currval][i][j]=0.25*(temp[nextval][i-1][j]+temp[nextval][i+1][j]+temp[nextval][i][j-1]+temp[nextval][i][j+1]);
            if(temp[currval][i][j]!=temp[nextval][i][j])
            {
                /*Disapproval of steady state condition*/
                flag=1;
            }

            }
        }
        if(flag==0)
            break;

    }
        /*Calculation of end time*/

        endtime=clock();

        printf("-----------------------------------------\n");
        int val=ceil(n/8);
        for(i=val;i<=n;i+=val){
            for(j=val;j<=n;j+=val){
                printf("%.2f\t",temp[currval][i][j]);
                }
                printf("\n");
        }

        printf("-----------------------------------------\n");
        printf("Number of iterations it went through: %d ",iter);


        time_used = endtime - starttime;
        printf("\n Time taken : %f ",time_used);
}
