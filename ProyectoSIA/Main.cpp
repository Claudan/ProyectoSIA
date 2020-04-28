#include <iostream>
#include <string>
#include <vector>

#include "ExpertoLib.h"
#include "GeneticoLib.h"
//#include "FID3Lib.h"

using namespace std;
using namespace ExpertoLib;
using namespace GeneticoLib;
//using namespace FID3Lib;

Experto conocimientoExpertoFIFA();

int main()
{
    /*Experto exp = conocimientoExpertoFIFA();
    exp.generaGrafico();

    vector<string> input = { "4-4-2", "Defensiva", "Posesion","4-5-1", "4-3-2-1", "Contraataque", "Directo" };
    vector<vector<string>> soluciones = exp.infiereTodasLasSolucionesBC(input);*/
    
    string rutaarchivoplantel ="..\\GeneticoLib\\Polivalencia_coquimbo.csv";
    string rutasinergias = "..\\GeneticoLib\\sinergiaCoquimbo.txt";
    string rutaRoles = "..\\GeneticoLib\\Formaciones\\Formacion1.txt";
    Plantel plantel;
    plantel.cargarArchivo(rutaarchivoplantel, rutasinergias);
    string forTactica = devolverForTactica(rutaRoles);
    int * rol = devolverRoles(rutaRoles);
    char modo = devolverModo(rutaRoles);
    vector<Formacion> sol;
    //nombrearchivoplantel, roljugadores, porcentajemutacion, iteraciones, poblacion,porcentaje mutacion, de 0 a 100,cantidad generaciones maxima,tamano poblacion
	sol=Genetico(plantel,rol,modo,forTactica,50,5000,20);
    for (int i = 0; i < sol.size(); i++) sol.at(i).ImprimirFormacion();
    entregarResultados(plantel, sol, rol, forTactica);

    return(0);
}

int mainIdealPrototipoSIA() {
    //PASOS:

    //ESTADO: FUNCIONANDO
    //-----------------------------------------
    // 1. ExpertoLib (Librería Sistema Experto)
    //-----------------------------------------
    // Generamos un arbol dinámico con 34 reglas FIFA (preparado para ser consultado)
    // Al ser consultado retorna las formaciones detalladas ideales  
    // para contrarrestar una formación enemiga dada
    
    //ESTADO: PENDIENTE 
    //---------------------------------
    // 2. FID3Lib (Librería ID3 difuso)
    //---------------------------------
    //Generamos un arbol con reglas difusas para clasificar a cada jugador 
    //de acuerdo a su polivalencia (que tan "aptos" son para cada posición)
   
    //ESTADO: FUNCIONANDO
    //------------------------------------------------
    // 3. GeneticoLib (Librería de Algoritmo Genético)
    //------------------------------------------------
    // Este Algoritmo (Genético) permite optimizar el equipo.
    // Obtiene la mejor posición y jugadores que deberían estar en dichas posiciones 
    // Dada la formación del equipo que contrarreste el equipo rival, 
    // la polivalencia de los jugadores y sinergia

    return(0);
}

Experto conocimientoExpertoFIFA()
{
    Experto exp = Experto();

    vector<string> condiciones;
    string consecuencia;
    string formacionGuia;
 
    //Insertar regla 3-1-4-2
    consecuencia = "3-1-4-2/A";
    condiciones = { "4-4-1-1", "Ofensiva" };
    formacionGuia = "3,3,3,6,7,7,8,8,13,13;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar regla 3-4-1-2
    consecuencia = "3-4-1-2/A";
    condiciones = { "4-2-2-2", "Ofensiva", "Atacar" }; //equipo rival, estrategia, modo de juego
    formacionGuia = "3,3,3,7,7,8,8,9,13,13;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));
    
    //Insertar 3-4-2-1
    consecuencia = "3-4-2-1/A";
    condiciones = { "4-1-2-1-2", "Ofensiva", "Atacar" };
    formacionGuia = "3,3,3,7,7,8,8,12,12,13;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-4-2-1/B";
    condiciones = { "4-3-3", "Ofensiva", "Atacar" };
    formacionGuia = "3,3,3,7,7,8,8,12,12,13;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-4-2-1/C";
    condiciones = { "4-4-2", "Ofensiva", "Atacar" };
    formacionGuia = "3,3,3,7,7,8,8,12,12,13;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));
  
    //Insertar 3-4-3
    consecuencia = "3-4-3/A";
    condiciones = { "4-1-4-1", "Ofensiva" };
    formacionGuia = "3,3,3,7,7,8,8,13,14,15;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-4-3/B";
    condiciones = { "4-3-1-2", "Ofensiva" };
    formacionGuia = "3,3,3,7,7,8,8,13,14,15;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-4-3/C";
    condiciones = { "4-4-2", "Ofensiva", "Banda" };
    formacionGuia = "3,3,3,7,7,8,8,13,14,15;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-4-3/D";
    condiciones = { "4-5-1", "Ofensiva", "Banda" };
    formacionGuia = "3,3,3,7,7,8,8,13,14,15;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));
 
    //Insertar 3-5-2
    consecuencia = "3-5-2/A";
    condiciones = { "4-1-2-1-2", "Ofensiva", "Contraataque" };
    formacionGuia = "3,3,3,6,6,8,8,9,13,13;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-5-2/B";
    condiciones = { "4-2-2-2", "Ofensiva", "Contraataque" };
    formacionGuia = "3,3,3,6,6,8,8,9,13,13;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-5-2/C";
    condiciones = { "4-3-3", "Ofensiva", "Contraataque" };
    formacionGuia = "3,3,3,6,6,8,8,9,13,13;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-5-2/D";
    condiciones = { "4-4-2", "Ofensiva", "Contraataque" };
    formacionGuia = "3,3,3,6,6,8,8,9,13,13;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-5-2/E";
    condiciones = { "4-5-1", "Ofensiva", "Contraataque" };
    formacionGuia = "3,3,3,6,6,8,8,9,13,13;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-5-2/F";
    condiciones = { "5-2-2-1", "Ofensiva" };
    formacionGuia = "3,3,3,6,6,8,8,9,13,13;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-5-2/G";
    condiciones = { "5-4-1", "Ofensiva", "Contraataque" };
    formacionGuia = "3,3,3,6,6,8,8,9,13,13;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));
    
    //Insertar 4-1-2-1-2
    consecuencia = "4-1-2-1-2/A";
    condiciones = { "4-2-3-1", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "3,3,4,5,6,8,8,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-1-2-1-2/B";
    condiciones = { "4-3-3", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "3,3,4,5,6,8,8,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-1-2-1-2/C";
    condiciones = { "3-4-1-2", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "3,3,4,5,6,8,8,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));
    
    //Insertar 4-1-2-1-2 (2)
    consecuencia = "4-1-2-1-2 (2)/A";
    condiciones = { "4-2-3-1", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "3,3,4,5,6,7,7,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-1-3-2
    consecuencia = "4-1-3-2/A";
    condiciones = { "3-1-4-2", "Balanceada", "Atacar", "Directo" };
    formacionGuia = "3,3,4,5,6,7,8,8,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-1-3-2/B";
    condiciones = { "3-5-2", "Balanceada", "Atacar", "Directo" };
    formacionGuia = "3,3,4,5,6,7,8,8,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));
   
    //Insertar 4-1-4-1
    consecuencia = "4-1-4-1/A";
    condiciones = { "4-3-3", "Balanceada", "Corto" };
    formacionGuia = "3,3,4,5,6,7,7,8,8,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-2-2-2
    consecuencia = "4-2-2-2/A";
    condiciones = { "3-4-2-1", "Balanceada", "Largos" };
    formacionGuia = "3,3,4,5,6,6,9,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-2-2/B";
    condiciones = { "4-2-3-1", "Balanceada", "Largos" };
    formacionGuia = "3,3,4,5,6,6,9,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-2-2/C";
    condiciones = { "4-3-3", "Balanceada", "Largos" };
    formacionGuia = "3,3,4,5,6,6,9,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-2-2/D";
    condiciones = { "4-5-1", "Balanceada", "Largos" };
    formacionGuia = "3,3,4,5,6,6,9,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-2-3-1
    consecuencia = "4-2-3-1/A";
    condiciones = { "3-4-1-2", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/B";
    condiciones = { "3-4-2-1", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/C";
    condiciones = { "3-4-3", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/D";
    condiciones = { "4-1-4-1", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/E";
    condiciones = { "4-2-2-2", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/F";
    condiciones = { "4-2-4", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/G";
    condiciones = { "4-3-1-2", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/H";
    condiciones = { "4-3-2-1", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/I";
    condiciones = { "4-3-3", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/J";
    condiciones = { "4-4-1-1", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/K";
    condiciones = { "4-4-2", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/L";
    condiciones = { "4-5-1", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/M";
    condiciones = { "5-2-2-1", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,9,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));


    //Insertar 4-2-3-1 (2)
    consecuencia = "4-2-3-1 (2)/A";
    condiciones = { "4-3-1-2", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "3,3,4,5,6,6,8,8,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-3-1-2
    consecuencia = "4-3-1-2/A";
    condiciones = { "3-1-4-2", "Balanceada", "Posesion", "Directo" };
    formacionGuia = "3,3,4,5,7,7,7,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-1-2/B";
    condiciones = { "3-4-3", "Balanceada", "Posesion" };
    formacionGuia = "3,3,4,5,7,7,7,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-1-2/C";
    condiciones = { "3-5-2", "Balanceada", "Posesion", "Directo" };
    formacionGuia = "3,3,4,5,7,7,7,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-1-2/D";
    condiciones = { "4-3-2-1", "Balanceada", "Posesion", "Directo" };
    formacionGuia = "3,3,4,5,7,7,7,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-1-2/E";
    condiciones = { "4-3-3", "Balanceada", "Posesion", "Directo" };
    formacionGuia = "3,3,4,5,7,7,7,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-1-2/F";
    condiciones = { "5-3-2", "Balanceada", "Posesion", "Directo" };
    formacionGuia = "3,3,4,5,7,7,7,9,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-3-2-1
    consecuencia = "4-3-2-1/A";
    condiciones = { "5-3-2", "Balanceada", "Contraataque" }; //Aun pensar.
    formacionGuia = "3,3,4,5,7,7,7,12,12,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-2-1/B";
    condiciones = { "5-4-1", "Balanceada", "Contraataque" };
    formacionGuia = "3,3,4,5,7,7,7,12,12,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-3-3
    consecuencia = "4-3-3/A";
    condiciones = { "4-1-3-2", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,7,13,14,15;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/B";
    condiciones = { "4-1-4-1", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,7,13,14,15;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/C";
    condiciones = { "4-2-2-2", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,7,13,14,15;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/D";
    condiciones = { "4-2-4", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,7,13,14,15;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/E";
    condiciones = { "4-4-1-1", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,7,13,14,15;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/F";
    condiciones = { "5-2-1-2", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,7,13,14,15;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/G";
    condiciones = { "5-2-2-1", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,7,13,14,15;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/H";
    condiciones = { "5-3-2", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,7,13,14,15;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-3-3 (2)
    consecuencia = "4-3-3 (2)/A";
    condiciones = { "4-1-3-2", "Balanceada", "Posesion", "Banda", "Corto" };
    formacionGuia = "3,3,4,5,6,7,7,13,14,15;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));


    //Insertar 4-3-3 (3)
    consecuencia = "4-3-3 (3)/A";
    condiciones = { "3-4-2-1", "Defensiva", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,6,6,7,13,14,15;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3 (3)/B";
    condiciones = { "3-4-1-2", "Defensiva", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,6,6,7,13,14,15;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3 (3)/C";
    condiciones = { "4-5-1", "Defensiva", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,6,6,7,13,14,15;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-3-3 (4)
    consecuencia = "4-3-3 (4)/A";
    condiciones = { "3-1-4-2", "Ofensiva", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,9,13,14,15;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3 (4)/B";
    condiciones = { "3-5-2", "Ofensiva", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,9,13,14,15;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3 (4)/C";
    condiciones = { "4-3-3", "Ofensiva", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,9,13,14,15;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3 (4)/D";
    condiciones = { "5-3-2", "Ofensiva", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,9,13,14,15;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3 (4)/E";
    condiciones = { "5-4-1", "Ofensiva", "Contraataque", "Banda" };
    formacionGuia = "3,3,4,5,7,7,9,13,14,15;O";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-4-1-1
    consecuencia = "4-4-1-1/A";
    condiciones = { "4-1-2-1-2", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "3,3,4,5,7,7,8,8,12,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-1-1/B";
    condiciones = { "4-3-3", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "3,3,4,5,7,7,8,8,12,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-1-1/C";
    condiciones = { "4-4-2", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "3,3,4,5,7,7,8,8,12,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-1-1/D";
    condiciones = { "5-2-2-1", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "3,3,4,5,7,7,8,8,12,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));
    
    //Insertar 4-4-2
    consecuencia = "4-4-2/A";
    condiciones = { "4-1-3-2", "Balanceada", "Posesion" };
    formacionGuia = "3,3,4,5,7,7,8,8,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-2/B";
    condiciones = { "4-2-3-1", "Balanceada", "Posesion" };
    formacionGuia = "3,3,4,5,7,7,8,8,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-2/C";
    condiciones = { "4-2-4", "Balanceada", "Posesion" };
    formacionGuia = "3,3,4,5,7,7,8,8,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-2/D";
    condiciones = { "4-3-3", "Balanceada", "Posesion" };
    formacionGuia = "3,3,4,5,7,7,8,8,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-2/E";
    condiciones = { "4-4-1-1", "Balanceada", "Posesion" };
    formacionGuia = "3,3,4,5,7,7,8,8,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-2/F";
    condiciones = { "4-5-1", "Balanceada", "Posesion" };
    formacionGuia = "3,3,4,5,7,7,8,8,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-2/G";
    condiciones = { "5-2-1-2", "Balanceada", "Posesion" };
    formacionGuia = "3,3,4,5,7,7,8,8,13,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-5-1
    consecuencia = "4-5-1/A";
    condiciones = { "3-1-4-2", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "3,3,4,5,7,8,8,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/B";
    condiciones = { "3-4-1-2", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "3,3,4,5,7,8,8,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/C";
    condiciones = { "3-4-2-1", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "3,3,4,5,7,8,8,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/D";
    condiciones = { "3-5-2", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "3,3,4,5,7,8,8,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/E";
    condiciones = { "4-1-2-1-2", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "3,3,4,5,7,8,8,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/F";
    condiciones = { "4-1-3-2", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "3,3,4,5,7,8,8,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/G";
    condiciones = { "4-1-4-1", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "3,3,4,5,7,8,8,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/H";
    condiciones = { "4-2-3-1", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "3,3,4,5,7,8,8,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/I";
    condiciones = { "4-3-3", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "3,3,4,5,7,8,8,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/J";
    condiciones = { "4-4-1-1", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "3,3,4,5,7,8,8,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/K";
    condiciones = { "5-4-1", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "3,3,4,5,7,8,8,9,9,13;B";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 5-2-1-2
    consecuencia = "5-2-1-2/A";
    condiciones = { "4-2-3-1", "Defensiva", "Contraataque" };
    formacionGuia = "3,3,3,7,7,10,11,12,13,13;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-2-1-2/B";
    condiciones = { "5-2-1-2", "Defensiva", "Contraataque" };
    formacionGuia = "3,3,3,7,7,10,11,12,13,13;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 5-2-2-1
    consecuencia = "5-2-2-1/A";
    condiciones = { "3-4-3", "Defensiva", "Contraataque", "Directo" };
    formacionGuia = "3,3,3,7,7,10,11,13,14,15;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-2-2-1/B";
    condiciones = { "4-3-2-1", "Defensiva", "Contraataque", "Directo" };
    formacionGuia = "3,3,3,7,7,10,11,13,14,15;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-2-2-1/C";
    condiciones = { "5-2-1-2", "Defensiva", "Contraataque", "Directo" };
    formacionGuia = "3,3,3,7,7,10,11,13,14,15;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 5-3-2
    consecuencia = "5-3-2/A";
    condiciones = { "3-4-3", "Defensiva", "Posesion" };
    formacionGuia = "3,3,3,7,7,7,10,11,13,13;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/B";
    condiciones = { "4-1-2-1-2", "Defensiva", "Posesion" };
    formacionGuia = "3,3,3,7,7,7,10,11,13,13;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/C";
    condiciones = { "4-2-4", "Defensiva", "Posesion" };
    formacionGuia = "3,3,3,7,7,7,10,11,13,13;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/D";
    condiciones = { "4-3-1-2", "Defensiva", "Posesion" };
    formacionGuia = "3,3,3,7,7,7,10,11,13,13;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/E";
    condiciones = { "4-3-2-1", "Defensiva", "Posesion" };
    formacionGuia = "3,3,3,7,7,7,10,11,13,13;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/F";
    condiciones = { "4-4-1-1", "Defensiva", "Posesion" };
    formacionGuia = "3,3,3,7,7,7,10,11,13,13;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/G";
    condiciones = { "4-4-2", "Defensiva", "Posesion" };
    formacionGuia = "3,3,3,7,7,7,10,11,13,13;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/H";
    condiciones = { "4-5-1", "Defensiva", "Posesion" };
    formacionGuia = "3,3,3,7,7,7,10,11,13,13;D";
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    return exp;
}

//#include "Genetico.h"
//#include <vector>
//#include "Util.h"
//
//
//int main() 
//{
//
//	string rutaarchivoplantel ="Polivalencia_coquimbo.txt";
//	string rutaRoles = "Formaciones\\Formacion1.txt";
//	Plantel p;
//	p.cargarArchivo(rutaarchivoplantel);
//	string forTactica = devolverForTactica(rutaRoles);
//	int * rol = devolverRoles(rutaRoles);
//	char modo = devolverModo(rutaRoles);
//	vector<Formacion> sol;
//				//nombrearchivoplantel, roljugadores, porcentajemutacion, iteraciones, poblacion
//		sol=Genetico(p /*nombre archivo plantel*/
//			, rol /*rol de los jugadores*/
//			,modo
//			,forTactica
//			, 50 /*porcentaje mutacion, de 0 a 100*/
//			, 5000 /*cantidad generaciones maxima*/
//			, 20 /*tamano poblacion*/
//		);
//	for (int i = 0; i < sol.size(); i++) sol.at(i).ImprimirFormacion();
//	entregarResultados(rutaarchivoplantel, sol, rol, forTactica);
//	return 0;
//}
