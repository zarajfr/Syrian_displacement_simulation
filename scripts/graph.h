#ifndef __graphh__
#define __graphh__

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <random>
#include <algorithm>
#include <iterator>
#include <string>
#include <cstddef>
#include "node.h"

class graph{
public:
	graph();
	graph(const graph& g);
	graph& operator=(const graph& g);
	graph(int n);
	~graph();
	// int Sum_Deg();
	int net_size;
	std::vector<node*> nodes;
	std::vector<std::vector<double> > distances;
	// bool is_connected(int i , int j);
	// double clustering(int u);
	// double global_clustering();
	// double connectivity();
	// std::vector<double> deg_dist();
	void SetConflict(std::ifstream& f);
	void SetBorder(std::ifstream& f);
	// void SetDisconnect(std::ifstream& f);
	void SetAvgWage(std::ifstream& f);
	void SetHospitals(std::ifstream& f);
	void SetAids(std::ifstream& f);
	void SetCamps();
	void Normalize();
	void nclosest_towns_to(int i, int n, int* c, bool idp);
	void print_destination_probs(double g1, double g2, double g3, double g4);
};

// some nodes are govs and some are borders

void SYR_Gen(graph* g, std::ifstream& f);

#endif
