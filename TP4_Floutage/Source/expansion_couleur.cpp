// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250],cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);

   int histoValR[256],histoValG[256],histoValB[256];
   for(int i=0;i<256;i++){
       histoValR[i]=0;
       histoValG[i]=0;
       histoValB[i]=0;
   }
	
   for (int i=0; i < nTaille3; i+=3)
     {
       nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];
       histoValR[nR]++;
       histoValG[nG]++;
       histoValB[nB]++;
     }

    double Vmin=0;
    double Vmax=255;
    int vR0,vR1,vG0,vG1,vB0,vB1;
    
    vR0=0;
    while (histoValR[vR0]==0){vR0++;}
    vR1=255;
    while (histoValR[vR1]==0){vR1--;}
    double dR=(Vmin*vR1-Vmax*vR0)/(vR1-vR0);
    double gR=(Vmax-Vmin)/(vR1-vR0);
    printf("vRMin=%d, vRMax=%d\n",vR0,vR1);

    vG0=0;
    while (histoValG[vG0]==0){vG0++;}
    vG1=255;
    while (histoValG[vG1]==0){vG1--;}
    double dG=(Vmin*vG1-Vmax*vG0)/(vG1-vG0);
    double gG=(Vmax-Vmin)/(vG1-vG0);
    printf("vGMin=%d, vGMax=%d\n",vG0,vG1);

    vB0=0;
    while (histoValB[vB0]==0){vB0++;}
    vB1=255;
    while (histoValB[vB1]==0){vB1--;}
    double dB=(Vmin*vB1-Vmax*vB0)/(vB1-vB0);
    double gB=(Vmax-Vmin)/(vB1-vB0);
    printf("vBMin=%d, vBMax=%d\n",vB0,vB1);

    printf("dR=%lf, gR=%lf\n",dR,gR);
    printf("dG=%lf, gG=%lf\n",dG,gG);
    printf("dB=%lf, gB=%lf\n",dB,gB);

    for (int i=0; i < nTaille3; i+=3)
     {
       nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];

       ImgOut[i]=255*((double)(nR-vR0)/(double)(vR1-vR0));
       ImgOut[i+1]=255*((double)(nG-vG0)/(double)(vG1-vG0));
       ImgOut[i+2]=255*((double)(nB-vB0)/(double)(vB1-vB0));
     }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
