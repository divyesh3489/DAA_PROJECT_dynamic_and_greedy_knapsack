#include <stdio.h>
int n,W;
void dynamic_knapsack();
void dynamic_print(int b[n+1][W+1], int w[]);
void greedy_knapsack();
void main()
{
    int ch;
    printf("------------------------\n");
    printf("|KNAPSACK PROBLEM USING|\n");
     printf("------------------------\n");
    printf("1--> DYNAMIC PROGRAMMING\n2-->GREEDY APPROACH\n\n\n");
    printf("ENTER YOUR CHOICE:");
    scanf("%d",&ch);
    switch(ch)
    { 
	case 1:
    dynamic_knapsack();
    break;
    case 2:
    greedy_knapsack();
    break;
	}
   
}
void dynamic_knapsack()
{
	int  i;
    printf("ENTER NUMBER OF OBJECT:");
    scanf("%d", &n);
    int w[n + 1], v[n + 1];
    for (i = 1; i <= n; i++)// get the value of wight and profit
    {
        printf("ENTER WEIGHT AND PROFIT OF OBJECT %d:", i);
        scanf("%d %d", &w[i], &v[i]);
    }
    printf("ENTER CAPACTIY OF KANPSACK:");
    scanf("%d", &W);
    int  j, b[n + 1][W + 1];

    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= W; j++)
        {
            if (i == 0 || j == 0) 
            {
                b[i][j] = 0;
            }
            else if (w[i] <= j)
            {
                if (v[i] + b[i - 1][j - w[i]] > b[i - 1][j])  // if the value of object wieght is equal to or  lass then  j then find the maximumprofit
                {
                    b[i][j] = v[i] + b[i - 1][j - w[i]];
                }
                else                                          //take value of b[i-1,j]
                {
                    b[i][j] = b[i - 1][j];
                }
            }
            else
            {
                b[i][j] = b[i - 1][j];
            }
        }
    }
    for (i = 0; i <= n; i++)          //display matrix 
    {
        for (j = 0; j <= W; j++)
        {
            printf("%d\t", b[i][j], i, j);
        }
        printf("\n");
    }
    printf("\n\n  -----------------\n");
    printf("  |TOTAL PROFIT:%d|\n", b[n][W]); //display total profit
     printf("  -----------------\n");
    dynamic_print(b,w);   //print the witch item selected
}
void dynamic_print( int b[n+1][W+1], int w[])
{
    int i = n, j = W, a[n + 1];

    while (i > 0 && j > 0)
    {
        
        if (b[i][j] != b[i - 1][j])       //witch object selected 
        {
            a[i]=1;                     
            j = j - w[i];
        }
        else
        {
             a[i] = 0;                   
        }

        i = i - 1;
    }
    printf("SELECTED OBJECT->\t");
    printf("(");
     for (i = 1; i<=n ; i++)       //printf selected object
   {
   	
          printf("%d",a[i]);
          if (i<n)
          {
            printf(",");
          }
          
   }  
   printf(")");
}
void greedy_knapsack()
{
    int  i;
    printf("ENTER NUMBER OF OBJECT:");
    scanf("%d", &n);
    int w[n + 1], v[n + 1];
    for (i = 1; i <= n; i++)
    {
        printf("ENTER WEIGHT AND VALUE OF %d:", i);
        scanf("%d %d", &w[i], &v[i]);
    }
    printf("ENTER CAPACTIY OF KANPSACK:");
    scanf("%d", &W);
	int j,temp1,temp2,temp3,temp4,index[n];
    float d[n];
    for ( i = 1; i <= n; i++)          // find the pi/wi
    {
        d[i]=((float) v[i]/w[i]);
        index[i]=i;                   //store the index of pi/wi 
    }
    for ( i = 1; i <=n; i++)         //sorted value,wieght,pi/wi,andindex array into descending order of pi/wi 
    {
        for ( j = 1; j<=n-i; j++)
        {
            if(d[j]<d[j+1])
            {
                temp1=d[j+1];
                d[j+1]=d[j];
                d[j]=temp1;

                temp2=v[j+1];
                v[j+1]=v[j];
                v[j]=temp2;

                temp3=w[j+1];
                w[j+1]=w[j];
                w[j]=temp3;

                temp4=index[j+1];
                index[j+1]=index[j];
                index[j]=temp4;
            }
        }    
    }
    printf("OBJECT\tWEIGHT\tVALUE\tV/W\n");   //display in descending order of pi/wi 
    for ( i = 1; i <=n; i++) 
    {
        printf("%d\t%d\t%d\t%f\n",index[i],w[i],v[i],d[i]);
    }
   float tp=0,rw=W;
    int temp[n],t2,t3;
    for(i=1;i<=n;i++)    //for witch item has been seleted
    {
    	
    	if(rw>0)         
    	{
		
        if (rw>=w[i])           //remaining weight is more then object weight then take the object and find the  profit
        {
            tp=tp+v[i];
            rw=rw-w[i];
            temp[index[i]]=1;
            
        }
        else if (w[i]>rw)       ////remaining weight is lass then object weight then take the object into parts and find the  profit
        {
            tp=tp+(v[i]*(rw/w[i]));
            t2=rw;
            t3=w[i];
			rw=rw-(rw/w[i])*w[i];
        }
	}
    }
     printf("\n\n  ------------------\n");
	printf(" |PROFIT-->%f|\n",tp);
	 printf("  ------------------\n");
   printf("\nSELECTED OBJECTS-->");
    printf("(");
	for ( i = 1; i <=n ; i++)   //display witch item has been selected
    {
    	if(i<n)
    	{
		
    	if(temp[i]==1)
        printf("%d,",temp[i]);
        
        else if (temp[i]==0)
        {
        	printf("%d,",temp[i]);
		}
		else
		printf("(%d/%d),",t2,t3);
	    }
	    else
	    {
		
	    if(temp[i]==1)
        printf("%d",temp[i]);
        
        else if (temp[i]==0)
        {
        	printf("%d",temp[i]);
		}
		else
		printf("(%d/%d)",t2,t3);
	    }
    }    
    printf(")");
}
