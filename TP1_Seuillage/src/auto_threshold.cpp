// seuil_auto.cpp : Seuille une image en niveau de gris automatiquement

#include <stdio.h>
#include "../header/image_ppm.h"

int main(int argc, char* argv[])
{
	char cNomImgLue[250], cNomImgEcrite[250];
	int indiceVal[256];
	int nH, nW, nTaille, nb_thresholds, S;

	if (argc != 4) 
	{
		printf("Usage: ImageIn.pgm ImageOut.pgm Nb_thresholds\n"); 
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	sscanf (argv[3],"%d",&nb_thresholds);

	OCTET *ImgIn, *ImgOut;

	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);

	//Compute img_in histogram
	for(int i=0;i<256;i++){
		indiceVal[i]=0;
	}
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			indiceVal[ImgIn[i*nW+j]]++;
		}
	}

	//Compute threshold steps
	int pixel_per_step = nTaille/nb_thresholds;
	printf("%d pixels in total, %d pixel per threshold\n",nTaille,pixel_per_step);
	int thresholds_steps[nb_thresholds];
	int i=0;
	for(int j =0;j<nb_thresholds;j++){	
		int nb_pixel=0;

		while(i<256 && nb_pixel<pixel_per_step){
			nb_pixel+=indiceVal[i];
			i++;
		}
		printf("Threshold set at %d, %d pixels in it\n",i,nb_pixel);
		thresholds_steps[j]=i;
	}

	printf("Thresholds set at grey level :");
	for(int j =0;j<nb_thresholds;j++){	
		printf("%d ",thresholds_steps[j]);
	}
	printf("\n");


	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			for(int k=0; k<nb_thresholds; k++){
				if(ImgIn[i*nW+j] < thresholds_steps[k]){
					ImgOut[i*nW+j]=(int)((255.0/nb_thresholds)*k);
					break;
				}
			}
		}
	}

  	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
  	free(ImgOut);
  	free(ImgIn);
	return 1;
}
