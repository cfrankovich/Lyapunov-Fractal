#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <SDL2/SDL.h>

#include "Debug.h"
#include "Definitions.h"

/* Take lambda as an input and output the color code for the fractal */
color_t get_exponent_color(double y)
{
    int value;
    int l;
    color_t color;

    if (y > -4 && y <= -1)
    {
        l = 3;
        y += 4;
        value = floor(255 * (abs(y) / l));

        color.red = value; 
        color.green = value; 
        color.blue = 0x00; 
    }
    else if (y > -1 && y <= 0)
    {
        l = 1;
        y += 1;
        value = floor(255 * (abs(y) / l));

        color.red = 0xFF; 
        color.green = 0xFF; 
        color.blue = value; 
    }
    else if (y > 0 && y <= 1)
    {
        l = 1;
        value = floor(255 * (abs(y) / l));

        color.red = 255 - value; 
        color.green = 255 - value; 
        color.blue = 0xFF; 
    }
    else if (y > 1 && y <= 3)
    {
        l = 2;
        y -= 1;
        value = floor(255 * (abs(y) / l));

        color.red = 0x00; 
        color.green = 0x00; 
        color.blue = 255 - value; 
    }
    else 
    {
        color.red = 0x00;
        color.green = 0x00;
        color.blue = 0x00;
    }

    return color;
} 

/* Takes the sequence string and creates an array of the r values (A and B) */
std::vector<double> get_sequence(std::string str, double A, double B)
{
    std::vector<double> sequence;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == 'A')
        {
            sequence.push_back(A);
        }
        else
        {
            sequence.push_back(B);
        }
    }

    return sequence;
} 

/* Inputs x for x_n-1 and r for r. Will output x_n */
double modified_logistical_map(double x, double r)
{
    return r * x * (1 - x);
}

/* Update the iterator to repeat */
void update_iterator(int* iterator, size_t size)
{
    (*iterator)++; // increment 
    (*iterator) %= size; // if it goes above the size, bring it back in range [0, size-1]
}

/* See Notes.pdf for the actual formula */
double calculate_lyapunov_exponent(int iterations, double x0, std::vector<double> sequence)
{
    double total, x;
    int sequence_iter;

    total = 0;

    sequence_iter = 0;

    x = modified_logistical_map(x0, sequence[sequence_iter]);

    for (int n = 0; n < iterations; n++)
    {
        total += log( abs(sequence[sequence_iter] * (1 - (2 * x))) ); 
        update_iterator(&sequence_iter, sequence.size());
        x = modified_logistical_map(x, sequence[sequence_iter]); 
    }    

    return total/iterations;
}

int main()
{
    /* User Inputs */
    std::string sequencestr; // Sequence of As and Bs used to calculate
    std::cout << "Sequence of As and Bs. (Example: AB): ";
    std::cin >> sequencestr;

    int iterations; // N 
    std::cout << "Number of iterations (N): ";
    std::cin >> iterations;

    int resolution; // The number of rows and cols for calculation 
    std::cout << "Resolution (in pixels): ";
    std::cin >> resolution;

    /* Computing */
    int counter;
    double A, B;
    double lambda;
    std::vector<color_t> grid_scale_values; 
    std::vector<double> lambda_values;
    std::vector<double> sequence; 

    counter = 0;
    std::cout << "Computing Values [" << counter << "/" << pow(resolution, 2) << "]";
    for (int i = 0; i < resolution; i++)
    {
        B = (MAX_R_VALUE/(resolution-1)) * i;
        for (int j = 0; j < resolution; j++)
        {
            A = (MAX_R_VALUE/(resolution-1)) * j;
            sequence = get_sequence(sequencestr, A, B);

            lambda = calculate_lyapunov_exponent(iterations, x_0, sequence);
            lambda_values.push_back(lambda);

            color_t color = get_exponent_color(lambda);
            grid_scale_values.push_back(color);

            std::cout << "\rComputing Values [" << ++counter << "/" << pow(resolution, 2) << "]";
        }
    }

    create_debug_file(grid_scale_values, lambda_values);

    /* Graphics */ 
    bool running;
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;

    running = true;
    window = NULL;
    renderer = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Lyapunov's Fractal", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resolution, resolution, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    while (running)
    {
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            std::cout << "Exiting...\n";
            running = false;
            break;
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // draw here //
        for (int x = 0; x < resolution; x++)
        {
            for (int y = 0; y < resolution; y++)
            {
                SDL_SetRenderDrawColor(renderer, grid_scale_values[x*y].red, grid_scale_values[x*y].green, grid_scale_values[x*y].blue, 0xFF);
                SDL_RenderDrawPoint(renderer, x, resolution-y);
            }
        }

        SDL_RenderPresent(renderer);
    }

    return 0;
}