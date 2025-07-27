#ifndef PPM_H
#define PPM_H
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <sys/mman.h>
#include <omp.h>
#include <unistd.h>
#include "scene.h"

void create_vec(int , int , vector *, int , int , vector *);
float inner_prod(vector *, vector *);
float norm(vector *);
float ray_sphere_intersection(vector *, sphere *);
void create_ppm(const char *, int, int , vector *, background *, spheres *);

#endif
