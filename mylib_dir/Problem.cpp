#include "Problem.h"

void Problem::solve()const{
    
    std::cout << "--- Solve problem ---" <<std::endl;

    for( float i = (*ptr_imesh).get_tmp_init(); i< (*ptr_imesh).get_tmp_fin() ; i=i+(*ptr_imesh).get_dt()){
        std::cout << "--- compute equation at time : " << i << " ---"<<std::endl;
        eq.compute(ptr_imesh);
    }
}
