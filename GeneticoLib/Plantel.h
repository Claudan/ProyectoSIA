#ifndef Plantel_H
#define Plantel_H

#include "Jugador.h" 

#include <list>

namespace GeneticoLib {

	class Plantel
	{
	private:
		std::list<Jugador> ListaJ;

	public:
		Plantel();
		std::list<Jugador> getLista();
		void mostrarPlantel();
		std::vector<std::vector<int>> archivoMalaSinergia(std::string nombreArchivo);
		std::vector<std::vector<int>> archivoBuenoSinergia(std::string nombreArchivo);
		void cargarArchivo(std::string nombrePolivalencia, std::string nombreSinergia);
		int getLargo();
		Jugador getJugadorById(int id);
		int getIdByNombre(std::string nombreJ);
	};
}

#endif
