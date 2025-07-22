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

void create_vec(int j, int i, vec *vec, int width, int height, viewpoint *vp);
float inner_prod(vec *vec1, vec *vec2);
float norm(vec *vec);
float ray_sphere_intersection(vec *vec, sphere *sphere);
void create_ppm(const char *file_name, int width, int height, viewpoint *vp, background *bg, spheres *spheres);

#endif
