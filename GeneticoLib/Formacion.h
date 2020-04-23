#ifndef Formacion_H
#define Formacion_H

namespace GeneticoLib {

	class Formacion
	{
	private:
		int formacion[10];// numero del jugador dentro de la lista del plantel
		float calculoFitness = 0;
	
	public:
		static bool Compare(Formacion f1, Formacion f2);
		void Cruzamiento(Formacion padre1, Formacion padre2, int iniciosegmento, int finalsegmento);
		void Cruzamiento(Formacion padre1, Formacion padre2);
		void Mutacion(int rangoid, int porcentajemutacion);
		void generarFormacionAleatoria(int rangoid);
		void ImprimirFormacion();
		bool estaNumeroPresente(int numero, int numeros[10]);
		int *getFormacion();
		float getCalculoFitness();
		//void setFormacion(int* _formacion);
		void setCalculoFitness(float _calculoFitness);
	};

}

#endif

