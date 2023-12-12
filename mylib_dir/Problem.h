#include "Equation.h"


class Problem{
    
    IMeshPtr ptr_imesh;
    Equation eq;
    
    public :
    
    /*
    Problem(UniformMesh* ptr_UMesh, Equation equation){
        ptr_imesh = ptr_UMesh;
        eq = equation ;
    }
     
     Problem(NonUniformMesh* ptr_NUMesh,Equation equation){
         ptr_imesh = ptr_NUMesh;
         eq = equation ;
     }
     
     ~Problem(){ delete ptr_imesh;}
     */
    
    Problem(float ti,float tf,float td,float xi,float xf,float xd){
            ptr_imesh = std::make_shared<UniformMesh>( ti, tf, td, xi, xf, xd);
    }
    
    Problem(){
            ptr_imesh = std::make_shared<NonUniformMesh>();
    }
    
    
    
    void solve();
    void solve_parallel(); // using thread BASE
    void solve_parallel_async(); //using async BONUS
};




