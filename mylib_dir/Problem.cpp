#include "Problem.h"

void Problem::solve(){
    
    int n = (*ptr_imesh).x_size();
    
    Variable var {ptr_imesh};
    var.u_n.reserve(n);
    var.u_np1.reserve(n);

    fill(var.u_np1.begin(), var.u_np1.end(), -1);
    eq.compute_initial_condition(ptr_imesh,var);
    
    for(int i =0; i<= n;++i){
        var.u_n[i] = var[i];
        std::cout << "u_n[i] = " << var.u_n[i] << " ---"<<std::endl;
    }
    
    
    std::cout << "--- Solve problem ---" <<std::endl;
    for( float t = (*ptr_imesh).get_tmp_init(); t< (*ptr_imesh).get_tmp_fin() ; t=t+(*ptr_imesh).get_dt()){
        std::cout << "--- compute equation at time : " << t << " ---"<<std::endl;
        eq.compute(ptr_imesh, var.u_n, var.u_np1);
        var.u_np1.reserve(n);
        fill(var.u_np1.begin(), var.u_np1.end(), -1);
    }
    
}
