#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

double random_step()
{	
	double r=1;
	//while(r==1)
	r = rand() / ((double) RAND_MAX);
	//return  -1*log(1-r);
	double A=1/9.9;
	return -1/(r/A+10); 

}
double random_trend()
{	
	return rand() / ((double) RAND_MAX);	
}
void trend(int n,double x, double y)
{
	int i;
	double R;
	FILE *fp;
	fp = fopen("trend.txt", "w");		
		for ( i = 0; i < n; i++)
		{
			fprintf(fp,"%lf	%lf\n",x,y);
			double step=random_step();
			double trend=random_trend();
				if(trend <0.25)
				{
					x+=step;
				}
				else
				{
					if((trend>0.24)&&(trend<0.5))
					{
						x-=step;
					}
					else
					{
						if((trend>0.49)&&(trend<0.75))
						{
							y+=step;
						}
						else
						{
							y-=step;
						}
					}
				}			
		}
	fclose(fp);
}
double maximum(double *mas,int n)
{
	int i;
	double max=mas[0];
	for ( i = 1; i < n; i++)
	{
		if(max<mas[i]) max=mas[i];
	}
	return max;
}
void trend_M(int n,int M,double x, double y,double *mas)
{
	int i,j;
	double R;
	FILE *fp;	
	for (i = 0; i < M; i++)
	{	x=0,y=0;
		for ( j = 0; j < n; j++)
		{			
			double step=random_step();
			double trend=random_trend();
				if(trend <0.25)
				{
					x+=step;
				}
				else
				{
					if((trend>0.24)&&(trend<0.5))
					{
						x-=step;
					}
					else
					{
						if((trend>0.49)&&(trend<0.75))
						{
							y+=step;
						}
						else
						{
							y-=step;
						}
					}
				}			
		}
		R=sqrt(x*x+y*y);
		mas[i]=R;
	}
	double max=maximum(mas,M);
	double h=max/20;
	int kol;
	fp = fopen("trend_M.txt", "w");
	for ( i = 0; i < 20; i++)
	{
		kol=0;
		for (int j = 0; j < M; j++)
		{
			if((mas[j]>=i*h)&&(mas[j]<(i+1)*h+1))
				kol+=1;
		}
		fprintf(fp,"%lf	%lf\n",(i+0.5)*h,(double)kol/(double)M);
	}
	fclose(fp);
}

int main()
{
	double x0 = 0 , y0 = 0;
	int N=100,M=30000;
	double *R;
	R = (double *)malloc(M * sizeof(double)); 

	trend(N,x0,y0);
	trend_M(N,M,x0,y0,R);
	
	return 0;
}