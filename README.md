# Lyapunov's Fractal Renderer
For a full, detailed explanation visit [my website](https://frankovich.dev). 

This program will calculate all the values used to render the [Lyapunov Fractal](https://en.wikipedia.org/wiki/Lyapunov_fractal).

Playing around with different values of A, B, N, and R will yield different results.

## How To Use
Before using this program, knowing how the math works will provide optimal and meaningful results. Throwing in random values will give random or unwanted results! 

Execute the program in a terminal thus allowing the user to input values requested.

The program will begin asking the user for values A and B which are the values for r that will be repeated based on the user's input of a sequence (ABBAA, AB, AAB, etc.). 

After the user gives the values for A, B, and the sequence of A and B, the user will be prompted to input the number of iterations (N). Keep in mind, the greater N is, the more accurate the results.

Lyapunov's exponent is calculated by taking an infinite number of iterations so the true value for λ is when N = ∞. 

The final input is the resolution (R). The resolution will determine how large and how detailed the result will look. A resolution of 10 will output a 10x10 grid of colors. Again, to understand these values, read the blog linked above.

If the user doesn't want to play around with values here are some values used for testing...
```
A =
B =
Sequence = AB
N = 
R = 
```

After entering values, the program will render the fractal.

## Dependencies
To render the actual image, this project uses the [Simple DirectMedia Layer](https://www.libsdl.org) (SDL) library. This program has only been tested on a Macbook (Apple Silicon Chip); however, SDL is portable meaning it should work on any platform.
