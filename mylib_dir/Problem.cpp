#include "Problem.h"

void Problem::solve()const{
    
    Variable var {ptr_imesh};
    
    std::cout << "--- Solve problem ---" <<std::endl;

    for( float t = (*ptr_imesh).get_tmp_init(); t< (*ptr_imesh).get_tmp_fin() ; t=t+(*ptr_imesh).get_dt()){
        std::cout << "--- compute equation at time : " << t << " ---"<<std::endl;
        var.u_n = t;
        var.u_np1 = var.u_n+(*ptr_imesh).get_dt();
        eq.compute(ptr_imesh);
    }
    
    var.u_np1 = var.u_n;
}
