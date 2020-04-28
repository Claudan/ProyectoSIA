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

	std::list<Jugador> ListaJ;

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

	std::vector<std::vector<int>> Plantel::archivoMalaSinergia(std::string nombreArchivo)
	{
		std::ifstream FileSinergia;
		FileSinergia.open(nombreArchivo);
		if (!FileSinergia)
		{
			std::cout << "No se pudo abrir el archivo de sinergias.";
			exit(1); // terminate with error
		}
		std::string token;
		std::vector<int> malaSinergia;
		std::vector<std::vector<int>> todasMalasSinergias;
		std::string lineFromFile;
		getline(FileSinergia, lineFromFile);
		todasMalasSinergias.clear();
		while (!FileSinergia.eof())
		{
			malaSinergia.clear();
			std::stringstream ss(lineFromFile);
			std::string token;
			std::string token2;
			char delim = ';';
			char delim2 = ',';
			getline(ss, token, delim);
			std::stringstream ss2(token);
			while (getline(ss2, token2, delim2))
			{
				malaSinergia.insert(malaSinergia.end(), std::stoi(token2));
			}
			todasMalasSinergias.push_back(malaSinergia);
			getline(ss, token, delim);
			getline(FileSinergia, lineFromFile);
		}
		FileSinergia.close();
		//std::cout << "Lectura mala sinergia OK. N:"<<todasMalasSinergias.size()<<"\n";
		return todasMalasSinergias;
	}

	std::vector<std::vector<int>> Plantel::archivoBuenoSinergia(std::string nombreArchivo)
	{
		std::ifstream FileSinergia;
		FileSinergia.open(nombreArchivo);
		if (!FileSinergia)
		{
			std::cout << "No se pudo abrir el archivo de sinergias.";
			exit(1); // terminate with error
		}
		std::string token;
		std::vector<int> buenaSinergia;
		std::vector<std::vector<int>> todasBuenasSinergias;
		std::string lineFromFile;
		getline(FileSinergia, lineFromFile);
		todasBuenasSinergias.clear();
		while (!FileSinergia.eof())
		{
			buenaSinergia.clear();
			std::stringstream ss(lineFromFile);
			std::string token;
			std::string token2;
			char delim = ';';
			char delim2 = ',';
			getline(ss, token, delim);
			getline(ss, token, delim);
			std::stringstream ss2(token);
			while (getline(ss2, token2, delim2))
			{
				buenaSinergia.insert(buenaSinergia.end(), std::stoi(token2));
			}
			todasBuenasSinergias.push_back(buenaSinergia);
			getline(FileSinergia, lineFromFile);
		}
		FileSinergia.close();
		//std::cout << "Lectura buena sinergia OK. N:" << todasBuenasSinergias.size() << "\n";
		return todasBuenasSinergias;
	}

	void Plantel::cargarArchivo(std::string nombrePolivalencia, std::string nombreSinergia)
	{

		std::ifstream FilePolivalencia;
		FilePolivalencia.open(nombrePolivalencia);
		if (!FilePolivalencia)
		{
			std::cout << "No se pudo abrir uno de los archivos.";
			exit(1); // terminate with error
		}

		std::string lineFromFile;
		getline(FilePolivalencia, lineFromFile);
		int nro = 1; 
		float n = 0;//Donde se ocupa esto?!

		std::vector<float> compatibilidadPos;
		std::vector<std::vector<int>> todasMalasSinergias = archivoMalaSinergia(nombreSinergia);
		std::vector<std::vector<int>> todasBuenasSinergias = archivoBuenoSinergia(nombreSinergia);
		std::vector<int> malaSinergia;
		std::vector<int> buenaSinergia;
		int sum = 0;
		while (!FilePolivalencia.eof())
		{
			compatibilidadPos.clear();
			malaSinergia.clear();
			buenaSinergia.clear();
			sum = 0;
			std::stringstream ss(lineFromFile);
			std::string token;
			//char delim = ';';
			char delim = ',';
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
				sum++;
			}

			malaSinergia = todasMalasSinergias[nro - 1];
			buenaSinergia = todasBuenasSinergias[nro - 1];
			getline(FilePolivalencia, lineFromFile);
			ListaJ.push_back(Jugador(nombre, nro, compatibilidadPos, malaSinergia, buenaSinergia));
			nro++;
		}
		FilePolivalencia.close();
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
