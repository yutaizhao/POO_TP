#include "Problem.h"

void Problem::solve(){
    
    int n = (*ptr_imesh).x_size();
    Variable var {ptr_imesh};
    var.u_n.reserve(n+1);
    var.u_np1.resize(n+1,-1);

    auto f = [](float lam, float mu, float pi, float xi){return (1/(lam*sqrt(2*pi)))*exp(-pow((xi - mu),2)/(2*pow(lam,2)));};

    eq.compute_initial_condition(ptr_imesh,var,f);
    
    for(int i =0; i<= n;++i){
        var.u_n.push_back(var[i]);
    }
    
    
    std::cout << "--- Solve problem ---" <<std::endl;
    for( float t = (*ptr_imesh).get_tmp_init(); t< (*ptr_imesh).get_tmp_fin() ; t=t+(*ptr_imesh).get_dt()){
        std::cout << "--- compute equation at time : " << t << " ---"<<std::endl;
        eq.compute_exact_solution (ptr_imesh, var, t);
        eq.compute(ptr_imesh, var.u_n, var.u_np1);
        std::cout << "U_ref" << std::endl;
        var.print(var.u_ref);
        std::cout << "U_np1" << std::endl;
        var.print(var.u_np1);
    }
}
