#include "node.h"

node::node(){
	type = 'g';
	id = 0;
}

node::node(int i){
	id = i;
	type = 'g';
}

node::node(const node& n){
    type = n.type;
    id = n.id;
    neighbors = n.neighbors;
		conflict = n.conflict;
		border_functionality = n.border_functionality;
		// foodwagedisconnect = n.foodwagedisconnect;
		avgwage = n.avgwage;
		hospitals_functionality = n.hospitals_functionality;
		// percentage_left = n.percentage_left;
		camps = n.camps;
		aids = n.aids;
}

char node::Type(){
	return type;
}

void node::SetType(char t){
	type = t;
}

node& node::operator=(const node& n)
{
    if(this==&n)
        return *this;
    type = n.type;
    neighbors = n.neighbors;
    id = n.id;
		conflict = n.conflict;
		border_functionality = n.border_functionality;
		// foodwagedisconnect = n.foodwagedisconnect;
		avgwage = n.avgwage;
		aids = n.aids;
		hospitals_functionality = n.hospitals_functionality;
		// percentage_left = n.percentage_left;
		camps = n.camps;

    return *this;
}

void node::SetID(int d){
	id = d;
}

int node::Id(){
	return id;
}

node::~node(){
	int x;
	x = neighbors.size();
	for(int i = 0; i < x; i++){
		delete neighbors[i];
	}
}

void node::SetConflict(std::vector<double> v){
	this->conflict = v; //assuming borders have conflict data too?
}

void node::SetAid(std::vector<double> v){
	this->aids = v; //assuming borders have conflict data too?
}

void node::SetBorderFunc(std::vector<double> v){
	if(type=='b'){
		this->border_functionality = v;
	}
	else{
		std::cout<<"Error: this is not a border!"<<std::endl;
	}
}
void node::SetAvgw(std::vector<double> v){
		this->avgwage = v;
}
void node::SetHF(std::vector<double> v){
	this->hospitals_functionality = v;
}
// void node::SetPL(std::vector<double> v){
// 	this->percentage_left = v;
// }
// void node::Set_Discon(std::vector<double> v){
// 	if(type=='g'){
// 		this->foodwagedisconnect = v;
// 	}
// 	else{
// 		std::cout<<"Error: this is not a governoarte!"<<std::endl;
// 	}
// }
