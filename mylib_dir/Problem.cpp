#include "Problem.h"

/*
 Due to performance tests
 code for graphe plot are commented by 
 */

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
    eq.a = CFL*(*ptr_imesh).get_dx()/(*ptr_imesh).get_dt();
    
    Timer time_loop{};
    time_loop.start();
    std::cout << "--- Solve problem ---" <<std::endl;
    for( float t = (*ptr_imesh).get_tmp_init(); t< (*ptr_imesh).get_tmp_fin() ; t=t+(*ptr_imesh).get_dt()){
        std::cout << "--- compute equation at time : " << t << " ---"<<std::endl;
        
        u_n.print(t/(*ptr_imesh).get_dt());
        u_n_2nd_order.print(t/(*ptr_imesh).get_dt());
        
        eq.compute_exact_solution (ptr_imesh, u_ref, t);
        
        eq.compute_for_scheme<Upwind>(ptr_imesh, u_n, u_np1);
        // you can also use eq.compute(ptr_imesh, u_n, u_np1);
        u_n = u_np1;
        eq.compute_for_scheme<LaxWendroff>(ptr_imesh, u_n_2nd_order, u_np1_2nd_order);
        u_n_2nd_order = u_np1_2nd_order;
        
    }
    time_loop.stop();
    time_loop.print("The time-looping took :");
    
    
    std::ofstream graphe("../data/graphe.data");
    
    for(int i =0; i<= n;++i){
        graphe << (*ptr_imesh).x_i(i) << " " << u_init[i] << " " << u_n[i] << " " << u_n_2nd_order[i] <<" " <<u_ref[i] <<  std::endl;
    }
    graphe.close();
     
    
    
    
}



void Problem::solve_parallel(){
    
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
    eq.a = CFL*(*ptr_imesh).get_dx()/(*ptr_imesh).get_dt();
    
    Timer time_loop{};
    time_loop.start();
    
    
    
    std::thread first_thread([&u_ref,this](){
        std::cout << "--- Solve problem ---" <<std::endl;
        for( float t = (*ptr_imesh).get_tmp_init(); t< (*ptr_imesh).get_tmp_fin() ; t=t+(*ptr_imesh).get_dt()){
            std::cout << "--- compute equation at time : " << t << " ---"<<std::endl;
            
            eq.compute_exact_solution (ptr_imesh, u_ref, t);
            
        }
    });
    std::thread second_thread([&u_n,&u_np1,this](){
        std::cout << "--- Solve problem ---" <<std::endl;
        for( float t = (*ptr_imesh).get_tmp_init(); t< (*ptr_imesh).get_tmp_fin() ; t=t+(*ptr_imesh).get_dt()){
            std::cout << "--- compute equation at time : " << t << " ---"<<std::endl;
            
            u_n.print(t/(*ptr_imesh).get_dt());
            eq.compute_for_scheme<Upwind>(ptr_imesh, u_n, u_np1);
            // you can also use eq.compute(ptr_imesh, u_n, u_np1);
            u_n = u_np1;
            
        }
    });
    std::thread third_thread([&u_n_2nd_order,&u_np1_2nd_order,this](){
        std::cout << "--- Solve problem ---" <<std::endl;
        for( float t = (*ptr_imesh).get_tmp_init(); t< (*ptr_imesh).get_tmp_fin() ; t=t+(*ptr_imesh).get_dt()){
             std::cout << "--- compute equation at time : " << t << " ---"<<std::endl;
            
            u_n_2nd_order.print(t/(*ptr_imesh).get_dt());
            eq.compute_for_scheme<LaxWendroff>(ptr_imesh, u_n_2nd_order, u_np1_2nd_order);
            u_n_2nd_order = u_np1_2nd_order;
            
        }
    });
    
    
    
    
    first_thread.join();
    second_thread.join();
    third_thread.join();
    
    time_loop.stop();
    time_loop.print("The time-looping took :");
    
    
     std::ofstream graphe("../data/graphe.data");
     for(int i =0; i<= n;++i){
     graphe << (*ptr_imesh).x_i(i) << " " << u_init[i] << " " << u_n[i] << " " << u_n_2nd_order[i] <<" " <<u_ref[i] <<  std::endl;
     }
     graphe.close();
     
    
    
}

void Problem::solve_parallel_async(){
    
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
    eq.a = CFL*(*ptr_imesh).get_dx()/(*ptr_imesh).get_dt();
    
    Timer time_loop{};
    time_loop.start();
    
    
    /*
     std::launch::async : to run in parallel
     std::launch::deferred : to run in seq
     */
    std::future first_task = std::async(std::launch::async,[&u_ref,this](){
        std::cout << "--- Solve problem ---" <<std::endl;
        for( float t = (*ptr_imesh).get_tmp_init(); t< (*ptr_imesh).get_tmp_fin() ; t=t+(*ptr_imesh).get_dt()){
            std::cout << "--- compute equation at time : " << t << " ---"<<std::endl;
            
            eq.compute_exact_solution (ptr_imesh, u_ref, t);
            
        }
    });
    std::future second_task = std::async(std::launch::async,[&u_n,&u_np1,this](){
        std::cout << "--- Solve problem ---" <<std::endl;
        for( float t = (*ptr_imesh).get_tmp_init(); t< (*ptr_imesh).get_tmp_fin() ; t=t+(*ptr_imesh).get_dt()){
            std::cout << "--- compute equation at time : " << t << " ---"<<std::endl;
            
            u_n.print(t/(*ptr_imesh).get_dt());
            eq.compute_for_scheme<Upwind>(ptr_imesh, u_n, u_np1); 
            // you can also use eq.compute(ptr_imesh, u_n, u_np1);
            u_n = u_np1;
            
        }
    });
    std::future third_task = std::async(std::launch::async,[&u_n_2nd_order,&u_np1_2nd_order,this](){
        std::cout << "--- Solve problem ---" <<std::endl;
        for( float t = (*ptr_imesh).get_tmp_init(); t< (*ptr_imesh).get_tmp_fin() ; t=t+(*ptr_imesh).get_dt()){
            std::cout << "--- compute equation at time : " << t << " ---"<<std::endl;
            
            u_n_2nd_order.print(t/(*ptr_imesh).get_dt());
            eq.compute_for_scheme<LaxWendroff>(ptr_imesh, u_n_2nd_order, u_np1_2nd_order);
            u_n_2nd_order = u_np1_2nd_order;
            
        }
    });
    
    first_task.wait();
    second_task.wait();
    third_task.wait();
    
    time_loop.stop();
    time_loop.print("The time-looping took :");
    
    
     std::ofstream graphe("../data/graphe.data");
     for(int i =0; i<= n;++i){
     graphe << (*ptr_imesh).x_i(i) << " " << u_init[i] << " " << u_n[i] << " " << u_n_2nd_order[i] <<" " <<u_ref[i] <<  std::endl;
     }
     graphe.close();
     
    
    
}
