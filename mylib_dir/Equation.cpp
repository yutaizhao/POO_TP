#include "Equation.h"

void Equation::compute(IMesh* imesh)const{
    int h = (*imesh).get_tmp_fin()/(*imesh).get_dt();
    for (int x = 0; x<=h; ++x){
        std::cout << "-- at x_i = " << (*imesh).get_pos_init()+x*(*imesh).get_dx() <<std::endl;
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

