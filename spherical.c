/*
 * spherical.c includes design calculations, user inputs,
 * output for spherical type pressure vessel,
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


int spherical(int index_operation, double yield_strength, 
        double ultimate_strength)
{
    int success_flag = 0;
    double ret_double = 0;
    double pressure = 0, thickness = 0, internal_diameter = 0,
           volume = 0, fos_ys, fos_uts = 0, weld_efficiency = 0;

    const int max_type_methods = 4;
    const char *methods[] = {"Membrane Theory", "Svensson's Formula", 
        "ASME BPVC", "Lame's Equation"};
    int index_method = 0;
    char *title = (char *)malloc(MAX_MEMORY*sizeof(char));
    char *selection_message = (char *)malloc(MAX_MEMORY*sizeof(char));

    if(index_operation == 1)
    {
        // Direct Design
        title_message("[*] Activating Spherical Vessel Design Module");
        printf("Pressing '0' at any stage will exit PVD tool\n");
        do
        {
            user_input_message("(*) Enter Factor of Safety on YS: ");
            ret_double = double_input_reader(&success_flag);
        } while(!success_flag);

        fos_ys = ret_double;

        success_flag = 0;
        do
        {
            user_input_message("(*) Enter Factor of Safety on UTS: ");
            ret_double = double_input_reader(&success_flag);
        } while(!success_flag);

        fos_uts = ret_double;

        success_flag = 0;
        do
        {
            user_input_message("(*) Enter Weld Efficiency: ");
            ret_double = double_input_reader(&success_flag);
        } while(!success_flag);

        weld_efficiency = ret_double;

        success_flag = 0;
        do
        {
            user_input_message("(*) Enter Internal Pressure in bar: ");
            ret_double = double_input_reader(&success_flag);
        } while(!success_flag);

        pressure = ret_double*pow(10, 5); // bar to Pa

        // Volume or Internal Diameter
        internal_diameter = get_sphere_diameter();

        // menu to select technique
        strcpy(title, "[*] List of Design Methods:");
        strcpy(selection_message, "(*) Enter the index to select the method"
            " to design the pressure vessel \nor press '0' to exit: ");
        index_method = menu_generator(methods, title,
                selection_message, max_type_methods);

        // Implement equations
        double t_ys = 0, t_uts = 0, t_bpvc=0, max_allowable_stress=0;
        switch(index_method)
        {
            case 1: 
                t_ys = fos_ys*pressure*internal_diameter/\
                       (4.0*weld_efficiency*yield_strength);
                t_uts = fos_uts*pressure*internal_diameter/\
                        (4.0*weld_efficiency*ultimate_strength);
                if (t_ys > t_uts)
                {
                    thickness = t_ys;
                    printf("Thickness %f mm w.r.t to YS\n", thickness*1e3);
                }
                else
                {
                    thickness = t_uts;
                    printf("Thickness %f mm w.r.t to UTS\n", thickness*1e3);
                }
                break;
            case 2:
                printf("Method yet to be implemented\n");
                break;
            case 3:
	// Section II, Mandatory Appendix 1
		max_allowable_stress=((ultimate_strength/3.5)<(2*yield_strength/3)?\
				       (ultimate_strength/3.5):(2*yield_strength/3));
		if(fos_uts*pressure < 0.665*max_allowable_stress*weld_efficiency)
		{
	// Section VIII, UG - 27 of BPVC Document
		t_bpvc= fos_uts*pressure*internal_diameter/\
		   (2*(2*max_allowable_stress*weld_efficiency-0.2*fos_uts*pressure));
		}
		else
		{
	// Section VIII, Mandatory Appendix 1 (1-3)
		    t_bpvc=(internal_diameter/2)*(exp(0.5*fos_uts*pressure/\
		    (max_allowable_stress*weld_efficiency))-1);
		}
		printf("Thickness %f mm\n",t_bpvc*1e3);                
                break;
            case 4:
                printf("Method yet to be implemented\n");
                break;
            default:
                break;
        }
    }

    free(title);
    free(selection_message);
    return 1;
}
