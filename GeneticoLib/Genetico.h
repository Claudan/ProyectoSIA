#ifndef Genetico_H
#define Genetico_H

#include<vector>
#include "Plantel.h"
#include "Formacion.h"
#include "FuncionesFitness.h"
#include <algorithm>
#include <string>
#include <iostream>

namespace GeneticoLib {

	std::vector<Formacion> Genetico(Plantel p, int* rol, char modo, std::string forTecnica, int porcentajemutacion, int generacionespermitidas, int cantidadpoblacion) {

		float diferencia = 0.000001f;

		std::vector<Formacion> soluciones;
		Formacion f, hijo1, hijo2;

		//std::cout << "Generando Soluciones Iniciales:\n";
		for (int i = 0; i < cantidadpoblacion; i++) {
			f.generarFormacionAleatoria(p.getLargo());
			f.setCalculoFitness(FuncionesFitness::Fitness(f.getFormacion(), p, rol, modo, forTecnica));

			soluciones.push_back(f);
		}

		sort(soluciones.begin(), soluciones.end(), Formacion::Compare);
		//cout << "Ordenando e imprimiendo:\n";
		//for (int i = 0; i < soluciones.size(); i++) soluciones.at(i).ImprimirFormacion();

		int generaciones = 0;
		int random1 = 0, random2 = 0;

		//std::cout << "Presione enter para empezar!\n";
		//getchar();
		//getchar();

		//Ambas condiciones de termino, deber�amos elegir una sola?
		//hasta que las mejores 2 soluciones convergan a un valor
		//o hasta que se alcance una cantidad de generaciones permitidas.
		while (soluciones.at(0).getCalculoFitness() - soluciones.at(1).getCalculoFitness() > diferencia&& generaciones < generacionespermitidas) {
			while (random1 == random2) {
				//Selecciona los padres del nuevo hijo al azar, estilo torneo.
				//Siempre distintos!!!!
				random1 = rand() % cantidadpoblacion;
				random2 = rand() % cantidadpoblacion;
			}
			//Cruzamiento tipo OX con 2 hijos.
			int comienzo = rand() % 10;
			int final = rand() % (10 - comienzo) + comienzo;
			//cout << "Segmento:" << comienzo << "-" << final << endl;
			hijo1.Cruzamiento(soluciones.at(random1), soluciones.at(random2), comienzo, final);
			hijo1.Mutacion(p.getLargo(), porcentajemutacion);
			hijo1.setCalculoFitness(FuncionesFitness::Fitness(hijo1.getFormacion(), p, rol, modo, forTecnica));
			hijo2.Cruzamiento(soluciones.at(random2), soluciones.at(random1), comienzo, final);
			hijo2.Mutacion(p.getLargo(), porcentajemutacion);
			hijo2.setCalculoFitness(FuncionesFitness::Fitness(hijo2.getFormacion(), p, rol, modo, forTecnica));
			//cout << "Padre A: "; soluciones.at(random1).ImprimirFormacion(); cout << "Padre B: "; soluciones.at(random2).ImprimirFormacion();
			//cout << "Hijo1: "; hijo1.ImprimirFormacion(); cout << "Hijo2: "; hijo2.ImprimirFormacion();

			//Si los nuevos hijos son mejores que las peores soluciones (al final del vector), los inserta en la poblaci�n.
			bool ordenar = false;
			if (soluciones[cantidadpoblacion - 1].getCalculoFitness() < hijo1.getCalculoFitness()) {
				soluciones[cantidadpoblacion - 1] = hijo1;
				ordenar = true;
			}
			if (soluciones[cantidadpoblacion - 1].getCalculoFitness() < hijo2.getCalculoFitness()) {
				if (soluciones[cantidadpoblacion - 2].getCalculoFitness() < hijo2.getCalculoFitness()) {
					soluciones[cantidadpoblacion - 2] = hijo2;
				}
				else soluciones[cantidadpoblacion - 1] = hijo2;
				ordenar = true;
			}
			if (ordenar) sort(soluciones.begin(), soluciones.end(), Formacion::Compare);
			ordenar = false;

			//std::cout << "Generacion: " << generaciones + 1 << "/"<<generacionespermitidas <<"\n";
			std::cout << "Calculando formaciones: " << (int)((generaciones + 1)*100 / generacionespermitidas) << "%\n";
			generaciones++;
			//getchar();
		}

		//for (int i = 0; i < soluciones.size(); i++) soluciones.at(i).ImprimirFormacion();
		return soluciones;
	}
}

#endif