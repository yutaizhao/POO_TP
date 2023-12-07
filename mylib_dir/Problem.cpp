#include "Problem.h"

void Problem::solve(){
    
    int n = (*ptr_imesh).x_size();
    
    Variable u_n {ptr_imesh, "ordre_1"};
    Variable u_np1 {ptr_imesh, "ordre_1" };
    Variable u_n_2nd_order {ptr_imesh, "ordre_2" };
    Variable u_np1_2nd_order {ptr_imesh, "ordre_2"};
    
    Variable u_ref {ptr_imesh,"u_ref"};
    Variable u_init {ptr_imesh,"u_init"};
    
    float mu = ((*ptr_imesh).get_pos_fin() - (*ptr_imesh).get_pos_init())/2;
    float sig = 10*(*ptr_imesh).get_dx();
    float pi = 4*atan(1);
    
    auto f = [sig, mu, pi](float xi){return (1/(sig*sqrt(2*pi)))*exp(-pow((xi - mu),2)/(2*pow(sig,2)));};
    
    eq.compute_initial_condition(ptr_imesh,u_init,f);
    
    eq.compute_initial_condition(ptr_imesh,u_n,f);
    eq.compute_initial_condition(ptr_imesh,u_n_2nd_order,f);
    
    std::cout << "--- Solve problem ---" <<std::endl;
    for( float t = (*ptr_imesh).get_tmp_init(); t< (*ptr_imesh).get_tmp_fin() ; t=t+(*ptr_imesh).get_dt()){
        std::cout << "--- compute equation at time : " << t << " ---"<<std::endl;
        
        u_n.print(t/(*ptr_imesh).get_dt());
        u_n_2nd_order.print(t/(*ptr_imesh).get_dt());
        
        eq.compute_exact_solution (ptr_imesh, u_ref, t);
        
        eq.compute<Upwind>(ptr_imesh, u_n, u_np1);
        eq.compute<LaxWendroff>(ptr_imesh, u_n_2nd_order, u_np1_2nd_order);
        
    }
    
    std::ofstream graphe("../data/graphe.data");
    for(int i =0; i<= n;++i){
        graphe << (*ptr_imesh).x_i(i) << " " << u_init[i] << " " << u_n[i] << " " << u_n_2nd_order[i] <<" " <<u_ref[i] <<  std::endl;
    }
    graphe.close();
}
