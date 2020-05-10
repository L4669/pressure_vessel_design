/*
 * aux.c constains all auxilliary functions for input reading,
 * menu generator etc;
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


#include "pvd.h"


void error_message(char message[])
{
    printf("\033[1;31m");
    printf("%s\n", message);
    printf("\033[0m");
}

void exit_message(char message[])
{
    printf("\033[1;33m");
    printf("%s\n", message);
    printf("\033[0m");
}

void user_input_message(char *message)
{
    printf("\033[1;32m");
    printf("%s", message);
    printf("\033[0m");
}

void title_message(char *message)
{
    printf("\033[1;33m");
    printf("%s\n", message);
    printf("\033[0m");
}

// generates a list of options with integer index
// return integer index corresponding to seleted option
int menu_generator(const char *menu[], char *title, char *selection_message, 
        int menu_length)
{
    int i = 0, ret = 0, index = 0, success_flag = 0;
    char *buffer;
    buffer = (char *)malloc(MAX_MEMORY*sizeof(int)); 
    
    if(buffer == NULL)
    {
        free(title);
        free(selection_message);
        error_message("Error: Unable to allocate memory");
        exit_message("Exiting PVD Tool");
        exit(EXIT_FAILURE);
    }
    
    do
    {
        title_message(title);
        for (i = 0; i < menu_length; i++)
        {
            printf("[%d] %s\n", (i+1), menu[i]);
        }
        user_input_message(selection_message);

        if (!fgets(buffer, MAX_MEMORY, stdin))
        {
            free(title);
            free(selection_message);
            error_message("Error: fget reading from stdin");
            exit(EXIT_FAILURE);
        }
       
        char *endptr;
        errno = 0; // reset error number
        ret = strtol(buffer, &endptr, 10);
        if (errno != 0) 
        {
            error_message("Error: Conversion from str to integer in strtol");
            success_flag = 0;
        }
        else if (endptr == buffer || (ret > menu_length) || (ret < 0))
        {
            // no character was read
            error_message("ERROR: Enter a valid index");
            success_flag = 0;
        }
        else if (*endptr && *endptr != '\n')
        {
            // *endptr is neither end of string nor newline,
            // so we didn't convert the *whole* input
            success_flag = 0;
        }
        else
        {
            success_flag = 1;
            free(buffer);
        }
    } while(!success_flag);

    if(success_flag == 1 && ret == 0)
    {
        free(title);
        free(selection_message);
        exit_message("Exiting PVD Tool");
        exit(EXIT_SUCCESS);
    }
    else
    {
        index = ret;
    }

    return index;
}

// reading floating point numbers from stdin
double double_input_reader(int *success_flag)
{
    double ret = 0;
    char *buffer;

    buffer = (char *)malloc(MAX_MEMORY*sizeof(int)); 
    if(buffer == NULL)
    {
        error_message("Error: Unable to allocate memory");
        exit_message("Exiting PVD Tool");
        exit(EXIT_FAILURE);
    }
        
    if (!fgets(buffer, MAX_MEMORY, stdin))
    {
        free(buffer);
        error_message("Error: fget reading from stdin");
        exit_message("Exiting PVD Tool");
        exit(EXIT_FAILURE);
    }
   
    char *endptr;
    errno = 0; // reset error number
    ret = strtod(buffer, &endptr);
    if (errno != 0) 
    {
        error_message("Error: Conversion from str to double in strtod");
        *success_flag = 0;
    }
    else if (endptr == buffer || (ret < 0))
    {
        // no character was read
        error_message("ERROR: Enter a valid index");
        *success_flag = 0;
    }
    else if (*endptr && *endptr != '\n')
    {
        // *endptr is neither end of string nor newline,
        // so we didn't convert the *whole* input
        *success_flag = 0;
    }
    else
    {
        *success_flag = 1;
        free(buffer);
    }

    if(*success_flag == 1 && ret == 0)
    {
        free(buffer);
        exit_message("Exiting PVD Tool");
        exit(EXIT_SUCCESS);
    }
    
    return ret;
}

// Confirmation for continuation of program
void program_continue_confirmation()
{
    int success_flag = 0;
    char *buffer;
    buffer = (char *)malloc(MAX_MEMORY*sizeof(int));
    
    if(buffer == NULL)
    {
        free(buffer);
        error_message("Error: Unable to allocate memory");
        exit_message("Exiting PVD Tool");
        exit(EXIT_FAILURE);
    }
    success_flag = 0;

    do
    {
        user_input_message("(*) Do you want to continue further (yes/no): ");
        if (!fgets(buffer, MAX_MEMORY, stdin))
        {
            free(buffer);
            error_message("Error: fget reading from stdin");
            exit(EXIT_FAILURE);
        }
        if (strcmp(buffer, "yes\n") == 0) 
        {
            success_flag = 1;
            free(buffer);
        }
        else if (strcmp(buffer, "no\n") == 0)
        {
            free(buffer);
            exit_message("Exiting PVD Tool");
            exit(EXIT_SUCCESS);
        }
        else
        {
            error_message("ERROR: Enter a valid index");
            success_flag = 0;
        }
    } while(!success_flag);
}

// Reading mechanical properties of selected material
void mechanical_property_reader(int index_material, const char *material_type[],
        char *buffer, double *density, double *ultimate_strength, 
        double *yield_strength)
{
    int ret = 0;
    
    FILE *fp = fopen("material.db", "r");
    if (fp == NULL)
    {
        free(buffer);
        error_message("Error: Opening material database");
        exit_message("Exiting PVD Tool");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        ret = fscanf(fp, "%s %le %lf %lf", buffer, density, ultimate_strength,
                    yield_strength);   
        if (ret == EOF)
        {
            printf("Material database successfully read\n");
            break;
        }
        else if (ret != 4) //replace 4 with const variable on top
        {
            free(buffer);
            fclose(fp);
            error_message("Error: material database format wrong");
            exit_message("Exiting PVD Tool");
            exit(EXIT_FAILURE);
        }
        else
        {
            // selected material properties would be in the variables
            if (strcmp(buffer, material_type[index_material-1]) == 0)
                break;
        }
    }
    fclose(fp);
}

// Volume or Internal Diameter
double get_sphere_diameter()
{
    int success_flag = 0;
    double internal_diameter = 0, volume = 0;
    char *buffer;
    buffer = (char *)malloc(MAX_MEMORY*sizeof(int));
    
    if(buffer == NULL)
    {
        free(buffer);
        error_message("Error: Unable to allocate memory");
        exit_message("Exiting PVD Tool");
        exit(EXIT_FAILURE);
    }
    success_flag = 0;

    do
    {
        user_input_message("(*) Do you want to provide Volume or" 
                " Internal Diameter (vol/dia): ");
        if (!fgets(buffer, MAX_MEMORY, stdin))
        {
            free(buffer);
            error_message("Error: fget reading from stdin");
            exit(EXIT_FAILURE);
        }
        if (strcmp(buffer, "vol\n") == 0) 
        {
            int success_flag_2 = 0;
            do
            {
                user_input_message("(*) Enter Volume of the Spherical"
                        " Vessel in liters: ");
                volume = double_input_reader(&success_flag_2);
            } while(!success_flag_2);
            
            double radius = 3*volume*0.001/4/M_PI;
            internal_diameter = 2*pow(radius , 1.0/3.0);
            success_flag = 1;
            free(buffer);
            break;
        }
        else if (strcmp(buffer, "dia\n") == 0)
        {
            int success_flag_2 = 0;
            do
            {
                user_input_message("(*) Enter Internal Diameter of the"
                        " Spherical Vessel in mm: ");
                internal_diameter = double_input_reader(&success_flag_2)/1000;
            } while(!success_flag_2);

            free(buffer);
            break;
        }
        else
        {
            error_message("ERROR: Enter a valid index");
            success_flag = 0;
        }
    } while(!success_flag);

    return internal_diameter;
}


// Display results of the design operation

void print_design_results(double thickness, double stress_meop, 
        double fos_ys, double fos_uts, char *remarks)
{
    printf("************RESULTS*****************\n");
    printf("====================================\n");
    printf("%-15s \t %5s\n", "Parameters", "Values");
    printf("====================================\n");
    printf("%-15s \t %5.3f\n", "Thickness (mm)", thickness); 
    printf("------------------------------------\n");
    printf("%-15s \t %5.3f\n", "Stress @ MEOP (MPa)", stress_meop); 
    printf("------------------------------------\n");
    printf("%-15s \t %5.3f\n", "FoS-YS", fos_ys);
    printf("------------------------------------\n");
    printf("%-15s \t %5.3f\n", "FoS-UTS", fos_uts);
    printf("------------------------------------\n");
    printf("%-15s \t %s\n", "Remarks:", remarks);
    printf("====================================\n");
}
