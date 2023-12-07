#include "Equation.h"


 void Equation::compute_exact_solution (IMeshPtr imesh, Variable & u_ref, float t){
     //NOT required to use lambda function

     float mu = ((*imesh).get_pos_fin() - (*imesh).get_pos_init())/2;
     float sig = 10*(*imesh).get_dx();
     float pi = 4*atan(1);
     
     int i = 0 ;
     std::for_each(u_ref.begin(), u_ref.end(), [&i,this,t,imesh,mu,sig,pi](auto& vi) {
         float x = (*imesh).x_i(i)-a*t;
         vi = (1/(sig*sqrt(2*pi)))*exp(-pow((x - mu),2)/(2*pow(sig,2)));
         ++i;}
                   );
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

