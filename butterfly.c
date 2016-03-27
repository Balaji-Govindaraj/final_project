#include "mex.h"
#include<stdio.h>
double *left,*right,*palm;

int ShuffledXor(int l,int ri)
{
    int i,in,a[8],a1[8],res[8],dec=0,j=0,dec1;
    
    //printf("\nl=%d, ri=%d",l,ri);
    in=7;
    for (i = 0; i < 8; ++i) {  // assuming a 32 bit int
    a[in] = l & (1 << i) ? 1 : 0;
    in--;
    }
   /*printf("\n");
    for (i = 0; i < 8; ++i) { // assuming a 32 bit int
   printf("%d\t",a[i]);
    }*/
    in=7;
    for (i = 0; i < 8; ++i) {  // assuming a 32 bit int
    a1[in] = ri & (1 << i) ? 1 : 0;
    in--;
    }
  /*printf("\n");
    for (i = 0; i < 8; ++i) { // assuming a 32 bit int
   printf("%d\t",a1[i]);
    }*/
    //shuffled xor
    j=7;
    for(i=0;i<8;i++)
    {
      res[i]=a[i]^a1[j];
      j--;              
    } 
  
    
   dec1=1;
    dec=0;
    l=0;
    for(i=7;i>=0;i--)
    {
     if(res[i]==1)
     {

                for(j=0;j<l;j++)
                {
                      dec1=dec1*2; 
                //dec1=dec1+2;
                  }
    //              printf("\n square value %d",dec1);
                  dec=dec+dec1;
     }
     dec1=1;
                  l++;
                  }    
   

return dec;           
}
void butterfly(int pass[],int n)
{
     
     int c=2,m=1;
     int j,k;
    
     while(c<=n)
     {
                j=0;
                k=j+m;
                while(j<n&&k<n)
                {
                    pass[j]=ShuffledXor(pass[j],pass[k])%256;
                   // printf("\n%d",pass[j]);
                    pass[k]=ShuffledXor(pass[j],pass[k])%256;
                    //printf("\n%d",pass[k]);
                    if((k+1)%c==0)
                    {
                                  j=k+1;
                                  k=j+m;
                                  }
                                  else
                                  {
                                      j=j+1;
                                      k=k+1;
                                      }
                                      }
                                      c=c*2;
                                      m=m*2;
                                      }
                                     printf("\n\nAFTER PROCESSING BY BUTTERFLY PARALLEL ALGORITHM\n");
                                      for(j=0;j<50;j++)
                                      printf("%d\t",pass[j]);
                                            
}
void mexFunction(int nlhs, mxArray *plhs[],
int nrhs, const mxArray *prhs[])
{
    int x=1,i;
    int k,dec=0,resultant;
    int pass[50];
    double l[50];
    double r[50];
    double p[50];
   
printf("\n ***************MODIFIED BUTTERFLY PARALLEL ALGORITHM********************** ");
    
   
	left=mxGetPr(prhs[0]);
	right=mxGetPr(prhs[0]);
	palm=mxGetPr(prhs[0]);
	
    printf("\n\n RECEIVED RIDGES AND BIFURCATIONS VALUES OF REGISTERED LEFT FINGERPRINT\n");
	for(k=0;k<50;k++){
	printf("%0.0f\t" ,left[k]);
	l[k]=left[k];
}
    printf("\n\nRECEIVED RIDGES AND BIFURCATIONS VALUES OF REGISTERED RIGHT FINGERPRINT\n");
    i=0;
	for(k=50;k<100;k++){
	printf("%0.0f\t" ,right[k]);
    r[i]=right[k];
    i++;
}
    printf("\n\nRECEIVED RIDGES AND BIFURCATIONS VALUES OF REGISTERED PALM PRINT\n");
    i=0;
	for(k=100;k<150;k++){
	printf("%0.0f\t", palm[k]);
    p[i]=palm[k];
    i++;
}
    printf("\n\nRESULT OF PROCESSING BY shuffled MODEL XOR\n ");
	for(k=0;k<50;k++)
    {    
         resultant= (l[k]*x*x)+(r[k]*x)+p[k];
         resultant=resultant%256;
         dec=ShuffledXor(p[k],resultant);
         
         //dec1=dec%256; 
         //printf("%d\t",abs(dec1));
        // printf("\n%d",dec);
         dec=dec%256;
          printf("%d\t",dec);
         pass[k]=dec;   
         //printf("\n%d",pass[k]);                
     }
     butterfly(pass,50);
     plhs[0] = mxCreateDoubleMatrix(1,50 , mxREAL);
    memcpy(mxGetPr(plhs[0]), pass, 50*sizeof(double));
    if (nlhs > 1) {
        plhs[1] = mxCreateDoubleScalar(50);
  
}
}
