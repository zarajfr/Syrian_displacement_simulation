#include "simulator.h"

simulator::simulator( double pp1, double g1, double g2, double g3, double g4, double g5){
	simlen = 40; //default
	// static const int arr[] = { 92000, 44200, 19900, 24000, 31800, 25400, 35200, 29200, 25500, 1700, 18300, 56600, 7200, 15700};
	static const int arr[] = { 23000, 11050, 4975, 6000, 7950, 6350, 8800, 7300, 6375, 425, 4575, 14150, 1800, 3925};
	std::vector<int> v (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	size_pop = v;

	net = new graph(26);
	std::ifstream dfile;
  dfile.open("combined-distances.csv");
  SYR_Gen(net, dfile);
	dfile.close();

	std::ifstream cfile;
  cfile.open("conflict.csv");
  net->SetConflict(cfile);
	cfile.close();

  std::ifstream fwdfile2;
  fwdfile2.open("avgwage.csv");
	net->SetAvgWage(fwdfile2);
	fwdfile2.close();

	std::ifstream fwdfile3;
  fwdfile3.open("fpfhospitalsoverall.csv");
	net->SetHospitals(fwdfile3);
	fwdfile3.close();

	std::ifstream borderfile;
	// borderfile.open("computed_finalborder.csv");
	borderfile.open("jordan-closure.csv");
	net->SetBorder(borderfile);
	borderfile.close();

	std::ifstream f5;
	f5.open("orig_aid.csv");
	net->SetAids(f5);
	f5.close();

	net->SetCamps();

  net->Normalize();

	p1 = pp1;
	gamma1 = g1;
	gamma2 = g2;
	gamma3 = g3;
	gamma4 = g4;
	gamma5 = g5;
	// population_resolution = 50.0; //default
	population_resolution = 200.0; //default
}
simulator::simulator(const simulator& s){
	simlen = s.simlen;
	size_pop = s.size_pop;
	net = s.net;
	agents = s.agents;
	p1 = s.p1;
	gamma1 = s.gamma1;
	gamma2 = s.gamma2;
	gamma3 = s.gamma3;
	gamma4 = s.gamma4;
	gamma5 = s.gamma5;

	real_data = s.real_data;
	// aggregate_data = s.aggregate_data;
	output_data = s.output_data;
	population_resolution = s.population_resolution;
}
simulator& simulator::operator=(const simulator& s){
	if(this==&s) return *this;
		simlen = s.simlen;
		size_pop = s.size_pop;
		net = s.net;
		agents = s.agents;
		p1 = s.p1;
		gamma1 = s.gamma1;
		gamma2 = s.gamma2;
		gamma3 = s.gamma3;
		gamma4 = s.gamma4;
		gamma5 = s.gamma5;

		real_data = s.real_data;
		// aggregate_data = s.aggregate_data;
		output_data = s.output_data;
		population_resolution = s.population_resolution;
		return *this;
}

simulator::~simulator(){
	int x = agents.size();
	for(int i = 0; i<x; i++){
		delete agents[i];
	}
	net->~graph();
}

void simulator::populate(){ //create agents with id and governoarte based on a given vector of size 14 of pop in govs
	int ncounter = 0;
	for(int i = 0; i<size_pop.size() ; i++){
		for(int j = 0; j< size_pop[i]; j++){
			agent* a = new agent(ncounter, i, net);
			agents.push_back(a);
			ncounter++;
		}
	}
}

void simulator::read_data(){
	std::vector<std::vector<double> > destination_flow_counts(18, std::vector<double>(42, 0.0));
	std::ifstream f;
	f.open("finaldestinationflow.csv");
	for(int i  = 0; i<18; i++){
		for(int j = 0; j<42; j++){
			std::string dummy;
			double df;
			std::getline(f,dummy,',');
			df = std::stod(dummy);
			destination_flow_counts[i][j] = df;
		}
	}
	f.close();
	real_data = destination_flow_counts;
}


std::vector< std::vector<double> > simulator::pass_output_data(){return output_data;}


std::vector< std::vector<int> > simulator::approximate_flee(double a0,double a1,double a2,double b0, double b1, double d1){
	std::vector< std::vector<int> > estimation;
	for(int i =0; i<14; i++){
		std::vector<int> flee_from_i;
		for(int j =0; j<simlen; j++){
			double total_utility = b0*net->nodes[i]->conflict[j+10] + b1*net->nodes[i]->conflict[j+9] - ( a0*net->nodes[i]->avgwage[j] + a1*net->nodes[i]->camps + a2*net->nodes[i]->aids[j] ) ;
			if(total_utility<0) total_utility = 0.0;
			double flee_p = double(total_utility)/double(d1 + total_utility);
			int expected = flee_p*size_pop[i];
			flee_from_i.push_back(expected);
		}
		estimation.push_back(flee_from_i);
	}
	return estimation;
}

std::vector< std::vector < double > > simulator::run(){

	std::vector< std::vector<double> > fleeflow(14, std::vector<double>(simlen, 0.0));
	std::vector< std::vector<double> > dflow(18, std::vector<double>(simlen, 0.0));
	std::vector<std::vector<int> > flee_approximation = approximate_flee(0.000000, 0.000000, 0.000000, 0.104212, 0.087418, 2.665873);
	// net->print_destination_probs(gamma1,gamma2,gamma3,gamma4);
	// std::vector<int> leaving_community;
	for(int t = 0; t<simlen; t++){
		std::vector<int> leaving_community_t;
		for(int i = 0; i<14; i++){
			//no randomisation required now
			if(flee_approximation[i][t]!=0){
				int j=0;
				while(j<flee_approximation[i][t]){
					int selected = rand() % size_pop[i];
					for(int k =0; k<i; k++){selected += size_pop[k];}
					if(leaving_community_t.size()==0){
						if(agents[selected]->get_loc() == i){
							leaving_community_t.push_back(selected);
							j++;
						}
					}
					else if(std::find(leaving_community_t.begin(), leaving_community_t.end(), selected)==leaving_community_t.end() && agents[selected]->get_loc() == i){
							leaving_community_t.push_back(selected);
							j++;
					}
				}
			}
		}

		for(int i = 0; i<leaving_community_t.size(); i++){
			fleeflow[agents[leaving_community_t[i]]->get_loc()][t] += 1;
			agents[leaving_community_t[i]]->leave(t, p1, gamma1, gamma2, gamma3, gamma4, gamma5);
			if(agents[leaving_community_t[i]]->get_loc()<14) dflow[agents[leaving_community_t[i]]->get_loc()][t] += 1;
			else if (agents[leaving_community_t[i]]->get_loc() < 17) dflow[14][t] += 1;
			else if (agents[leaving_community_t[i]]->get_loc() < 22) dflow[15][t] += 1;
			else if (agents[leaving_community_t[i]]->get_loc() < 25) dflow[16][t] += 1;
			else if (agents[leaving_community_t[i]]->get_loc() < 26) dflow[17][t] += 1;
		}
	}
	//calibrating flee

	// output_data = fleeflow;
	// std::vector<std::vector<double> > discrepancy(14, std::vector<double>(42, 0.0));
	// for(int i =0;i<14;i++){
	// 	for(int j = 0;j<simlen;j++){
	// 		discrepancy[i][j] = abs(-0.005 + double(flee_approximation[i][j])/double(size_pop[i]) - real_data[i][j]/double(size_pop[i]*population_resolution));
	// 	}
	// }
	// return discrepancy;

	//calibrating destinationflow
	std::vector<std::vector<double> > discrepancy(18, std::vector<double>(simlen, 0.0));
	double all_leaving = 0.0;
	for(int i =0; i<fleeflow.size(); i++){
		all_leaving += std::accumulate(fleeflow[i].begin(), fleeflow[i].end(), 0);
	}
	// all_leaving= 19315.0;
	output_data = dflow;
	double sum_err=0.0;
	for(int j =0; j<simlen; j++){
		for(int i =0; i<18;i++){
			// discrepancy[i][j-15] = abs( -2+ double(dflow[i][j])*population_resolution - real_data[i][j] );
			discrepancy[i][j] = abs( double(dflow[i][j])/double(all_leaving) - real_data[i][j]/3863073.0 ); //0-40 so sum of all_leaving by month 40
			sum_err += discrepancy[i][j];
				}
	}
	return discrepancy;





	// output_data = dflow;
	// for(int j =0; j<simlen; j++){
	// 	for(int i =0; i<18;i++){
	// 		dflow[i][j] = abs( -0.001 + dflow[i][j]/double(all_leaving) - real_data[i][j]/3863073.0 ); //0-40 so sum of all_leaving by month 40
	// 	}
	// }
	// return dflow;

}
