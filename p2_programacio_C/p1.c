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
	    printf("Elements 0 al 9 del vector V1:\n");
        PrintVect(V1, 0, 10);PrintVect (V1, 256, 10);

        printf("Elements 256 al 265 del vector V2:\n");
        PrintVect(V2, 0, 10);PrintVect (V2, 256, 10);

        printf("Elements 0 al 9 del vector V3:\n");
        PrintVect(V3, 0, 10);PrintVect (V3, 256, 10);

//b
		printf("Mat fila 0 i fila 100 del 0 al 9:\n");
		PrintRow(Mat, 0, 0, 10); 
		PrintRow(Mat, 100, 0, 10);

//c
		printf("MatDD fila 0 del 0 al 9 i fila 100 del 95 al 104:\n");
		PrintRow(MatDD, 0, 0, 10);
		PrintRow(MatDD, 100, 95, 10); 

//h?
		printf("Els elements 0 al 9 i 256 al 265 del resultat de multiplicar V3 x 2.0 són:\n");
    	PrintVect(vectres, 0, 10);   
    	PrintVect(vectres, 256, 10);  
		
}
