#include <iostream>

double mapfunc(double x, double r)
{
    return r * x * (1 - x); 
}

int main()
{
    /* Inputs */
    double x, r;
    int n;

    std::cout << "x_0 = ";
    std::cin >> x;

    std::cout << "r = ";
    std::cin >> r;

    std::cout << "n = ";
    std::cin >> n;

    /* Computation */
    for (int i = 1; i < n+1; i++)
    {
        x = mapfunc(x, r);
        std::cout << "x_" << i << " = " << x << "\n";
    }

    return 0;
}