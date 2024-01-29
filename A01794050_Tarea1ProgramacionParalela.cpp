/*
T A R E A  1: P R O G R A M  A C I Ó N   D E   U N A   S O L U C I Ó N   P A R A L E L A

1.-Crear un proyecto en Visual Studio
2.- Configurarlo para que pueda utilizar la librería OpenMP
3.- Crear los arreglos y asignarles valores aleatorios o pedirle los valores al usuario (la cantidad de elementos puede ser de 1000 para ejemplificar el proceso y obtener rápidamente resultados)
4.- Realizar un for paralelo a través de las funciones de la librería OpenMP
5.- Imprimir los arreglos o parte de ellos para comprobar que el arreglo resultante contiene la suma de los dos arreglos
*/


/* Verificando que la libreria OMP se encuentre operando adecuadamente*/
#include <iostream>
#include <omp.h>
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif 

//Defininedo las variables que vamos a utilizar, por el momento podemos sumar hasta 10,000 elementos
#define n 10000
#define chunk n/100 //Fraccionamos el total de arreglos en pequeños pedazos

using namespace std;
int pedazos = chunk;
float Sumando1[n], Sumando2[n], Suma[n];
int tid;
int nHilos;
int i;
int x;
int N;
int mostrar;

//Funcion para imprimir la suma

void imprimeArreglo(float* d) 
{

	for (x= 0; x < mostrar; x++)
		std::cout << "[Pos "<<x << "] Valor: "<<d[x] << std::endl;
}

//Se solicita que el usuario determine el numero de elementos que va a sumar y cuantos va mostrar
int main()
{
	std::cout << "SUMANDO ARREGLOS EN PARALELO \n" << std::endl;

	cout << "¿Cuantos elementos vas a sumar?' : ";
	cin >> N;
	cout << "¿Cuantos elementos vas a mostrar?' : ";
	cin >> mostrar;

//Se generan valores aleatorios, la cantidad está determinada por el usuario en el paso previo. 
	for (i = 0; i < N ; i++) 
	{
		Sumando1[i] = rand();
		Sumando2[i] = rand();
		

	}

//Se cra la region paralela
	#pragma omp parallel  for \
    shared(Sumando1, Sumando2, Suma, pedazos) private (i) \
    schedule(static, pedazos) 

//Se realiza el calculo de la suma usando la region paralela

		for (i = 0; i < N; i++)
			Suma[i] = Sumando1[i] + Sumando2[i]; 
//Se imprimen los valores de los sumandos y suma 
		std::cout << "\nImprimiendo " << mostrar << " valores del sumando 1:\n" << std::endl;
		imprimeArreglo(Sumando1);
		std::cout << "\nImprimiendo " << mostrar << " valores del sumando 2:\n" << std::endl;
		imprimeArreglo(Sumando2);
		std::cout << "\nImprimiendo la suma de ambos sumandos: \n" << std::endl;
		imprimeArreglo(Suma);

	
}


