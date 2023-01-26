#include "agent.h"
#include "math.h"
#include <iomanip>

agent::agent(){
	idd = 0;
	// number_journeys=0;
}

agent::agent(int i){
	idd = i;
	// number_journeys=0;
}

agent::agent(const agent& a){
    idd = a.idd;
		geonet = a.geonet;
		districtid = a.districtid;
		income = a.income;
		// utilities_leave = a.utilities_leave;
		// utilities_stay = a.utilities_stay;
		utility_leave = a.utility_leave;
		utility_stay = a.utility_stay;
		// number_journeys = a.number_journeys;

}

agent::agent(int i, int gov, graph* g){
	idd = i;
	districtid = gov;
	geonet = g;
	utility_stay = 0.0;
	utility_leave = 0.0;
	// number_journeys=0;
}

agent& agent::operator=(const agent& a)
{
    if(this==&a)
        return *this;
    idd = a.idd;
		geonet = a.geonet;
    districtid = a.districtid;
		income = a.income;
		// utilities_leave = a.utilities_leave;
		// utilities_stay = a.utilities_stay;
		utility_leave = a.utility_leave;
		utility_stay = a.utility_stay;
		// number_journeys = a.number_journeys;
    return *this;
}

agent::~agent(){ }
double agent::get_wage(){return income;}
void agent::set_wage(double w){income = w;}
// int agent::get_journeys(){return number_journeys;}
int agent::get_loc(){return districtid;}

int select_from_list(double p[], int l){
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<double> dist(0,1);
	double r = dist(eng);
	for(int i = 1; i<l; i++){
		p[i] += p [i-1];
	}
	if(r <= p[0]) return 0;
	for(int i = 1; i<l; i++){
		if(r>p[i-1] && r<=p[i]) return i;
	}
}

// void agent::calculate_utilities(double alpha0,double alpha1,double beta0, double beta1, int t){
//
// 	utility_stay = alpha0*geonet->nodes[districtid]->hospitals_functionality[t] + alpha1*geonet->nodes[districtid]->camps; // (alpha1*income); // home bias + if job/income
// 	utility_leave = beta0*geonet->nodes[districtid]->conflict[t+10] + beta1*geonet->nodes[districtid]->conflict[t+9]; // + beta2*geonet->nodes[districtid]->percentage_left[t];// + beta2*geonet->nodes[districtid]->foodwagedisconnect[t]; // conflict + foodwage without feedbackeffect
//
// 	// utilities_stay.push_back(utility_stay);
// 	// utilities_leave.push_back(utility_leave);
// }
//
// bool agent::decide_stay_flee(double d0, double d1){
//
// 	/* now its only one way of decision making, we can add heterogeneity later on.
// 		an alternative is to calciulate pxp(u-u)/sum(u-u)
// 		uncertainty or randomness (could do a signal one like Gumble noise or white or whienner or whatever)
// 		here factors that encourage or discourage FLEE: violence / strong home bias / something with jobs and economy / net effect */
//
// 	std::random_device rd;
// 	std::mt19937 eng(rd());
// 	std::uniform_real_distribution<double> dist(0,1);
// 	double eu = utility_leave - utility_stay;
// 	// std::cout <<eu<<"  versus  ";
// 	// eu = draw_from_normal(eu, 0.001*eu);
// 	// double eun = gen_ran(eu, d0*eu);
// 	// std::cout <<eu<<std::endl;
// 	double p = double(eu)/double(d1 + eu);
// 	double r = dist(eng);
// 	if( r < p) {
// 		return 1;
// 	}
// 		else return 0;
// }
void agent::leave(int t, double p1, double alpha1, double alpha2, double alpha3, double alpha4, double alpha5){

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<double> dist(0,1);
	bool idp = 1;
	bool moved = 0;
	int destination=0;
	int m1 = 2;
	int m2 = 3;

	double avg_borders = 0.0;
	int* cref = new int[m1];
	geonet->nclosest_towns_to(districtid, m1, cref, 0);
	for(int i =0; i <m1; i++){avg_borders += geonet->nodes[cref[i]]->border_functionality[t];}
	avg_borders = avg_borders/m1;
	delete[]cref;

	if(dist(eng) < (p1*avg_borders) ) idp = 0;
	if(!idp){
		//refugee
		int* c = new int[m1];
		double p[m1];
		double Sp = 0.0;
		geonet->nclosest_towns_to(districtid, m1, c, idp);
		for(int i = 0; i<m1; i++){
			p[i] = geonet->nodes[c[i]]->border_functionality[t]*exp(-1.0*alpha1*geonet->distances[districtid][c[i]]/760.0);
			Sp += p[i];
		}
		if(Sp != 0.0){
		for(int i = 0; i<m1; i++){
			p[i] = p[i]/Sp;
		}
		int best = c[select_from_list(p,m1)];
		destination = best;
		moved = 1;
	}
	else if(Sp==0.0) {idp=1;}

		delete []c;
	}

	if(idp){
		//idp
		int* c = new int[m2];
		double p[m2];
		double Sp = 0.0;
		geonet->nclosest_towns_to(districtid, m2, c, idp);
		for(int i = 0; i<m2; i++){
			p[i] = exp(- 1.0*( alpha1*geonet->distances[districtid][c[i]]/760.0 - alpha2*geonet->nodes[c[i]]->avgwage[t] - alpha3*geonet->nodes[c[i]]->camps - alpha4*geonet->nodes[c[i]]->aids[t] - alpha5*geonet->nodes[c[i]]->hospitals_functionality[t] ) );
			Sp += p[i];
		}
		for(int i = 0; i<m2; i++){
			p[i] = p[i]/Sp;
			// std::cout<<p[i]<<"\n";
		}
		destination = c[select_from_list(p,m2)];
		delete []c;
	}
	// number_journeys++;
	districtid = destination;
}
