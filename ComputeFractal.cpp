#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#define x_0 0.5

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
    double A, B;
    std::cout << "A = ";
    std::cin >> A;
    std::cout << "B = ";
    std::cin >> B;

    std::string sequencestr; // Sequence of As and Bs used to calculate
    std::cout << "Sequence of As and Bs. (Example: AB): ";
    std::cin >> sequencestr;

    int iterations; // N 
    std::cout << "Number of iterations (N): ";
    std::cin >> iterations;

    int resolution; // The number of rows and cols for calculation 
    std::cout << "Resolution (in pixels): ";
    std::cin >> resolution;

    /* Compute */
    std::vector<double> sequence = get_sequence(sequencestr, A, B);

    double lambda = calculate_lyapunov_exponent(iterations, x_0, sequence);
    std::cout << lambda << "\n";

    return 0;
}