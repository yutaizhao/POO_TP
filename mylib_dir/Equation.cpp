#include "Equation.h"

void Equation::compute(IMeshPtr imesh, std::vector<float>& u_n, std::vector<float>& u_np1){
    for (float x = (*imesh).get_pos_init(); x<=(*imesh).get_pos_fin(); x=x+(*imesh).get_dx()){
        std::cout << "-- at x_i = " << x <<std::endl;
    }
    compute_for_scheme<Upwind>(a,imesh,u_n,u_np1);
}

void Equation::compute_exact_solution (IMeshPtr imesh, Variable & v, float t){
    int n = (*imesh).x_size();
    v.u_ref.resize(n+1,-1);
    for(int i =0; i<= n;++i){
        float mu = ((*imesh).get_pos_fin() - (*imesh).get_pos_init())/2;
        float lam = 10*(*imesh).get_dx();
        float pi = 4*atan(1);
        float x = (*imesh).x_i(i)-a*t;
        v.u_ref[i] = (1/(lam*sqrt(2*pi)))*exp(-pow((x - mu),2)/(2*pow(lam,2)));
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

