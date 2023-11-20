#include "Equation.h"

void Equation::compute(IMesh* imesh, std::vector<float>& u_n, std::vector<float>& u_np1){
    int cnt = 0;
    for (int x = (*imesh).get_pos_init(); x<=(*imesh).get_pos_fin(); x=x+(*imesh).get_dx()){
        std::cout << "-- at x_i = " << x << "; U_i = " << u_n[cnt] <<std::endl;
        cnt = cnt +1;
    }
    compute_for_scheme<Upwind>(a,imesh,u_n,u_np1);

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

