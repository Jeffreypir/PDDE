/*
   Problema Estaionário Unidimensional (PEU)
   Metodo de Elementos finitos
   Uni-dimensional
   - (Alpha)u'' + (Beta)u = f(x)
   tipo=1: u() prescrita  
   tipo=2: du() prescrita
   Linear solver: Tri-diagonal matrix
*/

#include <stdio.h>
#include <math.h>
#include <string.h>

#define  Nosm   102
#define  Nelm   101
#define  Xi1    -sqrt(3)/3
#define  Xi2    sqrt(3)/3

FILE  *f1;
int   Nel,Nos;
int   tipo1,tipo2;
float X[Nosm], Xe[3];
float H[Nelm];
float K[Nosm][4];
float F[Nosm],D[Nosm];
float Alpha,Beta;
float A1,A2;
float Uh[Nosm];

void InputData()
{
   printf("Constante Alpha = ");
   scanf("%f", &Alpha);
   printf("Constante Beta = ");
   scanf("%f", &Beta);
   fprintf(f1,"Alpha = %f\n", Alpha);
   fprintf(f1,"Beta  = %f\n", Beta);
   printf("\n\nNumeros de elementos = ");
   scanf("%d", &Nel);
   fprintf(f1,"Numero de elementos = %d\n", Nel);
}

void InputCondFront()
{
   printf("\nCond. Contorno:(tipo: 1-Dirichlet 2-Neumann)\n");
   printf("Cond. do no %d (tipo, valor):", 1);
   scanf("%d %f", &tipo1, &A1);
   printf("Cond. do no %d (tipo, valor):", Nos);
   scanf("%d %f", &tipo2, &A2);
}

void CoordGlobal()
{  int i;
   float dl;

   /* divisao uniforme */
   printf("Entre com a coord. do No' esquerda:\n");
   scanf("%f", &X[1]);
   printf("Entre com a coord. do No' direta:\n");
   scanf("%f", &X[Nos]);
   dl = (X[Nos]-X[1])/Nel;
   for (i=2; i<Nos; i++) X[i]=X[1]+dl*(i-1);

   printf("\nCoord. Global:\n");
   fprintf(f1,"\nCoord. Global:\n");
   for (i=1; i<=Nos; i++)
   {
     printf(" No %d = %f\n", i, X[i]);
     fprintf(f1," No %d = %f\n", i, X[i]);
   }
}

void CoordLocal(int e)
{
   Xe[1] = X[e];
   Xe[2] = X[e+1];
   H[e] = Xe[2] - Xe[1];
}

int LM(int e,int a)
{
   if (a==1)  return  e;
   else       return  (e+1);
}

float Xi(int e, float x)  /* Transf. perimetrica */
{
   return (Xe[1] + H[e]/2*(x+1));
}

void MatrizRigidez()
{  int e;
   float K11,K22,K12,K21;
   for (e=1; e<=Nel; e++)
   {
      CoordLocal(e);
      K11 = Alpha/H[e] + Beta/3*H[e];
      K22 = Alpha/H[e] + Beta/3*H[e];
      K12 = -Alpha/H[e] + Beta/6*H[e];
      K21 = -Alpha/H[e] + Beta/6*H[e];
      /* Matriz Rigidez */
      K[e][2] += K11;
      K[e][3]  = K12;
      K[e+1][1]  = K21;
      K[e+1][2]  = K22;
   }
}

float forca(float x)
{
   return x;   /* funcao de forca prescrita */
}

float g1(int e, float x)
{
   return  (.5*forca(Xi(e,x))*(1 - x));
}
float g2(int e, float x)
{
   return  (.5*forca(Xi(e,x))*(1 + x));
}

void VetorForca()
{
   int e;
   float Fe1,Fe2;
   for (e=1; e<=Nel; e++)
   {
   /* Forca local - Quadratura Gauss 2-pts */
      CoordLocal(e);
      Fe1 = H[e]/2*(g1(e,Xi1)+g1(e,Xi2));
      Fe2 = H[e]/2*(g2(e,Xi1)+g2(e,Xi2));
   /* Forca global */
      F[LM(e,1)] += Fe1;
      F[LM(e,2)]  = Fe2;
}  }

void CondFront(float A, float B)
{
   switch (tipo1)
   { case 1:{
        K[1][2] = 1;
        K[1][3] = 0;
        F[1]  = A;
        F[2] += -K[2][1]*A;
        K[2][1] = 0;
        break;}
     case 2:{
        F[1] = F[1] - Alpha*A;
        break;}
   }
   switch (tipo2)
   { case 1:{
        F[Nos-1] += -K[Nos-1][3]*B;
        F[Nos] = B;
        K[Nos-1][3] = 0;
        K[Nos][1] = 0;
        K[Nos][2] = 1;
        break;}
     case 2:{
        F[Nos] = F[Nos] + Alpha*B;
        break;}
   }
}

void LinearSolver(float M[Nosm][4], float F[Nosm],float X[Nosm])
{  int i;
   float y;
   for (i=1; i<Nos; i++)
   {
       y = M[i+1][1]/M[i][2];
       M[i+1][2] += -y*M[i][3];
       F[i+1] += -y*F[i];
   }
   /* Retro-Substituicao */
   X[Nos] = F[Nos]/M[Nos][2];
   for (i=Nos-1; i>=1; i--)
       X[i] = (F[i]-M[i][3]*X[i+1])/M[i][2];
}

void SolExata()
{ int i;
  float Gama =  sqrt(Beta/Alpha);
  float c1 = exp(Gama);
  float c2 = exp(-Gama);
  float c3 =(A2-(1./Beta));
  float c4 =(A1*c2);
  float c5 =(A1*c1);
  float c6 =((1./Beta)-A1);
  float c8 =(Gama*(c1+c2));
  float U1[Nosm],U2,U3;

  for (i=1; i<=Nos; i++)
  U1[i]=1./Beta*X[i];

  switch (tipo1)
  { case 1:
    {
     switch (tipo2)
     { case 1:
       /*cond. fronteira:u(x[1])=A1 e u(x[Nos])=A2*/
       /*tipo1-case1,tipo2-case1*/
       { for (i=1; i<=Nos; i++)
         { U2= (c3-A1*c2)*pow(c1,X[i]);
           U3= (A1*c1-c3)*pow(c2,X[i]);
           Uh[i]= U1[i]+1./(c1-c2)*(U2+U3);
         }
         break;
       } 
       case 2:
       /*cond. fronteira:u(x[1])=A1 e Du(x[Nos]=A2*/
       /*tipo1-case1, tipo2-case2*/
       { for (i=1; i<=Nos; i++)
         { U2=(c3+Gama*c4)*pow(c1,X[i]);
           U3=(Gama*c5-c3)*pow(c2,X[i]);
           Uh[i]=U1[i]+1./c8*(U2+U3);
         }
         break;
    }} }
    break;
    case 2:
    {
     switch (tipo2)
     { case 1:
       /*cond. fronteira:Du(x[1])=A1 e u(x[Nos]=A2*/
       /*tipo1-case2,tipo2-case1*/
       { for (i=1; i<=Nos; i++)
         { U2= (-c2*c6+Gama*c3)*pow(c1,X[i]);
           U3= ( c1*c6+Gama*c3)*pow(c2,X[i]);
           Uh[i]= U1[i]+1./c8*(U2+U3);
         }
         break;
       }
       case 2:
       /*cond. fronteira:Du(x[1])=A1 e Du(x[Nos]=A2*/
       /*tipo1-case2,tipo2-case2*/
       { for (i=1; i<=Nos; i++)
         { U2=(-c6/Gama)*pow(c1,X[i]);
           U3=1./Gama/(c1-c2)*(c6*c1+c3)*(pow(c1,X[i])+pow(c2,X[i]));
           Uh[i]= U1[i]+(U2+U3);
         }
         break;
  } }} }
}

void OutputData()
{  int i,j;
   fprintf(f1,"\nMatriz Rigidez:\n");
   for (i=1; i<=Nos; i++)
   {
       for (j=1; j<=3; j++)
         fprintf(f1,"  K(%d,%d)=%f", i,j, K[i][j]);
         fprintf(f1,"\n");
   }
   fprintf(f1,"\nForca Prescrita:\n");
   for (i=1; i<=Nos; i++)
       fprintf(f1,"  F(%d)=%f", i, F[i]);
       fprintf(f1,"\n");
}

void OutputResultado()
{  int i;
   fprintf(f1,"\nSolucao Nodal (Numerica, Exata):\n");
   for (i=1; i<=Nos; i++)
   {
       fprintf(f1,"\n %3d: (%5e, %5e) ", i, D[i], Uh[i]);
   }
       fprintf(f1,"\n");
}

int main()
/*void main()*/
{
   f1=fopen("PEU.out","w");
   InputData();
   Nos = Nel + 1;
   CoordGlobal();
   InputCondFront();
   MatrizRigidez();
   VetorForca();
   /* Cond. Contorno: */
   CondFront(A1,A2);
   OutputData();
   LinearSolver(K,F,D);
   SolExata();
   OutputResultado();
   fclose(f1);
}

