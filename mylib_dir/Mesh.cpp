#include "Mesh.h"

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

