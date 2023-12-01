#include "Equation.h"


class Problem{
    
    IMeshPtr ptr_imesh;
    Equation eq;
    
    public :
    Problem(float ti,float tf,float td,float xi,float xf,float xd){
        ptr_imesh = std::make_shared<UniformMesh>( ti, tf, td, xi, xf, xd);
        eq.a = CFL*(*ptr_imesh).get_dx()/(*ptr_imesh).get_dt();
    }
    Problem(){
        ptr_imesh = std::make_shared<NonUniformMesh>();
    }
    
    
    void solve();//donnee t_i
    
};




