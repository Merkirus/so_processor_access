#include <vector>
#include <iostream>
#include "Proces.h"
#include "Generator.h"
#include "RR.h"
#include "FCFS.h"
#include "SJFW.h"

using namespace std;

auto main() -> int {

	std::vector<Proces> procesy {Generator::generujProcesy(150)};
	// std::vector<Proces> procesy1 {Generator::generujProcesy(50)};
	// std::vector<Proces> procesy2 {Generator::generujProcesy(50)};
	// std::vector<Proces> procesy3 {Generator::generujProcesy(50)};
	// std::vector<Proces> procesy4 {Generator::generujProcesy(50)};
	// std::vector<Proces> procesy5 {Generator::generujProcesy(50)};

	FCFS fcfs (procesy);
	// FCFS fcfs1 (procesy1);
	// FCFS fcfs2 (procesy2);
	// FCFS fcfs3 (procesy3);
	// FCFS fcfs4 (procesy4);
	// FCFS fcfs5 (procesy5);

	RR rr (procesy, 1);
	// RR rr1 (procesy1, 5);
	// RR rr2 (procesy2, 5);
	// RR rr3 (procesy3, 5);
	// RR rr4 (procesy4, 5);
	// RR rr5 (procesy5, 5);

	SJFW sjfw (procesy);
	// SJFW sjfw1 (procesy1);
	// SJFW sjfw2 (procesy2);
	// SJFW sjfw3 (procesy3);
	// SJFW sjfw4 (procesy4);
	// SJFW sjfw5 (procesy5);
	
	fcfs.run();
	rr.run();
	sjfw.run();

	cout << "------------" << '\n';
	fcfs.display();
	cout << "------------" << '\n';
	rr.display();
	cout << "------------" << '\n';
	sjfw.display();

	return 0;
}