#include <string>
#include <iostream>
#include <fstream>
#include "simulator.h"
#include "ga_destination.h"
// #include "example_mo1.h"
#include "openga.hpp"

int main()
{
	//SO
	EA::Chronometer timer;
	timer.tic();
	GA_Type ga_obj;
	ga_obj.problem_mode= EA::GA_MODE::SOGA;
	// ga_obj.multi_threading=true;
	ga_obj.multi_threading=true;
	ga_obj.idle_delay_us=1; // switch between threads quickly
	ga_obj.verbose=false;
	ga_obj.population=40;
	ga_obj.generation_max=1000;
	ga_obj.calculate_SO_total_fitness=calculate_SO_total_fitness;
	ga_obj.init_genes= init_genes;
	ga_obj.eval_solution= eval_solution;
	ga_obj.mutate= mutate;
	ga_obj.crossover= crossover;
	ga_obj.SO_report_generation= SO_report_generation;
	ga_obj.best_stall_max=10;
	ga_obj.elite_count=10;
	ga_obj.crossover_fraction=0.45;
	ga_obj.mutation_rate=0.3;
	std::cout<<"N_thread:  "<< ga_obj.N_threads << std::endl;
	// ga_obj.solve();

	// simulator* s = new simulator(0.011649, 2.292932, 0.579494, 1.049109, 1.195684);
	// simulator* s = new simulator(0.359033, 0.515888, 0.088987, 1.371547, 0.580273); //better
	// simulator* s = new simulator(	0.341215, 1.808526, 0.353991, 1.843177, 1.750442, 0.657798);

		// simulator* s = new simulator(0.765287, 1.980907, 0.858260, 2.588330, 0.749486, 0.008946); //best pattern
		// simulator* s = new simulator(0.501992, 1.457139, 1.358246, 2.808256, 1.215129, 0.048564); // 18
		// simulator* s = new simulator(0.761059, 1.815692, 1.917239, 2.831702, 1.157506, 0.225870); // 14
		simulator* s = new simulator(0.761059, 1.815692, 1.917239, 2.831702, 1.157506, 0.225870);
		s->populate();
		s->read_data();
		s->run();
		std::vector< std::vector<double> > v = s->pass_output_data();
		s->~simulator();
		std::ofstream output_file2;
		output_file2.open("destinationsimflow-sim00.csv");
		for(int i = 0; i  < v.size(); i++){
			for(int j = 0; j< v[i].size(); j++){
				double a = v[i][j]; //population_resolution
				output_file2 << a << ',';
			}
			output_file2 << '\n';
		}
		output_file2.close();

	return 0;
}
