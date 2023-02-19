#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include <SDL2/SDL.h>

#define x_0 0.5

typedef struct {
    int red;
    int green;
    int blue;
} color_t;

/* Take lambda as an input and output the color code for the fractal */
color_t get_exponent_color(double y)
{
    int value;
    int l;
    color_t color;

    if (y > -3 && y <= -1)
    {
        l = 2;
        y += 3;
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
    //std::cin >> sequencestr;

    int iterations; // N 
    std::cout << "Number of iterations (N): ";
    //std::cin >> iterations;

    int resolution; // The number of rows and cols for calculation 
    std::cout << "Resolution (in pixels): ";
    //std::cin >> resolution;

    //std::vector<double> sequence = get_sequence(sequencestr, A, B);

    //double lambda = calculate_lyapunov_exponent(iterations, x_0, sequence);
    //std::cout << lambda << "\n";

    /* Computing */
    int counter;
    counter = 0;
    std::vector<std::vector<int> > grid_scale_values; 

    std::cout << "Computing Values [" << counter << "/" << pow(resolution, 2) << "]";
    for (int i = 1; i <= resolution; i++)
    {
        for (int k = 1; k <= resolution; k++)
        {
            std::cout << "\rComputing Values [" << ++counter << "/" << pow(resolution, 2) << "]";
        }
    }

    double lambda = 0;
    std::cin >> lambda;
    color_t mycolor = get_exponent_color(lambda);
    std::cout << "0x" << std::hex << mycolor.red << mycolor.green << mycolor.blue << "\n"; 


    /* Graphics 
    bool running;
    running = true;
    SDL_Event event;

    SDL_Window* window;
    SDL_Renderer* renderer;
    window = NULL;
    renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Lyapunov's Fractal", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
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
        d

        SDL_RenderPresent(renderer);
    }
    */    

    return 0;
}