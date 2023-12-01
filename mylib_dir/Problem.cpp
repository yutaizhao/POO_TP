#include "Problem.h"

void Problem::solve(){
    
    int n = (*ptr_imesh).x_size();
    float a = eq.a;
    
    Variable var {ptr_imesh};
    
    var.registerClass<Upwind>("Upwind",a);
    var.registerClass<LaxWendroff>("LaxWendroff",a);
    
    
    var.u_n.resize(n+1,-1); //or reserve -> append
    var.u_np1.resize(n+1,-1);
    
    var.u_n_2nd_order.resize(n+1,-1);
    var.u_np1_2nd_order.resize(n+1,-1);

    auto f = [](float lam, float mu, float pi, float xi){return (1/(lam*sqrt(2*pi)))*exp(-pow((xi - mu),2)/(2*pow(lam,2)));};

    eq.compute_initial_condition(ptr_imesh,var,f);
    
    std::cout << "--- Solve problem ---" <<std::endl;
    for( float t = (*ptr_imesh).get_tmp_init(); t< (*ptr_imesh).get_tmp_fin() ; t=t+(*ptr_imesh).get_dt()){
        std::cout << "--- compute equation at time : " << t << " ---"<<std::endl;
        eq.compute_exact_solution (ptr_imesh, var, t);
        eq.compute<Upwind>(ptr_imesh, var.u_n, var.u_np1);
        eq.compute<LaxWendroff>(ptr_imesh, var.u_n_2nd_order, var.u_np1_2nd_order);
        var.print(t/(*ptr_imesh).get_dt());
    }
    
    std::ofstream graphe("../data/graphe.data");
    for(int i =0; i<= n;++i){
        graphe << (*ptr_imesh).x_i(i) << " " << var[i] << " " << var.u_n[i] <<" " <<var.u_ref[i] <<  std::endl;
    }
    graphe.close();
}
