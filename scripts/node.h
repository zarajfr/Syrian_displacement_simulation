
#ifndef __nodee__
#define __nodee__

#include <iostream>
#include <vector>
#include <array>
#include <random>
#include "math.h"

class node{
public:
	std::vector<node*> neighbors;
	node();
	node(int i);
	node(const node& n);
	node& operator=(const node& n);
	~node();

	void SetType(char t);
	char Type();
	void SetID(int d);
	int Id();
	void SetConflict(std::vector<double> v);
	void SetBorderFunc(std::vector<double> v);
	void SetAvgw(std::vector<double> v);
	void SetHF(std::vector<double> v);
	void SetAid(std::vector<double> v);
	// void SetPL(std::vector<double> v);
	// void Set_Discon(std::vector<double> v);

	char type; //can be g or b
	int id;
	std::vector<double> conflict; // conflict did not came across significant as causualties, but the deconstruction level came significant in the spatial interaction
	std::vector<double> border_functionality;
	// std::vector<double> foodwagedisconnect;
	std::vector<double> avgwage;
	std::vector<double> aids;
	std::vector<double> hospitals_functionality;
	// std::vector<double> percentage_left;
	double camps; // it will be a vector later on when we synthetise.
};

#endif
