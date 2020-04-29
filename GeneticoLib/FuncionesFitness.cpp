#include "FuncionesFitness.h"
#include "Plantel.h"

#include <vector>

namespace GeneticoLib {

	float FuncionesFitness::Fitness(int formacion[10], Plantel p, int rol[10], char modo, std::string forTecnica)
	{

		double suma = 0;
		// char modo = 'D';
		// string forTecnica = "433";
		double sumaParcial = 0;
		int i = 0;
		int x = 0;
		float factor = 1.5f;
		int defensa = 0;
		int medio = 0;
		int ataque = 0;
		if (forTecnica.size() == 3)
		{
			defensa = forTecnica[0] - '0';
			medio = forTecnica[1] - '0';
			ataque = forTecnica[2] - '0';
			//cout << defensa << medio << ataque << '\n';
		}
		else
		{
			defensa = forTecnica[0] - '0';
			medio = (forTecnica[1] - '0') + (forTecnica[2] - '0');
			ataque = forTecnica[3] - '0';
		}

		if (modo == 'D')
		{
			std::vector<int> formacionDefensa;
			for (x = i; x < defensa; x++)
			{
				formacionDefensa.insert(formacionDefensa.end(), formacion[x]);
			}
			// for (int indice = 0; indice < formacionDefensa.size(); indice++)
			// {
			// 	cout << formacionDefensa.at(indice);
			// }
			// getchar();

			// cout  << '\n';
			double sinergia;
			for (i; i < defensa; i++)
			{

				double compatibilidadActual = p.getJugadorById(formacion[i]).getCompatibilidadPosicion()[rol[i] - 1];

				sinergia = 0;
				Jugador j = p.getJugadorById(formacion[i]);
				std::vector<int> buenaS = p.getJugadorById(formacion[i]).getBuenaSinergia();
				std::vector<int> malaS = p.getJugadorById(formacion[i]).getMalaSinergia();

				// for(int indice = 0;indice < buenaS.size();indice++){
				// 	cout << buenaS[indice] << '\n';
				// }
				//getchar();

				// for(int indice = 0;indice < malaS.size();indice++){
				// 	cout << malaS[indice] << '\n';
				// }

				// //getchar();

				for (int a = 0; a < defensa; a++)
				{
					//cout << a << '\n';

					if (j.ExisteSinergiaBuena(formacionDefensa[a]))
					{
						sinergia = sinergia + 1;
					}
					if (j.ExisteSinergiaMala(formacionDefensa[a]))
					{
						sinergia = sinergia - 1;
						//cout << sinergia << '\n';
						//getchar();
					}
				}

				// cout << sinergia << '\n';
				// getchar();
				if (sinergia == 0)
				{
					suma = suma + compatibilidadActual;
				}

				else
				{
					//cout << sinergia << '\n';
					compatibilidadActual = (compatibilidadActual * 0.8) + (sinergia * 0.2);
					//cout << compatibilidadActual << '\n';
					suma = suma + compatibilidadActual;
					//getchar();
				}
			}

			if (suma < 0.8 * defensa) {
				suma = suma / factor;
			}
			else {
				suma = suma * factor;
			}

			//cout << suma << '\n';

			std::vector<int> formacionMedio;
			for (x = i; x < defensa + medio; x++)
			{
				formacionMedio.insert(formacionMedio.end(), formacion[x]);
			}

			// for (int indice = 0; indice < formacionMedio.size(); indice++)
			// {
			// 	cout << formacionMedio.at(indice);
			// }

			// cout  << '\n';

			for (i; i < (defensa + medio); i++)
			{
				double compatibilidadActual = p.getJugadorById(formacion[i]).getCompatibilidadPosicion()[rol[i] - 1];
				double sinergia = 0;
				Jugador j = p.getJugadorById(formacion[i]);

				for (int a = 0; a < medio; a++)
				{
					if (j.ExisteSinergiaBuena(formacionMedio[a]))
					{
						sinergia++;
					}
					if (j.ExisteSinergiaMala(formacionMedio[a]))
					{
						sinergia--;
					}
				}

				if (sinergia == 0)
				{
					suma = suma + compatibilidadActual;
				}

				else
				{
					compatibilidadActual = compatibilidadActual * 0.9 + sinergia * 0.1;
					suma = suma + compatibilidadActual;
				}
			}

			//cout << suma << '\n';

			std::vector<int> formacionAtaque;
			for (x = i; x < 10; x++)
			{
				formacionAtaque.insert(formacionAtaque.end(), formacion[x]);
			}

			// for (int indice = 0; indice < formacionAtaque.size(); indice++)
			// {
			// 	cout << formacionAtaque.at(indice);
			// }

			// cout << '\n';
			sumaParcial = 0;
			for (i; i < 10; i++)
			{
				float compatibilidadActual = p.getJugadorById(formacion[i]).getCompatibilidadPosicion()[rol[i] - 1];
				//cout << compatibilidadActual << ' ' <<i << '\n';
				double sinergia = 0;
				Jugador j = p.getJugadorById(formacion[i]);

				for (int a = 0; a < ataque; a++)
				{
					if (j.ExisteSinergiaBuena(formacionAtaque[a]))
					{
						sinergia++;
					}
					if (j.ExisteSinergiaMala(formacionAtaque[a]))
					{
						sinergia--;
					}
				}
				if (sinergia == 0)
				{
					suma = suma + compatibilidadActual;
				}

				else
				{
					compatibilidadActual = compatibilidadActual * 0.9 + sinergia * 0.1;
					suma = suma + compatibilidadActual;
					//cout << "se modificó la sinergia \n";
				}
			}
		}

		//cout <<  p.getJugadorById(formacion[i]).compatibilidadPosicion[rol[i]-1] << '\n';

		if (modo == 'A' || modo== 'O')
		{
			std::vector<int> formacionDefensa;
			for (x = i; x < defensa; x++)
			{
				formacionDefensa.insert(formacionDefensa.end(), formacion[x]);
			}
			// for (int indice = 0; indice < formacionDefensa.size(); indice++)
			// {
			// 	cout << formacionDefensa.at(indice);
			// }

			// cout  << '\n';

			for (i; i < defensa; i++)
			{

				float compatibilidadActual = p.getJugadorById(formacion[i]).getCompatibilidadPosicion()[rol[i] - 1];

				double sinergia = 0;
				Jugador j = p.getJugadorById(formacion[i]);
				std::vector<int> buenaS = p.getJugadorById(formacion[i]).getBuenaSinergia();

				for (int a = 0; a < defensa; a++)
				{
					if (j.ExisteSinergiaBuena(formacionDefensa[a]))
					{
						sinergia++;
					}
					if (j.ExisteSinergiaMala(formacionDefensa[a]))
					{
						sinergia--;
					}
				}

				if (sinergia == 0)
				{
					suma = suma + compatibilidadActual;
				}

				else
				{
					//cout << sinergia << '\n';
					compatibilidadActual = (compatibilidadActual * 0.9) + (sinergia * 0.1);
					//cout << compatibilidadActual << '\n';
					suma = suma + compatibilidadActual;
				}
			}

			//cout << suma << '\n';

			std::vector<int> formacionMedio;
			for (x = i; x < defensa + medio; x++)
			{
				formacionMedio.insert(formacionMedio.end(), formacion[x]);
			}

			// for (int indice = 0; indice < formacionMedio.size(); indice++)
			// {
			// 	cout << formacionMedio.at(indice);
			// }

			// cout  << '\n';

			for (i; i < (defensa + medio); i++)
			{
				float compatibilidadActual = p.getJugadorById(formacion[i]).getCompatibilidadPosicion()[rol[i] - 1];
				double sinergia = 0;
				Jugador j = p.getJugadorById(formacion[i]);

				for (int a = 0; a < medio; a++)
				{
					if (j.ExisteSinergiaBuena(formacionMedio[a]))
					{
						sinergia++;
					}
					if (j.ExisteSinergiaMala(formacionMedio[a]))
					{
						sinergia--;
					}
				}

				if (sinergia == 0)
				{
					suma = suma + compatibilidadActual;
				}

				else
				{
					compatibilidadActual = compatibilidadActual * 0.9 + sinergia * 0.1;
					suma = suma + compatibilidadActual;
				}
			}

			//cout << suma << '\n';

			std::vector<int> formacionAtaque;
			for (x = i; x < 10; x++)
			{
				formacionAtaque.insert(formacionAtaque.end(), formacion[x]);
			}

			// for (int indice = 0; indice < formacionAtaque.size(); indice++)
			// {
			// 	cout << formacionAtaque.at(indice);
			// }

			// cout << '\n';
			sumaParcial = 0;
			for (i; i < 10; i++)
			{
				float compatibilidadActual = p.getJugadorById(formacion[i]).getCompatibilidadPosicion()[rol[i] - 1];
				//cout << compatibilidadActual << ' ' << i << '\n';
				int sinergia = 0;
				Jugador j = p.getJugadorById(formacion[i]);

				for (int a = 0; a < ataque; a++)
				{
					if (j.ExisteSinergiaBuena(formacionAtaque[a]))
					{
						sinergia++;
					}
					if (j.ExisteSinergiaMala(formacionAtaque[a]))
					{
						sinergia--;
					}
				}
				if (sinergia == 0)
				{
					sumaParcial = sumaParcial + compatibilidadActual;
				}

				else
				{
					compatibilidadActual = compatibilidadActual * 0.9 + sinergia * 0.1;
					sumaParcial = sumaParcial + compatibilidadActual;
					//cout << "se modificó la sinergia \n";
				}
			}
			if (sumaParcial < 0.8 * ataque) {
				sumaParcial = sumaParcial / factor;
			}
			else {
				sumaParcial = sumaParcial * factor;
			}
			suma = sumaParcial + suma;
			//cout <<  p.getJugadorById(formacion[i]).compatibilidadPosicion[rol[i]-1] << '\n';
		}

		if (modo == 'B')
		{
			std::vector<int> formacionDefensa;
			for (x = i; x < defensa; x++)
			{
				formacionDefensa.insert(formacionDefensa.end(), formacion[x]);
			}
			// for (int indice = 0; indice < formacionDefensa.size(); indice++)
			// {
			// 	cout << formacionDefensa.at(indice);
			// }

			// cout  << '\n';

			for (i; i < defensa; i++)
			{

				float compatibilidadActual = p.getJugadorById(formacion[i]).getCompatibilidadPosicion()[rol[i] - 1];

				int sinergia = 0;
				Jugador j = p.getJugadorById(formacion[i]);
				std::vector<int> buenaS = p.getJugadorById(formacion[i]).getBuenaSinergia();

				for (int a = 0; a < defensa; a++)
				{
					if (j.ExisteSinergiaBuena(formacionDefensa[a]))
					{
						sinergia++;
					}
					if (j.ExisteSinergiaMala(formacionDefensa[a]))
					{
						sinergia--;
					}
				}

				if (sinergia == 0)
				{
					suma = suma + compatibilidadActual;
				}

				else
				{
					//cout << sinergia << '\n';
					compatibilidadActual = (compatibilidadActual * 0.9) + (sinergia * 0.1);
					//cout << compatibilidadActual << '\n';
					suma = suma + compatibilidadActual;
				}
			}

			//cout << suma << '\n';

			std::vector<int> formacionMedio;
			for (x = i; x < defensa + medio; x++)
			{
				formacionMedio.insert(formacionMedio.end(), formacion[x]);
			}

			// for (int indice = 0; indice < formacionMedio.size(); indice++)
			// {
			// 	cout << formacionMedio.at(indice);
			// }

			// cout  << '\n';

			for (i; i < (defensa + medio); i++)
			{
				float compatibilidadActual = p.getJugadorById(formacion[i]).getCompatibilidadPosicion()[rol[i] - 1];
				int sinergia = 0;
				Jugador j = p.getJugadorById(formacion[i]);

				for (int a = 0; a < medio; a++)
				{
					if (j.ExisteSinergiaBuena(formacionMedio[a]))
					{
						sinergia++;
					}
					if (j.ExisteSinergiaMala(formacionMedio[a]))
					{
						sinergia--;
					}
				}

				if (sinergia == 0)
				{
					suma = suma + compatibilidadActual;
				}

				else
				{
					compatibilidadActual = compatibilidadActual * 0.9 + sinergia * 0.1;
					suma = suma + compatibilidadActual;
				}
			}

			//cout << suma << '\n';

			std::vector<int> formacionAtaque;
			for (x = i; x < 10; x++)
			{
				formacionAtaque.insert(formacionAtaque.end(), formacion[x]);
			}

			// for (int indice = 0; indice < formacionAtaque.size(); indice++)
			// {
			// 	cout << formacionAtaque.at(indice);
			// }

			// cout << '\n';
			sumaParcial = 0;
			for (i; i < 10; i++)
			{
				float compatibilidadActual = p.getJugadorById(formacion[i]).getCompatibilidadPosicion()[rol[i] - 1];
				//cout << compatibilidadActual << ' ' <<i << '\n';
				int sinergia = 0;
				Jugador j = p.getJugadorById(formacion[i]);

				for (int a = 0; a < ataque; a++)
				{
					if (j.ExisteSinergiaBuena(formacionAtaque[a]))
					{
						sinergia++;
					}
					if (j.ExisteSinergiaMala(formacionAtaque[a]))
					{
						sinergia--;
					}
				}
				if (sinergia == 0)
				{
					suma = suma + compatibilidadActual;
				}

				else
				{
					compatibilidadActual = compatibilidadActual * 0.9 + sinergia * 0.1;
					suma = suma + compatibilidadActual;
					//cout << "se modificó la sinergia \n";
				}
			}

			//cout <<  p.getJugadorById(formacion[i]).compatibilidadPosicion[rol[i]-1] << '\n';
		}

		// cout << suma << '\n';
		return suma;
	}

}