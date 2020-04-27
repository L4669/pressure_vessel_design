/*
 * Pressure Vessel Design (PVD) Tool - based on analytcal methods (NO FEM)
 * Supports standard geometry found in engineering application
*/


#include "pvd.h"


int main(int argc, char *argv[])
{
    //Type of Vessels
    const int max_type_vessel = 4;
    const char *vessel_type[] = {"Sphere", "Cylinder", "Cone", "Torus"};
    int index_vessel_type = 0;
    
    // Material Related
    const int max_type_material = 4;
    const char *material_type[] = {"AISI304L", "Ti6Al4V_STA", 
                                    "Ti6Al4V_ANNEALED", "15CdV6"};
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

    // Confirmation for continuation of program
    program_continue_confirmation();

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
    
    //printf("%s %lf %lf %lf\n", material_name, density, ultimate_strength, 
    //        yield_strength);
    
    free(material_name);
    
    // Confirmation for continuation of program
    program_continue_confirmation();
    
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
