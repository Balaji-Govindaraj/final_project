#include "mex.h"
#include<stdio.h>

double *left,*right,*palm;
int XMODELxor(int l,int ri)
{
    int i,in,r,s,array[8],array1[8],result[16],dec=0,j;
    in=7;
    for (i = 0; i < 8; ++i) {  // assuming a 32 bit int
    array[in] = l & (1 << i) ? 1 : 0;
    in--;
    }
  
    for (i = 0; i < 8; ++i) {  // assuming a 32 bit int
   // printf("\n%d",array[i]);
    }
    in=7;
    for (i = 0; i < 8; ++i) {  // assuming a 32 bit int
    array1[in] = ri & (1 << i) ? 1 : 0;
    in--;
    }
  // printf("\n\n");
    for (i = 0; i < 8; ++i) {  // assuming a 32 bit int
    
// printf("%d",array1[i]);
    }
    
    //part of xor 
    s=1;
    j=0;

    // printf("\n\n");
    for(r=0;r<7;r++)
    {   
        result[j++]=array[r]^array1[s];      
      s++;   
    }
    result[j++]=array[7]^array1[0];
     

    
    // second part of xor
    
    r=1;
   for(s=0;s<7;s++)
    {
                     result[j++]=array[r]^array1[s];
                     r++;
                     }
                     result[j]=array[0]^array1[7];
                     
                    // printf("\n\n");
                    for(i=0;i<16;i++)
                    // printf("%d",result[i]);
                    // printf("\n\n");
    j=0;                
    for(i=15;i>=0;i--)
    {
                      if(result[i]==1){
                      dec=dec+pow(2,j);
                      
                      }
                      
    j++;
}

return dec;
}
void parallel(int pass[],int n)
{
int m=1,c=1,j,k,i;
    while(1)
    {
                   
                   j=0;
                   k=j+m;
                   if(k>n)
                   break;
                   while(j<n&k<n)
                   {
                                     pass[j]=XMODELxor(pass[k],pass[j]);
                                     pass[j]=pass[j]%256;
                                     j=j+(2*c);
                                     k=k+(2*c);
                   
                                     }
                                     c++;
                                     m=2*m;
}
printf("\n\n AFTER PROCESSING BY MODIFIED PARALLEL ADDITION\n");
for(i=0;i<50;i++)
printf("\t%d",abs(pass[i]));

}

void mexFunction(int nlhs, mxArray *plhs[],
int nrhs, const mxArray *prhs[])
{
    int x=1;
int k,dec=0,dec1,resultant,i;

int pass[50];
printf("\n************MODIFIEDD PARALLEL ADDITION ALGORITHM*****************");
   
	left=mxGetPr(prhs[0]);
	right=mxGetPr(prhs[0]);
	palm=mxGetPr(prhs[0]);
	printf("\n\n RECEIVED RIDGES AND BIFURCATIONS VALUES OF REGISTERED LEFT FINGERPRINT\n");
	for(k=0;k<50;k++)
	printf("%0.0f\t" ,left[k]);
	printf("\n\nRECEIVED RIDGES AND BIFURCATIONS VALUES OF REGISTERED RIGHT FINGERPRINT\n");
	for(k=50;k<100;k++)
	printf("%0.0f\t" ,right[k]);
	printf("\n\nRECEIVED RIDGES AND BIFURCATIONS VALUES OF REGISTERED PALM PRINT\n");
	for(k=100;k<150;k++)
	printf("%0.0f\t", palm[k]);
	printf("\n\nRESULT OF PROCESSING BY X MODEL XOR\n ");
	for(k=0;k<50;k++)
{    
    dec=XMODELxor(left[k],right[k]); 
    dec1=dec%256; 
    printf("%d\t",abs(dec1));
    

resultant= (right[k]*x*x)+(palm[k]*x)+dec;
resultant=resultant%256;

pass[k]=resultant;
                      
           
                    
}

parallel(pass,50);
plhs[0] = mxCreateDoubleMatrix(1,50 , mxREAL);
    memcpy(mxGetPr(plhs[0]), pass, 50*sizeof(double));
    if (nlhs > 1) {
        plhs[1] = mxCreateDoubleScalar(50);
  
}
  printf("\n");   
}

