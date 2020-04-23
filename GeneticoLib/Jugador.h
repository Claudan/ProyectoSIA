#ifndef Jugador_H
#define Jugador_H

#include <vector>
#include <string>

namespace GeneticoLib {

	class Jugador
	{
	private:
		std::string nombre;
		int numeroJugador;
		std::vector<float> compatibilidadPosicion;
		std::vector<int> malaSinergia;
		std::vector<int> buenaSinergia;

	public:
		Jugador(std::string name, int nro, std::vector<float> comp, std::vector<int> ms, std::vector<int> bs);
		Jugador(std::string name, int nro, std::vector <float> comp);
		void setMalaSinergia(std::vector<int> ms);
		void setBuenaSinergia(std::vector<int> bs);
		bool ExisteSinergiaBuena(int id);
		bool ExisteSinergiaMala(int id);
		int getNumeroJugador();
		std::string getNombreJugador();
		std::vector<float> getCompatibilidadPosicion();
		std::vector<int> getMalaSinergia();
		std::vector<int> getBuenaSinergia();
	};
}

#endif

