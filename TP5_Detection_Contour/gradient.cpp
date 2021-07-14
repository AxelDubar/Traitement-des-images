// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"


void gradientImage(OCTET *ImgIn,OCTET *ImgOut,int nH,int nW){
  int currentValue;
  int nbVect;
  int valeurGrad;
  for(int i=0;i<nH;i++){
    for(int j=0;j<nW;j++){
      nbVect=0;
      valeurGrad=0;
      currentValue=ImgIn[i*nW+j];
      
      if(i!=0){
        valeurGrad+=(ImgIn[(i-1)*nW+j]-currentValue)*(ImgIn[(i-1)*nW+j]-currentValue);
      }
      else if(i!=nH-1){
        valeurGrad+=(ImgIn[(i+1)*nW+j]-currentValue)*(ImgIn[(i+1)*nW+j]-currentValue);
      }

      if(j!=0){
        valeurGrad+=(ImgIn[i*nW+j-1]-currentValue)*(ImgIn[i*nW+j-1]-currentValue);
      }
      else if(j!=nH-1){
        valeurGrad+=(ImgIn[i*nW+j+1]-currentValue)*(ImgIn[i*nW+j+1]-currentValue);
      }
      ImgOut[i*nW+j]=sqrt(valeurGrad);
    }
  }
}


int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	
  gradientImage(ImgIn,ImgOut,nH,nW);

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
