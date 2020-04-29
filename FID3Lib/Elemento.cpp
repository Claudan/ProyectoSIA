#include "Elemento.h"
#include <iostream>

namespace FID3Lib {

	Elemento::Elemento() 
	{
	
	}

	Elemento::Elemento(std::vector<AtributoDifuso> _valores, std::string _clase)
	{
		atributosDifusos = _valores;
		clase   = _clase;
	}

	Elemento::Elemento(std::vector<AtributoDifuso> _valores, std::string _clase, std::map<std::string, double> _clases)
	{
		atributosDifusos = _valores;
		clase = _clase;
		clases = _clases;
	}

	Elemento::Elemento(std::string _nombre, std::vector<AtributoDifuso> _valores, std::string _clase, std::map<std::string, double> _clases)
	{
		nombre = _nombre;
		atributosDifusos = _valores;
		clase = _clase;
		clases = _clases;
	}
	

	void Elemento::setClase(std::string _clase)
	{
		clase = _clase;
	}

	void Elemento::setClases(std::string _clase, double valor)
	{
		clases[_clase] = valor;
	}

	void Elemento::setValoresDifusos(AtributoDifuso _atributoDifuso)
	{
		atributosDifusos.insert(atributosDifusos.end(), _atributoDifuso);
	}
	void Elemento::setNombre(std::string _nombre)
	{
		nombre = _nombre;
	}

	std::string Elemento::getClase()
	{
		return clase;
	}
	std::map<std::string, double> Elemento::getClases() {
		
		return clases;
	}
	std::string Elemento::getNombre() {
		return nombre;
	}

	std::vector<AtributoDifuso> Elemento::getAtributosDifusos()
	{
		return atributosDifusos;
	}
	
	std::string Elemento::imprimir(std::vector<std::string> clasesOrdenadas) {

		std::string tupla;
		tupla = getNombre();  
		std::cout << getNombre() << "algo" << std::endl;
		std::map<std::string, double>::iterator it;

		// Itero en todas las clases que tiene elemento
		int i = 0;
		std::cout << getClases().size() << std::endl;
		
		for (int j = 1; j < clasesOrdenadas.size(); j++) {
			tupla = tupla + "," + std::to_string(getClases()[clasesOrdenadas[j]]);
			std::cout << tupla << std::endl;
			//getchar();
		}
		std::cout << tupla  << "tupla" <<std::endl;
		return tupla;		
	}
	// Nuevo metodo para clasificar
	double Elemento::getValorDifuso(std::string nombreAtributoDifuso, std::string atributoDifuso) {
		
		
		for (int i = 0; i < atributosDifusos.size(); i++) {
			if (atributosDifusos[i].getNombre() == nombreAtributoDifuso) {
				double valor = (atributosDifusos[i]).getTipos()[atributoDifuso];
				return valor;
			}
		}
		return 1;  // La raiz siempre es 1, es decir siempre el elemento se puede clasificar.
	}

	void Elemento::clear()
	{
		atributosDifusos.clear();
	}
}