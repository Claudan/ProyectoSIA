#include <iostream>
#include <string>
#include <vector>

#include "ExpertoLib.h"
#include "GeneticoLib.h"
#include "FID3Lib.h"

#include <ManipuladorArchivos.h>

using namespace std;
using namespace ExpertoLib;
using namespace GeneticoLib;
using namespace FID3Lib;

Experto conocimientoExpertoFIFA();
int mainIdealPrototipoSIA();
int calcularPolivalencia();

int main()
{
    mainIdealPrototipoSIA();
    return(0);
}

int mainIdealPrototipoSIA() {
    string rutaequipo;
    string rutaarchivoplantel="..\\Polivalencia_coquimbo.csv";;
    string rutasinergias= "..\\sinergiaCoquimbo.txt";

    int seleccion = 0;
    int equipo = 0;
    while (seleccion !=1 && seleccion != 2) {
        cout << "Seleccione equipo propio (1 o 2):" << endl;
        cout << "\t1.-Club Deportes La Serena"<<endl;
        cout << "\t2.-Club Deportes Coquimbo Unido" << endl<<"\t";
        cin >> seleccion;
        if (seleccion == 1) {
            rutaarchivoplantel = "..\\Polivalencia_serena.csv";
            rutasinergias = "..\\sinergiaSerena.txt";
            equipo = 1;
        }
        else if (seleccion == 2) {
            rutaarchivoplantel = "..\\Polivalencia_coquimbo.csv";
            rutasinergias = "..\\sinergiaCoquimbo.txt";
            equipo = 2;
        }
        else cout << "Opcion no valida. Ingreselo nuevamente." << endl<<endl;
    }
    cout <<endl;

    seleccion = 0;
    while (seleccion != 1 && seleccion != 2) {
        cout << "Desea recalcular las polivalencias de los jugadores?" << endl;
        cout << "\t1.-No." << endl;
        cout << "\t2.-Si." << endl << "\t";
        cin >> seleccion;
        if (seleccion == 1) {
            cout << "Utilizando polivalencias calculadas anteriormente." << endl;
        }
        else if (seleccion == 2)
        {
            cout <<"Recalculando polivalencia de los jugadores.(Pendiente)"<<endl;
            //ID3 acá. NO SOBREESCRIBIR LOS ARCHIVOS DE RUTAARCHIVOPLANTEL!!!!!!!!!
            //Crear un polivalencia nuevo y asignar el rutaarchivoplantel al archivo creado.
            if (equipo == 1) {
                //Sacar la polivalencia de serena.
            }
            else if (equipo == 2) {
                //Sacar la polivalencia de coquimbo.
            }
        }
        else cout << "Opcion no valida. Ingreselo nuevamente." << endl << endl;
    }
    cout << endl;

    //Ahora son cosas para el sistema experto
    string formacionrival;
    cout << "Ingrese la formacion del EQUIPO RIVAL, indicando con numeros la cantidad de jugadores por linea y separados por guion. (Ej: 4-3-3 , 5-3-2)" << endl<<"\t";
    cin >> formacionrival;
    seleccion = 0;
    cout << endl;

    string estrategiapropia;
    while (seleccion < 1 || seleccion > 3) {
        cout << "Cual es la estrategia que quiere utilizar en SU equipo? Escriba un numero:" << endl;
        cout << "\t1.-Ofensiva" << endl;
        cout << "\t2.-Defensiva" << endl;
        cout << "\t3.-Balanceada" << endl;
        cout << "\t";
        cin >> seleccion;
        if (seleccion == 1) estrategiapropia = "Ofensiva";
        else if (seleccion == 2) estrategiapropia = "Defensiva";
        else if (seleccion == 3) estrategiapropia = "Balanceada";
        else cout << "Opcion no valida. Ingreselo nuevamente." << endl;
    }
    cout << "Seleccionado: " << estrategiapropia << endl<<endl;
    seleccion = 0;
    string modojuegopropio;
    while (seleccion < 1 || seleccion > 3) {
        cout << "Cual es la forma de juego que utilizara en su equipo? Elija uno de los siguientes valores:" << endl;
        cout << "\t1.-Atacar" << endl;
        cout << "\t2.-Contraataque" << endl;
        cout << "\t3.-Posesion" << endl;
        cout << "\t";
        cin >> seleccion;
        if (seleccion == 1) modojuegopropio = "Atacar";
        else if (seleccion == 2) modojuegopropio = "Contraataque";
        else if (seleccion == 3) modojuegopropio = "Posesion";
        else cout << "Opcion no valida. Ingreselo nuevamente." << endl;
    }
    cout << "Seleccionado: " << modojuegopropio << endl << endl;

    seleccion = 0;
    string estiloataquepropio;
    while (seleccion < 1 || seleccion > 2) {
        cout << "Que tipo de ataque prefiere utilizar? Elija uno de los siguientes valores:" << endl;
        cout << "\t1.-Directo" << endl;
        cout << "\t2.-Banda" << endl;
        cout << "\t";
        cin >> seleccion;
        if (seleccion == 1) estiloataquepropio = "Directo";
        else if (seleccion == 2) estiloataquepropio = "Banda";
        else cout << "Opcion no valida. Ingreselo nuevamente." << endl;
    }
    cout << "Seleccionado: " << estiloataquepropio << endl << endl;


    seleccion = 0;
    string tipopases;
    while (seleccion < 1 || seleccion > 2) {
        cout << "Que tipo de pases desea utilizar mas? Elija uno de los siguientes valores:" << endl;
        cout << "\t1.-Largos" << endl;
        cout << "\t2.-Cortos" << endl;
        cout << "\t";
        cin >> seleccion;
        if (seleccion == 1) tipopases = "Largo";
        else if (seleccion == 2) tipopases = "Corto";
        else cout << "Opcion no valida. Ingreselo nuevamente." << endl;
    }

    cout << "Seleccionado: " << tipopases << endl<<endl;
    cout<<"Calculando tipos de formaciones para enfrentar al rival."<<endl<<endl;

    Experto exp = conocimientoExpertoFIFA();
    vector<string>inforival = { formacionrival, estrategiapropia, modojuegopropio,estiloataquepropio, tipopases};
    vector<vector<string>> solucionesexp = exp.infiereTodasLasSolucionesBC(inforival);

    string linea;
    seleccion = 0;
    if (solucionesexp.size() == 0) {
        cout << "No hay formaciones en la base de conocimiento que contrarresten al rival." << endl;
        while (seleccion < 1 || seleccion >6) {
            cout << "Seleccione la formacion que desea usar." << endl;
            cout << "\t1.- 4-3-3 Balanceada"<<endl;
            cout << "\t2.- 4-3-3 Ofensiva" << endl;
            cout << "\t3.- 4-3-3 Defensiva" << endl;
            cout << "\t4.- 5-3-2 Balanceada" << endl;
            cout << "\t5.- 5-3-2 Ofensiva" << endl;
            cout << "\t6.- 5-3-2 Defensiva" << endl;
            cout << "\t";
            cin >> seleccion;
            if (seleccion == 1) linea = "433;2,2,3,4,6,6,6,12,13,14;B";
            else if (seleccion == 2) linea = "433;2,2,3,4,6,6,6,12,13,14;O";
            else if (seleccion == 3) linea = "433;2,2,3,4,6,6,6,12,13,14;D";
            else if (seleccion == 4) linea = "532;2,2,2,6,6,6,9,10,12,12;B";
            else if (seleccion == 5) linea = "532;2,2,2,6,6,6,9,10,12,12;O";
            else if (seleccion == 6) linea = "532;2,2,2,6,6,6,9,10,12,12;D";
            else if (seleccion<1 || seleccion>solucionesexp.size()) cout << "Opcion no valida. Ingreselo nuevamente." << endl;
            else seleccion = 0;
        }
                                                                   
        //cout << "Intentando con 4-3-3 Balanceada." << endl << endl; //Failsafe (?)
        //linea = linea + "433;" + "2,2,3,4,6,6,6,12,13,14;B";
    }
    else {
        while (seleccion < 1 || seleccion > solucionesexp.size()) {
            cout << "Seleccione la formacion que desea usar." << endl;
            for (int i = 0; i < solucionesexp.size(); i++) {
                cout << "\t" << i + 1 << ".-";
                for (int j = 0; j < 1/* soluciones[i].size()*/; j++) {
                    cout << solucionesexp[i][j] << " ";
                    if (solucionesexp[i][1].back() == 'O') cout << "Ofensiva";
                    else if (solucionesexp[i][1].back() == 'B') cout << "Balanceada";
                    else if (solucionesexp[i][1].back() == 'D') cout << "Defensiva";
                    else if (solucionesexp[i][1].back() == 'A') cout << "Ataque";
                }
                cout << endl;
            }
            cout << "\t";
            cin >> seleccion;
            if (seleccion<1 || seleccion>solucionesexp.size()) cout << "Opcion no valida. Ingreselo nuevamente." << endl;
        }
        seleccion--;

        linea = solucionesexp[seleccion][0] + ";" + solucionesexp[seleccion][1];
        char letramodo = linea.back();
        string modopalabra;
        if (letramodo == 'O') modopalabra = "Ofensiva";
        else if (letramodo == 'B') modopalabra = "Balanceada";
        else if (letramodo == 'D') modopalabra = "Defensiva";
        if (letramodo == 'A') modopalabra = "Ataque";
        cout << "Seleccionado: " << solucionesexp[seleccion][0] << " " << modopalabra << endl;
    }
    cout << endl;
    ofstream archivo;
    string rutaRoles = "..\\formacionprueba.txt";
    archivo.open(rutaRoles);
    archivo << linea;
    archivo.close();

    //Ahora es el algoritmo genetico.
    //cout << rutaarchivoplantel << " " << rutasinergias;
    Plantel plantel;
    plantel.cargarArchivo(rutaarchivoplantel, rutasinergias);
    string forTactica = devolverForTactica(rutaRoles);
    int* rol = devolverRoles(rutaRoles);
    char modo = devolverModo(rutaRoles);
    vector<Formacion> sol;
    cout << "Generando formaciones de jugadores optimizadas para enfrentar al rival:" << endl;
    //nombrearchivoplantel, roljugadores, porcentajemutacion, iteraciones, poblacion,porcentaje mutacion, de 0 a 100,cantidad generaciones maxima,tamano poblacion
    sol = Genetico(plantel, rol, modo, forTactica, 40, 5000, 20);
    cout << endl<<endl;
    entregarResultados(plantel, sol, rol, forTactica, true, "..\\outputformaciones.txt");
    //remove(rutaRoles);
    cout << endl << "Presione ENTER para salir...";
    getchar();
    getchar();
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


int calcularPolivalencia()
{
    std::vector<std::string> vectorJugadores;
    FID3 objetoFID3 = FID3();
    //FID3 objetoFID3 = FID3( 0.8, 0.1 ); //FID3(thetarR, thetaN)

    //---------------
    // Inserta Clases
    //---------------
    objetoFID3.agregaClase("Defensa central");
    objetoFID3.agregaClase("Pivote");
    objetoFID3.agregaClase("Delantero centro");
    objetoFID3.agregaClase("Interior derecho");
    objetoFID3.agregaClase("Interior izquierdo");
    objetoFID3.agregaClase("Mediocentro ofensivo");
    objetoFID3.agregaClase("Mediocentro");
    objetoFID3.agregaClase("Mediapunta");
    objetoFID3.agregaClase("Extremo izquierdo");
    objetoFID3.agregaClase("Extremo derecho");
    objetoFID3.agregaClase("Lateral derecho");
    objetoFID3.agregaClase("Lateral izquierdo");
    objetoFID3.agregaClase("Libero");
    objetoFID3.agregaClase("Medio campo");
    //	objetoFID3.agregaClase("Portero");

        //-----------------------------------------------------------------------
        // Lee documento(input) con elementos(jugadores) y sus clases resultantes
        // e ingresa estos datos de entrenamiento
        //-----------------------------------------------------------------------
    ManipuladorArchivos archivo = ManipuladorArchivos("DatosJugadoresFutbolNuevos.csv");
    archivo.leerArchivo("DataFuzzy.csv");

    std::ifstream ip("DataFuzzy.csv");
    if (!ip.is_open()) std::cout << "ERROR: No se pudo abrir el archivo" << std::endl;
    //polivalencia
    std::string polivalencia_baja_s;
    std::string polivalencia_media_s;
    std::string polivalencia_alta_s;
    double temp_polivalencia_baja;
    double temp_polivalencia_media;
    double temp_polivalencia_alta;

    //goleador
    std::string goleador_baja_s;
    std::string goleador_media_s;
    std::string goleador_alta_s;
    double temp_goleador_baja;
    double temp_goleador_media;
    double temp_goleador_alta;

    //concentracionPartidosRelevantes 
    std::string concentracionPartidosRelevantes_baja_s;
    std::string concentracionPartidosRelevantes_alta_s;
    double temp_concentracionPartidosRelevantes_baja;
    double temp_concentracionPartidosRelevantes_alta;

    //experiencia
    std::string experiencia_baja_s;
    std::string experiencia_media_s;
    std::string experiencia_alta_s;
    double temp_experiencia_baja;
    double temp_experiencia_media;
    double temp_experiencia_alta;

    //garra
    std::string garra_baja_s;
    std::string garra_alta_s;
    double temp_garra_baja;
    double temp_garra_alta;

    //biorritmo
    std::string biorritmo_baja_s;
    std::string biorritmo_media_s;
    std::string biorritmo_alta_s;
    double temp_biorritmo_baja;
    double temp_biorritmo_media;
    double temp_biorritmo_alta;

    //salud
    std::string salud_baja_s;
    std::string salud_media_s;
    std::string salud_alta_s;
    double temp_salud_baja;
    double temp_salud_media;
    double temp_salud_alta;

    //desempeno
    std::string desempeno_baja_s;
    std::string desempeno_media_s;
    std::string desempeno_alta_s;
    double temp_desempeno_baja;
    double temp_desempeno_media;
    double temp_desempeno_alta;

    //temperamento
    std::string temperamento_baja_s;
    std::string temperamento_alta_s;
    double temp_temperamento_baja;
    double temp_temperamento_alta;

    //madurezEmocional
    std::string madurezEmocional_baja_s;
    std::string madurezEmocional_alta_s;
    double temp_madurezEmocional_baja;
    double temp_madurezEmocional_alta;

    //companerismo
    std::string companerismo_baja_s;
    std::string companerismo_alta_s;
    double temp_companerismo_baja;
    double temp_companerismo_alta;

    //vision
    std::string vision_media_s;
    std::string vision_alta_s;
    double temp_vision_media;
    double temp_vision_alta;

    //liderazgo
    std::string liderazgo_baja_s;
    std::string liderazgo_alta_s;
    double temp_liderazgo_baja;
    double temp_liderazgo_alta;

    //clase
    std::string clase;
    std::string nombre;
    Elemento elemento = Elemento();
    std::map<std::string, double> fuzzyTypes;
    int c = 0;
    while (ip.good() && c < 100)
    {

        getline(ip, nombre, ';');
        getline(ip, polivalencia_baja_s, ';');
        std::cout << "ENTRENAMIENTO polivalencia_baja_s: " << polivalencia_baja_s << std::endl;
        getline(ip, polivalencia_media_s, ';');
        //std::cout << "polivalencia_media_s: "<< polivalencia_media_s << std::endl;
        getline(ip, polivalencia_alta_s, ';');
        //std::cout << "polivalencia_alta_s: " << polivalencia_alta_s  << std::endl;
        getline(ip, goleador_baja_s, ';');
        //std::cout << "goleador_baja_s: " << goleador_baja_s << std::endl;
        getline(ip, goleador_media_s, ';');
        //std::cout << "goleador_media_s: "<< goleador_media_s << std::endl;
        getline(ip, goleador_alta_s, ';');
        //std::cout << "goleador_alta_s: "<< goleador_alta_s << std::endl;
        //getline(ip, concentracionPartidosRelevantes_baja_s, ';');
        //std::cout << "concentracionPartidosRelevantes_baja_s: "<< concentracionPartidosRelevantes_baja_s << std::endl;
        //getline(ip, concentracionPartidosRelevantes_alta_s, ';');
        //std::cout << "concentracionPartidosRelevantes_alta_s: "<< concentracionPartidosRelevantes_alta_s << std::endl;
        getline(ip, experiencia_baja_s, ';');
        //std::cout << "experiencia_baja_s: " << experiencia_baja_s << std::endl;
        getline(ip, experiencia_media_s, ';');
        //std::cout << "experiencia_media_s: "<< experiencia_media_s << std::endl;
        getline(ip, experiencia_alta_s, ';');
        //std::cout << "experiencia_alta_s: "<< experiencia_alta_s << std::endl;
        //getline(ip, garra_baja_s, ';');
        //std::cout << "garra_baja_s: "<< garra_baja_s << std::endl;
        //getline(ip, garra_alta_s, ';');
        //std::cout << "garra_alta_s: " << garra_alta_s << std::endl;
        //getline(ip, biorritmo_baja_s, ';');
        //std::cout << "biorritmo_baja_s: " << biorritmo_baja_s << std::endl;
        //getline(ip, biorritmo_media_s, ';');
        //getline(ip, biorritmo_alta_s, ';');

        getline(ip, salud_baja_s, ';');
        getline(ip, salud_media_s, ';');
        getline(ip, salud_alta_s, ';');
        //getline(ip, desempeno_baja_s, ';');
        //getline(ip, desempeno_media_s, ';');
        //getline(ip, desempeno_alta_s, ';');
        getline(ip, temperamento_baja_s, ';');
        getline(ip, temperamento_alta_s, ';');
        //getline(ip, madurezEmocional_baja_s, ';');
        //getline(ip, madurezEmocional_alta_s, ';');
        //getline(ip, companerismo_baja_s, ';');
        //getline(ip, companerismo_alta_s, ';');
        //getline(ip, vision_media_s, ';');
        //getline(ip, vision_alta_s, ';');
        //getline(ip, liderazgo_baja_s, ';');
        //getline(ip, liderazgo_alta_s, ';');
        //std::cout << "liderazgo_alta_s: " << liderazgo_alta_s << std::endl;

        getline(ip, clase, '\n'); //falta agregar en el csv
        std::cout << "clase: " << clase << std::endl;

        temp_polivalencia_baja = stod(polivalencia_baja_s);
        temp_polivalencia_media = stod(polivalencia_media_s);
        temp_polivalencia_alta = stod(polivalencia_alta_s);
        temp_goleador_baja = stod(goleador_baja_s);
        temp_goleador_media = stod(goleador_media_s);
        temp_goleador_alta = stod(goleador_alta_s);
        //temp_concentracionPartidosRelevantes_baja = stod(concentracionPartidosRelevantes_baja_s);
        //temp_concentracionPartidosRelevantes_alta = stod(concentracionPartidosRelevantes_alta_s);
        temp_experiencia_baja = stod(experiencia_baja_s);
        temp_experiencia_media = stod(experiencia_media_s);
        temp_experiencia_alta = stod(experiencia_alta_s);
        //temp_garra_baja = stod(garra_baja_s);
        //temp_garra_alta = stod(garra_alta_s);
        //temp_biorritmo_baja = stod(biorritmo_baja_s);
        //temp_biorritmo_media = stod(biorritmo_media_s);
        //temp_biorritmo_alta = stod(biorritmo_alta_s);

        temp_salud_baja = stod(salud_baja_s);
        temp_salud_media = stod(salud_media_s);
        temp_salud_alta = stod(salud_alta_s);
        //temp_desempeno_baja = stod(desempeno_baja_s);
        //temp_desempeno_media = stod(desempeno_media_s);
        //temp_desempeno_alta = stod(desempeno_alta_s);
        temp_temperamento_baja = stod(temperamento_baja_s);
        temp_temperamento_alta = stod(temperamento_alta_s);
        //temp_madurezEmocional_baja = stod(madurezEmocional_baja_s);
        //temp_madurezEmocional_alta = stod(madurezEmocional_alta_s);
        //temp_companerismo_baja = stod(companerismo_baja_s);
        //temp_companerismo_alta = stod(companerismo_alta_s);
        //temp_vision_media = stod(vision_media_s);
        //temp_vision_alta = stod(vision_alta_s);
        //temp_liderazgo_baja = stod(liderazgo_baja_s);
        //temp_liderazgo_alta = stod(liderazgo_alta_s);

        //---------
        // Elemento
        //---------
        elemento.setNombre(nombre);
        elemento.setClase(clase);
        //Polivalencia
        fuzzyTypes = { {"baja",temp_polivalencia_baja}, {"media",temp_polivalencia_media}, {"alta",temp_polivalencia_alta} };
        elemento.setValoresDifusos(AtributoDifuso("Polivalencia", fuzzyTypes));
        //Goleador
        fuzzyTypes = { {"baja",temp_goleador_baja}, {"media",temp_goleador_media}, {"alta",temp_goleador_alta} };
        elemento.setValoresDifusos(AtributoDifuso("Goleador", fuzzyTypes));
        //ConcentracionPartidosRelevantes
        //fuzzyTypes = { {"baja",temp_concentracionPartidosRelevantes_baja}, {"alta",temp_concentracionPartidosRelevantes_alta} };
        //elemento.setValoresDifusos(AtributoDifuso("ConcentracionPartidosRelevantes", fuzzyTypes));
        //Experiencia

        fuzzyTypes = { {"baja",temp_experiencia_baja}, {"media",temp_experiencia_media}, {"alta",temp_experiencia_alta} };
        elemento.setValoresDifusos(AtributoDifuso("Experiencia", fuzzyTypes));
        //Garra
        //fuzzyTypes = { {"baja",temp_garra_baja}, {"alta",temp_garra_alta} };
        //elemento.setValoresDifusos(AtributoDifuso("Garra", fuzzyTypes));
        //Biorritmo
        //fuzzyTypes = { {"baja",temp_biorritmo_baja}, {"media",temp_biorritmo_media}, {"alta",temp_biorritmo_alta} };
        //elemento.setValoresDifusos(AtributoDifuso("Biorritmo", fuzzyTypes));

        //Salud
        fuzzyTypes = { {"baja",temp_salud_baja}, {"media",temp_salud_media}, {"alta",temp_salud_alta} };
        elemento.setValoresDifusos(AtributoDifuso("Salud", fuzzyTypes));
        //Desempeno
        //fuzzyTypes = { {"baja",temp_desempeno_baja}, {"media",temp_desempeno_media}, {"alta",temp_desempeno_alta} };
        //elemento.setValoresDifusos(AtributoDifuso("Desempeno", fuzzyTypes));
        //Temperamento
        fuzzyTypes = { {"baja",temp_temperamento_baja}, {"alta",temp_temperamento_alta} };
        elemento.setValoresDifusos(AtributoDifuso("Temperamento", fuzzyTypes));
        //MadurezEmocional
        //fuzzyTypes = { {"baja",temp_madurezEmocional_baja}, {"alta",temp_madurezEmocional_alta} };
        //elemento.setValoresDifusos(AtributoDifuso("MadurezEmocional", fuzzyTypes));
        //Companerismo
        //fuzzyTypes = { {"baja",temp_companerismo_baja}, {"alta",temp_companerismo_alta} };
        //elemento.setValoresDifusos(AtributoDifuso("Companerismo", fuzzyTypes));
        //Vision
        //fuzzyTypes = { {"baja",temp_vision_media}, {"alta",temp_vision_alta} };
        //elemento.setValoresDifusos(AtributoDifuso("Vision", fuzzyTypes));
        //objetoFID3.agregaElemento(elemento);
        //Liderazgo
        //fuzzyTypes = { {"baja",temp_liderazgo_baja}, {"alta",temp_liderazgo_alta} };
        //lemento.setValoresDifusos(AtributoDifuso("Liderazgo", fuzzyTypes));

        objetoFID3.agregaElemento(elemento);

        elemento.clear();
        //std::cout << "--------------" << std::endl;
        c++;
    }
    ip.close();

    //--------------------------------------------------------------------------
    // Genera arbol FID3 (con los datos de entrenamiento previamente ingresados)
    //--------------------------------------------------------------------------

    objetoFID3.generaArbolFID3(); //lo crea en memoria principal

    //----------------------------------------------------------------------
    // Clasificacion del arbol
    //----------------------------------------------------------------------
    //Fuzzificar atributos de equipo 
    ManipuladorArchivos archivo2 = ManipuladorArchivos("LaSerena.csv");
    archivo2.leerArchivo("DataFuzzySerena.csv");
    // 

    // ACA DEBERIA CREAR EL VECTOR JUGADORES A PARTIR DE UN JUGADORES.CSV
    // ---------------------------------------------------------------
    std::vector<Elemento> Jugadores;
    Elemento elemento_c = Elemento();
    // Archivo de lectura

    std::ifstream ip2("DataFuzzySerena.csv"); //Coquimbo.csv
    //std::ifstream ip2("LaSerena.csv"); //LaSerena.csv
    if (!ip2.is_open()) std::cout << "ERROR: No se pudo abrir el archivo" << std::endl;

    c = 0;
    std::string nombres;
    while (ip2.good() && c < 22)
    {

        getline(ip2, nombres, ';');
        getline(ip2, polivalencia_baja_s, ';');
        std::cout << "polivalencia_baja_s: " << polivalencia_baja_s << std::endl;
        getline(ip2, polivalencia_media_s, ';');
        std::cout << "polivalencia_media_s: " << polivalencia_media_s << std::endl;
        getline(ip2, polivalencia_alta_s, ';');
        std::cout << "polivalencia_alta_s: " << polivalencia_alta_s << std::endl;
        getline(ip2, goleador_baja_s, ';');
        std::cout << "goleador_baja_s: " << goleador_baja_s << std::endl;
        getline(ip2, goleador_media_s, ';');
        std::cout << "goleador_media_s: " << goleador_media_s << std::endl;
        getline(ip2, goleador_alta_s, ';');
        std::cout << "goleador_alta_s: " << goleador_alta_s << std::endl;
        //getline(ip2, concentracionPartidosRelevantes_baja_s, ';');
        //std::cout << "concentracionPartidosRelevantes_baja_s: " << concentracionPartidosRelevantes_baja_s << std::endl;
        //getline(ip2, concentracionPartidosRelevantes_alta_s, ';');
        //std::cout << "concentracionPartidosRelevantes_alta_s: " << concentracionPartidosRelevantes_alta_s << std::endl;
        getline(ip2, experiencia_baja_s, ';');
        std::cout << "experiencia_baja_s: " << experiencia_baja_s << std::endl;
        getline(ip2, experiencia_media_s, ';');
        std::cout << "experiencia_media_s: " << experiencia_media_s << std::endl;
        getline(ip2, experiencia_alta_s, ';');
        std::cout << "experiencia_alta_s: " << experiencia_alta_s << std::endl;
        //getline(ip2, garra_baja_s, ';');
        //std::cout << "garra_baja_s: " << garra_baja_s << std::endl;
        //getline(ip2, garra_alta_s, ';');
        //std::cout << "garra_alta_s: " << garra_alta_s << std::endl;
        //getline(ip2, biorritmo_baja_s, ';');
        //std::cout << "biorritmo_baja_s: " << biorritmo_baja_s << std::endl;
        //getline(ip2, biorritmo_media_s, ';');
        //getline(ip2, biorritmo_alta_s, ';');

        getline(ip2, salud_baja_s, ';');
        getline(ip2, salud_media_s, ';');
        getline(ip2, salud_alta_s, ';');
        //getline(ip2, desempeno_baja_s, ';');
        //getline(ip2, desempeno_media_s, ';');
        //getline(ip2, desempeno_alta_s, ';');
        getline(ip2, temperamento_alta_s, ';');
        getline(ip2, temperamento_baja_s, ';');
        //getline(ip2, madurezEmocional_baja_s, ';');
        //getline(ip2, madurezEmocional_alta_s, ';');
        //getline(ip2, companerismo_baja_s, ';');
        //getline(ip2, companerismo_alta_s, ';');
        //std::cout << "COQUIMBO companerismo_alta_s: " << companerismo_alta_s << std::endl;
        //getline(ip2, vision_media_s, ';');
        //std::cout << "COQUIMBO vision_media_s: " << vision_media_s << std::endl;
        //getline(ip2, vision_alta_s, ';');
        //std::cout << "COQUIMBO vision_alta_s: " << vision_alta_s << std::endl;
        //getline(ip2, liderazgo_baja_s, ';');
        //std::cout << "COQUIMBO liderazgo_baja_s: " << liderazgo_baja_s << std::endl;
        //getline(ip2, liderazgo_alta_s, ';');
        //std::cout << "COQUIMBO liderazgo_alta_s: " << liderazgo_alta_s << std::endl;


        getline(ip2, clase, '\n'); //falta agregar en el csv
        //std::cout << "clase: " << clase << std::endl;

        temp_polivalencia_baja = stod(polivalencia_baja_s);
        temp_polivalencia_media = stod(polivalencia_media_s);
        temp_polivalencia_alta = stod(polivalencia_alta_s);
        temp_goleador_baja = stod(goleador_baja_s);
        temp_goleador_media = stod(goleador_media_s);
        temp_goleador_alta = stod(goleador_alta_s);
        //temp_concentracionPartidosRelevantes_baja = stod(concentracionPartidosRelevantes_baja_s);
        //temp_concentracionPartidosRelevantes_alta = stod(concentracionPartidosRelevantes_alta_s);
        temp_experiencia_baja = stod(experiencia_baja_s);
        temp_experiencia_media = stod(experiencia_media_s);
        temp_experiencia_alta = stod(experiencia_alta_s);
        //temp_garra_baja = stod(garra_baja_s);
        //temp_garra_alta = stod(garra_alta_s);
        //temp_biorritmo_baja = stod(biorritmo_baja_s);
        //temp_biorritmo_media = stod(biorritmo_media_s);
        //temp_biorritmo_alta = stod(biorritmo_alta_s);

        temp_salud_baja = stod(salud_baja_s);
        temp_salud_media = stod(salud_media_s);
        temp_salud_alta = stod(salud_alta_s);
        //temp_desempeno_baja = stod(desempeno_baja_s);
        //temp_desempeno_media = stod(desempeno_media_s);
        //temp_desempeno_alta = stod(desempeno_alta_s);
        temp_temperamento_baja = stod(temperamento_baja_s);
        temp_temperamento_alta = stod(temperamento_alta_s);
        //temp_madurezEmocional_baja = stod(madurezEmocional_baja_s);
        //temp_madurezEmocional_alta = stod(madurezEmocional_alta_s);
        //temp_companerismo_baja = stod(companerismo_baja_s);
        //temp_companerismo_alta = stod(companerismo_alta_s);
        //temp_vision_media = stod(vision_media_s);
        //temp_vision_alta = stod(vision_alta_s);
        //temp_liderazgo_baja = stod(liderazgo_baja_s);
        //temp_liderazgo_alta = stod(liderazgo_alta_s);

        //---------
        // Elemento
        //---------
        elemento_c.setClase(clase);
        elemento_c.setNombre(nombres);
        //Polivalencia
        fuzzyTypes = { {"baja",temp_polivalencia_baja}, {"media",temp_polivalencia_media}, {"alta",temp_polivalencia_alta} };
        elemento_c.setValoresDifusos(AtributoDifuso("Polivalencia", fuzzyTypes));
        //Goleador
        fuzzyTypes = { {"baja",temp_goleador_baja}, {"media",temp_goleador_media}, {"alta",temp_goleador_alta} };
        elemento_c.setValoresDifusos(AtributoDifuso("Goleador", fuzzyTypes));
        //ConcentracionPartidosRelevantes
        //fuzzyTypes = { {"baja",temp_concentracionPartidosRelevantes_baja}, {"alta",temp_concentracionPartidosRelevantes_alta} };
        //elemento_c.setValoresDifusos(AtributoDifuso("ConcentracionPartidosRelevantes", fuzzyTypes));
        //Experiencia
        fuzzyTypes = { {"baja",temp_experiencia_baja}, {"media",temp_experiencia_media}, {"alta",temp_experiencia_alta} };
        elemento_c.setValoresDifusos(AtributoDifuso("Experiencia", fuzzyTypes));
        //Garra
        //fuzzyTypes = { {"baja",temp_garra_baja}, {"alta",temp_garra_alta} };
        //elemento_c.setValoresDifusos(AtributoDifuso("Garra", fuzzyTypes));
        //Biorritmo
        //fuzzyTypes = { {"baja",temp_biorritmo_baja}, {"media",temp_biorritmo_media}, {"alta",temp_biorritmo_alta} };
        //elemento_c.setValoresDifusos(AtributoDifuso("Biorritmo", fuzzyTypes));
        //Salud
        fuzzyTypes = { {"baja",temp_salud_baja}, {"media",temp_salud_media}, {"alta",temp_salud_alta} };
        elemento_c.setValoresDifusos(AtributoDifuso("Salud", fuzzyTypes));
        //Desempeno
        //fuzzyTypes = { {"baja",temp_desempeno_baja}, {"media",temp_desempeno_media}, {"alta",temp_desempeno_alta} };
        //elemento_c.setValoresDifusos(AtributoDifuso("Desempeno", fuzzyTypes));
        //Temperamento
        fuzzyTypes = { {"baja",temp_temperamento_baja}, {"alta",temp_temperamento_alta} };
        elemento_c.setValoresDifusos(AtributoDifuso("Temperamento", fuzzyTypes));
        //MadurezEmocional
        //fuzzyTypes = { {"baja",temp_madurezEmocional_baja}, {"alta",temp_madurezEmocional_alta} };
        //elemento_c.setValoresDifusos(AtributoDifuso("MadurezEmocional", fuzzyTypes));
        //Companerismo
        //fuzzyTypes = { {"baja",temp_companerismo_baja}, {"alta",temp_companerismo_alta} };
        //elemento_c.setValoresDifusos(AtributoDifuso("Companerismo", fuzzyTypes));
        //Vision
        //fuzzyTypes = { {"baja",temp_vision_media}, {"alta",temp_vision_alta} };
        //elemento_c.setValoresDifusos(AtributoDifuso("Vision", fuzzyTypes));
        //objetoFID3.agregaElemento(elemento_c);
        //Liderazgo
        //fuzzyTypes = { {"baja",temp_liderazgo_baja}, {"alta",temp_liderazgo_alta} };
        //elemento_c.setValoresDifusos(AtributoDifuso("Liderazgo", fuzzyTypes));
        //objetoFID3.agregaElemento(elemento_c);

        Jugadores.insert(Jugadores.end(), elemento_c);

        elemento_c.clear();
        c++;
        //std::cout << "--------------" << std::endl;

    }
    ip2.close();

    // Archivo de salida
    std::ofstream op3;
    op3.open("JugadoresSerena.csv"); // 
    for (int i = 0; i < Jugadores.size(); i++) {

        for (int j = 0; j < objetoFID3.getClases().size(); j++) {
            //std::cout << objetoFID3.getClases()[j] << std::endl;
            Jugadores[i].setClases(objetoFID3.getClases()[j], 0);
        }
        // Se clasifica a cada jugador
        objetoFID3.recorreArbolFID3(&(Jugadores[i]));
        // Se escribe en el archivo de salida op

        op3 << Jugadores[i].imprimir(objetoFID3.getClases()) << std::endl;
        //op3 << std::to_string(i) << std::endl;

    }


    op3.close();
    std::cout << "Libreria FID3" << std::endl;

    return(0);
}
