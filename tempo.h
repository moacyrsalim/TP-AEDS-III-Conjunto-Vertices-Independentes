#ifndef Tempo_H
#define Tempo_H

//#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <sys/resource.h>

double time_start();
double time_end(double tempo_inicial);

double system_time_start();
double system_time_end(double tempo_inicial);

double user_time_start();
double user_time_end(double tempo_inicial);

#endif