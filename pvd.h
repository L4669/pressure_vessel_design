/*
 * a common header file for PVD Tool
 *
 * Copyright (C) <year>  <name of author>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
void print_design_results(double thickness, double stress_meop, 
        double fos_ys, double fos_uts, char *remarks);

// defined in spherical.c
int spherical(int index_operation, double yield_strength,
        double ultimate_strength);

#endif
