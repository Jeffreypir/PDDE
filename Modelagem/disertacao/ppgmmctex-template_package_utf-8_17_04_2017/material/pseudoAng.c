#include<stdio.h>
#include <stdlib.h>
#include <math.h> 
#define EXIT_SUCESS 0

/*==================== PROGRAM ==============================
 * Program: pseudoAng.c 
 * Description: qua 06 nov 2019 03:58:26
 * Date of Create: qua 06 nov 2019 05:13:58 
 * Update in:  qua 06 nov 2019 03:58:34 
 * Author:Jefferson Bezerra dos Santos
 * Compler: gcc -lm pseudoAng.c -o pseudoAng
 *===========================================================
 */


/*======================= FUNCTION ===========================
 * Function: pseudoAng.c
 * Description: Calcular o pseudo angulo
 *============================================================
 */
float  PseudoAng(float *x){
	float h;
	/* Teste para o primeiro quadrante */
	if( x[0] > 0 && x[1] > 0){//x1 > 0 e x2 > 0
		if(x[1] < x[0]){
		  h = x[1]/x[0]; 
		}else{
			h = 2 - x[0]/x[1];
		}
	}		
	/* Teste para o segundo quadrante*/
	if(x[0] < 0 && x[1] > 0){// x1 < 0 e x2 > 0
		if(abs(x[0]) < abs(x[1])){
			  h = 2 + (abs(x[0]))/(abs(x[1]));
		}else{
			h = 4 - (abs(x[1]))/(abs(x[0]));
		}
	}

	/* Teste para o terceiro quadrante*/
	if(x[0] < 0 && x[1] < 0){// x1 < 0 e x2 < 0
		if(abs(x[1]) < abs(x[0])){
			  h = 4 + (abs(x[1]))/(abs(x[0]));
		}else{
			h = 6 - (abs(x[0]))/(abs(x[1]));
		}
	}

	/* Teste para o quarto quadrante*/
	if(x[0] > 0 && x[1] < 0){// x1 > 0 e x2 < 0
		if(abs(x[0]) < abs(x[1])){
			  h = 6 + (abs(x[0]))/(abs(x[1]));
		}else{
			h = 8 - (abs(x[1]))/(abs(x[0]));
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
	float x[] = {-1,2}; float y[] = {-3,-4};	
	if(PseudoAng(x) > PseudoAng(y)){
		printf("O ângulo do vetor x é maior que do vetor y");
	}else{
		printf("O ângulo do vetor x é menor que do vetor y");
	}
		return EXIT_SUCESS;
}/*----------End of function-----------------*/
