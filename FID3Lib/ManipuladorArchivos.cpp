#include <algorithm>
#include <sstream>
#include "ManipuladorArchivos.h"
#include "Fuzzificador.h"


namespace FID3Lib {

    ManipuladorArchivos::ManipuladorArchivos(std::string _nombreyext) {
        nombreyext = _nombreyext;
    }


	void ManipuladorArchivos::agregaraListaAtributos(std::string atributo) 
	{
		ListaAtributos.insert(ListaAtributos.end() , atributo);
	}
	
	void ManipuladorArchivos::agregaraListaRangos(std::string rango) 
	{
		ListaRangos.insert(ListaRangos.end(), rango);
	}


    void ManipuladorArchivos::leerArchivo(std::string nombreArchivoSalida)
    {
		std::ifstream ip(nombreyext); //CAMBIAR POR EL nombreyext
		
		std::ofstream archivoSalida;
		archivoSalida.open(nombreArchivoSalida, std::ios::out);
		//archivoSalida.open("DataFuzzy.csv", std::ios::out);
		archivoSalida.close();
		

		if (!ip.is_open()) 
		{
			std::cout << "ERROR al abrir DataSet.csv" << '\n';
		}
		else 
		{
			std::vector<std::vector<std::string>> ListadoFinalJugadores;
			std::vector<double> ListaRangosCSV;
			
	   		int jugadores = 1;
			while ((ip.good()) && (jugadores <= 180)) {
				if(jugadores > 1){
					std::vector<std::string> ListaAtributosJugadores;
					std::string token;
					//Completar los Atributos del archivo de entrenamiento.
					std::string parcial;
					for (int i = 0; i < 15; i++) {		
						std::string valor;						
						if(i<14)
						{
							getline(ip, valor, ';');
						}
						else
						{
							getline(ip, valor, '\n');
						}
						ListaAtributosJugadores.insert(ListaAtributosJugadores.end(), valor);
					}
				
					//Fuzzificar Entrada: atributos de un jugador 1-10 o atributos difusos 1-10 , Salida : csv con valores fuzzificados y al final su respectiva clase de jugador.
					ListadoFinalJugadores.insert(ListadoFinalJugadores.end(), ListaAtributosJugadores);
					
					if (jugadores <= 2) {
						for (unsigned int i = 0; i < ListaAtributosJugadores.size(); i++) {
							ListaRangosCSV.insert(ListaRangosCSV.end(), 0);
						}
					}
					double rango;
					for (unsigned int i = 0; i < ListaAtributosJugadores.size(); i++) {
						std::stringstream(ListaAtributosJugadores[i]) >> rango;
						if (rango != -1 && rango>ListaRangosCSV[i])
						{
							ListaRangosCSV[i] = rango;
						}
					}
					ListaAtributosJugadores.clear();
				}
				jugadores++;
				
			}
			
			ip.close();
			for (unsigned int i = 0; i < ListadoFinalJugadores.size(); i++) {
				
				float dias;
				std::stringstream(ListadoFinalJugadores[i][2]) >> dias;
				float ciclofisico = sin(2 * dias * 3.14 / 23), cicloemocional = sin(2 * dias * 3.14 / 28), ciclointelectual = sin(2 * dias * 3.14 / 33);
				std::string nombre = ListadoFinalJugadores[i][0];
				for (int j = 0; j < ListadoFinalJugadores[i].size(); j++) {
					float rango;
					if (j != 14) {
						std::stringstream(ListadoFinalJugadores[i][j]) >> rango;
						if (rango != -1)
						{
							ListadoFinalJugadores[i][j] = NormalizarAtributos(ListadoFinalJugadores[i][j], ListaRangosCSV[j]);
						}
					}
				}
				//Atributos Discretos Normalizados
				//std::string nombre = ListadoFinalJugadores[i][0];
				std::string edad = ListadoFinalJugadores[i][1];
				//float dias;
				std::string nacionalidad = ListadoFinalJugadores[i][3];
				std::string valormercado = ListadoFinalJugadores[i][4];
				std::string partidos = ListadoFinalJugadores[i][5];
				std::string puntos = ListadoFinalJugadores[i][6];
				std::string goles = ListadoFinalJugadores[i][7];
				std::string asistencias = ListadoFinalJugadores[i][8];
				std::string tarjetas = ListadoFinalJugadores[i][9];
				std::string minutos = ListadoFinalJugadores[i][10];
				std::string rendimientoxposicion = ListadoFinalJugadores[i][11];
				std::string rendimientoxliga = ListadoFinalJugadores[i][12];
				std::string rendimientoxclub = ListadoFinalJugadores[i][13];
				std::string claseJugador = ListadoFinalJugadores[i][14];
				std::cout << "CLASE DEL JUGADOR: " <<claseJugador << "\n";
				//FUZZY
				std::vector<float> atributosFuzzificados;
				Fuzzificador fuzzificador;
				
				std::string madurezEmocional, companerismo, experiencia, garra;
				
				fuzzificador.calcularAtributoPolivalencia(rendimientoxposicion, rendimientoxliga);
				fuzzificador.fuzzificarAtributoPolivalencia();
				
				fuzzificador.calcularAtributoGoleador(goles, asistencias, rendimientoxposicion, rendimientoxclub, rendimientoxliga, valormercado);
				fuzzificador.fuzzificarAtributoGoleador();
				
			/*	fuzzificador.calcularAtributoConcentracionPartidosRelevantes(edad, nacionalidad, partidos, minutos, rendimientoxliga);
				fuzzificador.fuzzificarAtributoConcentracionPartidosRelevantes();
			*/

				fuzzificador.calcularAtributoExperiencia(partidos, rendimientoxposicion, edad, valormercado);
				experiencia = fuzzificador.getX();
				fuzzificador.fuzzificarAtributoExperiencia();
				
			/*	fuzzificador.calcularAtributoGarra(rendimientoxposicion, nacionalidad, edad, rendimientoxclub, rendimientoxliga, partidos);
			    fuzzificador.fuzzificarAtributoGarra();
			
				fuzzificador.calcularAtributoBiorritmo(ciclofisico, cicloemocional, ciclointelectual);
				fuzzificador.fuzzificarAtributoBiorritmo();
			*/
				fuzzificador.calcularAtributoSalud(edad, minutos, rendimientoxposicion, rendimientoxliga, partidos);
				fuzzificador.fuzzificarAtributoSalud();
				
			/*	fuzzificador.calcularAtributoDesempeno( minutos, partidos, rendimientoxposicion, rendimientoxclub, rendimientoxliga);
				fuzzificador.fuzzificarAtributoDesempeno();
				garra = fuzzificador.getX();
			 */
				std::string desenpeno = fuzzificador.getX();
				fuzzificador.calcularAtributoTemperamento(minutos, tarjetas, desenpeno);
				fuzzificador.fuzzificarAtributoTemperamento();

			/*	std::string temperamento = fuzzificador.getX();
				fuzzificador.calcularAtributoMadurezEmocional(edad, rendimientoxposicion, partidos, tarjetas, temperamento);
				
				madurezEmocional = fuzzificador.getX();
				fuzzificador.fuzzificarAtributoMadurezEmocional();
				
				madurezEmocional = fuzzificador.getX();
				fuzzificador.calcularAtributoCompanerismo(asistencias, partidos, puntos, madurezEmocional);
			
				companerismo = fuzzificador.getX();
				fuzzificador.fuzzificarAtributoCompanerismo();
				
				fuzzificador.calcularAtributoVision(asistencias, rendimientoxliga, fuzzificador.getX());
				fuzzificador.fuzzificarAtributoVision();

				fuzzificador.calcularAtributoLiderazgo(experiencia, garra, madurezEmocional, companerismo, rendimientoxposicion);
				fuzzificador.fuzzificarAtributoLiderazgo();
			*/
				std::ofstream archivoSalida;
				//archivoSalida.open("DataFuzzy.csv", std::ios::out | std::ios::app);
				archivoSalida.open(nombreArchivoSalida, std::ios::out | std::ios::app);

				//atributosFuzzificados.insert(atributosFuzzificados.end(), claseJugador);
				std::cout << "ATRIBUTOS FUZIFICADOS: " << fuzzificador.getListaAtributos().size() << std::endl;
				//std::cout << "CLASE JUGADOR: " << claseJugador << std::endl;
				archivoSalida << nombre + ";";
				if (claseJugador != "") {
					agregaraCSV(fuzzificador.getListaAtributos(), archivoSalida);
					archivoSalida << claseJugador + "\n";

					archivoSalida.close();
				}

				fuzzificador.limpiarValoresFuzzificados();
				
			}
			


		}

	}

	void ManipuladorArchivos::imprimirJugador()
	{
		std::cout << "Nombre : " << ListaAtributos[0] << '\n';
		std::cout << "Altura: " << ListaAtributos[1] << '\n';
		std::cout << "Edad: " << ListaAtributos[2] << '\n';
		std::cout << "Dias " << ListaAtributos[3] << '\n';
		std::cout << "Nacionalidad: " << ListaAtributos[4] << '\n';
		std::cout << "Equipo_Actual: " << ListaAtributos[5] << '\n';
		std::cout << "Posici�n_Actual: " << ListaAtributos[6] << '\n';
		std::cout << "Valor_Mercado: " << ListaAtributos[7] << '\n';
		std::cout << "N�mero_de_Partidos_Jugados: " << ListaAtributos[8] << '\n';
		std::cout << "Puntaje_promedio_de_los_partidos_jugados: " << ListaAtributos[9] << '\n';
		std::cout << "Goles: " << ListaAtributos[10] << '\n';
		std::cout << "Asistencias: " << ListaAtributos[11] << '\n';
		std::cout << "Tarjetas: " << ListaAtributos[12] << '\n';
		std::cout << "Minutos_Jugados: " << ListaAtributos[13] << '\n';
		std::cout << "Rendimiento_por_posici�n: " << ListaAtributos[14] << '\n';
		std::cout << "Rendimiento_por_club: " << ListaAtributos[15] << '\n';
		std::cout << "Rendimiento_por_liga: " << ListaAtributos[16] << '\n';
		std::cout << "--------------" << '\n';
	}

	void ManipuladorArchivos::agregaraCSV(std::vector<float> atributosFuzzificados , std::ofstream &archivoCSV ) 
	{
		std::vector<float>::iterator it = atributosFuzzificados.begin();
		for (it; it != atributosFuzzificados.end(); it++)
		{
			archivoCSV << std::to_string(*it) + ";";
		}
	}

	std::vector<float> ManipuladorArchivos::agregaraVector(std::vector<float> listaAtributosFuzzificadosORIGINAL, std::vector<float> atributoFuzzificado)
	{
		std::vector<float>::iterator it = atributoFuzzificado.begin();
		for (it; it != atributoFuzzificado.end(); it++)
		{
			listaAtributosFuzzificadosORIGINAL.insert(listaAtributosFuzzificadosORIGINAL.end() , *it);
		} 
		return listaAtributosFuzzificadosORIGINAL;


	}

	std::string ManipuladorArchivos::NormalizarAtributos(std::string valor, double _rango) 
	{
		float _valor, normalizado;
		std::stringstream(valor) >> _valor;
		normalizado = _valor / _rango;
		normalizado = normalizado / 0.1;
		if (_rango == 0 || normalizado<0)
			return "0";
		std::ostringstream ss;
		ss << normalizado;
		return ss.str();
	}


}


