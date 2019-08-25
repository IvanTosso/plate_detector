#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hist-equ.h"
#include <time.h>
#include "gabor.h"


void run_cpu_color_test(PPM_IMG img_in);
void run_gpu_color_test(PPM_IMG img_in);
void run_cpu_gray_test(PGM_IMG img_in);
void run_gpu_gray_test(PGM_IMG img_in);


int main(){
    
    PGM_IMG img_ibuf_gs;
    time_t start_time;
    time_t  time_difference;
    struct timespec gettime_now;
    
    clock_gettime(CLOCK_REALTIME, &gettime_now);
    start_time = gettime_now.tv_sec;		//Get nS value
    
   
    printf("Running contrast enhancement for color images.\n");
    img_ibuf_gs = read_pgm("testbench_photos/red_car.pgm"); 
	    /*plate_grayscale.pgm");("testbench_photos/Test1.pgm");*/    
	run_cpu_gray_test(img_ibuf_gs);
    //TODO: GPU implementation
    //run_gpu_color_test(img_ibuf_c);
    
    //GaborFilter gabor;
    //gabor.Initialize(img_ibuf_gs,img_ibuf_gs,0,3);

    free_pgm(img_ibuf_gs);
    clock_gettime(CLOCK_REALTIME, &gettime_now);
    time_difference = gettime_now.tv_sec - start_time;
    if (time_difference < 0)
	time_difference += 1000000000;//(Rolls over every 1 second)	
    
    printf ("Total execution time = %ld. \n", (long) time_difference);
    return 0;
}

void run_gpu_color_test(PPM_IMG img_in)
{
    printf("Starting GPU processing...\n");
    //TODO: run your GPU implementation here
    img_in = img_in; // To avoid warning...
}

void run_gpu_gray_test(PGM_IMG img_in)
{
    printf("Starting GPU processing...\n");
    //TODO: run your GPU implementation here
    img_in = img_in; // To avoid warning...
}

void run_cpu_color_test(PPM_IMG img_in)
{
    unsigned int timer = 0;
    PPM_IMG img_obuf_hsl, img_obuf_yuv;
    
    printf("Starting CPU processing...\n");
       img_obuf_hsl = contrast_enhancement_c_hsl(img_in);
   
    write_ppm(img_obuf_hsl, "out_hsl.ppm");
//TODO: Uncomment these functions for performance tests
    /*  img_obuf_yuv = contrast_enhancement_c_yuv(img_in);
   
    write_ppm(img_obuf_yuv, "out_yuv.ppm");
    */
    free_ppm(img_obuf_hsl);
    //free_ppm(img_obuf_yuv);
}




void run_cpu_gray_test(PGM_IMG img_in)
{
    unsigned int timer = 0;
    PGM_IMG img_obuf;
    
    
    printf("Starting CPU processing...\n");
    
    img_obuf = contrast_enhancement_g(img_in);
    GaborFilter gabor;
    gabor.Initialize(img_obuf,img_obuf,0,3);


    write_pgm(img_obuf, "out.pgm");
    free_pgm(img_obuf);
}



PPM_IMG read_ppm(const char * path){
    FILE * in_file;
    char sbuf[256];
    
    char *ibuf;
    PPM_IMG result;
    int v_max, i;
    in_file = fopen(path, "r");
    if (in_file == NULL){
        printf("Input file not found!\n");
        exit(1);
    }
    /*Skip the magic number*/
    fscanf(in_file, "%s", sbuf);


    //result = malloc(sizeof(PPM_IMG));
    fscanf(in_file, "%d",&result.w);
    fscanf(in_file, "%d",&result.h);
    fscanf(in_file, "%d\n",&v_max);
    printf("Image size: %d x %d\n", result.w, result.h);
    

    result.img_r = (unsigned char *)malloc(result.w * result.h * sizeof(unsigned char));
    result.img_g = (unsigned char *)malloc(result.w * result.h * sizeof(unsigned char));
    result.img_b = (unsigned char *)malloc(result.w * result.h * sizeof(unsigned char));
    ibuf         = (char *)malloc(3 * result.w * result.h * sizeof(char));

    
    fread(ibuf,sizeof(unsigned char), 3 * result.w*result.h, in_file);

    for(i = 0; i < result.w*result.h; i ++){
        result.img_r[i] = ibuf[3*i + 0];
        result.img_g[i] = ibuf[3*i + 1];
        result.img_b[i] = ibuf[3*i + 2];
    }
    
    fclose(in_file);
    free(ibuf);
    
    return result;
}

void write_ppm(PPM_IMG img, const char * path){
    FILE * out_file;
    int i;
    
    char * obuf = (char *)malloc(3 * img.w * img.h * sizeof(char));

    for(i = 0; i < img.w*img.h; i ++){
        obuf[3*i + 0] = img.img_r[i];
        obuf[3*i + 1] = img.img_g[i];
        obuf[3*i + 2] = img.img_b[i];
    }
    out_file = fopen(path, "wb");
    fprintf(out_file, "P6\n");
    fprintf(out_file, "%d %d\n255\n",img.w, img.h);
    fwrite(obuf,sizeof(unsigned char), 3*img.w*img.h, out_file);
    fclose(out_file);
    free(obuf);
}

void free_ppm(PPM_IMG img)
{
    free(img.img_r);
    free(img.img_g);
    free(img.img_b);
}

PGM_IMG read_pgm(const char * path){
    FILE * in_file;
    char sbuf[256];
    
    
    PGM_IMG result;
    int v_max;//, i;
    in_file = fopen(path, "r");
    if (in_file == NULL){
        printf("Input file not found!\n");
        exit(1);
    }
    
    fscanf(in_file, "%s", sbuf); /*Skip the magic number*/
    fscanf(in_file, "%d",&result.w);
    fscanf(in_file, "%d",&result.h);
    fscanf(in_file, "%d\n",&v_max);
    printf("Image size: %d x %d\n", result.w, result.h);
    

    result.img = (unsigned char *)malloc(result.w * result.h * sizeof(unsigned char));

        
    fread(result.img,sizeof(unsigned char), result.w*result.h, in_file);    
    fclose(in_file);
    
    return result;
}

void write_pgm(PGM_IMG img, const char * path){
    FILE * out_file;
    out_file = fopen(path, "wb");
    fprintf(out_file, "P5\n");
    fprintf(out_file, "%d %d\n255\n",img.w, img.h);
    fwrite(img.img,sizeof(unsigned char), img.w*img.h, out_file);
    fclose(out_file);
}

void free_pgm(PGM_IMG img)
{
    free(img.img);
}

