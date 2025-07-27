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

void create_vec(int j, int i, vector *vec, int width, int height, vector *vp);
float inner_prod(vector *vec1, vector *vec2);
float norm(vector *vec);
float ray_sphere_intersection(vector *vec, sphere *sphere);
void create_ppm(const char *file_name, int width, int height, vector *vp, background *bg, spheres *spheres);

#endif
