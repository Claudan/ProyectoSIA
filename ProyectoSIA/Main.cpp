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
int mainIdealPrototipoSIA();

int main()
{
    mainIdealPrototipoSIA();
    return(0);
}

int mainIdealPrototipoSIA() {
    string rutaequipo;
    int seleccion = 0;
    while (seleccion !=1 && seleccion != 2) { //Esto es parte del id3
        cout << "Seleccione equipo propio (1 o 2):" << endl;
        cout << "\t1.-Club Deportes La Serena"<<endl;
        cout << "\t2.-Club Deportes Coquimbo Unido" << endl<<"\t";
        cin >> seleccion;
        if (seleccion == 1) rutaequipo = ""; //TO-DO
        else if (seleccion == 2) rutaequipo = "";//TO-DO
        else cout << "Opcion no valida. Ingreselo nuevamente." << endl<<endl;
    }
    cout << seleccion;
    //Codigo para generar la polivalencia!!!
    // cout<<"Analizando equipo.<<endl;
    //Aquí se debe definir la ruta de salida de la polivalencia de serena o coquimbo
    //para pasarla al genetico.


    //Ahora son cosas para el sistema experto
    string formacionrival;
    cout << "Ingrese la formacion del equipo rival, indicando con numeros la cantidad de jugadores por linea y separados por guion. (Ej: 4-3-3 , 5-3-2)" << endl;
    cin >> formacionrival;
    seleccion = 0;
    
    string estrategiarival;
    while (seleccion < 1 || seleccion > 3) {
        cout << "Cual es la estrategia del equipo rival? Escriba un numero:" << endl;
        cout << "\t1.-Ofensiva" << endl;
        cout << "\t2.-Defensiva" << endl;
        cout << "\t3.-Balanceada" << endl;
        cout << "\t";
        cin >> seleccion;
        if (seleccion == 1) estrategiarival = "Ofensiva";
        else if (seleccion == 2) estrategiarival = "Defensiva";
        else if (seleccion == 3) estrategiarival = "Balanceada";
        else cout << "Opcion no valida. Ingreselo nuevamente." << endl;
    }
    cout << "Seleccionado: " << estrategiarival << endl<<endl;
    seleccion = 0;
    string modojuegorival;
    while (seleccion < 1 || seleccion > 3) {
        cout << "Cual es la forma de juego del equipo rival? Elija uno de los siguientes valores:" << endl;
        cout << "\t1.-Atacar" << endl;
        cout << "\t2.-Contraataque" << endl;
        cout << "\t3.-Posesion" << endl;
        cout << "\t";
        cin >> seleccion;
        if (seleccion == 1) modojuegorival = "Atacar";
        else if (seleccion == 2) modojuegorival = "Contraataque";
        else if (seleccion == 3) modojuegorival = "Posesion";
        else cout << "Opcion no valida. Ingreselo nuevamente." << endl;
    }
    cout << "Seleccionado: " << modojuegorival << endl<<endl;
    cout<<"Calculando tipos de formaciones para enfrentar al rival."<<endl<<endl;

    Experto exp = conocimientoExpertoFIFA();
    vector<string>inforival = { formacionrival, estrategiarival, modojuegorival};
    vector<vector<string>> solucionesexp = exp.infiereTodasLasSolucionesBC(inforival);

    string linea;
    seleccion = 0;
    if (solucionesexp.size() == 0) {
        cout << "No hay formaciones en la base de conocimiento que contrarresten al rival" << endl << endl;
        cout << "Intentando con 4-3-3." << endl << endl; //Failsafe (?)
        linea = linea + "433;" + "3,3,4,5,7,7,7,13,14,15;B";
    }
    else {
        while (seleccion < 1 || seleccion > solucionesexp.size()) {
            cout << "Seleccione la formación que desea usar." << endl;
            for (int i = 0; i < solucionesexp.size(); i++) {
                cout << "\t" << i + 1 << ".-";
                for (int j = 0; j < 1/* soluciones[i].size()*/; j++) {
                    cout << solucionesexp[i][j] << " ";
                }
                cout << endl;
            }
            cout << "\t";
            cin >> seleccion;
            if (seleccion<1 || seleccion>solucionesexp.size()) cout << "Opcion no valida. Ingreselo nuevamente." << endl;
        }
        seleccion--;

        linea = solucionesexp[seleccion][0] + ";" + solucionesexp[seleccion][1];
    }
    
    cout <<"Seleccionado: "<< linea<<endl<<endl;
    ofstream archivo;
    string rutaRoles = "..\\formacionprueba.txt";
    archivo.open(rutaRoles);
    archivo << linea;
    archivo.close();

    //Ahora es el algoritmo genetico.
    
    
    string rutaarchivoplantel = "..\\Polivalencia_coquimbo.csv";
    string rutasinergias = "..\\sinergiaCoquimbo.txt";
    Plantel plantel;
    plantel.cargarArchivo(rutaarchivoplantel, rutasinergias);
    string forTactica = devolverForTactica(rutaRoles);
    int* rol = devolverRoles(rutaRoles);
    char modo = devolverModo(rutaRoles);
    vector<Formacion> sol;
    cout << "Generando formaciones de jugadores optimizadas para enfrentar al rival." << endl << endl <<"...";
    //nombrearchivoplantel, roljugadores, porcentajemutacion, iteraciones, poblacion,porcentaje mutacion, de 0 a 100,cantidad generaciones maxima,tamano poblacion
    sol = Genetico(plantel, rol, modo, forTactica, 40, 5000, 20);
    //for (int i = 0; i < sol.size(); i++) sol.at(i).ImprimirFormacion();
    entregarResultados(plantel, sol, rol, forTactica, true, "..\\outputformaciones.txt");

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
    formacionGuia = "2,2,2,5,6,6,7,7,12,12;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar regla 3-4-1-2
    consecuencia = "3-4-1-2/A";
    condiciones = { "4-2-2-2", "Ofensiva", "Atacar" }; //equipo rival, estrategia, modo de juego
    formacionGuia = "2,2,2,6,6,7,8,8,12,12;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 3-4-2-1
    consecuencia = "3-4-2-1/A";
    condiciones = { "4-1-2-1-2", "Ofensiva", "Atacar" };
    formacionGuia = "2,2,2,6,6,7,7,11,11,12;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-4-2-1/B";
    condiciones = { "4-3-3", "Ofensiva", "Atacar" };
    formacionGuia = "2,2,2,6,6,7,7,11,11,12;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-4-2-1/C";
    condiciones = { "4-4-2", "Ofensiva", "Atacar" };
    formacionGuia = "2,2,2,6,6,7,7,11,11,12;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 3-4-3
    consecuencia = "3-4-3/A";
    condiciones = { "4-1-4-1", "Ofensiva" };
    formacionGuia = "2,2,2,6,6,7,7,12,13,14;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-4-3/B";
    condiciones = { "4-3-1-2", "Ofensiva" };
    formacionGuia = "2,2,2,6,6,7,7,12,13,14;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-4-3/C";
    condiciones = { "4-4-2", "Ofensiva", "Banda" };
    formacionGuia = "2,2,2,6,6,7,7,12,13,14;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-4-3/D";
    condiciones = { "4-5-1", "Ofensiva", "Banda" };
    formacionGuia = "2,2,2,6,6,7,7,12,13,14;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 3-5-2
    consecuencia = "3-5-2/A";
    condiciones = { "4-1-2-1-2", "Ofensiva", "Contraataque" };
    formacionGuia = "2,2,2,5,5,7,7,8,12,12;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-5-2/B";
    condiciones = { "4-2-2-2", "Ofensiva", "Contraataque" };
    formacionGuia = "2,2,2,5,5,7,7,8,12,12;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-5-2/C";
    condiciones = { "4-3-3", "Ofensiva", "Contraataque" };
    formacionGuia = "2,2,2,5,5,7,7,8,12,12;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-5-2/D";
    condiciones = { "4-4-2", "Ofensiva", "Contraataque" };
    formacionGuia = "2,2,2,5,5,7,7,8,12,12;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-5-2/E";
    condiciones = { "4-5-1", "Ofensiva", "Contraataque" };
    formacionGuia = "2,2,2,5,5,7,7,8,12,12;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-5-2/F";
    condiciones = { "5-2-2-1", "Ofensiva" };
    formacionGuia = "2,2,2,5,5,7,7,8,12,12;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "3-5-2/G";
    condiciones = { "5-4-1", "Ofensiva", "Contraataque" };
    formacionGuia = "2,2,2,5,5,7,7,8,12,12;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-1-2-1-2
    consecuencia = "4-1-2-1-2/A";
    condiciones = { "4-2-3-1", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "2,2,3,4,5,7,7,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-1-2-1-2/B";
    condiciones = { "4-3-3", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "2,2,3,4,5,7,7,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-1-2-1-2/C";
    condiciones = { "3-4-1-2", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "2,2,3,4,5,7,7,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-1-2-1-2 (2)
    consecuencia = "4-1-2-1-2 (2)/A";
    condiciones = { "4-2-3-1", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "2,2,3,4,5,6,6,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-1-3-2
    consecuencia = "4-1-3-2/A";
    condiciones = { "3-1-4-2", "Balanceada", "Atacar", "Directo" };
    formacionGuia = "2,2,3,4,5,6,7,7,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-1-3-2/B";
    condiciones = { "3-5-2", "Balanceada", "Atacar", "Directo" };
    formacionGuia = "2,2,3,4,5,6,7,7,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-1-4-1
    consecuencia = "4-1-4-1/A";
    condiciones = { "4-3-3", "Balanceada", "Corto" };
    formacionGuia = "2,2,3,4,5,6,6,7,7,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-2-2-2
    consecuencia = "4-2-2-2/A";
    condiciones = { "3-4-2-1", "Balanceada", "Largos" };
    formacionGuia = "2,2,3,4,5,5,8,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-2-2/B";
    condiciones = { "4-2-3-1", "Balanceada", "Largos" };
    formacionGuia = "2,2,3,4,5,5,8,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-2-2/C";
    condiciones = { "4-3-3", "Balanceada", "Largos" };
    formacionGuia = "2,2,3,4,5,5,8,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-2-2/D";
    condiciones = { "4-5-1", "Balanceada", "Largos" };
    formacionGuia = "2,2,3,4,5,5,8,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-2-3-1
    consecuencia = "4-2-3-1/A";
    condiciones = { "3-4-1-2", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,13;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/B";
    condiciones = { "3-4-2-1", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/C";
    condiciones = { "3-4-3", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/D";
    condiciones = { "4-1-4-1", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/E";
    condiciones = { "4-2-2-2", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/F";
    condiciones = { "4-2-4", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/G";
    condiciones = { "4-3-1-2", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/H";
    condiciones = { "4-3-2-1", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/I";
    condiciones = { "4-3-3", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/J";
    condiciones = { "4-4-1-1", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/K";
    condiciones = { "4-4-2", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/L";
    condiciones = { "4-5-1", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-2-3-1/M";
    condiciones = { "5-2-2-1", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,8,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));


    //Insertar 4-2-3-1 (2)
    consecuencia = "4-2-3-1 (2)/A";
    condiciones = { "4-3-1-2", "Balanceada", "Atacar", "Corto" };
    formacionGuia = "2,2,3,4,5,5,7,7,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-3-1-2
    consecuencia = "4-3-1-2/A";
    condiciones = { "3-1-4-2", "Balanceada", "Posesion", "Directo" };
    formacionGuia = "2,2,3,4,6,6,6,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-1-2/B";
    condiciones = { "3-4-3", "Balanceada", "Posesion" };
    formacionGuia = "2,2,3,4,6,6,6,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-1-2/C";
    condiciones = { "3-5-2", "Balanceada", "Posesion", "Directo" };
    formacionGuia = "2,2,3,4,6,6,6,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-1-2/D";
    condiciones = { "4-3-2-1", "Balanceada", "Posesion", "Directo" };
    formacionGuia = "2,2,3,4,6,6,6,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-1-2/E";
    condiciones = { "4-3-3", "Balanceada", "Posesion", "Directo" };
    formacionGuia = "2,2,3,4,6,6,6,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-1-2/F";
    condiciones = { "5-3-2", "Balanceada", "Posesion", "Directo" };
    formacionGuia = "2,2,3,4,6,6,6,8,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-3-2-1
    consecuencia = "4-3-2-1/A";
    condiciones = { "5-3-2", "Balanceada", "Contraataque" }; //Aun pensar.
    formacionGuia = "2,2,3,4,6,6,6,11,11,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-2-1/B";
    condiciones = { "5-4-1", "Balanceada", "Contraataque" };
    formacionGuia = "2,2,3,4,6,6,6,11,11,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-3-3
    consecuencia = "4-3-3/A";
    condiciones = { "4-1-3-2", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,6,12,13,14;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/B";
    condiciones = { "4-1-4-1", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,6,12,13,14;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/C";
    condiciones = { "4-2-2-2", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,6,12,13,14;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/D";
    condiciones = { "4-2-4", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,6,12,13,14;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/E";
    condiciones = { "4-4-1-1", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,6,12,13,14;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/F";
    condiciones = { "5-2-1-2", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,6,12,13,14;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/G";
    condiciones = { "5-2-2-1", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,6,12,13,14;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3/H";
    condiciones = { "5-3-2", "Balanceada", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,6,12,13,14;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-3-3 (2)
    consecuencia = "4-3-3 (2)/A";
    condiciones = { "4-1-3-2", "Balanceada", "Posesion", "Banda", "Corto" };
    formacionGuia = "2,2,3,4,5,6,6,12,13,14;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));


    //Insertar 4-3-3 (3)
    consecuencia = "4-3-3 (3)/A";
    condiciones = { "3-4-2-1", "Defensiva", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,5,5,6,12,13,14;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3 (3)/B";
    condiciones = { "3-4-1-2", "Defensiva", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,5,5,6,12,13,14;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3 (3)/C";
    condiciones = { "4-5-1", "Defensiva", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,5,5,6,12,13,14;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-3-3 (4)
    consecuencia = "4-3-3 (4)/A";
    condiciones = { "3-1-4-2", "Ofensiva", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,8,12,13,14;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3 (4)/B";
    condiciones = { "3-5-2", "Ofensiva", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,8,12,13,14;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3 (4)/C";
    condiciones = { "4-3-3", "Ofensiva", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,8,12,13,14;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3 (4)/D";
    condiciones = { "5-3-2", "Ofensiva", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,8,12,13,14;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-3-3 (4)/E";
    condiciones = { "5-4-1", "Ofensiva", "Contraataque", "Banda" };
    formacionGuia = "2,2,3,4,6,6,8,12,13,14;O";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-4-1-1
    consecuencia = "4-4-1-1/A";
    condiciones = { "4-1-2-1-2", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "2,2,3,4,6,6,7,7,11,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-1-1/B";
    condiciones = { "4-3-3", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "2,2,3,4,6,6,7,7,11,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-1-1/C";
    condiciones = { "4-4-2", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "2,2,3,4,6,6,7,7,11,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-1-1/D";
    condiciones = { "5-2-2-1", "Balanceada", "Posesion", "Corto" };
    formacionGuia = "2,2,3,4,6,6,7,7,11,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-4-2
    consecuencia = "4-4-2/A";
    condiciones = { "4-1-3-2", "Balanceada", "Posesion" };
    formacionGuia = "2,2,3,4,6,6,7,7,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-2/B";
    condiciones = { "4-2-3-1", "Balanceada", "Posesion" };
    formacionGuia = "2,2,3,4,6,6,7,7,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-2/C";
    condiciones = { "4-2-4", "Balanceada", "Posesion" };
    formacionGuia = "2,2,3,4,6,6,7,7,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-2/D";
    condiciones = { "4-3-3", "Balanceada", "Posesion" };
    formacionGuia = "2,2,3,4,6,6,7,7,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-2/E";
    condiciones = { "4-4-1-1", "Balanceada", "Posesion" };
    formacionGuia = "2,2,3,4,6,6,7,7,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-2/F";
    condiciones = { "4-5-1", "Balanceada", "Posesion" };
    formacionGuia = "2,2,3,4,6,6,7,7,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-4-2/G";
    condiciones = { "5-2-1-2", "Balanceada", "Posesion" };
    formacionGuia = "2,2,3,4,6,6,7,7,12,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 4-5-1
    consecuencia = "4-5-1/A";
    condiciones = { "3-1-4-2", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "2,2,3,4,6,7,7,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/B";
    condiciones = { "3-4-1-2", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "2,2,3,4,6,7,7,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/C";
    condiciones = { "3-4-2-1", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "2,2,3,4,6,7,7,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/D";
    condiciones = { "3-5-2", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "2,2,3,4,6,7,7,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/E";
    condiciones = { "4-1-2-1-2", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "2,2,3,4,6,7,7,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/F";
    condiciones = { "4-1-3-2", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "2,2,3,4,6,7,7,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/G";
    condiciones = { "4-1-4-1", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "2,2,3,4,6,7,7,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/H";
    condiciones = { "4-2-3-1", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "2,2,3,4,6,7,7,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/I";
    condiciones = { "4-3-3", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "2,2,3,4,6,7,7,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/J";
    condiciones = { "4-4-1-1", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "2,2,3,4,6,7,7,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "4-5-1/K";
    condiciones = { "5-4-1", "Balanceada", "Posesion", "Banda" };
    formacionGuia = "2,2,3,4,6,7,7,8,8,12;B";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 5-2-1-2
    consecuencia = "5-2-1-2/A";
    condiciones = { "4-2-3-1", "Defensiva", "Contraataque" };
    formacionGuia = "2,2,2,6,6,9,10,11,12,12;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-2-1-2/B";
    condiciones = { "5-2-1-2", "Defensiva", "Contraataque" };
    formacionGuia = "2,2,2,6,6,9,10,11,12,12;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 5-2-2-1
    consecuencia = "5-2-2-1/A";
    condiciones = { "3-4-3", "Defensiva", "Contraataque", "Directo" };
    formacionGuia = "2,2,2,6,6,9,10,12,13,14;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-2-2-1/B";
    condiciones = { "4-3-2-1", "Defensiva", "Contraataque", "Directo" };
    formacionGuia = "2,2,2,6,6,9,10,12,13,14;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-2-2-1/C";
    condiciones = { "5-2-1-2", "Defensiva", "Contraataque", "Directo" };
    formacionGuia = "2,2,2,6,6,9,10,12,13,14;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    //Insertar 5-3-2
    consecuencia = "5-3-2/A";
    condiciones = { "3-4-3", "Defensiva", "Posesion" };
    formacionGuia = "2,2,2,6,6,6,9,10,12,12;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/B";
    condiciones = { "4-1-2-1-2", "Defensiva", "Posesion" };
    formacionGuia = "2,2,2,6,6,6,9,10,12,12;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/C";
    condiciones = { "4-2-4", "Defensiva", "Posesion" };
    formacionGuia = "2,2,2,6,6,6,9,10,12,12;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/D";
    condiciones = { "4-3-1-2", "Defensiva", "Posesion" };
    formacionGuia = "2,2,2,6,6,6,9,10,12,12;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/E";
    condiciones = { "4-3-2-1", "Defensiva", "Posesion" };
    formacionGuia = "2,2,2,6,6,6,9,10,12,12;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/F";
    condiciones = { "4-4-1-1", "Defensiva", "Posesion" };
    formacionGuia = "2,2,2,6,6,6,9,10,12,12;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/G";
    condiciones = { "4-4-2", "Defensiva", "Posesion" };
    formacionGuia = "2,2,2,6,6,6,9,10,12,12;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    consecuencia = "5-3-2/H";
    condiciones = { "4-5-1", "Defensiva", "Posesion" };
    formacionGuia = "2,2,2,6,6,6,9,10,12,12;D";//Corregido
    exp.insertaRegla(Regla(condiciones, consecuencia, formacionGuia));

    return exp;
}

