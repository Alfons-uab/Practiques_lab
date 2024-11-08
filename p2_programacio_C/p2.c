#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 512
float Mat[N][N], MatDD[N][N];
float V1[N], V2[N], V3[N], V4[N];
float vectres[N];	

void InitData(){
 int i,j;
 srand(334411);
 for( i = 0; i < N; i++ )
	for( j = 0; j < N; j++ ){
 	 Mat[i][j]=(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
 	 if ( (abs(i - j) <= 3) && (i != j))
	  MatDD[i][j] = (((i*j)%3) ? -1 : 1)*(rand()/(1.0*RAND_MAX));
 	 else if ( i == j )
	  MatDD[i][j]=(((i*j)%3)?-1:1)*(10000.0*(rand()/(1.0*RAND_MAX)));
	 else MatDD[i][j] = 0.0;
	}

 for( i = 0; i < N; i++ ){
	V1[i]=(i<N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
	V2[i]=(i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
	V3[i]=(((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
	}
 }

//1
void PrintVect( float vect[N], int from, int numel ) {
    for (int i = from; i < from + numel && i < N; i++) {
        printf("%f ", vect[i]);
    }
    printf("\n");
}
//2
void PrintRow(float mat[N][N], int row, int from, int numel) {
    for (int i = from; i < from + numel; i++) {
        printf("%f ", mat[row][i]);
    }
    printf("\n");
}
//3
void MultEscalar(float vect[N], float vectres[N], float alfa) {
    for (int i = 0; i < N; i++) {
        vectres[i] = alfa * vect[i];
    }
}

//4
float Scalar(float vect1[N], float vect2[N]){
	float result = 0.0;
		for (int i = 0; i < N; i++) {
			result += vect1[i] * vect2[i];
		}
	return result;
}

//5
float Magnitude(float vect[N]) {
    float suma = 0.0;
    for (int i = 0; i < N; i++) {
        suma += vect[i] * vect[i];
    }
    return sqrt(suma); 
}

//6
int Ortogonal(float vect1[N], float vect2[N]){
	float producteescalar = Scalar(vect1,vect2);
	if (producteescalar == 0){
		return 1;
	}
	else{
		return 0;
	}
}

//7
void Projection(float vect1[N], float vect2[N], float vectres[N]) {
    float prodEscalar = Scalar(vect1, vect2);
    float magnitudV2 = Scalar(vect2, vect2);

    if (magnitudV2 == 0) {
        printf("Error: El vector sobre el qual es projecta és nul.\n");
        return;
    }
    float coeficient = prodEscalar / magnitudV2;
    for (int i = 0; i < N; i++) {
        vectres[i] = coeficient * vect2[i];
    }
}

//8
float Infininorm(float M[N][N]) {
    float maxSum = 0.0;

    for (int i = 0; i < N; i++) {
        float filaSum = 0.0; 
        for (int j = 0; j < N; j++) {
            filaSum += fabs(M[i][j]); 
        }
        if (filaSum > maxSum) {
            maxSum = filaSum;
        }
    }
    return maxSum; 
}

//9
float Onenorm(float M[N][N]) {
    float maxSum = 0.0;

    for (int j = 0; j < N; j++) {
        float columnaSum = 0.0; 
        for (int i = 0; i < N; i++) {
            columnaSum += fabs(M[i][j]);
        }
        if (columnaSum > maxSum) {
            maxSum = columnaSum;
        }
    }
    return maxSum;
}

//10
float NormFrobenius(float M[N][N]) {
    float suma = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            suma += M[i][j] * M[i][j];
        }
    }
    return sqrt(suma);
}

//11
int DiagonalDom(float M[N][N]) {
    for (int i = 0; i < N; i++) {
        float diagonalElement = fabs(M[i][i]); 
        float sumOthers = 0.0;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                sumOthers += fabs(M[i][j]);
            }
        }
        if (diagonalElement < sumOthers) {
            return 0; 
        }
    }    
    return 1;
}

//12
void Matriu_x_Vector(float M[N][N], float vect[N], float vectres[N]) {
    for (int i = 0; i < N; i++) {
        vectres[i] = 0.0;
        for (int j = 0; j < N; j++) {
            vectres[i] += M[i][j] * vect[j];
        }
    }
}







int main(){

	InitData();

//a
    // Visualitza els elements 0 al 9 i 256 al 265 del vector V1
    printf("Elements 0 al 9 del vector V1:\n");
    PrintVect(V1, 0, 10);
    printf("Elements 256 al 265 del vector V1:\n");
    PrintVect(V1, 256, 10);

    // Visualitza els elements 0 al 9 i 256 al 265 del vector V2
    printf("Elements 0 al 9 del vector V2:\n");
    PrintVect(V2, 0, 10);
    printf("Elements 256 al 265 del vector V2:\n");
    PrintVect(V2, 256, 10);

    // Visualitza els elements 0 al 9 i 256 al 265 del vector V3
    printf("Elements 0 al 9 del vector V3:\n");
    PrintVect(V3, 0, 10);
    printf("Elements 256 al 265 del vector V3:\n");
    PrintVect(V3, 256, 10);

    return 0;



//b
	// Imprimeix els elements del 0 al 9 de la fila 0 de la matriu Mat
    printf("Elements 0 al 9 de la fila 0 de Mat:\n");
    PrintRow(Mat, 0, 0, 10);

    // Imprimeix els elements del 0 al 9 de la fila 100 de la matriu Mat
    printf("Elements 0 al 9 de la fila 100 de Mat:\n");
    PrintRow(Mat, 100, 0, 10);

//c
	// Imprimeix els elements del 0 al 9 de la fila 0 de la matriu MatDD
    printf("Elements 0 al 9 de la fila 0 de MatDD:\n");
    PrintRow(MatDD, 0, 0, 10);

    // Imprimeix els elements del 90 al 99 de la fila 100 de la matriu MatDD
    printf("Elements 90 al 99 de la fila 100 de MatDD:\n");
    PrintRow(MatDD, 100, 90, 10);
    
//d
    // Càlcul i visualització de les normes i propietats per a la matriu Mat
    printf("Resultats per a la matriu Mat:\n");

    float infininorm_Mat = Infininorm(Mat);
    printf("Infini-norma de Mat: %f\n", infininorm_Mat);

    float norma1_Mat = Onenorm(Mat);
    printf("Norma ú de Mat: %f\n", norma1_Mat);

    float normaFrobenius_Mat = NormFrobenius(Mat);
    printf("Norma de Frobenius de Mat: %f\n", normaFrobenius_Mat);

    int diagonalDom_Mat = DiagonalDom(Mat);
    if (diagonalDom_Mat) {
        printf("La matriu Mat és diagonal dominant.\n");
    } else {
        printf("La matriu Mat NO és diagonal dominant.\n");
    }

    // Càlcul i visualització de les normes i propietats per a la matriu MatDD
    printf("\nResultats per a la matriu MatDD:\n");

    float infininorm_MatDD = Infininorm(MatDD);
    printf("Infini-norma de MatDD: %f\n", infininorm_MatDD);

    float norma1_MatDD = Onenorm(MatDD);
    printf("Norma ú de MatDD: %f\n", norma1_MatDD);

    float normaFrobenius_MatDD = NormFrobenius(MatDD);
    printf("Norma de Frobenius de MatDD: %f\n", normaFrobenius_MatDD);

    int diagonalDom_MatDD = DiagonalDom(MatDD);
    if (diagonalDom_MatDD) {
        printf("La matriu MatDD és diagonal dominant.\n");
    } else {
        printf("La matriu MatDD NO és diagonal dominant.\n");
    }

//e
    float prod_V1_V2 = Scalar(V1, V2);
    printf("Producte escalar V1 · V2: %f\n", prod_V1_V2);

    // Calcula i mostra el producte escalar V1 · V3
    float prod_V1_V3 = Scalar(V1, V3);
    printf("Producte escalar V1 · V3: %f\n", prod_V1_V3);

    // Calcula i mostra el producte escalar V2 · V3
    float prod_V2_V3 = Scalar(V2, V3);
    printf("Producte escalar V2 · V3: %f\n", prod_V2_V3);

//f
    float magnitud_V1 = Magnitude(V1);
    printf("Magnitud de V1: %f\n", magnitud_V1);

    // Calcula i mostra la magnitud de V2
    float magnitud_V2 = Magnitude(V2);
    printf("Magnitud de V2: %f\n", magnitud_V2);

    // Calcula i mostra la magnitud de V3
    float magnitud_V3 = Magnitude(V3);
    printf("Magnitud de V3: %f\n", magnitud_V3);

//g
    // Comprova i mostra si V1 és ortogonal amb V2
    if (Ortogonal(V1, V2)) {
        printf("V1 i V2 són ortogonals.\n");
    } else {
        printf("V1 i V2 no són ortogonals.\n");
    }

    // Comprova i mostra si V1 és ortogonal amb V3
    if (Ortogonal(V1, V3)) {
        printf("V1 i V3 són ortogonals.\n");
    } else {
        printf("V1 i V3 no són ortogonals.\n");
    }

    // Comprova i mostra si V2 és ortogonal amb V3
    if (Ortogonal(V2, V3)) {
        printf("V2 i V3 són ortogonals.\n");
    } else {
        printf("V2 i V3 no són ortogonals.\n");
    }

//h
    // Multiplica el vector V3 per l'escalar 2.0 i guarda el resultat en vectres
    MultEscalar(V3, vectres, 2.0);

    // Mostra els elements 0 al 9 del vector resultant (vectres)
    printf("Elements 0 al 9 del resultat de V3 * 2.0:\n");
    PrintVect(vectres, 0, 10);

    // Mostra els elements 256 al 265 del vector resultant (vectres)
    printf("Elements 256 al 265 del resultat de V3 * 2.0:\n");
    PrintVect(vectres, 256, 10);

//i
    
		
}
