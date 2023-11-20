#include "Equation.h"


class Problem{
    
    
    IMesh* ptr_imesh = nullptr;
    Equation eq;
    
    public :
    Problem(UniformMesh & um_ptr){
        ptr_imesh = &um_ptr;
        eq.a = CFL*(*ptr_imesh).get_dx()/(*ptr_imesh).get_dt();
    }
    Problem(NonUniformMesh & num_ptr){
        ptr_imesh = &num_ptr;
    }
    
    
    void solve();//donnee t_i
    
};




