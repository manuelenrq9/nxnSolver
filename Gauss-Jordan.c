#include <stdio.h>
#include <stdlib.h>

// Funcion swap
void swap(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

// Función para imprimir la matriz
void PrintMatrix(float a[][100], int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++)
            printf("%.3f ", a[i][j]); // Limitar a 3 decimales
        printf("\n");
    }
}

// Función para reducir la matriz a su forma escalonada reducida
int PerformOperation(float a[][100], int n){
    int i, j, k = 0, c, flag = 0, m = 0;
    float pro = 0;

    // Realizando operaciones elementales
    for (i = 0; i < n; i++)
    {
        if (a[i][i] == 0)
        {
            c = 1;
            while ((i + c) < n && a[i + c][i] == 0)
                c++;        
            if ((i + c) == n) {
                flag = 1;
                break;
            }
            for (j = i, k = 0; k <= n; k++)
                swap(&a[j][k], &a[j+c][k]);
        }

        for (j = 0; j < n; j++) {
            
            // Excluyendo todos los i == j
            if (i != j) {
                
                // Convirtiendo la matriz a su forma escalonada reducida
                float pro = a[j][i] / a[i][i];

                for (k = 0; k <= n; k++)                
                    a[j][k] = a[j][k] - (a[i][k]) * pro;            
            }
        }
    }
    return flag;
}

// Función para imprimir el resultado deseado
// si existen soluciones únicas, de lo contrario
// imprime que no existe solución o que hay soluciones infinitas
void PrintResult(float a[][100], int n, int flag){
    printf("El resultado es: ");

    if (flag == 2)    
        printf("Existen soluciones infinitas\n");
    else if (flag == 3)    
        printf("No existe solución\n");
    
    
    // Imprimiendo la solución dividiendo las constantes por
    // sus respectivos elementos diagonales
    else {
        for (int i = 0; i < n; i++)        
            printf("%.3f ", a[i][n] / a[i][i]); // Limitar a 3 decimales
    }
}

// Para verificar si existen soluciones infinitas
// o no existe solución
int CheckConsistency(float a[][100], int n, int flag)
{
    int i, j;
    float sum;
    
    // flag == 2 para solución infinita
    // flag == 3 para no solución
    flag = 3;
    for (i = 0; i < n; i++)
    {
        sum = 0;
        for (j = 0; j < n; j++)    
            sum = sum + a[i][j];
        if (sum == a[i][j])
            flag = 2;    
    }
    return flag;
}

// Función principal
int main()
{
    int n;
    printf("Ingrese el valor de N: ");
    scanf("%d", &n);
    
    float a[100][100];
    
    printf("Ingrese los coeficientes de las ecuaciones:\n");
    for (int i = 0; i < n; i++) {
        printf("Ecuacion %d:\n", i+1);
        for (int j = 0; j <= n; j++) {
            printf("Coeficiente %d: ", j+1);
            scanf("%f", &a[i][j]);
        }
    }
    
    // Realizando la transformación de la matriz
    int flag = PerformOperation(a, n);
    
    if (flag == 1)    
        flag = CheckConsistency(a, n, flag);

    // Imprimiendo la matriz final
    printf("La matriz aumentada final es: \n");
    PrintMatrix(a, n);
    printf("\n");
    
    // Imprimiendo soluciones (si existen)
    PrintResult(a, n, flag);

    return 0;
}
