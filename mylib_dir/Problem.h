#include "Equation.h"


class Problem{
    
    
    IMesh* ptr_imesh = nullptr;
    Equation eq;
    
    public :
    Problem(UniformMesh & um_ptr){
        ptr_imesh = &um_ptr;
    }
    Problem(NonUniformMesh & num_ptr){
        ptr_imesh = &num_ptr;
    }
    
    
    void solve()const;
};




