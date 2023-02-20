#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "Definitions.h"
#include "Debug.h"

void create_debug_file(std::vector<color_t> colors, std::vector<double> lambdas)
{
    std::ofstream output_file;
    output_file.open("debug.txt"); 

    for (int i = 0; i < colors.size(); i++)
    {
        output_file << "λ = " << lambdas[i] << "\tc = " << std::hex << colors[i].red << colors[i].green << colors[i].blue << "\n"; 
    }
    output_file.close();
}