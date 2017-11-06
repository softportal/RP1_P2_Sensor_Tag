
#include <stdio.h>
typedef unsigned short uint16_t;

int termtable[31][21] = {{16, 16, 17, 17, 17, 18, 18, 19, 19, 19, 19, 19, 20, 20, 20, 21, 21, 21, 21, 21, 21 },
                         {18, 18, 18, 19, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 22, 22 ,22 ,22, 22, 23 },
                         {19, 19, 19, 20, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 23 ,23 ,23, 23, 24 },
                         {20, 20, 20, 20, 21, 21, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 24 ,24 ,24, 25, 25 },
                         {21, 21, 22, 22, 22, 22, 23, 23, 23, 24, 24, 24, 24, 25, 25, 25, 25 ,26 ,26, 26, 26 },
                         {22, 23, 23, 23, 24, 24, 24, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27 ,27 ,28, 28 },
                         {24, 24, 24, 24, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 29 ,29 ,29, 30 },
                         {25, 25, 25, 25, 26, 26, 26, 27, 27, 27, 27, 28, 28, 29, 29, 30, 30, 31 ,31 ,31, 33 },
                         {26, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 31, 32, 32, 33 ,34 ,34, 36 },
                         {26, 26, 27, 27, 27, 28, 29, 29, 29, 29, 30, 30, 31, 33, 33, 34, 35, 35 ,37 ,38, 40 },
                         {27, 27, 28, 28, 28, 28, 29, 29, 30, 30, 31, 32, 33, 34, 35, 36, 37, 39 ,40 ,41, 45 },
                         {28, 28, 29, 29, 29, 29, 30, 31, 31, 31, 33, 34, 35, 36, 37, 39, 40, 41 ,45 ,45, 50 },
                         {29, 29, 29, 29, 30, 31, 31, 33, 33, 34, 35, 35, 37, 39, 40, 42, 44, 45 ,51 ,51, 55 },
                         {29, 29, 30, 30, 31, 33, 33, 34, 34, 35, 36, 38, 39, 42, 43, 45, 49, 49 ,53 ,54, 55 },
                         {30, 30, 31, 31, 32, 34, 34, 35, 36, 37, 38, 41, 42, 44, 47, 48, 50, 52 ,55 ,-1 ,-1 },
                         {31, 32, 32, 32, 33, 35, 35, 37, 37, 40, 40, 44, 45, 47, 51, 52, 55 ,-1 ,-1 ,-1 ,-1 },
                         {32, 33, 33, 34, 35, 36, 37, 39, 39, 42, 43, 46, 49, 50, 54, 55 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {32, 33, 34, 35, 36, 38, 38, 41, 41, 44, 46, 49, 51, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {33, 34, 35, 36, 37, 39, 40, 43, 44, 47, 49, 51, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {34, 35, 36, 37, 38, 41, 41, 44, 46, 50, 50, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {35, 36, 37, 39, 40, 43, 43, 47, 49, 53, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {35, 36, 38, 40, 41, 44, 45, 49, 50, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {36, 37, 39, 41, 42, 45, 47, 50, 52, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {37, 38, 40, 42, 44, 47, 49, 53 ,55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {38, 39, 41, 44, 45, 49, 52, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {38, 40, 42, 45, 47, 50, 54, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {39, 41, 43, 45, 49, 51, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {40, 42, 44, 47, 51, 54, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {41, 43, 45, 49, 53, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {42, 45, 47, 50, 54, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 },
                         {42, 45, 48, 50, 55 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 }
                        };

int term_sen(uint16_t temperature, uint16_t humidity)
{
    int t, h;

    if ((temperature < 20.00) || (temperature > 50.00))
        return -1;
    if ((humidity < 0.00) || (humidity >100.00))
        return -1;

    t = (int)temperature - 20;
    h = (int)humidity/5;

    return termtable[t][h];
}

int main()
{
    uint16_t a = 43;
    uint16_t b = 40;
    int success;
    printf("Example case: %hu grados, %hu de humedad\n", a, b);
    
    if ((success = term_sen(a, b)) != -1)
        printf("\n %i \n", term_sen(a, b));
    else
        printf ("\n not found\n");

}