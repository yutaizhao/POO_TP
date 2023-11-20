#include "Equation.h"

void Equation::compute(IMesh* imesh, std::vector<float> & u_n, std::vector<float> & u_np1){
    float CFL = 0.5;
    int cnt = 1; // car cnt=0 est initialise, u_n[0]=vecteur[0]
    
    for (int x = (*imesh).get_pos_init(); x<=(*imesh).get_pos_fin(); x=x+(*imesh).get_dx()){
        std::cout << "-- at x_i = " << x << "; U_i = " << u_n[cnt-1] <<std::endl;
        u_np1[cnt] =u_n[cnt] - CFL*(u_n[cnt] - u_n[cnt-1]);
        cnt = cnt+1;
    }
    u_np1[0] =u_n[0] - CFL* u_n[1] ;
    u_n = std::move(u_np1);
}

void Equation::compute_initial_condition(IMesh* imesh,Variable & v){
    for(int i =0; i<= (*imesh).x_size();++i){
        float mu = ((*imesh).get_pos_fin() - (*imesh).get_pos_init())/2;
        float lam = 10*(*imesh).get_dx();
        float xi = (*imesh).x_i(i);
        float pi = 4*atan(1);
        v[i] = (1/(lam*sqrt(2*pi)))*exp(-pow((xi - mu),2)/(2*pow(lam,2)));
    }
}

float UniformMesh::get_tmp_init  ()const{
    return t_ini;
}
float UniformMesh::get_tmp_fin ()const{
    return t_final;
}
float  UniformMesh::get_dt ()const{
    return dt;
}
float  UniformMesh::get_pos_init ()const{
    return x_min;
}
float  UniformMesh::get_pos_fin ()const{
    return x_max;
}
float  UniformMesh::get_dx ()const{
    return dx;
}

float NonUniformMesh::get_tmp_init  ()const{
    return t_ini;
}
float NonUniformMesh::get_tmp_fin ()const{
    return t_final;
}
float  NonUniformMesh::get_dt ()const{
    return dt;
}
float  NonUniformMesh::get_pos_init ()const{
    return x_min;
}
float  NonUniformMesh::get_pos_fin ()const{
    return x_max;
}
float  NonUniformMesh::get_dx ()const{
    return dx;
}

