#ifndef SCENE_H
#define SCENE_H

#include <sys/mman.h>
#include <omp.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
        float x;
        float y;
        float z;
}vector;

typedef struct {
	uint8_t R;
       	uint8_t G; 
	uint8_t B;
}background;

typedef struct {
	vector center;
	float r;
	uint8_t R, G, B;
}sphere;

typedef struct {
	int number_of_spheres;
	sphere *sps;
}spheres;

void get_viewpoint(vector *, FILE *);
void get_background(background *, FILE *);
int get_number_of_spheres(FILE *);
void get_spheres(spheres *, FILE *);





#endif
