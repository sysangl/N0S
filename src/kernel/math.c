#include "math.h"


double k_pow(double base, int exp)
{
    double result = 1.0;
    int i;
    for (i = 0; i < exp; i++)
        result *= base;
    return result;
}

double k_factorial(int n)
{
    double result = 1.0;
    int i;
    for (i = 2; i <= n; i++)
        result *= i;
    return result;
}

double g_sin_term, g_sin_result, g_cos_term, g_cos_result;
int g_trig_i;
double g_trig_x;

double sin(double x)
{
    while (x >  PI) x -= 2 * PI;
    while (x < -PI) x += 2 * PI;
    g_trig_x = x;
    g_sin_term = g_trig_x;
    g_sin_result = g_trig_x;
    for (g_trig_i = 1; g_trig_i < 10; g_trig_i++)
    {
        g_sin_term *= -g_trig_x * g_trig_x / ((2*g_trig_i) * (2*g_trig_i + 1));
        g_sin_result += g_sin_term;
    }
    return g_sin_result;
}

double cos(double x)
{
    while (x >  PI) x -= 2 * PI;
    while (x < -PI) x += 2 * PI;
    g_trig_x = x;
    g_cos_term = 1.0;
    g_cos_result = 1.0;
    for (g_trig_i = 1; g_trig_i < 10; g_trig_i++)
    {
        g_cos_term *= -g_trig_x * g_trig_x / ((2*g_trig_i - 1) * (2*g_trig_i));
        g_cos_result += g_cos_term;
    }
    return g_cos_result;
}

