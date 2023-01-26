#ifndef __agentt__
#define __agentt__

#include <iostream>
#include <vector>
#include <array>
#include <random>
#include "graph.h"


class agent{
public:
	agent();
	agent(int i);
	agent(const agent& a);
	agent(int i, int gov, graph* );
	agent& operator=(const agent& a);
	~agent();
	// void calculate_utilities(double alpha0,double alpha1,double beta0, double beta1, int t);
	// bool decide_stay_flee(double d0, double d1);
	void leave(int t, double p1, double alpha1, double alpha2, double alpha3, double alpha4, double alpha5);
	// int get_journeys();
	double get_wage();
	void set_wage(double);
	int get_loc();

private:
	int idd;
	int districtid;
	graph* geonet; //safe if you initialise it with null pointer
	double income;
	// std::vector<double> utilities_leave;
	// std::vector<double> utilities_stay;
	double utility_leave;
	double utility_stay;
	// int number_journeys;

	// short int age;
	// short int education;

	// bool permjob;
	// float distancefromviolence;
	//int experience;
	//socialinfluence
	//fear/perception
	//economic sit
	//kins
	// double rp; //risk perception

};
int select_from_list(int p[], int l);
#endif
