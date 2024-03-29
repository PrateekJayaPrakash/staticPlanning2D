#include <iostream>
#include <math.h>
#include </usr/local/include/nlopt.hpp> // Needs to point to where nlopt is installed

typedef struct {
    double a, b;
} my_constraint_data;

int count = 0;

double myvconstraint(const std::vector<double> &x, std::vector<double> &grad, void *data)
{
    my_constraint_data *d = reinterpret_cast<my_constraint_data*>(data);
    double a = d->a, b = d->b;
    if (!grad.empty()) {
        grad[0] = 3 * a * (a*x[0] + b) * (a*x[0] + b);
        grad[1] = -1.0;
    }
    return ((a*x[0] + b) * (a*x[0] + b) * (a*x[0] + b) - x[1]);
}


double myvfunc(const std::vector<double> &x, std::vector<double> &grad, void *my_func_data)
{
    ++count;
    if (!grad.empty()) {
        grad[0] = 0.0;
        grad[1] = 0.5 / sqrt(x[1]);
    }
    return sqrt(x[1]);
}


int main()
{
    nlopt::opt opt(nlopt::LD_MMA, 2);
    std::vector<double> lb(2);
    lb[0] = -HUGE_VAL; lb[1] = 0;
    opt.set_lower_bounds(lb);

    opt.set_min_objective(myvfunc, NULL);

    my_constraint_data data[2] = { {2,0}, {-1,1} };
    opt.add_inequality_constraint(myvconstraint, &data[0], 1e-8);
    opt.add_inequality_constraint(myvconstraint, &data[1], 1e-8);

    opt.set_xtol_rel(1e-4);
    std::vector<double> x(2);
    //x[0] = 1.234; x[1] = 5.678;
    x[0] = 0; x[1] = 5.5;
    double minf;

    try{
    nlopt::result result = opt.optimize(x, minf);
    std::cout<< "iteration count: " << count<< std::endl;
    std::cout << "found minimum at f(" << x[0] << "," << x[1] << ") = " << minf << std::endl;
    }
    catch(std::exception &e) {
        std::cout << "nlopt failed: " << e.what() << std::endl;
    }

    return 0;
}
