#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#define EXIT_SUCESS 0

/*==================== PROGRAM ==============================
 * Program:pseudoAng3.c
 * Description: qua 06 nov 2019 03:58:26
 * Date of Create: qua 06 nov 2019 05:13:58 
 * Update in: qua 06 nov 2019 11:24:00 
 * Author:Jefferson Bezerra dos Santos
 * Compler: gcc -lm pseudoAng3.c -o pseudoAng3
 *===========================================================
 */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ordemBruta
 *  Description: Faz a ordenação dos elementos 
 * =====================================================================================
 */

void ordemBruta (float *x,int n)

{
		int m;
		float aux;
		for (int i = 0;i <= n-2;i++) {
				m = i;

				for (int j = i+1;j <= n-1 ; j++ ) {
						
						if ( x[j] < x[m] ) {
								m = j;
								
						}
				}
				aux = x[i];
				x[i] = x[m];
				x[m] = aux;
		}
		

}		/* -----  end of function ordemBruta  ----- */



/*======================= FUNCTION ===========================
 * Function: pseudoAng.c
 * Description: Calcular o pseudo angulo
 *============================================================
 */

float  PseudoAng(float *x){
	float h;
	if(x[1] > 0){//x1 > 0 e x2 > 0
		/* Teste para o primeiro quadrante*/
		if(x[0] > 0){
			if(x[1] < x[0]){
				h = x[1]/x[0]; 
			}else{
				h = 2 - x[0]/x[1];
			}
		}else{
			/* Teste para o segundo quadrante*/
			if(x[0] < 0){// x1 < 0 e x2 > 0
				if(fabs(x[0]) < fabs(x[1])){
					h = 2 + (fabs(x[0]))/(fabs(x[1]));
				}else{
					h = 4 - (fabs(x[1]))/(fabs(x[0]));
				}
			}
		}
	}else{/* Teste para o terceiro quadrante*/
		if(x[0] < 0){// x1 < 0 e x2 < 0
			if(fabs(x[1]) < fabs(x[0])){
				h = 4 + (fabs(x[1]))/(fabs(x[0]));
			}else{
				h = 6 - (fabs(x[0]))/(fabs(x[1]));
			}
		}
		/* Teste para o quarto quadrante*/
		else {// x1 > 0 e x2 < 0
			if(fabs(x[0]) < fabs(x[1])){
				h = 6 + (fabs(x[0]))/(fabs(x[1]));
			}else{
				h = 8 - (fabs(x[1]))/(fabs(x[0]));
			}
		}
	}
	
   	return h;
}/*---------End of function-------------*/


/*=================== FUNCTION MAIN () ======================
 * Function: main()
 * Description: Executar pseudo angulo 
 * ==========================================================
 */
int main(void){
	float x1[] = {0.5,-0.04}; float x2[] = {-1,5};float x3[] = {-1,-0.75};float x4[] = {1,-2.5};//vetores a serem verificados
	float ang1[4];//Vetor auxiliar para guardar o valor do pseudo-angulo
	float ang2[4];//Vetor auxiliar para guardar o valor do pseudo-angulo
	char theta[6][5];//Vetor de strings para auxiliar para impressao

	ang1[0]= PseudoAng(x1);
	ang1[1] = PseudoAng(x2);
	ang1[2] = PseudoAng(x3);
	ang1[3] = PseudoAng(x4);

	ang2[0] = ang1[0];
	ang2[1] = ang1[1];
	ang2[2] = ang1[2];
	ang2[3] = ang1[3];

	/*Ordenando os angulos*/
	ordemBruta (ang1,4);

	printf("Listando os ângulos do menor paro maior:\n");
		for (int i = 0; i <= 3; i++){

			if(ang1[i]==ang2[0]){
			strcpy(theta[i],"x1");
			}

			if(ang1[i]==ang2[1]){
			strcpy(theta[i],"x2");
			}
			
			if(ang1[i]==ang2[2]){
			strcpy(theta[i],"x3");
			}

			if(ang1[i]==ang2[3]){
			strcpy(theta[i],"x4");
			}
			
			if(i < 3){
				printf(" Theta(%s) < ",theta[i]);
			}else{
				printf(" Theta(%s) ",theta[i]);
			}
		}	
			puts("\n");


			return EXIT_SUCESS;
}/*----------End of function-----------------*/


