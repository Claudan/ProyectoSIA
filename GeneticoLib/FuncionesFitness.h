#ifndef FuncionesFitness_H
#define FuncionesFitness_H

#include "Plantel.h"
#include <string>

namespace GeneticoLib {

	class FuncionesFitness
	{

	public:
		static float Fitness(int formacion[10], Plantel p, int rol[10], char modo, std::string forTecnica);
	};

}
#endif