#ifndef __simulatorr__
#define __simulatorr__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <random>
#include <string>
#include <cstdlib>
#include "graph.h"
#include "agent.h"
#include <time.h>
#include <limits>

//she keeps track of time, she runs the agents, updates them, she does the God's job!
class simulator{

public:
	simulator( double pp1, double g1, double g2, double g3, double g4, double g5);
	simulator(const simulator& s);
	simulator& operator=(const simulator& a);
	~simulator();
	void populate();
	void read_data();
	std::vector< std::vector<double> > pass_output_data();
	std::vector< std::vector<int> > approximate_flee(double ,double ,double ,double , double , double );
	std::vector< std::vector< double> >run();

private:
	std::vector<int> size_pop;
	int simlen;
	graph* net;
	std::vector<agent*> agents;
	// std::vector<double> aggregate_data;
	//destination flow
	double p1;
	double gamma1;
	double gamma2;
	double gamma3;
	double gamma4;
	double gamma5;
	std::vector< std::vector<double> > real_data;
	std::vector< std::vector<double> > output_data;
	double population_resolution;
};

#endif
