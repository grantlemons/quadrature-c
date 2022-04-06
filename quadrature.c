#include <stdio.h>
#include <math.h>
#include "tinyexpr.h"
#include "quadrature.h"

char exp_input[50];

void main() {
    float a, b, n;

    printf("f(x) = ");
    scanf("%s", &exp_input);
    
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
    //printf("simpson\'s rule: %f\n", simpsons_rule(a, b, n));
    if(a == -1 && b == 1) {
        printf("gaussian quadricature: %f\n", gaussian_quad(a, b, n));
    }
}

double f(double x) {
    int err;
    te_variable vars[] = {{"x", &x}}; // in order to work x must be a double
    te_expr *expr = te_compile(exp_input, vars, 2, &err);
    double output = te_eval(expr);
    te_free(expr);
    return output;
}

double left_sum(float a, float b, int sub_intervals) {
    double dx = (b-a)/sub_intervals;
    long double sum = 0; // changing to long double breaks it
    for(int i=0; i<sub_intervals; i++) {
        sum += f(a+(dx*i));
    }
    return dx*sum;
}

double right_sum(float a, float b, int sub_intervals) {
    double dx = (b-a)/sub_intervals;
    double sum = 0;
    for(int i=0; i<sub_intervals; i++) {
        sum += f(a+(dx*(i+1)));
    }
    return dx*sum;
}

double midpoint_sum(float a, float b, int sub_intervals) {
    double dx = (b-a)/sub_intervals;
    double sum = 0;
    for(int i=0; i<sub_intervals; i++) {
        sum += f(a+(dx*i)+(dx/2));
    }
    return dx*sum;
}

double trapezoidal_rule(float a, float b, int sub_intervals) {
    double dx = (b-a)/sub_intervals;
    double last_height = f(a);
    double sum = 0;
    for(int i=0; i<sub_intervals; i++) {
        double right_height = f(a+(dx*(i+1)));
        sum += (last_height+right_height)/2;
        last_height = right_height;
    }
    return dx*sum;
}

double simpsons_rule(float a, float b, int n) {
    double dx = (b-a)/n;
    long double sum = 0;
    for(int i=1; i < n/2; i++) {
        float j = a+(i*dx);
        sum += f(2*j-2)+4*f(2*j-1)+f(2*j);
    }
    return dx/3 * sum;
}
/*
double simpsons_38rule(float a, float b, int sub_intervals) {
    double dx = (b-a)/sub_intervals;
    double sum = 0;
    for(int i=0; i < n-1; i++) {
        float j = a+(i*dx);
        sum += f(j)+2;
    }
    for(int i=1; i < n/3-1; i++) {
        float j = a+(i*dx);
        sum += ;
    }
    return (3*dx)/8 * (f(a)+sum);
}
*/
double gaussian_quad(float a, float b, int n) {
    if(n > 4) n = 4;
    if(a == -1 && b == 1) {
        if(n == 2) return 1*f(-1/sqrt(3))+1*f(1/sqrt(3));
        if(n == 3) return 5/9*f(-sqrt(3/5))+8/9*f(0)+5/9*f(sqrt(3/5));
        if(n == 4) return 0.34785*f(-0.86114)+0.65215*f(-0.33998)+0.65215*f(0.33998)+0.34785*f(0.86114);
    }
    return 0;
}
