#include "Plantel.h"
#include "Jugador.h"

#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

namespace GeneticoLib {

	Plantel::Plantel()
	{
	}

	std::list<Jugador> Plantel::getLista()
	{
		return ListaJ;
	}

	void Plantel::mostrarPlantel()
	{
		for (std::list<Jugador>::iterator it = ListaJ.begin(); it != ListaJ.end(); ++it)
		{
			std::cout << it->getNombreJugador() << ' ' << it->getBuenaSinergia()[0] << ' ' << it->getMalaSinergia()[0] << '\n';
		}
	}

	void Plantel::cargarArchivo(std::string nombreArchivo)
	{

		std::ifstream inFile;

		inFile.open(nombreArchivo);
		if (!inFile)
		{
			std::cout << "Unable to open file";
			exit(1); // terminate with error
		}

		std::string lineFromFile;
		getline(inFile, lineFromFile);
		int nro = 1;
		float n = 0;

		std::vector<float> compatibilidadPos;
		std::vector <int> malaSinergia;
		std::vector <int> buenaSinergia;
		int sum = 0;
		while (!inFile.eof())
		{
			compatibilidadPos.clear();
			malaSinergia.clear();
			buenaSinergia.clear();
			sum = 0;
			std::stringstream ss(lineFromFile);
			std::string token;
			char delim = ';';
			char secondDelim = ',';
			std::string secondToken;
			std::string nombre;
			while (getline(ss, token, delim))
			{
				if (sum == 0)
				{
					nombre = token;
				}
				else if (sum < 15)
				{
					compatibilidadPos.insert(compatibilidadPos.end(), strtof((token).c_str(), 0));
				}

				else if (sum == 15) {
					std::stringstream ss2(token);
					while (getline(ss2, secondToken, secondDelim)) {
						malaSinergia.insert(malaSinergia.end(), std::stoi(secondToken));
					}
				}
				else if (sum == 16) {
					std::stringstream ss2(token);
					while (getline(ss2, secondToken, secondDelim)) {
						buenaSinergia.insert(buenaSinergia.end(), std::stoi(secondToken));
					}
				}
				sum++;

			}
			getline(inFile, lineFromFile);
			ListaJ.push_back(Jugador(nombre, nro, compatibilidadPos, malaSinergia, buenaSinergia));
			nro++;
		}
		inFile.close();
	}

	int Plantel::getLargo()
	{
		return (int)ListaJ.size();
	}

	Jugador Plantel::getJugadorById(int id)
	{
		std::list<Jugador>::iterator it = ListaJ.begin();
		while (it->getNumeroJugador() != id || it != ListaJ.end())
		{
			if (it->getNumeroJugador() == id)
			{
				return Jugador(it->getNombreJugador(), it->getNumeroJugador(), it->getCompatibilidadPosicion(), it->getMalaSinergia(), it->getBuenaSinergia());
			}
			it++;
		}
	}

	int Plantel::getIdByNombre(std::string nombreJ) {
		std::list<Jugador>::iterator it = ListaJ.begin();
		while (it->getNombreJugador() != nombreJ || it != ListaJ.end())
		{
			if (it->getNombreJugador() == nombreJ)
			{
				return (it->getNumeroJugador());
			}
			it++;
		}
	}
}
