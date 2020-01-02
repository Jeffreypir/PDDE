/*
 * ======================================================
 *
 *       Filename: mult_cortes.c 
 *
 *    Description:  Programação utilizando os mult cortes de Benders, GNU GLPK
 *                  Despacho de energia, progrmação Linear,
 *                  programação estocástica. 
 *                  Viva o linux !!!
 *                  Por que amamos a liberdade.
 *
 *        Version:  0.1
 *        Created:  21-05-2019 11:05:42
 *       Revision:  21-05-2019 11:05:26
 *       Compiler:  gcc
 *
 *         Author:  Jefferson Bezerra dos Santos 
 *
 * ======================================================
 */

# include <stdio.h> /* Entrada e saida C */ 
# include <stdlib.h> /* Biblioteca padrão do C */
# include <glpk.h> /*  Gnu GLPK */
# include <math.h>
# define ERRO 3

int main(void){ // Inicio da main ()

		                            /* PROBABILIDADE ASSOCIADA AOS CENARIOS */
		   double C1 = 0.5,C2 = 0.5;                    

	      		                           /* CHUTE viável */

		                               /*DEFINIDO O ESTAGIO 1*/
		   /* ================================= INICIO ============================================================ */
		   /* Vazões turbinadas e vertidas das Usinas no estágio 1 */
		   double VTH1S1 = 50.0,VVH1S1 = 100.0,VTH2S1 = 40.0, VVH2S1 = 200.0; 

           /* Definindo a produtibilidade(s) da(s) Usina(s) */
		   double PRODUTIBILIDADE[2] = {20.0,30.0};

		   /* Atividade das térmicas associadas as Hidroletricas 1 e 2 respectivamente */
		   double G1 = 0.0, G2 = 0.0; 

		   /* Definido a demanda a ser atingida 1 estagio */
		   double DEMANDAs1[2]= {100.0,200.0};

		   /* Definindo os volumes máximos da(s) hidroelétrias */
		   double VOL1 = 10000.0;
		   double VOL2 = 10000.0;

		   /* Definindo o vetor de custo para o 1 estágio 1 */
		   double Cs1[6] = {1.0, 1.0, 1.0, 1.0, 3.0, 2.0};
		   /*=================================== FIM ============================================================= */

		                              /* DEFININDO O CENARIO 1: */
		   /*================================= INICIO ============================================================ */
		   /* Definindo o volume incremental da Usina hidroelétrica 1 */
		   double VOLI1_1 = 200.0;

		   /* Definindo o volume incremental da Usina hidroelétrica 2 */
		   double VOLI2_1 = VVH1S1;
		  
		    /* Definindo o volume inicial das Usinas */
		   double VINH1_1 = 100.0;  // Hidroeletrica 1
		   double VINH2_1 = 200.0;  // Hidroeletrica 2
		   /*=================================== FIM ============================================================= */

		                            /* DEFININDO O 2 ESTAGIO CENARIO 1 */
		   /*==================================== INICIO ========================================================= */
		   /* Vazões turbinadas e vertidas das Usinas no estágio 2 */
		   double VTH1S2_1 = 60.0,VVH1S2_1 = 20.0,VTH2S2_1 = 50.0,VV1H2S2_1 = 10.0; 

		   /* Definido a demanda a ser atingida 2 estagio */
		   double DEMANDAs2_1[2]= {50.0,100.0};

		   /* Dfinindo a variável auxiliar para guardar o valor do primal*/
		   double ALFA1_1 = VTH1S2_1*Cs2[0] + VVH1S2_1*Cs2[1] + VTH2S2_1*Cs2[2] + VVH2S2_1*Cs2[3] + G1_1*Cs2[4] + G2_1*Cs2[5]; 
		   double ALFA1_2;

		   /* Definindo a variavel auxiliar para guardar o valor do dual */ 
		   double ALFA1_1X = 10000.0;

		   /* Definindo os duais para a atualização */
		   double u1_1 = 0, u2_1 = 0, u3_1 = 0, u4_1 = 0, u5_1 = 0, u6_1 = 0;

		   /* Matriz dos coeficiente para a atualização dual */
		   double matriz_variavel_1[6][3]; 
		  /*==================================== FIM ============================================================= */

		                /* ATIVIDADE DAS TERMICAS ASSOCIADAS A HIFROELETRICA 1 E 2 RESPECTIVAMENTE */ 
		                            /* VARIAVIES COMUNS PARA OS CENARIOS */
		   /*=================================== INICIO =============================================================*/
		   /*Limite de operação das térmicas */
		   double TERMICAS = 100;

		   /* Dfinindo o vetor de custo para o 2 estágio 2 */ 
		   double Cs2[6] = {1.0, 1.0, 1.0, 1.0, 2.5, 2.0};
		   /*================================= FIM =================================================================*/

		                          /* AMOSTRANDO OS DADOS PARA O CENRARIO 1*/
		   /*==================================== INICIO ========================================================= */
		   printf ("INICIO \n");	
		   printf ("Primal \n");
		   printf ("Chute viável hidroelétrica 1 e 2 no estágio 1: \n"); 
		   printf ("VTH1S1 = %lf,VVH1S1 = %lf,VTH2S1 = %lf,VVH2S1 = %lf \n\n",VTH1S1,VVH1S1,VTH2S1,VVH2S1); 
		   printf ("Chute viável da hidroelétrica 1 e 2 no estágio 1 no cenário \n");
		   printf ("VTH1S2_1 = %lf,VVH1S2_1 = %f,VTH2S2_1 = %lf,VVH2S2_1 = %lf \n \n",VTH1S2_1,VVH1S2_1,VT1H2S2_1,VV1H2S2_1); 
		   printf ("Chute viável térmicas no estágio 1: \n");
		   printf ("G1 = %lf, G2 = %lf \n \n", G1,G2); 
		   printf ("Chute viável térmicas no estágio 2 Cenario : \n");
		   printf ("G1_1 = %lf, G2_1 = %lf \n \n", G1_1,G2_1); 
		   /*======================================= FIM ======================================================== */
 
		  /* PROBLEMA DUAL CENARIO 1
		   * Declarando as variaveis 
		   *
	       * ======== INICIO ======== */
		  glp_prob *ld_1;
		  int ia_1[100+1], ja_1[100+1];
		  double ar_1[100+1];
		  double u_1[10];
		  /* ========= FIM ========== */

		  /* PROBLEMA DUAL CENARIO 2
		   * Declarando as variaveis 
		   *
	       * ======== INICIO ======== */
		  glp_prob *ld_2;
		  int ia_2[100+1], ja_2[100+1];
		  double ar_2[100+1];
		  double u_2[10];
		  /* ========= FIM ========== */
		  
           /* PROBLEMA PRIMAL */

          /* Declarando as variaveis 
		   *
		   * ======== INICIO ====== */
		  glp_prob *lp;
		  int ia[400+1], ja[400+1];     // Inciando vetores dos indices das linhas e das colunas, mesmo tamanho para ambos
		  int j = 0,ci,cj;              // Contadores auxiliares 
		  double z;                     // Valores de saida
		  double ar[400+1];             // Vetor com os valores para os indices 
		  double sup_1[200+1];          // Vetor com os valores limites superiores para o cenário 1
		  double sup_2[200+1];          // vetor com os valores limites superiores para o cenário 2 
		  double inf_1[200+1];          // Vetor com os valores limites inferiores para o cenário 1  
		  double inf_2[200+1];          // Vetor com os valores limites inferiores para o cenário 2
		  double soma_1[200+1][200+1];  // Vetor com os valores do array dos coeficientes para colocar as restrições para cenário 1
		  double soma_2[200+1][200+1];  // Vetor com os valores do array dos coeficientes para colocar as restrições para cenário 2 
		  /*======== FIM ========== */


		  /* INICIANDO O LOOP */ 
		  while (fabs((ALFA_1X - ALFA_1)) >= ERRO){
				  printf ("Diferença de (ALFA_1x - ALFA_1) = %lf \n \n",fabs((ALFA_1X - ALFA_1)));	  
 
                                  /* CREANDO O PROBLEMA  DUAL PARA O CENARIO 1 */
		  /* ====================================== INICIO ===================================================== */
		  ld_1 = glp_create_prob();
		  glp_set_obj_dir(ld_1,GLP_MAX);

          /* Preenchimento dos dados do problema : 
		   * Número de linha(s) da matriz */
		  glp_add_rows(ld_1,6);
		  
		  /* Definindo os limitantes da(s) linhas (s)*/ 
		  glp_set_row_bnds(ld_1,1,GLP_UP,0.0,Cs2[0]);/* Custo associado a Hidroeletrica 1 vazão turbinada */
		  glp_set_row_bnds(ld_1,2,GLP_UP,0.0,Cs2[1]);/* Custo associado a Hidroeletrica 1 vazão vertida */
		  glp_set_row_bnds(ld_1,3,GLP_UP,0.0,Cs2[2]);/* Custo associado a Hidroeletrica 2 vazão turbinada */
		  glp_set_row_bnds(ld_1,4,GLP_UP,0.0,Cs2[3]);/* Custo associado a Hidroeletrica 2 vazão vertida */
		  glp_set_row_bnds(ld_1,5,GLP_UP,0.0,Cs2[4]);/* Custo associado a Termica 1 */
		  glp_set_row_bnds(ld_1,6,GLP_UP,0.0,Cs2[5]);/* Custo associado a Termica 2 */

		  /* Número de coluna(s) da matriz */
		  glp_add_cols(ld_1,6);

		  /* Defindo um limitante das coluns(s) default 0.0 */
		  glp_set_col_bnds(ld_1,1,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_1,2,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_1,3,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_1,4,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_1,5,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_1,6,GLP_LO,0.0,0.0);

		  /* Definindo os coeficentes da função objetivo */
		  glp_set_obj_coef(ld_1,1,DEMANDAs2[0] + DEMANDAs2[1]);
		  glp_set_obj_coef(ld_1,2,-TERMICAS);
		  glp_set_obj_coef(ld_1,3,(-VOL1 + VOLI1));
		  glp_set_obj_coef(ld_1,4,(-VOL2 + VOLI2));
		  glp_set_obj_coef(ld_1,5,-VINH1 - VTH1S1 - VVH1S1);
		  glp_set_obj_coef(ld_1,6,-VINH2 - VTH2S1 - VVH2S1);

		  /* Preechimento dos valores da matriz das restrições */

		              /* Definindo a 1 linha */
		  	ia_1[1] = 1, ja_1[1] = 1, ar_1[1] =  PRODUTIBILIDADE[0];   /* a[1,1] = -P1  */ 
		    ia_1[2] = 1, ja_1[2] = 2, ar_1[2] =  0.0;                  /* a[1,2] =  0.0 */
		    ia_1[3] = 1, ja_1[3] = 3, ar_1[3] =  0.0;                  /* a[1,3] =  0.0 */
		    ia_1[4] = 1, ja_1[4] = 4, ar_1[4] =  PRODUTIBILIDADE[1];   /* a[1,4] =  0.0 */
		    ia_1[5] = 1, ja_1[5] = 5, ar_1[5] =  1.0;                  /* a[1,5] = -1.0 */
		    ia_1[6] = 1, ja_1[6] = 6, ar_1[6] =  1.0;                  /* a[1,6] =  0.0 */

			         /* Definindo a 2 linha */
		  	ia_1[7]  = 2, ja_11[7] = 1, ar_1[7]  =  0.0;               /* a[2,1] =  0.0 */ 
		    ia_1[8]  = 2, ja_1[8]  = 2, ar_1[8]  =  0.0;               /* a[2,2] =  0.0 */
		    ia_1[9]  = 2, ja_1[9]  = 3, ar_1[9]  =  0.0;               /* a[2,3] = -P2  */
		    ia_1[10] = 2, ja_1[10] = 4, ar_1[10] =  0.0;               /* a[2,3] =  0.0 */
		    ia_1[11] = 2, ja_1[11] = 5, ar_1[11] = -1.0;               /* a[2,3] =  0.0 */
		    ia_1[12] = 2, ja_1[12] = 6, ar_1[12] = -1.0;               /* a[2,3] = -1.0 */

                      /* Definindo a 3 linha */
		  	ia_1[13] = 3, ja_1[13]  = 1, ar_1[13]  =  1.0;             /* a[3,1] = -1.0 */ 
		    ia_1[14] = 3, ja_1[14]  = 2, ar_1[14]  =  1.0;             /* a[3,2] = -1.0 */
		    ia_1[15] = 3, ja_1[15]  = 3, ar_1[15]  =  0.0;             /* a[3,3] =  0.0 */
		    ia_1[16] = 3, ja_1[16]  = 4, ar_1[16]  =  0.0;             /* a[3,3] =  0.0 */
		    ia_1[17] = 3, ja_1[17]  = 5, ar_1[17]  =  0.0;             /* a[3,3] =  0.0 */
		    ia_1[18] = 3, ja_1[18]  = 6, ar_1[18]  =  0.0;             /* a[3,3] =  0.0 */

			          /* Definindo a 4 linha */
		  	ia_1[19] = 4, ja_1[19]  = 1, ar_1[19]  =  0.0;             /* a[4,1] =  0.0 */ 
		    ia_1[20] = 4, ja_1[20]  = 2, ar_1[20]  =  0.0;             /* a[4,2] =  0.0 */
		    ia_1[21] = 4, ja_1[21]  = 3, ar_1[21]  =  1.0;             /* a[4,3] = -1.0 */
		    ia_1[22] = 4, ja_1[22]  = 4, ar_1[22]  =  1.0;             /* a[4,3] = -1.0 */
		    ia_1[23] = 4, ja_1[23]  = 5, ar_1[23]  =  0.0;             /* a[4,3] =  0.0 */
		    ia_1[24] = 4, ja_1[24]  = 6, ar_1[24]  =  0.0;             /* a[4,3] =  0.0 */

		           	  /* Definindo a 5 linha */
		  	ia_1[25] = 5, ja_1[25]  = 1, ar_1[25]  = -1.0;             /* a[5,1] =  0.0 */ 
		    ia_1[26] = 5, ja_1[26]  = 2, ar_1[26]  = -1.0;             /* a[5,2] =  0.0 */
		    ia_1[27] = 5, ja_1[27]  = 3, ar_1[27]  =  0.0;             /* a[5,3] = -1.0 */
		    ia_1[28] = 5, ja_1[28]  = 4, ar_1[28]  =  0.0;             /* a[5,3] = -1.0 */
		    ia_1[29] = 5, ja_1[29]  = 5, ar_1[29]  =  0.0;             /* a[5,3] =  0.0 */
		    ia_1[30] = 5, ja_1[30]  = 6, ar_1[30]  =  0.0;             /* a[5,3] =  0.0 */

       	              /* Definindo a 6 linha */
		  	ia_1[31] = 6, ja_1[31]  = 1, ar_1[31]  =  0.0;             /* a[6,1] =  0.0 */ 
		    ia_1[32] = 6, ja_1[32]  = 2, ar_1[32]  =  0.0;             /* a[6,2] =  0.0 */
		    ia_1[33] = 6, ja_1[33]  = 3, ar_1[33]  = -1.0;             /* a[6,3] =  1.0 */
		    ia_1[34] = 6, ja_1[34]  = 4, ar_1[34]  = -1.0;             /* a[6,3] =  1.0 */
		    ia_1[35] = 6, ja_1[35]  = 5, ar_1[35]  =  0.0;             /* a[6,3] =  0.0 */
		    ia_1[36] = 6, ja_1[36]  = 6, ar_1[36]  =  0.0;             /* a[6,3] =  0.0 */
	
		  /*Carregando a matriz do coefiecientes */
		  glp_load_matrix(ld,36,ia_1,ja_1,ar_1);

		  /* Resolve o problema */
		  glp_simplex(ld,NULL);

          /* Recuperar e resolver e exibir os resultdos */
		  ALFA1_1X  = glp_get_obj_val(ld);
		  u_1[0]    = glp_get_col_prim(ld,1);
		  u_1[1]    = glp_get_col_prim(ld,2);
		  u_1[2]    = glp_get_col_prim(ld,3);
		  u_1[3]    = glp_get_col_prim(ld,4);
		  u_1[4]    = glp_get_col_prim(ld,5);
		  u_1[5]    = glp_get_col_prim(ld,6);

	   printf(" Problema Dual Interação : %d \n", j);
	   printf("ALFA1_1X = %g;u1_1 = %g;u2_1 = %g u3_1 = %g;u4_1 = %g,u5_1 = %g,u6_1 = %g\n\n",ALFA1_1X,u_1[0],u_1[1],u_1[2],u_1[3],u_1[4],u_1[5]);

		  /* Atualizando o valor de Q para ser verificado */
		  u1_1 = u_1[0];
		  u2_1 = u_1[1];
		  u3_1 = u_1[2];
		  u4_1 = u_1[3];
		  u5_1 = u_1[4];
		  u6_1 = u_1[5];

		 /* Atualizando a matriz dos coeficientes */
	    matriz_variavel_1[0][0] = (DEMANDAs2[0]+DEMANDAs2[1])*u1_1,matriz_variavel_1[0][1] = 0*u1_1      ,matriz_variavel_1[0][2] = 0*u1_1;
        matriz_variavel_1[1][0] = -TERMICAS*u2_1                  ,matriz_variavel_1[1][1] = 0*u2_1      ,matriz_variavel_1[1][2] = 0*u2_1;
		matriz_variavel_1[2][0] = (-VOL1 + VOLI1)*u3_1            ,matriz_variavel_1[2][1] = 0*u3_1      ,matriz_variavel_1[2][2] = 0*u3_1;
		matriz_variavel_1[3][0] = (-VOL2 + VOLI2)*u4_1            ,matriz_variavel_1[3][1] = 0*u4_1      ,matriz_variavel_1[3][2] = 0*u4_1;
	    matriz_variavel_1[4][0] = -VINH1*u5_1                     ,matriz_variavel_1[4][1] = -VTH1S1*u5_1,matriz_variavel_1[4][2] = -VVH1S1*u5_1;
		matriz_variavel_1[5][0] = -VINH2*u6_1                     ,matriz_variavel_1[5][1] = -VTH2S1*u6_1,matriz_variavel_1[5][2] = -VVH2S1*u6_1;
	   /*====================================================== FIM ========================================================================== */
		
		                                    /* CREANDO O PROBLEMA  DUAL PARA O CENÁRIO 2 */
		/* ===================================================== INICO ======================================================================= */
		  ld_2 = glp_create_prob();
		  glp_set_obj_dir(ld_2,GLP_MAX);

          /* Preenchimento dos dados do problema : 
		   * Número de linha(s) da matriz */
		  glp_add_rows(ld_2,6);
		  
		  /* Definindo os limitantes da(s) linhas (s)*/ 
		  glp_set_row_bnds(ld_2,1,GLP_UP,0.0,Cs2[0]);/* Custo associado a Hidroeletrica 1 vazão turbinada */
		  glp_set_row_bnds(ld_2,2,GLP_UP,0.0,Cs2[1]);/* Custo associado a Hidroeletrica 1 vazão vertida */
		  glp_set_row_bnds(ld_2,3,GLP_UP,0.0,Cs2[2]);/* Custo associado a Hidroeletrica 2 vazão turbinada */
		  glp_set_row_bnds(ld_2,4,GLP_UP,0.0,Cs2[3]);/* Custo associado a Hidroeletrica 2 vazão vertida */
		  glp_set_row_bnds(ld_2,5,GLP_UP,0.0,Cs2[4]);/* Custo associado a Termica 1 */
		  glp_set_row_bnds(ld_2,6,GLP_UP,0.0,Cs2[5]);/* Custo associado a Termica 2 */

		  /* Número de coluna(s) da matriz */
		  glp_add_cols(ld_2,6);

		  /* Defindo um limitante das coluns(s) default 0.0 */
		  glp_set_col_bnds(ld_2,1,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_2,2,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_2,3,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_2,4,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_2,5,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(ld_2,6,GLP_LO,0.0,0.0);

		  /* Definindo os coeficentes da função objetivo */
		  glp_set_obj_coef(ld_2,1,DEMANDAs2[0] + DEMANDAs2[1]);
		  glp_set_obj_coef(ld_2,2,-TERMICAS);
		  glp_set_obj_coef(ld_2,3,(-VOL1 + VOLI1));
		  glp_set_obj_coef(ld_2,4,(-VOL2 + VOLI2));
		  glp_set_obj_coef(ld_2,5,-VINH1 - VTH1S1 - VVH1S1);
		  glp_set_obj_coef(ld_2,6,-VINH2 - VTH2S1 - VVH2S1);

		  /* Preechimento dos valores da matriz das restrições */

		              /* Definindo a 1 linha */
		  	ia_2[1] = 1, ja_2[1] = 1, ar_2[1] =  PRODUTIBILIDADE[0];   /* a[1,1] = -P1  */ 
		    ia_2[2] = 1, ja_2[2] = 2, ar_2[2] =  0.0;                  /* a[1,2] =  0.0 */
		    ia_2[3] = 1, ja_2[3] = 3, ar_2[3] =  0.0;                  /* a[1,3] =  0.0 */
		    ia_2[4] = 1, ja_2[4] = 4, ar_2[4] =  PRODUTIBILIDADE[1];   /* a[1,4] =  0.0 */
		    ia_2[5] = 1, ja_2[5] = 5, ar_2[5] =  1.0;                  /* a[1,5] = -1.0 */
		    ia_2[6] = 1, ja_2[6] = 6, ar_2[6] =  1.0;                  /* a[1,6] =  0.0 */

			         /* Definindo a 2 linha */
		  	ia_2[7]  = 2, ja_2[7]  = 1, ar_2[7]  =  0.0;               /* a[2,1] =  0.0 */ 
		    ia_2[8]  = 2, ja_2[8]  = 2, ar_2[8]  =  0.0;               /* a[2,2] =  0.0 */
		    ia_2[9]  = 2, ja_2[9]  = 3, ar_2[9]  =  0.0;               /* a[2,3] = -P2  */
		    ia_2[10] = 2, ja_2[10] = 4, ar_2[10] =  0.0;               /* a[2,3] =  0.0 */
		    ia_2[11] = 2, ja_2[11] = 5, ar_2[11] = -1.0;               /* a[2,3] =  0.0 */
		    ia_2[12] = 2, ja_2[12] = 6, ar_2[12] = -1.0;               /* a[2,3] = -1.0 */

                      /* Definindo a 3 linha */
		  	ia_2[13] = 3, ja_2[13]  = 1, ar_2[13]  =  1.0;             /* a[3,1] = -1.0 */ 
		    ia_2[14] = 3, ja_2[14]  = 2, ar_2[14]  =  1.0;             /* a[3,2] = -1.0 */
		    ia_2[15] = 3, ja_2[15]  = 3, ar_2[15]  =  0.0;             /* a[3,3] =  0.0 */
		    ia_2[16] = 3, ja_2[16]  = 4, ar_2[16]  =  0.0;             /* a[3,3] =  0.0 */
		    ia_2[17] = 3, ja_2[17]  = 5, ar_2[17]  =  0.0;             /* a[3,3] =  0.0 */
		    ia_2[18] = 3, ja_2[18]  = 6, ar_2[18]  =  0.0;             /* a[3,3] =  0.0 */

			          /* Definindo a 4 linha */
		  	ia_2[19] = 4, ja_2[19]  = 1, ar_2[19]  =  0.0;             /* a[4,1] =  0.0 */ 
		    ia_2[20] = 4, ja_2[20]  = 2, ar_2[20]  =  0.0;             /* a[4,2] =  0.0 */
		    ia_2[21] = 4, ja_2[21]  = 3, ar_2[21]  =  1.0;             /* a[4,3] = -1.0 */
		    ia_2[22] = 4, ja_2[22]  = 4, ar_2[22]  =  1.0;             /* a[4,3] = -1.0 */
		    ia_2[23] = 4, ja_2[23]  = 5, ar_2[23]  =  0.0;             /* a[4,3] =  0.0 */
		    ia_2[24] = 4, ja_2[24]  = 6, ar_2[24]  =  0.0;             /* a[4,3] =  0.0 */

		           	  /* Definindo a 5 linha */
		  	ia_2[25] = 5, ja_2[25]  = 1, ar_2[25]  = -1.0;             /* a[5,1] =  0.0 */ 
		    ia_2[26] = 5, ja_2[26]  = 2, ar_2[26]  = -1.0;             /* a[5,2] =  0.0 */
		    ia_2[27] = 5, ja_2[27]  = 3, ar_2[27]  =  0.0;             /* a[5,3] = -1.0 */
		    ia_2[28] = 5, ja_2[28]  = 4, ar_2[28]  =  0.0;             /* a[5,3] = -1.0 */
		    ia_2[29] = 5, ja_2[29]  = 5, ar_2[29]  =  0.0;             /* a[5,3] =  0.0 */
		    ia_2[30] = 5, ja_2[30]  = 6, ar_2[30]  =  0.0;             /* a[5,3] =  0.0 */

       	              /* Definindo a 6 linha */
		  	ia_2[31] = 6, ja_2[31]  = 1, ar_2[31]  =  0.0;             /* a[6,1] =  0.0 */ 
		    ia_2[32] = 6, ja_2[32]  = 2, ar_2[32]  =  0.0;             /* a[6,2] =  0.0 */
		    ia_2[33] = 6, ja_2[33]  = 3, ar_2[33]  = -1.0;             /* a[6,3] =  1.0 */
		    ia_2[34] = 6, ja_2[34]  = 4, ar_2[34]  = -1.0;             /* a[6,3] =  1.0 */
		    ia_2[35] = 6, ja_2[35]  = 5, ar_2[35]  =  0.0;             /* a[6,3] =  0.0 */
		    ia_2[36] = 6, ja_2[36]  = 6, ar_2[36]  =  0.0;             /* a[6,3] =  0.0 */
	
		  /*Carregando a matriz do coefiecientes */
		  glp_load_matrix(ld,36,ia_2,ja_2,ar_2);

		  /* Resolve o problema */
		  glp_simplex(ld,NULL);

          /* Recuperar e resolver e exibir os resultdos */
		  ALFA2_2X  = glp_get_obj_val(ld);
		  u_2[0]    = glp_get_col_prim(ld,1);
		  u_2[1]    = glp_get_col_prim(ld,2);
		  u_2[2]    = glp_get_col_prim(ld,3);
		  u_2[3]    = glp_get_col_prim(ld,4);
		  u_2[4]    = glp_get_col_prim(ld,5);
		  u_2[5]    = glp_get_col_prim(ld,6);

       printf(" Problema Dual Cenário 2: Interação : %d \n", j);
  	   printf("ALFA2_2x = %g;u1_2 = %g;u2_2 = %g;u3_2 = %g;u4_2 = %g,u5_2 = %g,u6_2 = %g\n\n",ALFA2_2X,u_2[0],u_2[1],u_2[2],u_2[3],u_2[4],u_2[5]);

		  /* Atualizando o valor de Q para ser verificado */
		  u1_2 = u[0];
		  u2_2 = u[1];
		  u3_2 = u[2];
		  u4_2 = u[3];
		  u5_2 = u[4];
		  u6_2 = u[5];

		 /* Atualizando a matriz dos coeficientes */
	    matriz_variavel_2[0][0] = (DEMANDAs2[0]+DEMANDAs2[1])*u1_2,matriz_variavel_2[0][1] = 0*u1_2      ,matriz_variavel_1[0][2] = 0*u1_2;
        matriz_variavel_2[1][0] = -TERMICAS*u2_2                  ,matriz_variavel_2[1][1] = 0*u2_2      ,matriz_variavel_1[1][2] = 0*u2_2;
		matriz_variavel_2[2][0] = (-VOL1 + VOLI1)*u3_2            ,matriz_variavel_2[2][1] = 0*u3_2      ,matriz_variavel_1[2][2] = 0*u3_2;
		matriz_variavel_2[3][0] = (-VOL2 + VOLI2)*u4_2            ,matriz_variavel_2[3][1] = 0*u4_2      ,matriz_variavel_1[3][2] = 0*u4_2;
	    matriz_variavel_2[4][0] = -VINH1*u5_2                     ,matriz_variavel_2[4][1] = -VTH1S1*u5_2,matriz_variavel_1[4][2] = -VVH1S1*u5_2;
		matriz_variavel_2[5][0] = -VINH2*u6_2                     ,matriz_variavel_2[5][1] = -VTH2S1*u6_2,matriz_variavel_1[5][2] = -VVH2S1*u6_2;
	   /*===================================================== FIM =========================================================================== */
 
		                                  /* CREANDO O PROBLEMA PRIMAL */
		/*============================================ INICIO ================================================================================ */
		  lp = glp_create_prob();
		  glp_set_obj_dir(lp,GLP_MIN);

          /* Preenchimento dos dados do problema : 
		   * Número de linha(s) matriz */
		  glp_add_rows(lp,6 + j);

  		   /* Número de coluna(s) da matriz */
		  glp_add_cols(lp,6);

          /* Definindo os coeficentes da função objetivo */
		  glp_set_obj_coef(lp,1,Cs1[0]);                       /* Custo associado a vazão turbinada Hidroelétrica 1 no estágio 1 */
		  glp_set_obj_coef(lp,2,Cs1[1]);                       /* Custo associado a vazão vertida   Hidroelétrica 1 no estágio 1 */
		  glp_set_obj_coef(lp,3,Cs1[2]);                       /* Custo associado a vazão turbinada Hidroelétrica 2 no estágio 1 */
		  glp_set_obj_coef(lp,4,Cs1[3]);                       /* Custo associado a vazão turbinada Hidroelétrica 2 no estágio 1 */
		  glp_set_obj_coef(lp,5,Cs1[4]);                       /* Custo associado a termoelétrica 1 no estágio 1 */
		  glp_set_obj_coef(lp,6,Cs1[5]);                       /* Custo associado a termoelétrica 2 no estágio 1 */
		  glp_set_obj_coef(lp,7,probabilidade[0]);             /* Coefiente de alfa1 */
		  glp_set_obj_coef(lp,8,probabilidade[1]);             /* Coefiente de alfa2 */

          /* Definido o limites das colunas por default deixe com zero para a maioria dos problemas de progração Linear */
		  glp_set_col_bnds(lp,1,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,2,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,3,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,4,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,5,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,6,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,7,GLP_LO,0.0,0.0);
		  glp_set_col_bnds(lp,8,GLP_LO,0.0,0.0);

		  /* Preechendo a(s) coluna(s) com os valores que seram utilizados nas restrições */
		  if (j >= 1){
				  for (cj = 0; cj < 3; cj++){
						  for (ci = 0; ci < 6; ci++){
								  soma_1[cj][j-1] += matriz_variavel_1[ci][cj];
								  soma_2[cj][j-1] += matriz_variavel_2[ci][cj];
						  }
				  } 
				  for (cj = 3; cj < 6; cj++){
						  soma_1[cj][j-1] = 0;
						  soma_2[cj][j-1] = 0;
				  }
		  }

		 /* Os elemento do array soma[][] obtida acima são utilizados nas restrições, use somente para cada interação a mesma coluna j */

                       /* DEFININDO OS LIMITES DAS LINHAS PARA O CENARIO 1 */

         /*========================== INICIO ==================================== */
		      /* Inferiores:             Superiores: */
		 
 		 		/* Dados para a matriz das restrições */
		  inf_1[0]  = -100.0,         sup_1[0]  = soma_1[0][0];  /* use colunas iguais  */
		  inf_1[1]  = -100.0,         sup_1[1]  = soma_1[0][1];  /* use colunas iguais  */
		  inf_1[2]  = -100.0,         sup_1[2]  = soma_1[0][2];  /* use colunas iguais  */
		  inf_1[3]  = -100.0,         sup_1[3]  = soma_1[0][3];  /* use colunas iguais  */
		  inf_1[4]  = -100.0,         sup_1[4]  = soma_1[0][4];  /* use colunas iguais  */ 
		  inf_1[5]  = -100.0,         sup_1[5]  = soma_1[0][5];  /* use colunas iguais  */
		  inf_1[6]  = -100.0,         sup_1[6]  = soma_1[0][6];  /* use colunas iguais  */
		  inf_1[7]  = -100.0,         sup_1[7]  = soma_1[0][7];  /* use colunas iguais  */
		  inf_1[8]  = -100.0,         sup_1[8]  = soma_1[0][8];  /* use colunas iguais  */
		  inf_1[9]  = -100.0,         sup_1[9]  = soma_1[0][9];  /* use colunas iguais  */
		  inf_1[10] = -100.0,         sup_1[10] = soma_1[0][10]; /* use colunas iguais  */
		  inf_1[11] = -100.0,         sup_1[11] = soma_1[0][11]; /* use colunas iguais  */
		  inf_1[12] = -100.0,         sup_1[12] = soma_1[0][12]; /* use colunas iguais  */
		  inf_1[13] = -100.0,         sup_1[13] = soma_1[0][13]; /* use colunas iguais  */
		  inf_1[14] = -100.0,         sup_1[14] = soma_1[0][14]; /* use colunas iguais  */
		  inf_1[15] = -100.0,         sup_1[15] = soma_1[0][15]; /* use colunas iguais  */
		  inf_1[16] = -100.0,         sup_1[16] = soma_1[0][16]; /* use colunas iguais  */
		  inf_1[17] = -100.0,         sup_1[17] = soma_1[0][17]; /* use colunas iguais  */
		  inf_1[18] = -100.0,         sup_1[18] = soma_1[0][18]; /* use colunas iguais  */
		  inf_1[19] = -100.0,         sup_1[19] = soma_1[0][19]; /* use colunas iguais  */
		  inf_1[20] = -100.0,         sup_1[20] = soma_1[0][20]; /* use colunas iguais  */
		  inf_1[21] = -100.0,         sup_1[21] = soma_1[0][21]; /* use colunas iguais  */
		  inf_1[22] = -100.0,         sup_1[22] = soma_1[0][22]; /* use colunas iguais  */
		  inf_1[23] = -100.0,         sup_1[23] = soma_1[0][23]; /* use colunas iguais  */
		  inf_1[24] = -100.0,         sup_1[24] = soma_1[0][24]; /* use colunas iguais  */
		  inf_1[25] = -100.0,         sup_1[25] = soma_1[0][25]; /* use colunas iguais  */
		  inf_1[26] = -100.0,         sup_1[26] = soma_1[0][26]; /* use colunas iguais  */
		  inf_1[27] = -100.0,         sup_1[27] = soma_1[0][27]; /* use colunas iguais  */
		  inf_1[28] = -100.0,         sup_1[28] = soma_1[0][28]; /* use colunas iguais  */
		  inf_1[29] = -100.0,         sup_1[29] = soma_1[0][29]; /* use colunas iguais  */
		  inf_1[30] = -100.0,         sup_1[30] = soma_1[0][30]; /* use colunas iguais  */
 		/* ============================FIM===================================== */

		             /* DEFININDO OS LIMITES DAS LINHAS PARA O CENARIO 2 */

         /*========================== INICIO ========================================== */
		      /* Inferiores:             Superiores: */
		 
 		 		/* Dados para a matriz das restrições */
		  inf_2[0]  = -100.0,         sup_2[0]  = soma_2[0][0];  /* use colunas iguais  */
		  inf_2[1]  = -100.0,         sup_2[1]  = soma_2[0][1];  /* use colunas iguais  */
		  inf_2[2]  = -100.0,         sup_2[2]  = soma_2[0][2];  /* use colunas iguais  */
		  inf_2[3]  = -100.0,         sup_2[3]  = soma_2[0][3];  /* use colunas iguais  */
		  inf_2[4]  = -100.0,         sup_2[4]  = soma_2[0][4];  /* use colunas iguais  */ 
		  inf_2[5]  = -100.0,         sup_2[5]  = soma_2[0][5];  /* use colunas iguais  */
		  inf_2[6]  = -100.0,         sup_2[6]  = soma_2[0][6];  /* use colunas iguais  */
		  inf_2[7]  = -100.0,         sup_2[7]  = soma_2[0][7];  /* use colunas iguais  */
		  inf_2[8]  = -100.0,         sup_2[8]  = soma_2[0][8];  /* use colunas iguais  */
		  inf_2[9]  = -100.0,         sup_2[9]  = soma_2[0][9];  /* use colunas iguais  */
		  inf_2[10] = -100.0,         sup_2[10] = soma_2[0][10]; /* use colunas iguais  */
		  inf_2[11] = -100.0,         sup_2[11] = soma_2[0][11]; /* use colunas iguais  */
		  inf_2[12] = -100.0,         sup_2[12] = soma_2[0][12]; /* use colunas iguais  */
		  inf_2[13] = -100.0,         sup_2[13] = soma_2[0][13]; /* use colunas iguais  */
		  inf_2[14] = -100.0,         sup_2[14] = soma_2[0][14]; /* use colunas iguais  */
		  inf_2[15] = -100.0,         sup_2[15] = soma_2[0][15]; /* use colunas iguais  */
		  inf_2[16] = -100.0,         sup_2[16] = soma_2[0][16]; /* use colunas iguais  */
		  inf_2[17] = -100.0,         sup_2[17] = soma_2[0][17]; /* use colunas iguais  */
		  inf_2[18] = -100.0,         sup_2[18] = soma_2[0][18]; /* use colunas iguais  */
		  inf_2[19] = -100.0,         sup_2[19] = soma_2[0][19]; /* use colunas iguais  */
		  inf_2[20] = -100.0,         sup_2[20] = soma_2[0][20]; /* use colunas iguais  */
		  inf_2[21] = -100.0,         sup_2[21] = soma_2[0][21]; /* use colunas iguais  */
		  inf_2[22] = -100.0,         sup_2[22] = soma_2[0][22]; /* use colunas iguais  */
		  inf_2[23] = -100.0,         sup_2[23] = soma_2[0][23]; /* use colunas iguais  */
		  inf_2[24] = -100.0,         sup_2[24] = soma_2[0][24]; /* use colunas iguais  */
		  inf_2[25] = -100.0,         sup_2[25] = soma_2[0][25]; /* use colunas iguais  */
		  inf_2[26] = -100.0,         sup_2[26] = soma_2[0][26]; /* use colunas iguais  */
		  inf_2[27] = -100.0,         sup_2[27] = soma_2[0][27]; /* use colunas iguais  */
		  inf_2[28] = -100.0,         sup_2[28] = soma_2[0][28]; /* use colunas iguais  */
		  inf_2[29] = -100.0,         sup_2[29] = soma_2[0][29]; /* use colunas iguais  */
		  inf_2[30] = -100.0,         sup_2[30] = soma_2[0][30]; /* use colunas iguais  */
 		/* ============================FIM============================================= */

 
		  /* Acrescentando as restrições  em que o loop procura o ótimo */

		  /* Definindo os limitantes da linha 1*/ 
		  glp_set_row_bnds(lp,1,GLP_UP,-100.0,-DEMANDAs1[0]-DEMANDAs1[1]); 

		  /* Preechimento dos valores da matriz das restrições linha 1 */
		  	ia[1]  = 1, ja[1]  = 1, ar[1]  = -PRODUTIBILIDADE[0];               /* a[1,1] */
		    ia[2]  = 1, ja[2]  = 2, ar[2]  =  0.0;                              /* a[1,2] */
		    ia[3]  = 1, ja[3]  = 3, ar[3]  = -PRODUTIBILIDADE[1];               /* a[1,3] */
			ia[4]  = 1, ja[4]  = 4, ar[4]  =  0.0;                              /* a[1,4] */
		    ia[5]  = 1, ja[5]  = 5, ar[5]  = -1.0;                              /* a[1,5] */
		    ia[6]  = 1, ja[6]  = 6, ar[6]  = -1.0;                              /* a[1,6] */
 
		  /* Definindo os limitantes da linha 2 */ 
		  glp_set_row_bnds(lp,2,GLP_UP,-100,TERMICAS); 

		  /* Preechimento dos valores da matriz das restrições linha 2 */
		  	ia[7]   = 2, ja[7]   = 1, ar[7]   =  0.0;                          /* a[2,1] */
		    ia[8]   = 2, ja[8]   = 2, ar[8]   =  0.0;                          /* a[2,2] */
		    ia[9]   = 2, ja[9]   = 3, ar[9]   =  0.0;                          /* a[2,3] */
			ia[10]  = 2, ja[10]  = 4, ar[10]  =  0.0;                          /* a[2,4] */
		    ia[11]  = 2, ja[11]  = 5, ar[11]  =  1.0;                          /* a[2,5] */
		    ia[12]  = 2, ja[12]  = 6, ar[12]  =  1.0;                          /* a[2,6] */
 
		  /* Definindo os limitantes da linha 3*/ 
		  glp_set_row_bnds(lp,3,GLP_UP,-100.0,(VOL1 - VOLI1)); 

		  /* Preechimento dos valores da matriz das restrições linha 3 */
		  	ia[13]  = 3, ja[13]  = 1, ar[13]  = -1.0;                          /* a[3,1] */
		    ia[14]  = 3, ja[14]  = 2, ar[14]  = -1.0;                          /* a[3,2] */
		    ia[15]  = 3, ja[15]  = 3, ar[15]  =  0.0;                          /* a[3,3] */
			ia[16]  = 3, ja[16]  = 4, ar[16]  =  0.0;                          /* a[3,4] */
		    ia[17]  = 3, ja[17]  = 5, ar[17]  =  0.0;                          /* a[3,5] */
		    ia[18]  = 3, ja[18]  = 6, ar[18]  =  0.0;                          /* a[3,6] */
  
		  /* Definindo os limitantes da linha 4 */ 
		  glp_set_row_bnds(lp,4,GLP_UP,-100.0,(VOL2 - VOLI2)); 

		  /* Preechimento dos valores da matriz das restrições linha 4 */
		  	ia[19]  = 4, ja[19]  = 1, ar[19]  =  0.0;                          /* a[4,1] */
		    ia[20]  = 4, ja[20]  = 2, ar[20]  =  0.0;                          /* a[4,2] */
		    ia[21]  = 4, ja[21]  = 3, ar[21]  = -1.0;                          /* a[4,3] */
			ia[22]  = 4, ja[22]  = 4, ar[22]  = -1.0;                          /* a[4,4] */
		    ia[23]  = 4, ja[23]  = 5, ar[23]  =  0.0;                          /* a[4,5] */
		    ia[24]  = 4, ja[24]  = 6, ar[24]  =  0.0;                          /* a[4,6] */
  
		   /* Definindo os limitantes da linha 5 */ 
		  glp_set_row_bnds(lp,5,GLP_UP,-100.0,VINH1); 

		  /* Preechimento dos valores da matriz das restrições linha 5 */
		  	ia[25]  = 5, ja[25]  = 1, ar[25]  =  1.0;                          /* a[5,1] */
		    ia[26]  = 5, ja[26]  = 2, ar[26]  =  1.0;                          /* a[5,2] */
		    ia[27]  = 5, ja[27]  = 3, ar[27]  =  0.0;                          /* a[5,3] */
			ia[28]  = 5, ja[28]  = 4, ar[28]  =  0.0;                          /* a[5,4] */
		    ia[29]  = 5, ja[29]  = 5, ar[29]  =  0.0;                          /* a[5,5] */
		    ia[30]  = 5, ja[30]  = 6, ar[30]  =  0.0;                          /* a[5,6] */
  
		  /* Definindo os limitantes da linha 6 */ 
		  glp_set_row_bnds(lp,6,GLP_UP,-100.0,VINH2); 

		  /* Preechimento dos valores da matriz das restrições linha 6 */
		  	ia[31]  = 6, ja[31]  = 1, ar[31]  =  0.0;                          /* a[6,1] */
		    ia[32]  = 6, ja[32]  = 2, ar[32]  =  0.0;                          /* a[6,2] */
		    ia[33]  = 6, ja[33]  = 3, ar[33]  =  1.0;                          /* a[6,3] */
			ia[34]  = 6, ja[34]  = 4, ar[34]  =  1.0;                          /* a[6,4] */
		    ia[35]  = 6, ja[35]  = 5, ar[35]  =  0.0;                          /* a[6,5] */
		    ia[36]  = 6, ja[36]  = 6, ar[36]  =  0.0;                          /* a[6,6] */

		  /* Restrição : 01 */
		  if (j >= 1){

		   /* Definindo os limitantes da linha 7*/ 
		  glp_set_row_bnds(lp,7,GLP_UP,inf_1[0],-sup_1[0]); 

		  /* Preechimento dos valores da matriz das restrições linha 7 */
		  	ia[37]  = 7, ja[37]  = 1, ar[37]  =  soma_1[1][0];                  /* a[7,1] */
		    ia[38]  = 7, ja[38]  = 2, ar[38]  =  soma_1[2][0];                  /* a[7,2] */
		    ia[39]  = 7, ja[39]  = 3, ar[39]  =  soma_1[3][0];                  /* a[7,3] */
			ia[40]  = 7, ja[40]  = 4, ar[40]  =  soma_1[4][0];                  /* a[7,4] */
		    ia[41]  = 7, ja[41]  = 5, ar[41]  =  soma_1[5][0];                  /* a[7,5] */
		    ia[42]  = 7, ja[42]  = 6, ar[42]  = -1.0;                           /* a[7,6] */ 

		  /* Definindo os limitantes da linha 8*/ 
		  glp_set_row_bnds(lp,8,GLP_UP,inf_2[0],-sup_2[0]); 

		  /* Preechimento dos valores da matriz das restrições linha 7 */
		  	ia[43]  = 8, ja[43]  = 1, ar[43]  =  soma_2[1][0];                  /* a[8,1] */
		    ia[44]  = 8, ja[44]  = 2, ar[44]  =  soma_2[2][0];                  /* a[8,2] */
		    ia[45]  = 8, ja[45]  = 3, ar[45]  =  soma_2[3][0];                  /* a[8,3] */
			ia[46]  = 8, ja[46]  = 4, ar[46]  =  soma_2[4][0];                  /* a[8,4] */
		    ia[47]  = 8, ja[47]  = 5, ar[47]  =  soma_2[5][0];                  /* a[8,5] */
		    ia[48]  = 8, ja[48]  = 6, ar[48]  = -1.0;                           /* a[8,6] */ 
		  }    

		  /* Restrição : 02 */
		  if (j >= 2){

		   /* Definindo os limitantes da linha 9*/ 
		  glp_set_row_bnds(lp,9,GLP_UP,-100,0.0); 

		  /* Preechimento dos valores da matriz das restrições linha 9 */
		  	ia[49]  = 9, ja[49]  = 1, ar[49]  =  DEMANDAs2_1[0];               /* a[9,1] */
		    ia[50]  = 9, ja[50]  = 2, ar[50]  =  0.0;                          /* a[9,2] */
		    ia[51]  = 9, ja[51]  = 3, ar[51]  =  0.0;                          /* a[9,3] */
			ia[52]  = 9, ja[52]  = 4, ar[52]  =  0.0;                          /* a[9,4] */
		    ia[53]  = 9, ja[53]  = 5, ar[53]  =  0.0;                          /* a[9,5] */
		    ia[54]  = 9, ja[54]  = 6, ar[54]  =  0.0;                          /* a[9,6] */ 

		  /* Definindo os limitantes da linha 10*/ 
		  glp_set_row_bnds(lp,10,GLP_UP,-100,0.0); 

		  /* Preechimento dos valores da matriz das restrições linha 10 */
		  	ia[55]  = 10, ja[55]  = 1, ar[55]  =  DEMANDAs2_2[0];             /* a[10,1] */
		    ia[56]  = 10, ja[56]  = 2, ar[56]  =  0.0;                        /* a[10,2] */
		    ia[57]  = 10, ja[57]  = 3, ar[57]  =  0.0;                        /* a[10,3] */
			ia[58]  = 10, ja[58]  = 4, ar[58]  =  0.0;                        /* a[10,4] */
		    ia[59]  = 10, ja[59]  = 5, ar[59]  =  0.0;                        /* a[10,5] */
		    ia[60]  = 10, ja[60]  = 6, ar[60]  =  0.0;                        /* a[10,6] */ 
		  }   

		  /* Restrição : 03 */
		  if (j >= 3){

		   /* Definindo os limitantes da linha 11*/ 
		  glp_set_row_bnds(lp,11,GLP_UP,inf_1[1],-sup_1[1]); 

		  /* Preechimento dos valores da matriz das restrições linha 11 */
		  	ia[61]  = 11, ja[61]  = 1, ar[61]  =  soma_1[1][1];               /* a[11,1] */
		    ia[62]  = 11, ja[62]  = 2, ar[62]  =  soma_1[2][1];               /* a[11,2] */
		    ia[63]  = 11, ja[63]  = 3, ar[63]  =  soma_1[3][1];               /* a[11,3] */
			ia[64]  = 11, ja[64]  = 4, ar[64]  =  soma_1[4][1];               /* a[11,4] */
		    ia[65]  = 11, ja[65]  = 5, ar[65]  =  soma_1[5][1];               /* a[11,5] */
		    ia[66]  = 11, ja[66]  = 6, ar[66]  = -1.0;                        /* a[11,6] */ 

		   	/* Definindo os limitantes da linha 12*/ 
		  glp_set_row_bnds(lp,12,GLP_UP,inf_2[1],-sup_2[1]); 

		  /* Preechimento dos valores da matriz das restrições linha 12 */
		  	ia2[67]  = 12, ja[67]  = 1, ar[67]  =  soma_2[1][1];              /* a[12,1] */
		    ia2[68]  = 12, ja[68]  = 2, ar[68]  =  soma_2[2][1];              /* a[12,2] */
		    ia2[69]  = 12, ja[69]  = 3, ar[69]  =  soma_2[3][1];              /* a[12,3] */
			ia2[70]  = 12, ja[70]  = 4, ar[70]  =  soma_2[4][1];              /* a[12,4] */
		    ia2[71]  = 12, ja[71]  = 5, ar[71]  =  soma_2[5][1];              /* a[12,5] */
		    ia2[72]  = 12, ja[72]  = 6, ar[72]  = -1.0;                       /* a[12,6] */ 
		  }   

		  /* Restrição : 04 */
		  if (j >= 4){

		   /* Definindo os limitantes da linha 13*/ 
		  glp_set_row_bnds(lp,13,GLP_UP,-100.0,0.0); 

		  /* Preechimento dos valores da matriz das restrições linha 13 */
		  	ia[73]  = 13, ja[73]  = 1, ar[73]  =  0.0;                     /* a[13,1] */
		    ia[74]  = 13, ja[74]  = 2, ar[74]  =  DEMANDAs2_1[1];;         /* a[13,2] */
		    ia[75]  = 13, ja[75]  = 3, ar[75]  =  0.0;                     /* a[13,3] */
			ia[76]  = 13, ja[76]  = 4, ar[76]  =  0.0;                     /* a[13,4] */
		    ia[77]  = 13, ja[77]  = 5, ar[77]  =  0.0;                     /* a[13,5] */
		    ia[78]  = 13, ja[78]  = 6, ar[78]  =  0.0;                     /* a[13,6] */

			/* Definindo os limitantes da linha 11*/ 
		  glp_set_row_bnds(lp,14,GLP_UP,-100.0,0.0); 

		  /* Preechimento dos valores da matriz das restrições linha 10 */
		  	ia[79]  = 14, ja[79]  = 1, ar[79]  =  0.0;                     /* a[14,1] */
		    ia[80]  = 14, ja[80]  = 2, ar[80]  =  DEMANDAs2_2[1];          /* a[14,2] */
		    ia[81]  = 14, ja[81]  = 3, ar[81]  =  0.0;                     /* a[14,3] */
			ia[82]  = 14, ja[82]  = 4, ar[82]  =  0.0;                     /* a[14,4] */
		    ia[83]  = 14, ja[83]  = 5, ar[83]  =  0.0;                     /* a[14,5] */
		    ia[84]  = 14, ja[84]  = 6, ar[84]  =  0.0;                     /* a[14,6] */ 

		  }   

		 /* Restrição : 05 */
		 if (j >= 5){

		   /* Definindo os limitantes da linha 11*/ 
		  glp_set_row_bnds(lp,15,GLP_UP,inf_1[2],-sup_1[2]); 

		  /* Preechimento dos valores da matriz das restrições linha 11 */
		  	ia[85]  = 15, ja[85]  = 1, ar[85]  =  soma_1[1][2];             /* a[15,1] */
		    ia[86]  = 15, ja[86]  = 2, ar[86]  =  soma_1[2][2];             /* a[15,2] */
		    ia[87]  = 15, ja[87]  = 3, ar[87]  =  soma_1[3][2];             /* a[15,3] */
			ia[88]  = 15, ja[88]  = 4, ar[88]  =  soma_1[4][2];             /* a[15,4] */
		    ia[89]  = 15, ja[89]  = 5, ar[89]  =  soma_1[5][2];             /* a[15,5] */
		    ia[90]  = 15, ja[90]  = 6, ar[90]  =  -1.0;                     /* a[15,6] */ 

			/* Definindo os limitantes da linha 11*/ 
		  glp_set_row_bnds(lp,16,GLP_UP,inf_2[2],-sup_2[2]); 

		  /* Preechimento dos valores da matriz das restrições linha 11 */
		  	ia[91]  = 16, ja[91]  = 1, ar[91]  =  soma_2[1][2];             /* a[16,1] */
		    ia[92]  = 16, ja[92]  = 2, ar[92]  =  soma_2[2][2];             /* a[16,2] */
		    ia[93]  = 16, ja[93]  = 3, ar[93]  =  soma_2[3][2];             /* a[16,3] */
			ia[94]  = 16, ja[94]  = 4, ar[94]  =  soma_2[4][2];             /* a[16,4] */
		    ia[95]  = 16, ja[95]  = 5, ar[95]  =  soma_2[5][2];             /* a[16,5] */
		    ia[96]  = 16, ja[96]  = 6, ar[96]  =  -1.0;                     /* a[16,6] */ 

		  }

		 /* Restrição : 06 */
		 if (j >= 6){

		   /* Definindo os limitantes da linha 12*/ 
		  glp_set_row_bnds(lp,17,GLP_UP,-100.0,0.0); 

		  /* Preechimento dos valores da matriz das restrições linha 12 */
		  	ia[97]   = 17, ja[97]  = 1, ar[97]   =  0.0;                   /* a[17,1] */
		    ia[98]   = 17, ja[98]  = 2, ar[98]   =  0.0;                   /* a[17,2] */
		    ia[99]   = 17, ja[99]  = 3, ar[99]   = -VOL1 + VOLI1_1;        /* a[17,3] */
			ia[100]  = 17, ja[100] = 4, ar[100]  =  0.0;                   /* a[17,4] */
		    ia[101]  = 17, ja[101] = 5, ar[101]  =  0.0;                   /* a[17,5] */
		    ia[102]  = 17, ja[102] = 7, ar[102]  =  0.0;                   /* a[17,6] */ 

	       /* Definindo os limitantes da linha 12*/ 
		  glp_set_row_bnds(lp,18,GLP_UP,-100.0,0.0); 

		  /* Preechimento dos valores da matriz das restrições linha 12 */
		  	ia[103]  = 18, ja[103]  = 1, ar[103]  =  0.0;                   /* a[18,1] */
		    ia[104]  = 18, ja[104]  = 2, ar[104]  =  0.0;                   /* a[18,2] */
		    ia[105]  = 18, ja[105]  = 3, ar[105]  = -VOL1 + VOLI1_2;        /* a[18,3] */
			ia[106]  = 18, ja[106]  = 4, ar[106]  =  0.0;                   /* a[18,4] */
		    ia[107]  = 18, ja[107]  = 5, ar[107]  =  0.0;                   /* a[18,5] */
		    ia[108]  = 18, ja[108]  = 6, ar[108]  =  0.0;                   /* a[18,6] */ 

		  }

		 /* Restrição : 07 */
		 if (j >= 7){

		   /* Definindo os limitantes da linha 13*/ 
		  glp_set_row_bnds(lp,19,GLP_UP,inf_1[3],-sup_1[3]); 

		  /* Preechimento dos valores da matriz das restrições linha 13 */
		  	ia[109]  = 19, ja[109]  = 1, ar[109]  =  soma_1[1][3];          /* a[19,1] */
		    ia[110]  = 19, ja[100]  = 2, ar[110]  =  soma_1[2][3];          /* a[19,2] */
		    ia[111]  = 19, ja[111]  = 3, ar[111]  =  soma_1[3][3];          /* a[19,3] */
			ia[112]  = 19, ja[112]  = 4, ar[112]  =  soma_1[4][3];          /* a[19,4] */
		    ia[113]  = 19, ja[113]  = 5, ar[113]  =  soma_1[5][3];          /* a[19,5] */
		    ia[114]  = 19, ja[114]  = 6, ar[114]  =  -1.0;                  /* a[19,6] */ 
		  }

		 /* Restrição : 08 */
		 if (j >= 8){

		   /* Definindo os limitantes da linha 14*/ 
		  glp_set_row_bnds(lp,14,GLP_UP,-100.0,0.0); 

		  /* Preechimento dos valores da matriz das restrições linha 14 */
		  	ia[79]  = 14, ja[79]  = 1, ar[79]  =  0.0;                    /* a[14,1] */
		    ia[80]  = 14, ja[80]  = 2, ar[80]  =  0.0;                    /* a[14,2] */
		    ia[81]  = 14, ja[81]  = 3, ar[81]  =  0.0;                    /* a[14,3] */
			ia[82]  = 14, ja[82]  = 4, ar[82]  = -VOL2 + VOLI2;           /* a[14,4] */
		    ia[83]  = 14, ja[83]  = 5, ar[83]  =  0.0;                    /* a[14,5] */
		    ia[84]  = 14, ja[84]  = 6, ar[84]  =  0.0;                    /* a[14,6] */ 
		  }

		 /* restrição : 09 */
		 if (j >= 9){

		   /* definindo os limitantes da linha 15*/ 
		  glp_set_row_bnds(lp,15,GLP_UP,inf[4],-sup[4]); 

		  /* preechimento dos valores da matriz das restrições linha 15 */
		  	ia[85]  = 15, ja[85]  = 1, ar[85]  =  soma[1][4];             /* a[15,1] */
		    ia[86]  = 15, ja[86]  = 2, ar[86]  =  soma[2][4];             /* a[15,2] */
		    ia[87]  = 15, ja[87]  = 3, ar[87]  =  soma[3][4];             /* a[15,3] */
			ia[88]  = 15, ja[88]  = 4, ar[88]  =  soma[4][4];             /* a[15,4] */
		    ia[89]  = 15, ja[89]  = 5, ar[89]  =  soma[5][4];             /* a[15,5] */
		    ia[90]  = 15, ja[90]  = 6, ar[90]  =  -1.0;                   /* a[15,6] */ 
		  }
		  
		 /* Restrição : 10 */
		 if (j >= 10){

		   /* Definindo os limitantes da linha 16*/ 
		  glp_set_row_bnds(lp,16,GLP_UP,-100.0,VINH1); 

		  /* Preechimento dos valores da matriz das restrições linha 16 */
		  	ia[91]  = 16, ja[91]  = 1, ar[91]  =  -1.0;                    /* a[16,1] */
		    ia[92]  = 16, ja[92]  = 2, ar[92]  =  -1.0;                    /* a[16,2] */
		    ia[93]  = 16, ja[93]  = 3, ar[93]  =   0.0;                    /* a[16,3] */
			ia[94]  = 16, ja[94]  = 4, ar[94]  =   0.0;                    /* a[16,4] */
		    ia[95]  = 16, ja[95]  = 5, ar[95]  =   0.0;                    /* a[16,5] */
		    ia[96]  = 16, ja[96]  = 6, ar[96]  =   0.0;                    /* a[16,6] */ 
		  }

		 /* Restrição : 11 */
		 if (j >= 11){

		   /* Definindo os limitantes da linha 17*/ 
		  glp_set_row_bnds(lp,17,GLP_UP,inf[5],-sup[5]); 

		  /* Preechimento dos valores da matriz das restrições linha 17 */
		  	ia[97]   = 17, ja[97]   = 1, ar[97]  =  soma[1][5];           /* a[17,1] */
		    ia[98]   = 17, ja[98]   = 2, ar[98]  =  soma[2][5];           /* a[17,2] */
		    ia[99]   = 17, ja[99]   = 3, ar[99]  =  soma[3][5];           /* a[17,3] */
			ia[100]  = 17, ja[100]  = 4, ar[100] =  soma[4][5];           /* a[17,4] */
		    ia[101]  = 17, ja[101]  = 5, ar[101] =  soma[5][5];           /* a[17,5] */
		    ia[102]  = 17, ja[102]  = 6, ar[102] =  -1.0;                 /* a[17,6] */ 
		  }

		 /* Restrição : 12 */
		 if (j >= 12){

		   /* Definindo os limitantes da linha 18*/ 
		  glp_set_row_bnds(lp,18,GLP_UP,-100.0,VINH2); 

		  /* Preechimento dos valores da matriz das restrições linha 18 */
		  	ia[103]  = 18, ja[103]  = 1, ar[103] =   0.0;                /* a[18,1] */
		    ia[104]  = 18, ja[104]  = 2, ar[104] =   0.0;                /* a[18,2] */
		    ia[105]  = 18, ja[105]  = 3, ar[105] =  -1.0;                /* a[18,3] */
			ia[106]  = 18, ja[106]  = 4, ar[106] =  -1.0;                /* a[18,4] */
		    ia[107]  = 18, ja[107]  = 5, ar[107] =   0.0;                /* a[18,5] */
		    ia[108]  = 18, ja[108]  = 6, ar[108] =   0.0;                /* a[18,6] */ 
		  }

		 /* Restrição : 13 */
		 if (j >= 13){

		   /* Definindo os limitantes da linha 19*/ 
		  glp_set_row_bnds(lp,19,GLP_UP,inf[5],-sup[5]); 

		  /* Preechimento dos valores da matriz das restrições linha 19 */
		  	ia[109]  = 19, ja[109]  = 1, ar[109] =  soma[1][6];           /* a[19,1] */
		    ia[110]  = 19, ja[110]  = 2, ar[110] =  soma[2][6];           /* a[19,2] */
		    ia[111]  = 19, ja[111]  = 3, ar[111] =  soma[3][6];           /* a[19,3] */
			ia[112]  = 19, ja[112]  = 4, ar[112] =  soma[4][6];           /* a[19,4] */
		    ia[113]  = 19, ja[113]  = 5, ar[113] =  soma[5][6];           /* a[19,5] */
		    ia[114]  = 19, ja[114]  = 6, ar[114] =  -1.0;                 /* a[19,6] */ 
		  }

		 /* Restrição : 14 */
		 if (j >= 14){

		   /* Definindo os limitantes da linha 20*/ 
		  glp_set_row_bnds(lp,20,GLP_UP,inf[7],-sup[7]); 

		  /* Preechimento dos valores da matriz das restrições linha 20 */
		  	ia[115]  = 20, ja[115]  = 1, ar[115] =  soma[1][7];           /* a[20,1] */
		    ia[116]  = 20, ja[116]  = 2, ar[116] =  soma[2][7];           /* a[20,2] */
		    ia[117]  = 20, ja[117]  = 3, ar[117] =  soma[3][7];           /* a[20,3] */
			ia[118]  = 20, ja[118]  = 4, ar[118] =  soma[4][7];           /* a[20,4] */
		    ia[119]  = 20, ja[119]  = 5, ar[119] =  soma[5][7];           /* a[20,5] */
		    ia[120]  = 20, ja[120]  = 6, ar[120] =  -1.0;                 /* a[20,6] */ 
		  }

		 /* Restrição : 15 */
		 if (j >= 15){

		   /* Definindo os limitantes da linha 20*/ 
		  glp_set_row_bnds(lp,21,GLP_UP,inf[8],-sup[8]); 

		  /* Preechimento dos valores da matriz das restrições linha 21 */
		  	ia[121]  = 21, ja[121]  = 1, ar[121] =  soma[1][8];           /* a[21,1] */
		    ia[122]  = 21, ja[122]  = 2, ar[122] =  soma[2][8];           /* a[21,2] */
		    ia[123]  = 21, ja[123]  = 3, ar[123] =  soma[3][8];           /* a[21,3] */
			ia[124]  = 21, ja[124]  = 4, ar[124] =  soma[4][8];           /* a[21,4] */
		    ia[125]  = 21, ja[125]  = 5, ar[125] =  soma[5][8];           /* a[21,5] */
		    ia[126]  = 21, ja[126]  = 6, ar[126] =  -1.0;                 /* a[21,6] */ 
		  }

		 /* Restrição : 16 */
		 if (j >= 16){

		   /* Definindo os limitantes da linha 22*/ 
		  glp_set_row_bnds(lp,22,GLP_UP,inf[9],-sup[9]); 

		  /* Preechimento dos valores da matriz das restrições linha 22 */
		  	ia[127]  = 22, ja[127]  = 1, ar[127] =  soma[1][9];           /* a[22,1] */
		    ia[128]  = 22, ja[128]  = 2, ar[128] =  soma[2][9];           /* a[22,2] */
		    ia[129]  = 22, ja[129]  = 3, ar[129] =  soma[3][9];           /* a[22,3] */
			ia[130]  = 22, ja[130]  = 4, ar[130] =  soma[4][9];           /* a[22,4] */
		    ia[131]  = 22, ja[131]  = 5, ar[131] =  soma[5][9];           /* a[22,5] */
		    ia[132]  = 22, ja[132]  = 6, ar[132] =  -1.0;                 /* a[22,6] */ 
		  }

		 /* Restrição : 17 */
		 if (j >= 17){

		   /* Definindo os limitantes da linha 23*/ 
		  glp_set_row_bnds(lp,23,GLP_UP,inf[10],-sup[10]); 

		  /* Preechimento dos valores da matriz das restrições linha 23 */
		  	ia[133]  = 23, ja[133]  = 1, ar[133] =  soma[1][10];           /* a[23,1] */
		    ia[134]  = 23, ja[134]  = 2, ar[134] =  soma[2][10];           /* a[23,2] */
		    ia[135]  = 23, ja[135]  = 3, ar[135] =  soma[3][10];           /* a[23,3] */
			ia[136]  = 23, ja[136]  = 4, ar[136] =  soma[4][10];           /* a[23,4] */
		    ia[137]  = 23, ja[137]  = 5, ar[137] =  soma[5][10];           /* a[23,5] */
		    ia[138]  = 23, ja[138]  = 6, ar[138] =  -1.0;                  /* a[23,6] */ 
		  }

		 /* Restrição : 18 */
		 if (j >= 18){

		   /* Definindo os limitantes da linha 24*/ 
		  glp_set_row_bnds(lp,24,GLP_UP,inf[11],-sup[11]); 

		  /* Preechimento dos valores da matriz das restrições linha 23 */
		  	ia[139]  = 24, ja[139]  = 1, ar[139] =  soma[1][11];           /* a[24,1] */
		    ia[140]  = 24, ja[140]  = 2, ar[140] =  soma[2][11];           /* a[24,2] */
		    ia[141]  = 24, ja[141]  = 3, ar[141] =  soma[3][11];           /* a[24,3] */
			ia[142]  = 24, ja[142]  = 4, ar[142] =  soma[4][11];           /* a[24,4] */
		    ia[143]  = 24, ja[143]  = 5, ar[143] =  soma[5][11];           /* a[24,5] */
		    ia[144]  = 24, ja[144]  = 6, ar[144] =  -1.0;                  /* a[24,6] */ 
		  }

		 /* Restrição : 19 */
		 if (j >= 19){

		   /* Definindo os limitantes da linha 25*/ 
		  glp_set_row_bnds(lp,25,GLP_UP,inf[12],-sup[12]); 

		  /* Preechimento dos valores da matriz das restrições linha 24 */
		  	ia[145]  = 25, ja[145]  = 1, ar[145] =  soma[1][12];           /* a[25,1] */
		    ia[146]  = 25, ja[146]  = 2, ar[146] =  soma[2][12];           /* a[25,2] */
		    ia[147]  = 25, ja[147]  = 3, ar[147] =  soma[3][12];           /* a[25,3] */
			ia[148]  = 25, ja[148]  = 4, ar[148] =  soma[4][12];           /* a[25,4] */
		    ia[149]  = 25, ja[149]  = 5, ar[149] =  soma[5][12];           /* a[25,5] */
		    ia[150]  = 25, ja[150]  = 6, ar[150] =  -1.0;                  /* a[25,6] */ 
		  }

		 /* Restrição : 20 */
		 if (j >= 20){

		   /* Definindo os limitantes da linha 26*/ 
		  glp_set_row_bnds(lp,26,GLP_UP,inf[13],-sup[13]); 

		  /* Preechimento dos valores da matriz das restrições linha 26 */
		  	ia[151]  = 26, ja[151]  = 1, ar[151] =  soma[1][13];           /* a[26,1] */
		    ia[152]  = 26, ja[152]  = 2, ar[152] =  soma[2][13];           /* a[26,2] */
		    ia[153]  = 26, ja[153]  = 3, ar[153] =  soma[3][13];           /* a[26,3] */
			ia[154]  = 26, ja[154]  = 4, ar[154] =  soma[4][13];           /* a[26,4] */
		    ia[155]  = 26, ja[155]  = 5, ar[155] =  soma[5][13];           /* a[26,5] */
		    ia[156]  = 26, ja[156]  = 6, ar[156] =  -1.0;                  /* a[26,6] */ 
		  }

		 /* Restrição : 21 */
		 if (j >= 21){

		   /* Definindo os limitantes da linha 27*/ 
		  glp_set_row_bnds(lp,27,GLP_UP,inf[14],-sup[14]); 

		  /* Preechimento dos valores da matriz das restrições linha 27 */
		  	ia[157]  = 27, ja[157]  = 1, ar[157] =  soma[1][14];           /* a[27,1] */
		    ia[158]  = 27, ja[158]  = 2, ar[158] =  soma[2][14];           /* a[27,2] */
		    ia[159]  = 27, ja[159]  = 3, ar[159] =  soma[3][14];           /* a[27,3] */
			ia[160]  = 27, ja[160]  = 4, ar[160] =  soma[4][14];           /* a[27,4] */
		    ia[161]  = 27, ja[161]  = 5, ar[161] =  soma[5][14];           /* a[27,5] */
		    ia[162]  = 27, ja[162]  = 6, ar[162] =  -1.0;                  /* a[27,6] */ 
		 }

		 /* Restrição : 22 */
		 if (j >= 22){

		   /* Definindo os limitantes da linha 28*/ 
		  glp_set_row_bnds(lp,28,GLP_UP,inf[15],-sup[15]); 

		  /* Preechimento dos valores da matriz das restrições linha 28 */
		  	ia[163]  = 28, ja[163]  = 1, ar[163] =  soma[1][15];           /* a[28,1] */
		    ia[164]  = 28, ja[164]  = 2, ar[164] =  soma[2][15];           /* a[28,2] */
		    ia[165]  = 28, ja[165]  = 3, ar[165] =  soma[3][15];           /* a[28,3] */
			ia[166]  = 28, ja[166]  = 4, ar[166] =  soma[4][15];           /* a[28,4] */
		    ia[167]  = 28, ja[167]  = 5, ar[167] =  soma[5][15];           /* a[28,5] */
		    ia[168]  = 28, ja[168]  = 6, ar[168] =  -1.0;                  /* a[28,6] */ 
		 }

		 /* Restrição : 23 */
		 if (j >= 23){

		   /* Definindo os limitantes da linha 29*/ 
		  glp_set_row_bnds(lp,29,GLP_UP,inf[16],-sup[16]); 

		  /* Preechimento dos valores da matriz das restrições linha 29 */
		  	ia[169]  = 29, ja[169]  = 1, ar[169] =  soma[1][16];           /* a[29,1] */
		    ia[170]  = 29, ja[170]  = 2, ar[170] =  soma[2][16];           /* a[29,2] */
		    ia[171]  = 29, ja[171]  = 3, ar[171] =  soma[3][16];           /* a[29,3] */
			ia[172]  = 29, ja[172]  = 4, ar[172] =  soma[4][16];           /* a[29,4] */
		    ia[173]  = 29, ja[173]  = 5, ar[173] =  soma[5][16];           /* a[29,5] */
		    ia[174]  = 29, ja[174]  = 6, ar[174] =  -1.0;                  /* a[29,6] */ 
		 }

		 /* Restrição : 24 */
		 if (j >= 24){

		   /* Definindo os limitantes da linha 30*/ 
		  glp_set_row_bnds(lp,30,GLP_UP,inf[17],-sup[17]); 

		  /* Preechimento dos valores da matriz das restrições linha 30 */
		  	ia[175]  = 30, ja[175]  = 1, ar[175] =  soma[1][17];           /* a[30,1] */
		    ia[176]  = 30, ja[176]  = 2, ar[176] =  soma[2][17];           /* a[30,2] */
		    ia[177]  = 30, ja[177]  = 3, ar[177] =  soma[3][17];           /* a[30,3] */
			ia[178]  = 30, ja[178]  = 4, ar[178] =  soma[4][17];           /* a[30,4] */
		    ia[179]  = 30, ja[179]  = 5, ar[179] =  soma[5][17];           /* a[30,5] */
		    ia[180]  = 30, ja[180]  = 6, ar[180] =  -1.0;                  /* a[30,6] */ 
		 }

		 /* Restrição : 25 */
		 if (j >= 25){

		   /* Definindo os limitantes da linha 31*/ 
		  glp_set_row_bnds(lp,31,GLP_UP,inf[18],-sup[18]); 

		  /* Preechimento dos valores da matriz das restrições linha 31 */
		  	ia[181]  = 31, ja[181]  = 1, ar[181] =  soma[1][18];           /* a[31,1] */
		    ia[182]  = 31, ja[182]  = 2, ar[182] =  soma[2][18];           /* a[31,2] */
		    ia[183]  = 31, ja[183]  = 3, ar[183] =  soma[3][18];           /* a[31,3] */
			ia[184]  = 31, ja[184]  = 4, ar[184] =  soma[4][18];           /* a[31,4] */
		    ia[185]  = 31, ja[185]  = 5, ar[185] =  soma[5][18];           /* a[31,5] */
		    ia[186]  = 31, ja[186]  = 6, ar[186] =  -1.0;                  /* a[31,6] */ 
		 }

		 /* Restrição : 26 */
		 if (j >= 26){

		   /* Definindo os limitantes da linha 32*/ 
		  glp_set_row_bnds(lp,32,GLP_UP,inf[19],-sup[19]); 

		  /* Preechimento dos valores da matriz das restrições linha 32 */
		  	ia[187]  = 32, ja[187]  = 1, ar[187] =  soma[1][19];           /* a[32,1] */
		    ia[188]  = 32, ja[188]  = 2, ar[188] =  soma[2][19];           /* a[32,2] */
		    ia[189]  = 32, ja[189]  = 3, ar[189] =  soma[3][19];           /* a[32,3] */
			ia[190]  = 32, ja[190]  = 4, ar[190] =  soma[4][19];           /* a[32,4] */
		    ia[191]  = 32, ja[191]  = 5, ar[191] =  soma[5][19];           /* a[32,5] */
		    ia[192]  = 32, ja[192]  = 6, ar[192] =  -1.0;                  /* a[32,6] */ 
		 }

		 /* Restrição : 27 */
		 if (j >= 27){

		   /* Definindo os limitantes da linha 33*/ 
		  glp_set_row_bnds(lp,33,GLP_UP,inf[20],-sup[20]); 

		  /* Preechimento dos valores da matriz das restrições linha 33 */
		  	ia[193]  = 33, ja[193]  = 1, ar[193] =  soma[1][20];           /* a[33,1] */
		    ia[194]  = 33, ja[194]  = 2, ar[194] =  soma[2][20];           /* a[33,2] */
		    ia[195]  = 33, ja[195]  = 3, ar[195] =  soma[3][20];           /* a[33,3] */
			ia[196]  = 33, ja[196]  = 4, ar[196] =  soma[4][20];           /* a[33,4] */
		    ia[197]  = 33, ja[197]  = 5, ar[197] =  soma[5][20];           /* a[33,5] */
		    ia[198]  = 33, ja[198]  = 6, ar[198] =  -1.0;                  /* a[33,6] */ 
		 }

		 /* Restrição : 28 */
		 if (j >= 28){

		   /* Definindo os limitantes da linha 34*/ 
		  glp_set_row_bnds(lp,34,GLP_UP,inf[21],-sup[21]); 

		  /* Preechimento dos valores da matriz das restrições linha 34 */
		  	ia[199]  = 34, ja[199]  = 1, ar[199] =  soma[1][21];           /* a[34,1] */
		    ia[200]  = 34, ja[200]  = 2, ar[200] =  soma[2][21];           /* a[34,2] */
		    ia[201]  = 34, ja[201]  = 3, ar[201] =  soma[3][21];           /* a[34,3] */
			ia[202]  = 34, ja[202]  = 4, ar[202] =  soma[4][21];           /* a[34,4] */
		    ia[203]  = 34, ja[203]  = 5, ar[203] =  soma[5][21];           /* a[34,5] */
		    ia[204]  = 34, ja[204]  = 6, ar[204] =  -1.0;                  /* a[34,6] */ 
		 }

		 /* Restrição : 29 */
		 if (j >= 29){

		   /* Definindo os limitantes da linha 35*/ 
		  glp_set_row_bnds(lp,35,GLP_UP,inf[22],-sup[22]); 

		  /* Preechimento dos valores da matriz das restrições linha 35 */
		  	ia[205]  = 35, ja[205]  = 1, ar[205] =  soma[1][22];           /* a[35,1] */
		    ia[206]  = 35, ja[206]  = 2, ar[206] =  soma[2][22];           /* a[35,2] */
		    ia[207]  = 35, ja[207]  = 3, ar[207] =  soma[3][22];           /* a[35,3] */
			ia[208]  = 35, ja[208]  = 4, ar[208] =  soma[4][22];           /* a[35,4] */
		    ia[209]  = 35, ja[209]  = 5, ar[209] =  soma[5][22];           /* a[35,5] */
		    ia[210]  = 35, ja[210]  = 6, ar[210] =  -1.0;                  /* a[35,6] */ 
		 }

		 /* Restrição : 30 */
		 if (j >= 30){

		   /* Definindo os limitantes da linha 36*/ 
		  glp_set_row_bnds(lp,36,GLP_UP,inf[23],-sup[23]); 

		  /* Preechimento dos valores da matriz das restrições linha 36 */
		  	ia[211]  = 36, ja[211]  = 1, ar[211] =  soma[1][23];           /* a[36,1] */
		    ia[212]  = 36, ja[212]  = 2, ar[212] =  soma[2][23];           /* a[36,2] */
		    ia[213]  = 36, ja[213]  = 3, ar[213] =  soma[3][23];           /* a[36,3] */
			ia[214]  = 36, ja[214]  = 4, ar[214] =  soma[4][23];           /* a[36,4] */
		    ia[215]  = 36, ja[215]  = 5, ar[215] =  soma[5][23];           /* a[36,5] */
		    ia[216]  = 36, ja[216]  = 6, ar[216] =  -1.0;                  /* a[36,6] */ 
		 }

		 /* Restrição : 31 */
		 if (j >= 31){

		   /* Definindo os limitantes da linha 37*/ 
		  glp_set_row_bnds(lp,37,GLP_UP,-100.0,-1.0); 

		  /* Preechimento dos valores da matriz das restrições linha 36 */
		  	ia[217]  = 37, ja[217]  = 1, ar[217] =  -1.0;                  /* a[37,1] */
		    ia[218]  = 37, ja[218]  = 2, ar[218] =   0.0;                  /* a[37,2] */
		    ia[219]  = 37, ja[219]  = 3, ar[219] =   0.0;                  /* a[37,3] */
			ia[220]  = 37, ja[220]  = 4, ar[220] =   0.0;                  /* a[37,4] */
		    ia[221]  = 37, ja[221]  = 5, ar[221] =   0.0;                  /* a[37,5] */
		    ia[222]  = 37, ja[222]  = 6, ar[222] =   0.0;                  /* a[37,6] */ 
		 }

		 /* Restrição : 32 */
		 if (j >= 32){

		   /* Definindo os limitantes da linha 38*/ 
		  glp_set_row_bnds(lp,38,GLP_UP,inf[24],-sup[24]); 

		  /* Preechimento dos valores da matriz das restrições linha 38 */
		  	ia[223]  = 38, ja[223]  = 1, ar[223] =   soma[1][24];          /* a[38,1] */
		    ia[224]  = 38, ja[224]  = 2, ar[224] =   soma[2][24];;         /* a[38,2] */
		    ia[225]  = 38, ja[225]  = 3, ar[225] =   soma[3][24];;         /* a[38,3] */
			ia[226]  = 38, ja[226]  = 4, ar[226] =   soma[4][24];;         /* a[38,4] */
		    ia[227]  = 38, ja[227]  = 5, ar[227] =   soma[5][24];;         /* a[38,5] */
		    ia[228]  = 38, ja[228]  = 6, ar[228] =  -1.0;                  /* a[38,6] */ 
		 }

		 /* Restrição : 33 */
		 if (j >= 33){

		   /* Definindo os limitantes da linha 39*/ 
		  glp_set_row_bnds(lp,39,GLP_UP,inf[25],-sup[25]); 

		  /* Preechimento dos valores da matriz das restrições linha 38 */
		  	ia[229]  = 39, ja[229]  = 1, ar[229] =   0.0;                 /* a[39,1] */
		    ia[230]  = 39, ja[230]  = 2, ar[230] =  -1.0;                 /* a[39,2] */
		    ia[231]  = 39, ja[231]  = 3, ar[231] =   0.0;                 /* a[39,3] */
			ia[232]  = 39, ja[232]  = 4, ar[232] =   0.0;                 /* a[39,4] */
		    ia[233]  = 39, ja[233]  = 5, ar[233] =   0.0;                 /* a[39,5] */
		    ia[234]  = 39, ja[234]  = 6, ar[234] =   0.0;                 /* a[39,6] */ 
		 }

		 /* Restrição : 34 */
		 if (j >= 34){

		   /* Definindo os limitantes da linha 40*/ 
		  glp_set_row_bnds(lp,40,GLP_UP,inf[26],-sup[26]); 

		  /* Preechimento dos valores da matriz das restrições linha 38 */
		  	ia[235]  = 40, ja[235]  = 1, ar[235] =   soma[1][26];         /* a[40,1] */
		    ia[236]  = 40, ja[236]  = 2, ar[236] =   soma[2][26];         /* a[40,2] */
		    ia[237]  = 40, ja[237]  = 3, ar[237] =   soma[3][26];         /* a[40,3] */
			ia[238]  = 40, ja[238]  = 4, ar[238] =   soma[4][26];         /* a[40,4] */
		    ia[239]  = 40, ja[239]  = 5, ar[239] =   soma[5][26];         /* a[40,5] */
		    ia[240]  = 40, ja[240]  = 6, ar[240] =  -1.0;                 /* a[40,6] */ 
		 }

		 /* Restrição : 35 */
		 if (j >= 35){

		   /* Definindo os limitantes da linha 41*/ 
		  glp_set_row_bnds(lp,41,GLP_UP,inf[27],-sup[27]); 

		  /* Preechimento dos valores da matriz das restrições linha 38 */
		  	ia[241]  = 41, ja[241]  = 1, ar[241] =  soma[1][27];         /* a[41,1] */
		    ia[242]  = 41, ja[242]  = 2, ar[242] =  soma[2][27];         /* a[41,2] */
		    ia[243]  = 41, ja[243]  = 3, ar[243] =  soma[3][27];         /* a[41,3] */
			ia[244]  = 41, ja[244]  = 4, ar[244] =  soma[4][27];         /* a[41,4] */
		    ia[245]  = 41, ja[245]  = 5, ar[245] =  soma[5][27];         /* a[41,5] */
		    ia[246]  = 41, ja[246]  = 6, ar[246] =  -1.0;                /* a[41,6] */ 
		 }

		 /* Restrição : 36 */
		 if (j >= 36){

		   /* Definindo os limitantes da linha 42*/ 
		  glp_set_row_bnds(lp,42,GLP_UP,inf[28],-sup[28]); 

		  /* Preechimento dos valores da matriz das restrições linha 38 */
		  	ia[247]  = 42, ja[247]  = 1, ar[247] =  soma[1][28];         /* a[42,1] */
		    ia[248]  = 42, ja[248]  = 2, ar[248] =  soma[2][28];         /* a[42,2] */
		    ia[249]  = 42, ja[249]  = 3, ar[249] =  soma[3][28];         /* a[42,3] */
			ia[250]  = 42, ja[250]  = 4, ar[250] =  soma[4][28];         /* a[42,4] */
		    ia[251]  = 42, ja[251]  = 5, ar[251] =  soma[5][28];         /* a[42,5] */
		    ia[252]  = 42, ja[252]  = 6, ar[252] =  -1.0;                /* a[42,6] */ 
		 }

		  /*Carregando a matriz do coefiecientes */
		  glp_load_matrix(lp,36 + 6*j,ia,ja,ar);

		  /* Resolve o problema */
		  glp_simplex(lp,NULL);

          /* Recuperar e resolver e exibir os resultdos */
		  z = glp_get_obj_val(lp);
		  VTH1S1 = glp_get_col_prim(lp,1);
		  VVH1S1 = glp_get_col_prim(lp,2);
		  VTH2S1 = glp_get_col_prim(lp,3);
		  VVH2S1 = glp_get_col_prim(lp,4);
		  G1 = glp_get_col_prim(lp,5);
		  G2 = glp_get_col_prim(lp,6);
		  ALFA1_1 = glp_get_col_prim(lp,7);
		  ALFA1_2 = glp_get_col_prim(lp,8);
		  printf ("Primal interação : %d  \n",j);
		  printf ("z = %g; VTH1S2 = %g; VVH1S2 = %g;VTH2S2 = %g;VVH2S2 = %g; G1 = %g; G2 = %g \n \n", z,VTH1S2,VVH1S2,VTH2S2,VVH2S2,G1,G2); 
		  j++; 
		  if (j >= 37){
				  goto start;
		  }

		  }

		/* Mostrando a convergência */
		 printf("Houve convergência na interação: %d, Erro =  %lf \n \n",j,fabs(ALFA1 - ALFA1X));

		 printf("Os pontos ótimos são: \n");
		 printf ("z = %lf \n",z);  
		 printf("VTH1S2 = %lf,VVH1S2 = %lf,VTH2S2 = %lf, VVH2S2 = %lf, G1 = %lf,G2 = %lf \n",VTH1S2,VVH1S2,VTH2S2,VVH2S2,G1,G2);
		 printf("O valor ótimo de z: \n");
		 printf("z = %lf\n \n", z);
		 goto end;

start:
		 /* Atigindo o número de interações */
		 printf("Não houve convergência,número de interações: %d, Erro =  %lf,condição de erro: %lf \n \n",j,fabs(ALFA1 - ALFA1X),(double)(ERRO));
		 printf("Os pontos são: \n");
		 printf ("z = %lf \n",z);  
		 printf("VTH1S2 = %lf,VVH1S2 = %lf,VTH2S2 = %lf, VVH2S2 = %lf, G1 = %lf,G2 = %lf \n",VTH1S2,VVH1S2,VTH2S2,VVH2S2,G1,G2);
		 printf("O valor de z: \n");
		 printf("z = %lf\n \n", z);

end:
         /* Limpeza */
		 glp_delete_prob(lp);
		 glp_delete_prob(ld);
		 glp_free_env();

		  return 0;

} // Fim da main()

