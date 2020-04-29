#ifndef FUZZIFICADOR_H
#define FUZZIFICADOR_H

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

namespace FID3Lib {

	class Fuzzificador
	{
	private:
		double x;
		std::vector<float> valoresfuzzificados;

	public:
		Fuzzificador();
		std::string getX();

		void calcularAtributoPolivalencia(std::string rendimientoxposicion, std::string rendimientoxliga);
		void calcularAtributoVision(std::string asistencias, std::string rendimientoxliga, std::string companerismo);
		void calcularAtributoTemperamento(std::string  minutosjugados, std::string tarjetas, std::string desenpeno);
		void calcularAtributoLiderazgo(std::string experiencia, std::string garra, std::string madurezemocional, std::string companerismo, std::string rendimientoxposicion);
		void calcularAtributoMadurezEmocional(std::string edad, std::string rendimientoxposicion, std::string numeropartidosjugados, std::string tarjetas, std::string temperamento);
		void calcularAtributoGoleador(std::string goles, std::string asistencias, std::string rendimientoxposicion, std::string rendimientoxclub, std::string rendimientoxliga, std::string valormercado);
		void calcularAtributoConcentracionPartidosRelevantes(std::string edad, std::string nacionalidad, std::string numeropartidosjugados, std::string minutosjugados, std::string rendimientoxliga);
		void calcularAtributoCompanerismo(std::string asistencias, std::string numeropartidosjugados, std::string puntajepromediopartidos, std::string madurezemocional);
		void calcularAtributoExperiencia(std::string numeropartidosjugados, std::string rendimientoxposicion, std::string edad, std::string valormercado);
		void calcularAtributoGarra(std::string rendimientoxposicion, std::string nacionalidad, std::string edad, std::string rendimientoxclub, std::string rendimientoxliga, std::string numeropartidosjugados);
		void calcularAtributoBiorritmo(int ciclofisico, int cicloemocional, int ciclointelectual);
		void calcularAtributoSalud(std::string edad, std::string minutosjugados, std::string rendimientoxposicion, std::string rendimientoxliga, std::string numeropartidosjugados);
		void calcularAtributoDesempeno(std::string minutosjugados, std::string numeropartidosjugados, std::string rendimientoxposicion, std::string rendimientoxclub, std::string rendimientoxliga);

		void fuzzificarAtributoPolivalencia();
		std::vector<float> fuzzificarAtributoVision();
		std::vector<float> fuzzificarAtributoTemperamento();
		std::vector<float> fuzzificarAtributoLiderazgo();
		std::vector<float> fuzzificarAtributoMadurezEmocional();
		std::vector<float> fuzzificarAtributoGoleador();
		std::vector<float> fuzzificarAtributoConcentracionPartidosRelevantes();
		std::vector<float> fuzzificarAtributoCompanerismo();
		std::vector<float> fuzzificarAtributoExperiencia();
		std::vector<float> fuzzificarAtributoGarra();
		std::vector<float> fuzzificarAtributoBiorritmo();
		std::vector<float> fuzzificarAtributoSalud();
		std::vector<float> fuzzificarAtributoDesempeno();

		std::vector<float> getListaAtributos();
		void limpiarValoresFuzzificados();

		double funcionPertenenciaBMA(double x, std::string termino);
		double funcionPertenenciaBA(double x, std::string termino);
	};
}
#endif