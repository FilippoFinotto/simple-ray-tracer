#ifndef SCENE_H
#define SCENE_H

#include <sys/mman.h>
#include <omp.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
typedef struct {
        float x;
        float y;
        float z;
}vec;

typedef struct {
	float x;
	float y;
	float z;
}camera;

typedef struct {
	uint8_t R;
       	uint8_t G; 
	uint8_t B;
}background;


typedef struct {
	float x;
	float y;
	float z;
}viewpoint;


typedef struct {
	vec *center;
	float r;
	uint8_t R, G, B;
}sphere;

typedef struct {
	int number_of_spheres;
	sphere *sps;
}spheres;




void get_viewpoint(viewpoint *vp, FILE *fp);
void get_background(background *bg, FILE *fp);
int get_number_of_spheres(FILE *fp);
void get_spheres(spheres *spheres, FILE *fp);





#endif
