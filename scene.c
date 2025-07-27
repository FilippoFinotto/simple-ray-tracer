#include "scene.h"

void get_viewpoint(vector *vp, FILE *fp){
	fscanf(fp, " VP  %f %f %f", &vp->x, &vp->y, &vp->z);
}

void get_background(background *bg, FILE *fp){
	int tempR = 0;
       	int tempG = 0;
       	int tempB = 0;
	if(fscanf(fp, " BG %d %d %d", &tempR, &tempG, &tempB) == 3) {
		if(tempR >= 0 && tempR <= 255 && tempG >= 0 && tempG <= 255 && tempB >= 0 && tempB <= 255){
			bg->R = (uint8_t)tempR;
			bg->G = (uint8_t)tempG;
			bg->B = (uint8_t)tempB;
		}else{
			printf("Errore i valori rbg del background non sono corretti");
		}
	}else printf("Errore");
}


int get_number_of_spheres(FILE *fp){
	int n;
	fscanf(fp, " OBJ_N %i", &n);
	return n;
}

void get_spheres(spheres *spheres, FILE *fp){
	spheres->number_of_spheres = get_number_of_spheres(fp);
	spheres->sps = (sphere *)malloc(spheres->number_of_spheres * sizeof(sphere));	
	for(int i=0;i<spheres->number_of_spheres;i++){
		int tempR, tempG, tempB;
		if(fscanf(fp, " S %f %f %f %f %d %d %d", 
			&spheres->sps[i].center.x,
			&spheres->sps[i].center.y,
			&spheres->sps[i].center.z,
			&spheres->sps[i].r, &tempR, &tempG, &tempB)==7){
			if(tempR >= 0 && tempR <= 255 && tempG >= 0 && tempG <= 255 && tempB >= 0 && tempB <= 255){
	                        spheres->sps[i].R = (uint8_t)tempR;
	                        spheres->sps[i].G = (uint8_t)tempG;
	      	                spheres->sps[i].B = (uint8_t)tempB;
	                }else{
	                        printf("Errore i valori rbg del background non sono corretti");
	                }

		}

	}
}










