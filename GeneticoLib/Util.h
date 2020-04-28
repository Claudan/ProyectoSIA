#include <fstream>

#include "Plantel.h"
#include "Formacion.h"
#include <string>
#include <vector>

#include <list>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>


namespace GeneticoLib {

	std::string getRoles(int i) {
		std::string roles[14] = {
			"Libero / LIB",
			"Defensa Central/DFC",
			"Lateral izquierdo / LI",
			"Lateral derecho / LD",
			"Pivote / MCD",
			"Medio Centro / MC",
			"Medio Campo / MD / MI",
			"Medio centro ofensivo / MCO",
			"Interior izquierdo / CAI",
			"Interior derecho / CAD",
			"Mediapunta / SD / SDI / SDD",
			"Delantero centro / DC",
			"Extremo izquierdo / EI",
			"Extremo derecho / ED" };

		if (i < 15 && i > 0) return roles[i - 1];
		else return "Rol desconocido";
	}

	void entregarResultados(Plantel p, std::vector<Formacion> soluciones, int rol[], std::string tipoformacion) {
		std::ofstream salida;
		salida.open("output.txt");
		Formacion f;
		for (int i = 0; i < 5; i++) {
			f = soluciones.at(i);
			salida << "Formacion " << i + 1 << " (Tipo: "<<tipoformacion<<")"<<" (Valoracion: "<<f.getCalculoFitness()<<")"<<std::endl;
			for (int k = 0; k < 10; k++) {
				salida << k + 1 << ": " << p.getJugadorById(f.getFormacion()[k]).getNombreJugador() << " (" << getRoles(rol[k]) <<  ")" << std::endl;
			}
			salida << '\n';
		}
		salida.close();
	}

	std::string devolverForTactica(std::string nombreArchivo){

		std::ifstream inFile;
		inFile.open(nombreArchivo);
			if (!inFile)
			{
				std::cout << "No se pudo abrir el archivo";
				exit(1); // terminate with error
			}

		std::string lineFromFile;
		getline(inFile, lineFromFile);
		std::stringstream ss(lineFromFile);
		std::string token;
		char delim = ';';
		getline(ss, token, delim);
		return token;
		inFile.close();
	}

	int *devolverRoles(std::string nombreArchivo){
		std::ifstream inFile;
		inFile.open(nombreArchivo);
			if (!inFile)
			{
				std::cout << "Unable to open file";
				exit(1); // terminate with error
			}

		std::string lineFromFile;
		getline(inFile, lineFromFile);
		std::stringstream ss(lineFromFile);
		std::string token;
		std::string token2;
		char delim = ';';
		char delim2 = ',';
		int contador = 0;
		getline(ss, token, delim);
		getline(ss, token, delim);
		std::stringstream ss2(token);
		int * roles = new int[10];
		while(getline(ss2,token2,delim2)){
			roles[contador] = stoi(token2);
			contador ++;
		}
		return roles;
	
	}

	char devolverModo(std::string nombreArchivo){
		std::ifstream inFile;
		inFile.open(nombreArchivo);
			if (!inFile)
			{
				std::cout << "Unable to open file";
				exit(1); // terminate with error
			}

		std::string lineFromFile;
		getline(inFile, lineFromFile);
		std::stringstream ss(lineFromFile);
		std::string token;
		std::string token2;
		char delim = ';';
		getline(ss, token, delim);
		getline(ss, token, delim);
		getline(ss, token, delim);
		return token[0];
	}
}