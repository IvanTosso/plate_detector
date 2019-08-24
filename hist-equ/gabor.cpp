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
	float sigma_x,sigma_y,sinusoide_real,sinusoide_imaginaria,exponential,result,lambda,offset=0.0;
	
	float ratio = 0.25;//inputImage.w/inputImage.h;
	int radius=3;

	float filtre_real[radius][radius]; 
	float filtre_imaginari[radius][radius];	
	float filtre_real_invertit[radius][radius];
	float filtre_imaginari_invertit[radius][radius];

	lambda = 3;	
	sigma = 8;


//Primer creem el filtre
	for (int i =0; i<radius;i++)
	{
		for (int j =0; j< radius;j++)
		{
			
			exponential = exp(-(i*i+ratio*ratio*j*j)/(2*sigma*sigma));
			sinusoide_real= cos(((2*PI*i)/lambda)+offset);
			sinusoide_imaginaria= sin(((2*PI*i)/lambda)+offset);

			//Ara que faig? ... Trucar l'Ivan 
			filtre_real[i][j]= exponential*sinusoide_real;
			filtre_real_invertit[radius -(i+1)][radius-(j+1)]= exponential*sinusoide_real;
			//filtre_imaginari[i][j] = exponential*sinusoide_imaginaria;
		 	filtre_imaginari_invertit[radius -(i+1)][radius-(j+1)]= exponential*sinusoide_imaginaria;
			
		}

	}
	for (int i = 0; i < radius; i++)
    	{
        	for (int j = 0; j < radius; j++)
		{
	            	std::cout << (float)inputImage.img[(i)*inputImage.w+(j)] << ' ';
        	}
        	
		std::cout << std::endl;
	 }
	std::cout << "\n"<<std::endl;

	  for (int i =0; i < radius; i++)
    	{
        	for (int j =0; j < radius; ++j)
        	{
            		std::cout << filtre_real_invertit[i][j] << ' ';
        	}
        	std::cout << std::endl;
    	}	
		
	  std::cout << "\n"<<std::endl;


//Convolucio de l'imatge: https://nl.mathworks.com/help/images/what-is-image-filtering-in-the-spatial-domain.html

	for (int i =0; i<inputImage.w;i++)
	{
		for (int j =0; j< inputImage.h;j++)
		{
			//Sabem q les matricules no estan aqui, afecta per posterior processat? 
			if (1)//((i - radius) >0 && (j - radius)>0 )
			{
			float outcome=0.0;
		        	for (int outer_loop = 0;outer_loop<radius;outer_loop++)
				{	
					for (int inner_loop=0;inner_loop<radius;inner_loop++)
					{
						//in a 2D array: [a][b], a iterates through rows and b through columns
						//j*inputImage.w = #ROW you are in.
						//
	
						outcome+= (filtre_real_invertit[outer_loop][inner_loop]*(float)(inputImage.img[(j+outer_loop-1)*inputImage.w+(i+inner_loop-1)]));
		//				outcome+= (filtre_imaginari_invertit[outer_loop+radius/2][inner_loop+radius/2]*(float)(inputImage.img[(j+outer_loop)*inputImage.w+(i+inner_loop)]));
					}
				}
			
				inputImage.img [j*inputImage.w+i] = outcome;
				if (i <1)//( (i - radius) == 1 && (j - radius )==1)
				{
					std::cout << (float) inputImage.img[j*inputImage.w+i];
					std::cout<< "\n"<<std::endl;
				}
			}
		}
	
	}

	

	/*	for (int i =0; i<inputImage.w;i++)
	{
		for (int j =0; j< inputImage.h;j++)
		{
			
			exponential = exp(-(i*i+ratio*ratio*j*j)/(2*sigma*sigma));
			sinusoide= cos(((2*PI*i)/lambda)+offset);
			sinusoide_imaginaria= sin(((2*PI*i)/lambda)+offset);

			//Ara que faig? ... Trucar l'Ivan 
			result = exponential*sinusoide;
		//	std::cout <<i+j;
			inputImage.img [j*inputImage.w+i]=  (result*(float)(inputImage.img[j*inputImage.w+i]));//exponential*sinusoide;	 
	//		std::cout << (inputImage.img[i+j]);

		}
	
	}
*/

/*	void rotateMatrix (int mat[][N])
	{
		for (int i = N-1; i > 0; i--)
    		{
        		for (int j = N; j > 0; j--)
			{
				
			}
		}
	}
	std::cout<<("End of Gabor.\n");
 */

};

