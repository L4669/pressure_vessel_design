/*
 * Pressure Vessel Design (PVD) Tool - based on analytcal methods (NO FEM)
 * Supports standard geometry found in engineering application
 * 
 * Copyright (C) <2020>  <L><N>
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


int main(int argc, char *argv[])
{
    // Introduction & License Information
    char intro[] = "Pressure Vessel Design Tool for Standard Shapes\n"  
        "Copyright (C) <2020>  <L><N> \n"
        "This program comes with ABSOLUTELY NO WARRANTY;\n"
        "This is free software, and you are welcome to \n"
        "redistribute it under certain conditions;\n"
        "see http://www.gnu.org/licenses for details.\n";
    printf("************************************************\n");
    printf("%s", intro);
    printf("************************************************\n");

    //Type of Vessels
    const int max_type_vessel = 4;
    const char *vessel_type[] = {"Sphere", "Cylinder", "Cone", "Torus"};
    int index_vessel_type = 0;
    
    // Material Related
    const int max_type_material = 5;

    // by default custom is set to AISI304L properties
    // can be modified in material database file
    const char *material_type[] = {"AISI304L", "Ti6Al4V_STA", 
                                    "Ti6Al4V_ANNEALED", "15CdV6", "Custom"};
    int index_material = 0;

    double density = 0;
    double yield_strength = 0;
    double ultimate_strength = 0;
    
    // Operations
    const int max_type_operations = 2;
    const char *operations_list[] = {"Design", "Verification"};
    int index_operation = 0;

    // Misc. Variables 
    int success_flag = 0; 
    char *title = (char *)malloc(MAX_MEMORY*sizeof(char));
    char *selection_message = (char *)malloc(MAX_MEMORY*sizeof(char));

    // Vessel type selection
    strcpy(title, "[*] Type of Pressure Vessel"); // add error handling of strcpy
    strcpy(selection_message, "(*) Enter the index to select the type"
        " of pressure vessel \nor press '0' to exit: ");
    index_vessel_type = menu_generator(vessel_type, title, 
            selection_message, max_type_vessel);

    // Material Selection 
    strcpy(title, "[*] Material Selection");
    strcpy(selection_message, "(*) Enter the index to select the material"
        " of pressure vessel \nor press '0' to exit: ");
    index_material = menu_generator(material_type, title, 
            selection_message, max_type_material);
    
    
    // Reading mechanical properties of selected material
    char *material_name;
    material_name = (char *)malloc(MAX_MEMORY*sizeof(char));

    if(material_name == NULL)
    {
        error_message("Error: Unable to allocate memory");
        exit_message("Exiting PVD Tool");
        exit(EXIT_FAILURE);
    }

    mechanical_property_reader(index_material, material_type, material_name,
        &density, &ultimate_strength, &yield_strength);
    
    free(material_name);
    
    // Choice of operations - Design or Verification 
    strcpy(title, "[*] List of Operations");
    strcpy(selection_message, "(*) Enter the index to select operation \n"
        "or press '0' to exit: ");
    index_operation = menu_generator(operations_list, title, 
            selection_message, max_type_operations);
    
    // Confirmation for continuation of program
    program_continue_confirmation();
   
    // specific operations w.r.t vessel type 
    // actual structural computation
    success_flag = 0;

    switch(index_vessel_type)
    {
        case 1:
            success_flag = spherical(index_operation, yield_strength, 
                    ultimate_strength);
            break;
        case 2:
            printf("Support not yet added\n");
            break;
        case 3:
            printf("Support not yet added\n");
            break;
        case 4:
            printf("Support not yet added\n");
            break;
        default:
            printf("Error\n");
            break;
    }
    
    free(title);
    free(selection_message);
    return 0;
}
