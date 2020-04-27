#ifndef PVD_H_
#define PVD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#define MAX_MEMORY 1024

// defined in aux.c
void error_message(char message[]);
void exit_message(char message[]);
void user_input_message(char *message);
void title_message(char *message);
int menu_generator(const char *menu[], char *title, char *selection_message,
         int menu_length);
double double_input_reader(int *success_flag);
void program_continue_confirmation();
void mechanical_property_reader(int index_material, const char *material_type[],
        char *buffer, double *density, double *ultimate_strength,
        double *yield_strength);
double get_sphere_diameter();

// defined in spherical.c
int spherical(int index_operation, double yield_strength,
        double ultimate_strength);

#endif
