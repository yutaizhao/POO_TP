#include "Equation.h"


class Problem{
    
    IMeshPtr ptr_imesh;
    Equation eq;
    
    public :
    Problem(float ti,float tf,float td,float xi,float xf,float xd){
        ptr_imesh = std::make_shared<UniformMesh>( ti, tf, td, xi, xf, xd); //version optimisee de ce qui eest demande en td1
    }
    Problem(){
        ptr_imesh = std::make_shared<NonUniformMesh>();
    }
    
    
    void solve();
    void solve_parallel();
};




