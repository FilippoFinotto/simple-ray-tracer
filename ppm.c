#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <omp.h>
#include <stdint.h>
#include <math.h>
#include "ppm.h"
#include "scene.h"

void create_vec(int j, int i, vec *vec, int width, int height, viewpoint *vp){
	vec->x = (((vp->x)/(width-1))*i-((vp->x)/2));
	vec->y = (((vp->y)/(height-1))*j-((vp->y)/2));
	vec->z = vp->z;
	float vec_norm = norm(vec);
	vec->x = (vec->x)/vec_norm;
	vec->y = (vec->y)/vec_norm;
	vec->z = (vec->z)/vec_norm;

}


float norm(vec *vec){
	return sqrt(pow(vec->x,2)+pow(vec->y,2)+pow(vec->z,2));
}

float inner_prod(vec *vec1, vec*vec2){
	return vec1->x*vec2->x + vec1->y*vec2->y + vec1->z*vec2->z;
}


float ray_sphere_intersection(vec *vec, sphere *sphere){
	float a,b,c;
	a = inner_prod(vec, vec);
	b = -2*inner_prod(sphere->center, vec);
	c = inner_prod(sphere->center, sphere->center) - pow(sphere->r, 2);
	if ((pow(b,2) - 4*a*c) < 0){
		return INFINITY;
	}
	if ((pow(b,2) - 4*a*c) == 0){
		return fabs(-b/(2*a));
	}
	if ((pow(b,2) - 4*a*c) > 0){
		return fmin(fabs((-b+sqrt(pow(b,2) - 4*a*c))/(2*a)), fabs((-b-sqrt(pow(b,2)-4*a*c))/(2*a)));
	}
	else return 0;
}


void create_ppm(const char *file_name, int width, int height, viewpoint *vp, background *bg, spheres *spheres){

	char header_buffer[40];
	int header_len = snprintf(header_buffer, sizeof(header_buffer), "P6\n%d %d\n255\n", width, height);

	long data_len = height * width * 3;
	long total_file_size = header_len + data_len;
	
	printf("size del file è: %li\n", total_file_size);


	FILE *fp = fopen(file_name, "wb+");
	int fd = fileno(fp);
	ftruncate(fd, total_file_size);
	uint8_t *map_ptr = mmap(
		NULL,
		total_file_size,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		fd,
		0
	);

	memcpy(map_ptr, header_buffer, header_len);

	uint8_t *pixel_data_ptr = map_ptr + header_len;
#pragma omp parallel for
	for (int j = 0; j < height; j++){
		for (int i = 0; i < width; i++){
			vec vec;
			create_vec(height-1-j, i, &vec, width, height, vp);
			




			float min_dist = INFINITY;
			int closest_sphere_index = 0;
			for (int k = 0; k < spheres->number_of_spheres; k++){
				if (ray_sphere_intersection(&vec, &spheres->sps[k]) < min_dist){
					min_dist = ray_sphere_intersection(&vec, &spheres->sps[k]);
					closest_sphere_index = k;
				}else {
					continue;
				}
			}
			
			long offset = (long)j * width * 3 + (long)i * 3;

			if (min_dist == INFINITY){
				pixel_data_ptr[offset] = bg->R;
				pixel_data_ptr[offset+1] = bg->G;
				pixel_data_ptr[offset+2] = bg->B;
			}
			if (min_dist != INFINITY){
				pixel_data_ptr[offset] = spheres->sps[closest_sphere_index].R;
				pixel_data_ptr[offset+1] = spheres->sps[closest_sphere_index].G;
				pixel_data_ptr[offset+2] = spheres->sps[closest_sphere_index].B;
			}
		}
	}
	munmap(map_ptr, total_file_size);
	fclose(fp);
}








