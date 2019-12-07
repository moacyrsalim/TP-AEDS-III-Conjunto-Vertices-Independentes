#include "tempo.h"

double time_start(){
	struct timespec tempo;
	clock_gettime(CLOCK_MONOTONIC, &tempo);
	return ((double)tempo.tv_nsec /1000 ) + ((double)tempo.tv_sec * 1000000); 
}

double time_end(double tempo_inicial){
	struct timespec tempo_final;
	clock_gettime(CLOCK_MONOTONIC, &tempo_final);
	return ((double)tempo_final.tv_nsec /1000 ) + ((double)tempo_final.tv_sec * 1000000) - tempo_inicial;
}

double system_time_start(){
	struct rusage use;
	getrusage(RUSAGE_SELF, &use);
	return (double)use.ru_stime.tv_usec + ((double)use.ru_stime.tv_sec * 1000000);
}

double user_time_start(){
	struct rusage use;
	getrusage(RUSAGE_SELF, &use);
	return (double)use.ru_utime.tv_usec + ((double)use.ru_utime.tv_sec * 1000000);	
}


double system_time_end(double tempo_inicial){
	struct rusage use;
	getrusage(RUSAGE_SELF, &use);
	return use.ru_stime.tv_usec + (use.ru_stime.tv_sec * 1000000) - tempo_inicial;
}

double user_time_end(double tempo_inicial){
	struct rusage use;
	getrusage(RUSAGE_SELF, &use);
	return use.ru_utime.tv_usec + (use.ru_utime.tv_sec * 1000000) - tempo_inicial;	
}