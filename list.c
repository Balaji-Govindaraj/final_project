#include "mex.h"
#include<stdio.h>
double *left,*right,*palm;
int SINEMODELxor(int l,int ri)
{
    int i,dec1,in,a[8],a1[8],res[16],dec=0,j=0;
    in=7;
for (i = 0; i < 8; ++i) {  // assuming a 32 bit int
    a[in] = l & (1 << i) ? 1 : 0;
    in--;
    }
  
  //  for (i = 0; i < 8; ++i) {  // assuming a 32 bit int
   //printf("%d\t",a[i]);
    //}
  //  printf("\n");
    in=7;
    for (i = 0; i < 8; ++i) {  // assuming a 32 bit int
    a1[in] = ri & (1 << i) ? 1 : 0;
    in--;
    }
//printf("\n second number in bits\n");
  //   for (i = 0; i < 8; ++i) {  // assuming a 32 bit int
   //printf("%d\t",a1[i]);
    //}
for(i=0;i<7;i++)
{
                if(i%2==0)
                          res[j]=a[i]^a1[i+1];
                else
                          res[j]=a1[i]^a[i+1];
j++;
}
res[j]=a1[i]^a[0];
j++;
for(i=0;i<7;i++)
{
                if(i%2==0)
                          res[j]=a1[i]^a[i+1];
                else
                          res[j]=a[i]^a1[i+1];
j++;
}
res[j]=a[i]^a1[0];
j++;
//printf("\n16 bits displayed\n");
//for(i=0;i<16;i++)
//printf("%d\t",res[i]);
dec1=1;
    dec=0;
    l=0;
    for(i=15;i>=0;i--)
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
   
    dec=dec%256;
//printf("\n inside xor %d",dec); 
return dec;
}
void list(int pass[],int n)
{
int m=1,j=0;
int k,i;
while(m<n)
{
    j=0;
    k=j+m;
    while(j<n && k<n)
    {
        pass[j]=SINEMODELxor(pass[j],pass[k]);
        //printf("\nmodified %d",pass[j]);
        
        j=j+1;
        k=k+1;
    }
    //printf("\n");
//    for(i=0;i<4;i++)
  //  printf("%d\t",pass[i]);
    m=2*m;
}
                       
printf("\n\n AFTER PROCESSING BY MODIFIED LIST RANKING PARALLEL ALGORITHM\n");
for(i=0;i<50;i++)
printf("\t%d",abs(pass[i])%256);

}

void mexFunction(int nlhs, mxArray *plhs[],
int nrhs, const mxArray *prhs[])
{ 
int x=1;
    int k,dec=0,i,resultant;
    int pass[50];
   
  double l[50];
    double r[50];
    double p[50];
   
printf("\n ***************MODIFIED LIST RANKING ALGORITHM********************** ");
    
   
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
    printf("\n\nRESULT OF PROCESSING BY SINE MODEL XOR\n ");
	for(k=0;k<50;k++)
    {    
         resultant= (l[k]*x*x)+(p[k]*x)+r[k];
         resultant=resultant%256;
         dec=SINEMODELxor(r[k],resultant);
         
         //dec1=dec%256; 
         //printf("%d\t",abs(dec1));
  //      printf("first pass \n%d",dec);
         
          printf("%d\t",abs(dec));
         pass[k]=dec;   
         //printf("\n%d",pass[k]);                
     }
     printf("\n");
   
     
    /* for(k=0;k<4;k++)
    {
       //printf("helooooooooooooooooooooooooooo");                 
     printf("%d\t",pass[k]);   
    }
     */
     
list(pass,50);
//SINEMODELxor(12,41);
printf("\n");
plhs[0] = mxCreateDoubleMatrix(1,50 , mxREAL);
    memcpy(mxGetPr(plhs[0]), pass, 50*sizeof(double));
    if (nlhs > 1) {
        plhs[1] = mxCreateDoubleScalar(50);
  
}
}
