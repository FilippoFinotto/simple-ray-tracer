#include "scene.h"
#include "ppm.h"


int main(){
	printf("Inserisci il nome del file di testo da usare per creare la scena: \n");
	char file_name[30]; 
	scanf("%s", file_name);
	FILE *fp;
	fp = fopen(file_name, "r");
	if (fp == NULL){
		printf("errore nell'apertura del file\n");
		return 1;
	}
	printf("Inserisci il nome del file immagine dove salvare il risultato del ray tracing: \n");
	char ppm_name[30];
	scanf("%s", ppm_name);
	

	int width, height;
	int res;
	do {
		printf("Inserire il valore della larghezza in pixel dell'immagine da generare: \n");
		res = scanf("%d", &width);
		if (res != 1 || width<= 0){
			printf("Il numero dev'essere intero e positivo \n");
			if (res != 1) while (getchar() != '\n');
		}
	} while (res != 1 || width <= 0);	


	int res2;
        do {
                printf("Inserire il valore dell'altezza  in pixel dell'immagine da generare: \n");
                res2 = scanf("%d", &height);
                if (res2 != 1 || height<= 0){
                        printf("Il numero dev'essere intero e positivo \n");
                        if (res2 != 1) while (getchar() != '\n');
                }
        } while (res2 != 1 || height <= 0);
	printf("%d, %d \n", width, height);


	vector vp;
	get_viewpoint(&vp, fp);

	
	background bg;
	get_background(&bg, fp);


	spheres spheres;
	get_spheres(&spheres, fp);

	create_ppm(ppm_name, width, height, &vp, &bg, &spheres);

	return 0;

}






