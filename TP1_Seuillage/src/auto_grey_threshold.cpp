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

	//Compute threshold steps
	float grey_level_per_step = 255.0/nb_thresholds;
	int thresholds_steps[nb_thresholds];


	for(int j =0;j<nb_thresholds;j++){
		thresholds_steps[j]=grey_level_per_step*(j+1);
	}

	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			for(int k=0; k<nb_thresholds; k++){
				if(ImgIn[i*nW+j] <= thresholds_steps[k]){
					ImgOut[i*nW+j]=thresholds_steps[k];
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
