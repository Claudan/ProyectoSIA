#include "Formacion.h"

#include <string>
#include<cstdlib>
#include<ctime>
#include <iostream>
#include "FuncionesFitness.h"

namespace GeneticoLib {

		bool Formacion::Compare(Formacion f1, Formacion f2) {
			return f1.calculoFitness > f2.calculoFitness;
		}

		void Formacion::Cruzamiento(Formacion padre1, Formacion padre2, int iniciosegmento, int finalsegmento) {
			for (int k = 0; k < 10; k++) formacion[k] = 0;

			for (int i = iniciosegmento; i <= finalsegmento; i++) {
				formacion[i] = padre1.formacion[i];
			}

			bool copiado = false;
			int i_padre = 0;
			int posicion = 0;
			while (posicion < 10) { //Ahora se rellena el hijo con los genes del otro padre que NO TENGA REPETIDOS!!!
				if (posicion == iniciosegmento) {
					posicion = finalsegmento + 1; //+1
				}
				else {
					i_padre = 0;
					copiado = false;
					while (!copiado && i_padre < 10) {
						copiado = false;
						//cout << "Esta " << padre2.formacion[i_padre] << " en el hijo?";
						if (!estaNumeroPresente(padre2.formacion[i_padre], formacion)) {

							//cout << "No. Copiando en posicion "<<posicion<<".\n";
							formacion[posicion] = padre2.formacion[i_padre];
							posicion++;
							copiado = true;
							i_padre++;
						}
						else {
							//cout << "Si. Saltando!\n";
							i_padre++;
						}
					}
				}
			}
		}

		void Formacion::Cruzamiento(Formacion padre1, Formacion padre2)
		{
			//Cruzamiento OX que retorna 1 hijo. Si se quiere otro hijo usela de nuevo. Jijij,
			//No, deberia hacerla de nuevo para que retorne 2 hijos.
			//Formacion hijo;
			for (int k = 0; k < 10; k++) formacion[k] = 0;
			//srand((int)time(0));
			int comienzo = rand() % 10;
			int posicion = 0, i_padre;
			int final = rand() % (10 - comienzo) + comienzo;
			//cout << comienzo << "-"<<final << "\n";
			bool copiado = false;
			if (rand() % 2 == 0) { //Al azar, se copia un segmento de un padre al hijo.
				//cout << "Copiando segmento de padre 1\n";
				for (int i = comienzo; i <= final; i++) {
					formacion[i] = padre1.formacion[i];
				}
				i_padre = 0;
				//ImprimirFormacion();
				//cout << "Rellenando hijo (con genes del padre 2)\n";
				while (posicion < 10) { //Ahora se rellena el hijo con los genes del otro padre que NO TENGA REPETIDOS!!!
					if (posicion == comienzo) {
						//cout << "Se llego al segmento, saltando! \n";
						posicion = final + 1; //+1
					}
					else {
						i_padre = 0;
						copiado = false;
						while (!copiado && i_padre < 10) {
							copiado = false;
							//cout << "Esta " << padre2.formacion[i_padre] << " en el hijo?";
							if (!estaNumeroPresente(padre2.formacion[i_padre], formacion)) {

								//cout << "No. Copiando en posicion "<<posicion<<".\n";
								formacion[posicion] = padre2.formacion[i_padre];
								posicion++;
								copiado = true;
								i_padre++;
							}
							else {
								//cout << "Si. Saltando!\n";
								i_padre++;
							}
						}
					}
				}
			}
			else {
				//cout << "Copiando segmento de padre 2\n";
				for (int i = comienzo; i <= final; i++) {
					formacion[i] = padre2.formacion[i];
				}
				i_padre = 0;
				//ImprimirFormacion();
				//cout << "Rellenando hijo (con genes del padre 1)\n";
				while (posicion < 10) { //Ahora se rellena el hijo con los genes del otro padre que NO TENGA REPETIDOS!!!
					if (posicion == comienzo) {
						//cout << "Se llego al segmento, saltando! \n";
						posicion = final + 1; //+1
					}
					else {
						i_padre = 0;
						copiado = false;
						while (!copiado && i_padre < 10) {
							copiado = false;
							//cout << "Esta " << padre1.formacion[i_padre] << " en el hijo?";
							if (!estaNumeroPresente(padre1.formacion[i_padre], formacion)) {

								//cout << "No. Copiando en posicion " << posicion << ".\n";
								formacion[posicion] = padre1.formacion[i_padre];
								posicion++;
								copiado = true;
								i_padre++;
							}
							else {
								//cout << "Si. Saltando!\n";
								i_padre++;
							}
						}
					}
				}
			}
			//cout << comienzo << "-" << final<<"\n";
		}

		void Formacion::Mutacion(int rangoid, int porcentajemutacion) //de 0% a 100% en int
			//Probablemente hay que modificarla. El rangoid deberia ser el largo de la lista de jugadores?
		{
			//srand((int)time(0));
			int posiblejugador;
			bool modificado = false;
			for (int i = 0; i < 10; i++)
			{
				modificado = false;
				//Esto es como traer el jugador de la banca.
				if (rand() % 100 < porcentajemutacion) {
					while (!modificado) {
						posiblejugador = (rand() % rangoid) + 1; //Que pasa si me sale el id de un arquero!?!?
						if (!estaNumeroPresente(posiblejugador, formacion)) {
							formacion[i] = posiblejugador;
							modificado = true;
						}
					}
				}
			}
			//Esto deberia hacerlo con el plantel, pero no esta listo aun.
		}

		void Formacion::generarFormacionAleatoria(int rangoid) {
			//srand((int)time(0));
			int posiblejugador;
			bool modificado = false;
			for (int i = 0; i < 10; i++) formacion[i] = 0;
			for (int i = 0; i < 10; i++)
			{
				modificado = false;
				while (!modificado) {
					posiblejugador = (rand() % rangoid) + 1;
					if (!estaNumeroPresente(posiblejugador, formacion)) {
						formacion[i] = posiblejugador;
						modificado = true;
					}
				}

			}
		}

		void Formacion::ImprimirFormacion() {

			std::cout << "[ ";
			for (int i = 0; i < 9; i++) std::cout << formacion[i] << " - ";
			std::cout << formacion[9] << "] Fitness: " << calculoFitness << "\n";
		}

		bool Formacion::estaNumeroPresente(int numero, int numeros[10]) {
			//cout << "Esta " << numero << " en el arreglo?";
			for (int i = 0; i < 10; i++) {
				if (numero == numeros[i]) {
					//cout << " Si.\n";
					return true;
				}
			}
			//cout << " No.\n";
			return false;
		}

		int* Formacion::getFormacion(){
			return formacion;
		}

		float Formacion::getCalculoFitness() {
			return calculoFitness;
		}

		/*void Formacion::setFormacion( int* _formacion) {
			formacion = _formacion;
		}*/

		void Formacion::setCalculoFitness(float _calculoFitness) {
			calculoFitness = _calculoFitness;
		}
}