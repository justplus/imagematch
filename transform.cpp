//#include "stdafx.h"
#include "transform.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double * MatrixOpp(double A[],int m,int n) /*æÿ’Û«ÛƒÊ*/  
 {  
 int i,j,x,y,k;  
 double *SP=NULL,*AB=NULL,*B=NULL,X,*C;  
 SP=(double *)malloc(m*n*sizeof(double));  
 AB=(double *)malloc(m*n*sizeof(double));  
 B=(double *)malloc(m*n*sizeof(double));  
  
 X=Surplus(A,m,n);  
 X=1/X;  
  
 for(i=0;i<m;i++)  
 for(j=0;j<n;j++)  
 {for(k=0;k<m*n;k++)  
 B[k]=A[k];  
 {for(x=0;x<n;x++)  
 B[i*n+x]=0;  
 for(y=0;y<m;y++)  
 B[m*y+j]=0;  
 B[i*n+j]=1;  
 SP[i*n+j]=Surplus(B,m,n);  
 AB[i*n+j]=X*SP[i*n+j];  
 }  
 }  
 C=MatrixInver(AB,m,n);  
  
 return C;  
 }  
  
 double * MatrixInver(double A[],int m,int n) /*æÿ’Û◊™÷√*/  
 {  
 int i,j;  
 double *B=NULL;  
 B=(double *)malloc(m*n*sizeof(double));  
  
 for(i=0;i<n;i++)  
 for(j=0;j<m;j++)  
 B[i*m+j]=A[j*n+i];  
  
 return B;  
 }  
  
 double Surplus(double A[],int m,int n) /*«Ûæÿ’Û––¡– Ω*/  
 {  
  
 int i,j,k,p,r;  
 double X,temp=1,temp1=1,s=0,s1=0;  
  
 if(n==2)  
 {for(i=0;i<m;i++)  
 for(j=0;j<n;j++)  
 if((i+j)%2) temp1*=A[i*n+j];  
 else temp*=A[i*n+j];  
 X=temp-temp1;}  
 else{  
 for(k=0;k<n;k++)  
 {for(i=0,j=k;i<m,j<n;i++,j++)  
 temp*=A[i*n+j];  
 if(m-i)  
 {for(p=m-i,r=m-1;p>0;p--,r--)  
 temp*=A[r*n+p-1];}  
 s+=temp;  
 temp=1;  
 }  
  
 for(k=n-1;k>=0;k--)  
 {for(i=0,j=k;i<m,j>=0;i++,j--)  
 temp1*=A[i*n+j];  
 if(m-i)  
 {for(p=m-1,r=i;r<m;p--,r++)  
 temp1*=A[r*n+p];}  
 s1+=temp1;  
 temp1=1;  
 }  
  
 X=s-s1;}  
 return X;  
 }  
 
//  æÿ’Ûœ‡≥À
//   A  *  B  = C
//  l*m   m*n  l*n
double *chengji(double A[],double B[],int m,int n,int k)
 {
	double *C=NULL;
	C=(double *)malloc(m*k*sizeof(double));
	 int i,j,l;
	 for(i=0;i<m;i++)
	 {
		 for(j=0;j<k;j++)
		 {
			 C[i*k+j]=0;
			 for(l=0;l<n;l++)
			 {
				 C[i*k+j]+=A[i*n+l]*B[l*k+j];
				
			 }
		}
	 }
	  return C;
 }


//æÿ’Û◊™÷√
 double * zhuanzhi(double A[],int m,int n) /*æÿ’Û◊™÷√*/  
 {  
 int i,j;  
 double *B=NULL;  
 B=(double *)malloc(m*n*sizeof(double));  
  
 for(i=0;i<n;i++)  
 for(j=0;j<m;j++)  
 B[i*m+j]=A[j*n+i];  
  
 return B;  
 }  

///////////////////////////////////////////////////////////////////////////////
//æÿ’Ûº∆À„

/************************************************************************
* matrix and/or vector multiplication	AB[m,n] = A[m,l] * B[l,n]									*
************************************************************************/
 /*
void matMultiply(double *A, double *B, double *AB, int m, int l, int n)
{
	int	i, j, k;
	
	memset( AB, 0, m*n*sizeof(double) );
	
	for (i = 0; i < m; i++) 
	{
		for (j = 0; j < n; j++) 
		{
			for (k = 0; k < l; k++) 
				*AB += A[i*l + k] * B[k*n + j];
			AB++;
		}
	}
	
}
*/

/************************************************************************
* matrix transpose	AT[n,m] = transpose(A[m,n])			*
*									*
* return -1 or -2 when error.						*
*									*
************************************************************************/

int matTranspose(double *A, double *AT, int m, int n)
{
	int i, j;
	
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			AT[j*m + i] = A[i*n + j];
	}
	
	return (0);
}

/************************************************************************
* inversion of symmetric matrix A[n, n]						
************************************************************************/
void matInverse_symm(double *A, int n)
{
	int i, j, k;
	
	double s, p;
	
	for (i = 0; i < n; i++) {
		s = A[i*n+i];
		
		for (k = 0; k < i; k++)
			s -= A[i*n+k] * A[i*n+k];
		
		p = sqrt(fabs(s)) / s;
		
		for (j = 0; j < n; j++) {
			s = A[j*n+i];
			
			if (j < i) s = 0.0;
			
			for (k = 0; k < i; k++) {
				if (j < i && k < j) A[j*n+k] = 0;
				else s -= A[j*n+k] * A[i*n+k];
			}
			
			A[j*n+i] = s * p;
			
			if (j == i) A[i*n+j] = p;
		}
	}
	
	for (i = 0; i < n; i++) {
		for (j = i; j < n; j++) {
			s = 0.0;
			for (k = j; k < n; k++)
				s += A[i*n+k] * A[j*n+k];
			
			A[i*n+j] = s;
			A[j*n+i] = s;
		}
	}
}



