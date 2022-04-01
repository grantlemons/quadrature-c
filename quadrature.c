#include <stdio.h>
#include <math.h>
//#include "tinyexpr.h"

double f(float x);
double left_sum(float a, float b, int sub_intervals);
double right_sum(float a, float b, int sub_intervals);
double midpoint_sum(float a, float b, int sub_intervals);
double trapezoidal_rule(float a, float b, int sub_intervals);
double simpsons_rule(float a, float b, int sub_intervals);
double simpsons_38rule(float a, float b, int sub_intervals);
double booles_rule(float a, float b, int sub_intervals);
double gaussian_quad(float a, float b, int sub_intervals);

//char exp_input[50];

void main() {
    float a, b, n;

    //printf("f(x) = ");
    //scanf("%s", &exp_input);
    printf("left bound: ");
    scanf("%f", &a);
    printf("right bound: ");
    scanf("%f", &b);
    printf("sub-intervals: ");
    scanf("%f", &n);

    printf("left sum: %f\n", left_sum(a, b, n));
    printf("right sum: %f\n", right_sum(a, b, n));
    printf("midpoint sum: %f\n", midpoint_sum(a, b, n));
    printf("trapezoidal sum: %f\n", trapezoidal_rule(a, b, n));
}

double f(float x) {
    /*
    int err;
    te_variable vars[] = {{"x", &x}};
    te_expr *expr = te_compile(exp_input, vars, 2, &err);
    return te_eval(expr);
    */
    return 0.5*pow(x, 3) + 2*pow(x, 2);
}

double left_sum(float a, float b, int sub_intervals) {
    float dx = (b-a)/sub_intervals;
    float sum;
    for(int i=0; i<sub_intervals; i++) {
        sum += f(a+(dx*i));
    }
    return dx*sum;
}

double right_sum(float a, float b, int sub_intervals) {
    float dx = (b-a)/sub_intervals;
    float sum;
    for(int i=0; i<sub_intervals; i++) {
        sum += f(a+(dx*(i+1)));
    }
    return dx*sum;
}

double midpoint_sum(float a, float b, int sub_intervals) {
    float dx = (b-a)/sub_intervals;
    float sum;
    for(int i=0; i<sub_intervals; i++) {
        sum += f(a+(dx*i)+(dx/2));
    }
    return dx*sum;
}

double trapezoidal_rule(float a, float b, int sub_intervals) {
    float dx = (b-a)/sub_intervals;
    float last_height = f(a);
    double sum;
    for(int i=0; i<sub_intervals; i++) {
        float right_height = f(a+(dx*(i+1)));
        sum += (last_height+right_height)/2;
        last_height = right_height;
    }
    return dx*sum;
}