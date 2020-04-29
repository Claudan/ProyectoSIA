#ifndef MANIPULADORARCHIVOS_H
#define MANIPULADORARCHIVOS_H

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

namespace FID3Lib {

    class ManipuladorArchivos
    {
    private:
        std::string nombreyext;
        std::vector<std::string> ListaAtributos;
        std::vector<std::string> ListaRangos;

    public:
        ManipuladorArchivos(std::string);
        void agregaraListaAtributos(std::string);
        void agregaraListaRangos(std::string);
        void leerArchivo(std::string nombreArchivoSalida);
        void imprimirJugador();
        std::vector<float> agregaraVector( std::vector<float> , std::vector<float>);
        void agregaraCSV( std::vector<float> , std::ofstream&  );
        std::string NormalizarAtributos(std::string , double rango);

    };

}

#endif