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
		void cargarArchivo(std::string nombreArchivo);
		int getLargo();
		Jugador getJugadorById(int id);
		int getIdByNombre(std::string nombreJ);
	};
}

#endif
