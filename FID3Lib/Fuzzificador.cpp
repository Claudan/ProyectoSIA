#include "Fuzzificador.h"
#include <vector>

namespace FID3Lib {

	Fuzzificador::Fuzzificador()
	{
		x = 0;
	}

	std::string Fuzzificador::getX()
	{
		return std::to_string(x);
	}

	std::vector<float> Fuzzificador::getListaAtributos() {
		return valoresfuzzificados;
	}

	void Fuzzificador::limpiarValoresFuzzificados() {
		valoresfuzzificados.clear();
	}
	//------------------------------------------------------------------
	// Funciones de pertenencia triangulares para variables cualitativas 
	//----------------------------------------------------- ------------
	//3 Terminos cualitativos
	double Fuzzificador::funcionPertenenciaBMA(double x, std::string termino)
	{
		//x viene normalizado de 0 a 10
		double a, m, b;
		double valor = 0;
		if (termino == "BAJA") {
			a = 0;
			m = 2.5;
			b = 5;
		}
		else if (termino == "MEDIA") {
			a = 2.5;
			m = 5;
			b = 7.5;
		}
		else if (termino == "ALTA") {
			a = 5;
			m = 7.5;
			b = 10;
		}
		//Triangular
		if (x <= a) {
			valor = 0;
		}
		else if (x > a&& x <= m) {
			valor = (x - a) / (m - a);
		}
		else if (x > m&& x < b) {
			valor = (b - x) / (b - m);
		}
		else if (x >= b) {
			valor = 0;
		}
		return valor;
	}
	//2 Terminos cualitativos
	double Fuzzificador::funcionPertenenciaBA(double x, std::string termino)
	{
		//x viene normalizado de 0 a 10
		double a, m, b;
		double valor = 0;
		if (termino == "BAJA") {
			a = 0;
			m = (10 / 3);
			b = 2 * (10 / 3);
		}
		else if (termino == "ALTA") {
			a = (10 / 3);
			m = 2 * (10 / 3);
			b = 10;
		}
		//Triangular
		if (x <= a) {
			valor = 0;
		}
		else if (x > a&& x <= m) {
			valor = (x - a) / (m - a);
		}
		else if (x > m&& x < b) {
			valor = (b - x) / (b - m);
		}
		else if (x >= b) {
			valor = 0;
		}
		return valor;
	}

	// orden : inferior -> central -> superior
	void Fuzzificador::calcularAtributoPolivalencia(std::string rendimientoxposicion, std::string rendimientoxliga)
	{
		double _rendimientoxposicion, _rendimientoxliga;
		x = 0;
		std::stringstream(rendimientoxposicion) >> _rendimientoxposicion;
		if (!(std::stringstream(rendimientoxposicion) >> _rendimientoxposicion))
			_rendimientoxposicion = 0;
		std::stringstream(rendimientoxliga) >> _rendimientoxliga;
		if (!(std::stringstream(rendimientoxliga) >> _rendimientoxliga))
			_rendimientoxliga = 0;
		x = _rendimientoxposicion * 0.7 + _rendimientoxliga * 0.3;
		std::cout << " _rendimientoxliga: " << _rendimientoxliga << std::endl;
		std::cout << " _rendimientoxposicion: " << _rendimientoxposicion << std::endl;
		std::cout << " x: " << x << std::endl;
	}
	void Fuzzificador::fuzzificarAtributoPolivalencia()
	{
		std::cout << "x en polivalencia: " << x << std::endl;
		std::cout << "funcionPertenenciaBMA(x, BAJA): " << funcionPertenenciaBMA(x, "BAJA") << std::endl;
		std::cout << "funcionPertenenciaBMA(x, MEDIA): " << funcionPertenenciaBMA(x, "MEDIA") << std::endl;
		std::cout << "funcionPertenenciaBMA(x, ALTA): " << funcionPertenenciaBMA(x, "ALTA") << std::endl;
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "MEDIA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "ALTA"));
	}

	void Fuzzificador::calcularAtributoVision(std::string asistencias, std::string rendimientoxliga, std::string companerismo)
	{
		double _asistencias, _rendimientoxliga, _companerismo;
		x = 0;
		std::stringstream(asistencias) >> _asistencias;
		std::stringstream(rendimientoxliga) >> _rendimientoxliga;
		std::stringstream(companerismo) >> _companerismo;
		if (!(std::stringstream(asistencias) >> _asistencias))
			_asistencias = 0;
		if (!(std::stringstream(rendimientoxliga) >> _rendimientoxliga))
			_rendimientoxliga = 0;
		if (!(std::stringstream(companerismo) >> _companerismo))
			_companerismo = 0;
		std::stringstream(asistencias) >> _asistencias;
		std::stringstream(rendimientoxliga) >> _rendimientoxliga;
		std::stringstream(companerismo) >> _companerismo;
		x = _asistencias * 0.55 + _rendimientoxliga * 0.25 + _companerismo * 0.2;
	}
	std::vector<float> Fuzzificador::fuzzificarAtributoVision()
	{
		std::cout << "x en VISION: " << x << std::endl;
		std::cout << "funcionPertenenciaBA(x, BAJA): " << funcionPertenenciaBA(x, "BAJA") << std::endl;
		std::cout << "funcionPertenenciaBA(x, ALTA): " << funcionPertenenciaBA(x, "ALTA") << std::endl;
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "ALTA"));
		return valoresfuzzificados;
	}

	void Fuzzificador::calcularAtributoTemperamento(std::string  minutosjugados, std::string tarjetas, std::string desenpeno)
	{
		double _minutosjugados, _tarjetas, _madurezemocional, _desenpeno;
		x = 0;
		std::stringstream(minutosjugados) >> _minutosjugados;
		if (!(std::stringstream(minutosjugados) >> _minutosjugados))
			_minutosjugados = 0;
		std::stringstream(tarjetas) >> _tarjetas;
		if (!(std::stringstream(tarjetas) >> _tarjetas))
			_tarjetas = 0;
		std::stringstream(desenpeno) >> _desenpeno;
		if (!(std::stringstream(desenpeno) >> _desenpeno))
			_desenpeno = 0;
		x = _minutosjugados * 0.2 + _tarjetas * 0.35 + _desenpeno * 0.45;
	}
	std::vector<float> Fuzzificador::fuzzificarAtributoTemperamento()
	{
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "ALTA"));
		return valoresfuzzificados;
	}

	void Fuzzificador::calcularAtributoLiderazgo(std::string experiencia, std::string garra, std::string madurezemocional, std::string companerismo, std::string rendimientoxposicion)
	{
		double _experiencia, _garra, _madurezemocional, _companerismo, _rendimientoxposicion;
		x = 0;
		std::stringstream(experiencia) >> _experiencia;
		if (!(std::stringstream(experiencia) >> _experiencia))
			_experiencia = 0;
		std::stringstream(garra) >> _garra;
		if (!(std::stringstream(garra) >> _garra))
			_garra = 0;
		std::stringstream(madurezemocional) >> _madurezemocional;
		if (!(std::stringstream(madurezemocional) >> _madurezemocional))
			_madurezemocional = 0;
		std::stringstream(companerismo) >> _companerismo;
		if (!(std::stringstream(companerismo) >> _companerismo))
			_companerismo = 0;
		std::stringstream(rendimientoxposicion) >> _rendimientoxposicion;
		if (!(std::stringstream(rendimientoxposicion) >> _rendimientoxposicion))
			_rendimientoxposicion = 0;

		x = _experiencia * 0.3 + _garra * 0.25 + _madurezemocional * 0.2 + _companerismo * 0.1 + _rendimientoxposicion * 0.15;
	}
	std::vector<float> Fuzzificador::fuzzificarAtributoLiderazgo()
	{
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "ALTA"));
		return valoresfuzzificados;
	}

	void Fuzzificador::calcularAtributoMadurezEmocional(std::string edad, std::string rendimientoxposicion, std::string numeropartidosjugados, std::string tarjetas, std::string temperamento)
	{
		double _edad, _rendimientoxposicion, _numeropartidosjugados, _tarjetas, _temperamento;
		std::stringstream(edad) >> _edad;
		if (!(std::stringstream(edad) >> _edad))
			_edad = 0;
		std::stringstream(rendimientoxposicion) >> _rendimientoxposicion;
		if (!(std::stringstream(rendimientoxposicion) >> _rendimientoxposicion))
			_rendimientoxposicion = 0;
		std::stringstream(numeropartidosjugados) >> _numeropartidosjugados;
		if (!(std::stringstream(numeropartidosjugados) >> _numeropartidosjugados))
			_numeropartidosjugados = 0;
		std::stringstream(tarjetas) >> _tarjetas;
		if (!(std::stringstream(tarjetas) >> _tarjetas))
			_tarjetas = 0;
		std::stringstream(temperamento) >> _temperamento;
		if (!(std::stringstream(temperamento) >> _temperamento))
			_temperamento = 0;
		x = _edad * 0.25 + _rendimientoxposicion * 0.05 + _numeropartidosjugados * 0.3 + _tarjetas * 0.07 + _temperamento * 0.33;
	}
	std::vector<float> Fuzzificador::fuzzificarAtributoMadurezEmocional()
	{
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "ALTA"));
		return valoresfuzzificados;
	}

	void Fuzzificador::calcularAtributoGoleador(std::string goles, std::string asistencias, std::string rendimientoxposicion, std::string rendimientoxclub, std::string rendimientoxliga, std::string valormercado)
	{
		double _goles, _asistencias, _rendimientoxposicion, _rendimientoxclub, _rendimientoxliga, _valormercado;
		std::stringstream(goles) >> _goles;
		if (!(std::stringstream(goles) >> _goles))
			_goles = 0;
		std::stringstream(asistencias) >> _asistencias;
		if (!(std::stringstream(asistencias) >> _asistencias))
			_asistencias = 0;
		std::stringstream(rendimientoxposicion) >> _rendimientoxposicion;
		if (!(std::stringstream(rendimientoxposicion) >> _rendimientoxposicion))
			_rendimientoxposicion = 0;
		std::stringstream(rendimientoxclub) >> _rendimientoxclub;
		if (!(std::stringstream(rendimientoxclub) >> _rendimientoxclub))
			_rendimientoxclub = 0;
		std::stringstream(rendimientoxliga) >> _rendimientoxliga;
		if (!(std::stringstream(rendimientoxliga) >> _rendimientoxliga))
			_rendimientoxliga = 0;
		std::stringstream(valormercado) >> _valormercado;
		if (!(std::stringstream(valormercado) >> _valormercado))
			_rendimientoxliga = 0;
		x = _goles * 0.45 + _asistencias * 0.2 + _rendimientoxposicion * 0.15 + _rendimientoxclub * 0.1 + _rendimientoxliga * 0.05 + _valormercado * 0.05;
	}
	std::vector<float> Fuzzificador::fuzzificarAtributoGoleador()
	{
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "MEDIA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "ALTA"));
		return valoresfuzzificados;
	}

	void Fuzzificador::calcularAtributoConcentracionPartidosRelevantes(std::string edad, std::string nacionalidad, std::string numeropartidosjugados, std::string minutosjugados, std::string rendimientoxliga)
	{
		double _edad, _nacionalidad, _numeropartidosjugados, _minutosjugados, _rendimientoxliga;
		std::stringstream(edad) >> _edad;
		if (!(std::stringstream(edad) >> _edad))
			_edad = 0;
		std::stringstream(nacionalidad) >> _nacionalidad;
		if (!(std::stringstream(nacionalidad) >> _nacionalidad))
			_nacionalidad = 0;
		std::stringstream(numeropartidosjugados) >> _numeropartidosjugados;
		if (!(std::stringstream(numeropartidosjugados) >> _numeropartidosjugados))
			_numeropartidosjugados = 0;
		std::stringstream(minutosjugados) >> _minutosjugados;
		if (!(std::stringstream(minutosjugados) >> _minutosjugados))
			_minutosjugados = 0;
		std::stringstream(rendimientoxliga) >> _rendimientoxliga;
		if (!(std::stringstream(rendimientoxliga) >> _rendimientoxliga))
			_rendimientoxliga = 0;
		x = _edad * 0.25 + _nacionalidad * 0.13 + _numeropartidosjugados * 0.35 + _minutosjugados * 0.17 + _rendimientoxliga * 0.1;
	}
	std::vector<float> Fuzzificador::fuzzificarAtributoConcentracionPartidosRelevantes()
	{
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "ALTA"));
		return valoresfuzzificados;
	}

	void Fuzzificador::calcularAtributoCompanerismo(std::string asistencias, std::string numeropartidosjugados, std::string puntajepromediopartidos, std::string madurezemocional)
	{
		double _asistencias, _numeropartidosjugados, _puntajepromediopartidos, _madurezemocional;
		std::stringstream(asistencias) >> _asistencias;
		if (!(std::stringstream(asistencias) >> _asistencias))
			_asistencias = 0;
		std::stringstream(numeropartidosjugados) >> _numeropartidosjugados;
		if (!(std::stringstream(numeropartidosjugados) >> _numeropartidosjugados))
			_numeropartidosjugados = 0;
		std::stringstream(puntajepromediopartidos) >> _puntajepromediopartidos;
		if (!(std::stringstream(puntajepromediopartidos) >> _puntajepromediopartidos))
			_puntajepromediopartidos = 0;
		std::stringstream(madurezemocional) >> _madurezemocional;
		if (!(std::stringstream(madurezemocional) >> _madurezemocional))
			_madurezemocional = 0;
		x = _asistencias * 0.45 + _numeropartidosjugados * 0.1 + _puntajepromediopartidos * 0.25 + _madurezemocional * 0.2;
	}
	std::vector<float> Fuzzificador::fuzzificarAtributoCompanerismo()
	{
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "ALTA"));
		return valoresfuzzificados;
	}

	void  Fuzzificador::calcularAtributoExperiencia(std::string numeropartidosjugados, std::string rendimientoxposicion, std::string edad, std::string valormercado)
	{
		double _numeropartidosjugados, _rendimientoxposicion, _edad, _valormercado;
		std::stringstream(numeropartidosjugados) >> _numeropartidosjugados;
		if (!(std::stringstream(numeropartidosjugados) >> _numeropartidosjugados))
			_numeropartidosjugados = 0;
		std::stringstream(rendimientoxposicion) >> _rendimientoxposicion;
		if (!(std::stringstream(rendimientoxposicion) >> _rendimientoxposicion))
			_rendimientoxposicion = 0;
		std::stringstream(edad) >> _edad;
		if (!(std::stringstream(edad) >> _edad))
			_edad = 0;
		std::stringstream(valormercado) >> _valormercado;
		if (!(std::stringstream(valormercado) >> _valormercado))
			_valormercado = 0;
		//falta conocer los rangos
		x = _numeropartidosjugados * 0.45 + _rendimientoxposicion * 0.4 + _edad * 0.1 + _valormercado * 0.05;
	}
	std::vector<float>  Fuzzificador::fuzzificarAtributoExperiencia()
	{
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "MEDIA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "ALTA"));
		return valoresfuzzificados;
	}

	void Fuzzificador::calcularAtributoGarra(std::string rendimientoxposicion, std::string nacionalidad, std::string edad, std::string rendimientoxclub, std::string rendimientoxliga, std::string numeropartidosjugados)
	{
		double _rendimientoxposicion, _nacionalidad, _edad, _rendimientoxclub, _rendimientoxliga, _numeropartidosjugados;

		std::stringstream(nacionalidad) >> _nacionalidad;
		if (!(std::stringstream(nacionalidad) >> _nacionalidad))
			_nacionalidad = 0;
		std::stringstream(edad) >> _edad;
		if (!(std::stringstream(edad) >> _edad))
			_edad = 0;
		std::stringstream(numeropartidosjugados) >> _numeropartidosjugados;
		if (!(std::stringstream(numeropartidosjugados) >> _numeropartidosjugados))
			_numeropartidosjugados = 0;

		std::stringstream(rendimientoxposicion) >> _rendimientoxposicion;
		if (!(std::stringstream(rendimientoxposicion) >> _rendimientoxposicion))
			_rendimientoxposicion = 0;
		std::stringstream(rendimientoxclub) >> _rendimientoxclub;
		if (!(std::stringstream(rendimientoxclub) >> _rendimientoxclub))
			_rendimientoxclub = 0;
		std::stringstream(rendimientoxliga) >> _rendimientoxliga;
		if (!(std::stringstream(rendimientoxliga) >> _rendimientoxliga))
			_rendimientoxliga = 0;
		x = _rendimientoxposicion * 0.05 + _nacionalidad * 0.2 + _edad * 0.05 + _rendimientoxclub * 0.25 + _rendimientoxliga * 0.3 + _numeropartidosjugados * 0.15;
	}
	std::vector<float> Fuzzificador::fuzzificarAtributoGarra()
	{
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBA(x, "ALTA"));
		return valoresfuzzificados;
	}

	void  Fuzzificador::calcularAtributoBiorritmo(int ciclofisico, int cicloemocional, int ciclointelectual)
	{
		x = (ciclofisico + cicloemocional + ciclointelectual) / 3;
	}
	std::vector<float>  Fuzzificador::fuzzificarAtributoBiorritmo()
	{
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "MEDIA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "ALTA"));
		return valoresfuzzificados;
	}

	void Fuzzificador::calcularAtributoSalud(std::string edad, std::string minutosjugados, std::string rendimientoxposicion, std::string rendimientoxliga, std::string numeropartidosjugados)
	{
		double _edad, _minutosjugados, _posicionactual, _rendimientoxposicion, _rendimientoxliga, _numeropartidosjugados;
		std::stringstream(edad) >> _edad;
		if (!(std::stringstream(edad) >> _edad))
			_edad = 0;
		std::stringstream(minutosjugados) >> _minutosjugados;
		if (!(std::stringstream(minutosjugados) >> _minutosjugados))
			_minutosjugados = 0;
		std::stringstream(rendimientoxposicion) >> _rendimientoxposicion;
		if (!(std::stringstream(rendimientoxposicion) >> _rendimientoxposicion))
			_rendimientoxposicion = 0;

		std::stringstream(rendimientoxliga) >> _rendimientoxliga;
		if (!(std::stringstream(rendimientoxliga) >> _rendimientoxliga))
			_rendimientoxliga = 0;
		std::stringstream(numeropartidosjugados) >> _numeropartidosjugados;
		if (!(std::stringstream(numeropartidosjugados) >> _numeropartidosjugados))
			_numeropartidosjugados = 0;
		x = _edad * 0.34 + _minutosjugados * 0.25 + _rendimientoxposicion * 0.18 + _rendimientoxliga * 0.18 + _numeropartidosjugados * 0.1;
	}
	std::vector<float> Fuzzificador::fuzzificarAtributoSalud()
	{
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "MEDIA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "ALTA"));
		return valoresfuzzificados;
	}

	void Fuzzificador::calcularAtributoDesempeno(std::string minutosjugados, std::string numeropartidosjugados, std::string rendimientoxposicion, std::string rendimientoxclub, std::string rendimientoxliga)
	{
		double _minutosjugados, _numeropartidosjugados, _rendimientoxposicion, _rendimientoxclub, _rendimientoxliga;
		std::stringstream(minutosjugados) >> _minutosjugados;
		if (!(std::stringstream(minutosjugados) >> _minutosjugados))
			_minutosjugados = 0;
		std::stringstream(rendimientoxposicion) >> _rendimientoxposicion;
		if (!(std::stringstream(rendimientoxposicion) >> _rendimientoxposicion))
			_rendimientoxposicion = 0;

		std::stringstream(rendimientoxliga) >> _rendimientoxliga;
		if (!(std::stringstream(rendimientoxliga) >> _rendimientoxliga))
			_rendimientoxliga = 0;
		std::stringstream(numeropartidosjugados) >> _numeropartidosjugados;
		if (!(std::stringstream(numeropartidosjugados) >> _numeropartidosjugados))
			_numeropartidosjugados = 0;
		std::stringstream(rendimientoxclub) >> _rendimientoxclub;
		if (!(std::stringstream(rendimientoxclub) >> _rendimientoxclub))
			_rendimientoxclub = 0;
		x = _minutosjugados * 0.15 + _numeropartidosjugados * 0.2 + _rendimientoxposicion * 0.35 + _rendimientoxclub * 0.2 + _rendimientoxliga * 0.1;
	}
	std::vector<float> Fuzzificador::fuzzificarAtributoDesempeno()
	{
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "BAJA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "MEDIA"));
		valoresfuzzificados.insert(valoresfuzzificados.end(), funcionPertenenciaBMA(x, "ALTA"));
		return valoresfuzzificados;
	}

}