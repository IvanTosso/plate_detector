#include "gabor.h"
//#include <cmath>
#include <bits/stdc++.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#define PI 3.14159265
//void GaborFilter::GaborFilter(){};
//void GaborFilter::~GaborFilter(){};
void GaborFilter::Initialize(PGM_IMG inputImage,PGM_IMG outputImage,float phase,float sigma)

{
	float sinusoide_real,sinusoide_imaginaria,exponential,result,lambda,offset=0.0;
	
	float ratio =0.95;// 0.5;//inputImage.w/inputImage.h;
	int radius=9;

	float filtre_real[radius][radius]; 
	float filtre_imaginari[radius][radius];	
	float filtre_real_invertit[radius][radius];
	float filtre_imaginari_invertit[radius][radius];

	lambda = 10;	
	sigma = 4;


//Primer creem el filtre
	for (int i =0; i<radius;i++)
	{
		for (int j =0; j< radius;j++)
		{
			int nTheta=PI/2;	
			exponential = exp(-((pow(i*cos(nTheta)+j*sin(nTheta),2))+ratio*ratio*(pow(-i*sin(nTheta)+j*cos(nTheta),2)))/(2*sigma*sigma));
			sinusoide_real= cos((2*PI*(i*cos(nTheta)+j*sin(nTheta))/lambda)+offset);
			sinusoide_imaginaria= sin((2*PI*(i*cos(nTheta)+j*sin(nTheta))/lambda)+offset);

		//Ara que faig? ... Trucar l'Ivan 
			filtre_real[i][j]= exponential*sinusoide_real;
			filtre_real_invertit[radius -(i+1)][radius-(j+1)]= exponential*sinusoide_real;
			//filtre_imaginari[i][j] = exponential*sinusoide_imaginaria;
		 	filtre_imaginari_invertit[radius -(i+1)][radius-(j+1)]= exponential*sinusoide_imaginaria;
			
		}

	}
//Convolucio de l'imatge: https://nl.mathworks.com/help/images/what-is-image-filtering-in-the-spatial-domain.html

	for (int i =0; i<inputImage.w;i++)
	{
		for (int j =0; j< inputImage.h;j++)
		{
			//Sabem q les matricules no estan aqui, afecta per posterior processat? 
			if ((i - radius) >0 && (j - radius)>0 )
			{
			float outcome=0.0;
		        	for (int outer_loop = 0;outer_loop<radius;outer_loop++)
				{	
					for (int inner_loop=0;inner_loop<radius;inner_loop++)
					{
						//in a 2D array: [a][b], a iterates through rows and b through columns
						//j*inputImage.w = #ROW you are in.
						//
	
						outcome+= (filtre_real_invertit[outer_loop][inner_loop]*(float)(inputImage.img[(j+outer_loop-(radius-1)/2)*inputImage.w+(i+inner_loop-(radius-1)/2)]));
					//	outcome+= (filtre_imaginari_invertit[outer_loop][inner_loop]*(float)(inputImage.img[(j+outer_loop-1)*inputImage.w+(i+inner_loop-1)]));
					}
				}
			
				inputImage.img [j*inputImage.w+i] = outcome;
						
			}
			else 
			{
			
				inputImage.img [j*inputImage.w+i] = 0;
			
			}
		}
	
	}

	
};

