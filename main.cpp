#include <vector>
#include "Proces.h"
#include "Generator.h"
#include "RR.h"

using namespace std;

auto main() -> int {

	std::vector<Proces> procesy {Generator::generujProcesy(50)};

	RR r(procesy, 5);

	r.run();

	return 0;
}