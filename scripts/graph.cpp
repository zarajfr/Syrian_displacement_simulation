#include "graph.h"

graph::graph(){
	net_size = 0;
	}

graph::graph(const graph& g){
	nodes = g.nodes;
	net_size = g.net_size;
	distances = g.distances;
}

graph::graph(int n){
	net_size = n;
	for(int i = 0; i<n; i++){
		node* n1 = new node(i);
		nodes.push_back(n1);
	}
	for(int i = 0; i<n; i++){
		std::vector<double> v;
		for(int j = 0; j<n; j++){
			v.push_back(0.0);
		}
		this->distances.push_back(v);
	}
}
graph& graph::operator=(const graph& g){
	if(this==&g)
		return *this;
	net_size = g.net_size;
	nodes = g.nodes;
	distances = g.distances;

	return *this;
}
graph::~graph(){
	int x = nodes.size();
	for(int i = 0; i<x; i++){
		for(int j = 0; j<nodes[i]->neighbors.size(); j++){
			nodes[i]->neighbors[j] = NULL;
		}
		delete nodes[i];
	}
}

// int graph::Sum_Deg(){ //O(n*m)
// 	int sum = 0;
// 	for(int i =0; i<nodes.size();i++){
// 		sum += nodes[i]->neighbors.size();
// 	}
// 	return sum;
// }
//
// double graph::global_clustering(){
// 	double c=0.0;
// 	for(int i = 0; i<this->nodes.size(); i++){
// 		c += clustering(i);
// 	}
// 	return double(c/double(this->net_size));
// }
//
// bool graph::is_connected(int i , int j){
// 	for(int k = 0; k < nodes[i]->neighbors.size(); k++){
// 		if(nodes[i]->neighbors[k]->Id() == j){return true;}
// 	}
// 	return false;
// }
// double graph::clustering(int u){
// 	double e = 0.0;
// 	for(int i =0; i<nodes[u]->neighbors.size(); i++)
// 		for(int j =i+1; j<nodes[u]->neighbors.size(); j++){
// 			if(is_connected(nodes[u]->neighbors[i]->Id(),nodes[u]->neighbors[j]->Id())) {e++;}
// 		}
// 	double sz = nodes[u]->neighbors.size()*(nodes[u]->neighbors.size()-1) ;
// 	    double cc;
// 	    if(sz !=0){
// 	        cc = double(2.0*e/sz);
// 	        return cc;
// 	    }
// 	    else return 0;
// }
// double graph::connectivity(){
// 	double c = 0.0;
// 	for(int i =0; i<nodes.size(); i++){
// 		c += nodes[i]->neighbors.size();
// 	}
// 	return double(c/(2*nodes.size()));
// }
// std::vector<double> graph::deg_dist(){
// 	std::vector<int> v;
// 	std::vector<double> d;
//
// 	for(int i=0; i<nodes.size(); i++){
// 		v.push_back(nodes[i]->neighbors.size());
// 	}
// 	// this can be oprimised easily
// 	for(int i = 0; i <net_size; i++){
// 		int count = 0;
// 		for(int j =0; j<v.size();j++){
// 			if(v[j] == i){count ++;}
// 			}
// 		d.push_back(count);
// 	}
// 	for(int i =0; i<d.size();i++){
// 		d[i] = double(d[i]/net_size);
// 	}
// 	return d;
// }

void graph::SetConflict(std::ifstream& f){
	if(!f.is_open()) std::cout << "File is not open!" << "\n";
	std::vector<std::vector<double> > cv;
	for(int i = 0; i<53; i++){
		std::vector<double> v;
		for(int j = 0; j<14; j++){
			std::string dummy;
			double c1;
			std::getline(f,dummy,',');
			c1 = double(std::stod(dummy));
			v.push_back(c1);
		}
		cv.push_back(v);
	}
	for(int i = 0; i<14; i++){
		std::vector<double> v1;
		for(int j = 0; j<53;j++){
			v1.push_back(cv[j][i]);
		}
		nodes[i]->SetConflict(v1);
	}
	for(int i = 14; i<26; i++){ //assuming outside there is no conflict
		std::vector<double> v1;
		for(int j = 0; j<53;j++){
			v1.push_back(0.0);
		}
			nodes[i]->SetConflict(v1);
	}
}

void graph::SetBorder(std::ifstream& f){

	for(int i = 14;i<26;i++){
		std::vector<double> v1;
			for(int j = 0; j<41; j++){ // data covers 41 months from 01-2016 to 05-2019
				std::string dummy2;
				double brd;
				std::getline(f,dummy2,',');
				brd = double(std::stod(dummy2));
				v1.push_back(brd);
			}
			nodes[i]->SetBorderFunc(v1);
	}
}
// void graph::SetDisconnect(std::ifstream& f){ //only in origins from 0 to 14
// 	if(!f.is_open()) std::cout << "File is not open!" << "\n";
// 	if(net_size <14) std::cout << "Syria has 14 governoartes";
// 	for(int i = 0; i<14; i++){
// 		std::vector<double> disc;
// 		for(int j = 0; j<42;j++){ // data covers 42 months from 01-2016 to 06-2019
// 			std::string dummy;
// 			double f1;
// 			std::getline(f,dummy,',');
// 			f1 = double(std::stod(dummy));
// 			disc.push_back(f1);
// 		}
// 		nodes[i]->Set_Discon(disc);
// 	}
// }
void graph::SetAvgWage(std::ifstream& f){
	for(int i = 0; i<14; i++){
		std::vector<double> avgw;
		for(int j = 0; j<42;j++){ // data covers 42 months from 01-2016 to 06-2019
			std::string dummy2;
			double f2;
			std::getline(f,dummy2,',');
			f2 = double(std::stod(dummy2));
			avgw.push_back(f2);
		}
		nodes[i]->SetAvgw(avgw);
		// std::cout<<nodes[i]->avgwage[0]<<std::endl;
	}
}

void graph::SetHospitals(std::ifstream& f){
	for(int i = 0; i<14; i++){
		std::vector<double> h;
		for(int j = 0; j<42;j++){ // data covers 42 months from 01-2016 to 06-2019
			std::string dummy2;
			double f2;
			std::getline(f,dummy2,',');
			f2 = double(std::stod(dummy2));
			h.push_back(f2);
		}
		nodes[i]->SetHF(h);
	}
}

void graph::SetAids(std::ifstream& f){
	for(int i =0; i<14; i++){
	std::vector<double> hf(41, 0.0);
	for(int j =0; j<41; j++){
		std::string dummy;
		double hff;
		std::getline(f,dummy,',');
		hff = double(std::stod(dummy));
		hf.push_back(hff);
		}
	nodes[i]->SetAid(hf);
	}
}

void graph::SetCamps(){
	static const int arr[] = {23,0,2,0,0,0,1,35,6,1,0,2,2,4};
	std::vector<int> v (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	for(int i = 0; i<14; i++){
		nodes[i]->camps = double(v[i])/35.0;
	}
}

void graph::Normalize(){ //here I nornmalise all variables related to regions wrt all govs at all times //maybe I should not normalise over all times? //numbers are max and min of the data set
	if(nodes.size()==0){
		std::cout<<"error: no node yet!"<<std::endl;
	} else {
		for(int i = 0; i<nodes.size();i++){
			for(int j = 0; j<nodes[i]->conflict.size();j++){
				nodes[i]->conflict[j] = double(nodes[i]->conflict[j]/816.0);
			}

			for(int k = 0; k<nodes[i]->avgwage.size();k++){
				nodes[i]->avgwage[k] = double(nodes[i]->avgwage[k]/4000.0);
				nodes[i]->aids[k] = double(nodes[i]->aids[k]/77.0);
			}
		}
	}
}

void graph::nclosest_towns_to(int i, int n, int* c, bool idp){
	std::vector<double> v = distances[i];
	if(idp){std::sort(v.begin(), v.begin()+14); v.erase(v.begin()+14, v.end());}
	else {std::sort(v.begin()+14, v.end()); v.erase(v.begin(), v.begin()+14);}
	// if IDP, no movement within same governorate is counted.
	for(int k =(0+idp);k<(n+idp);k++){
		for(int j = 0; j<v.size(); j++){
			if(idp){
				if(v[k] == distances[i][j] && j!= i){c[k-1] = j; break;}
					}
				else {
					if(v[k] == distances[i][j+14] && (j+14)!= i){c[k] = j+14; break;}
				}
			}
	}
}

void SYR_Gen(graph* g, std::ifstream& f){
	if(!f.is_open()) std::cout << "File is not open!" << "\n";
	for(int k = 14;k<26;k++){
		g->nodes[k]->type = 'b';
	}
	for(int i = 0; i<26; i++){
		for(int j = i+1; j<26; j++){
			g->nodes[i]->neighbors.push_back(g->nodes[j]);
			g->nodes[j]->neighbors.push_back(g->nodes[i]);
			std::string dummy;
			double d1;
			std::getline(f,dummy,',');
			d1 = double(std::stod(dummy));
			g->distances[i][j] = d1;
			g->distances[j][i] = d1;
		}
	}
}

void graph::print_destination_probs(double g1, double g2, double g3, double g4){
	for(int j =1; j<14;j++){
		for(int t =0; t<40; t++){
		// std::cout<<	exp(- 1.0*( g1*distances[j][0]/760.0 - g2*nodes[0]->avgwage[t] - g3*nodes[0]->camps[t] - g4*nodes[0]->aids[t] ) ) <<'\n';
   std::cout<< distances[j][0]/760.0<<"distance"<<"\n"<< nodes[0]->avgwage[t] <<"avgwage"<<"\n" << nodes[0]->camps <<"camps" <<'\n';
	}
	std::cout<<"nextt"<<'\n';
}
}
