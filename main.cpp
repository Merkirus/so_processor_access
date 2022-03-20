#include <vector>
#include <iostream>
#include "Proces.h"
#include "Generator.h"
#include "RR.h"
#include "FCFS.h"
#include "SJFW.h"

using namespace std;

auto main() -> int {

	std::vector<Proces> procesy {Generator::generujProcesy(10)};

	// FCFS fcfs (procesy);

	// RR rr (procesy, 5);

	// fcfs.run();

	// rr.run();

	// fcfs.display();

	// cout << "----------------" << '\n';

	// rr.display();

	return 0;
}