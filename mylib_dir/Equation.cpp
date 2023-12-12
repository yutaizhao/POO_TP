#include "Equation.h"

//this function has been modified during the last version
void Equation::compute(IMeshPtr imesh, Variable & u_n, Variable & u_np1){
    float CFL = 0.5;
    int cnt = 1;
    
    /*
     cuz for u_np1[0] =u_n[0] - CFL* (u_n[0]-u_np[-1]) ;
     index = cnt = -1 : dangerous
     */
    
    for (float x = (*imesh).get_pos_init(); x<=(*imesh).get_pos_fin(); x=x+(*imesh).get_dx()){//error : int x
        std::cout << "-- at x_i = " << x <<std::endl;
        u_np1[cnt] =u_n[cnt] - CFL*(u_n[cnt] - u_n[cnt-1]);
        cnt = cnt+1;
    }
    u_np1[0] =u_n[0] - CFL* u_n[0] ;
    //u_n = u_np1 is written in Problem::solve()
}


void Equation::compute_exact_solution (IMeshPtr imesh, Variable & u_ref, float t){
    //NOT required to use lambda function in tp

    //std::execution::par, doesnt work for Apple clang
    float mu = ((*imesh).get_pos_fin() - (*imesh).get_pos_init())/2;
    float sig = 10*(*imesh).get_dx();
    float pi = 4*atan(1);
    
    int i = 0 ;
    std::for_each(u_ref.begin(), u_ref.end(), [&i,this,t,imesh,mu,sig,pi](auto& vi) {
        float x = (*imesh).x_i(i)-a*t;
        vi = (1/(sig*sqrt(2*pi)))*exp(-pow((x - mu),2)/(2*pow(sig,2)));
        ++i;});
}


void Variable::print(int t){
    
    //std::execution::par, doesnt work for Apple clang
    
    std::ofstream data("../data/Variable_"+m_name+"_"+std::to_string(t)+".data");
    std::cout << m_name << std::endl;
    data << m_name << std::endl;
    
    std::for_each(this->begin(),this->end(),[&data](auto vi){
        std::cout << vi << std::endl;
        data << vi <<  std::endl;
    });
    data.close();
}



