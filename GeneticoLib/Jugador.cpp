#include "Jugador.h"

namespace GeneticoLib {

	Jugador::Jugador(std::string name, int nro, std::vector<float> comp, std::vector<int> ms, std::vector<int> bs)
	{
		nombre = name;
		numeroJugador = nro;
		compatibilidadPosicion = comp;
		malaSinergia = ms;
		buenaSinergia = bs;
	}

	Jugador::Jugador(std::string name, int nro, std::vector<float> comp) {
		nombre = name;
		numeroJugador = nro;
		compatibilidadPosicion = comp;
	}

	void Jugador::setMalaSinergia(std::vector <int> ms) {
		malaSinergia = ms;
	}

	void Jugador::setBuenaSinergia(std::vector <int> bs) {
		buenaSinergia = bs;
	}

	bool Jugador::ExisteSinergiaBuena(int id) {
		if (std::find(buenaSinergia.begin(), buenaSinergia.end(), id) != buenaSinergia.end()) {
			return true;
		}
		return false;
	}

	bool Jugador::ExisteSinergiaMala(int id) {
		if (std::find(malaSinergia.begin(), malaSinergia.end(), id) != malaSinergia.end()) {
			return true;
		}
		return false;
	}

	int Jugador::getNumeroJugador() {
		return numeroJugador;
	}

	std::string Jugador::getNombreJugador() {
		return nombre;
	}
	
	std::vector<float> Jugador::getCompatibilidadPosicion() {
		return compatibilidadPosicion;
	}

	std::vector<int> Jugador::getMalaSinergia() {
		return malaSinergia;
	}

	std::vector<int> Jugador::getBuenaSinergia() {
		return buenaSinergia;
	}
}