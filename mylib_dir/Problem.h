#include "Equation.h"


class Problem{
    
    IMeshPtr ptr_imesh;
    Equation eq;
    
    public :
    Problem(UniformMesh* ptr_UMesh, Equation equation){
        ptr_imesh = ptr_UMesh;
        eq = equation ;
    }
    
    Problem(NonUniformMesh* ptr_NUMesh,Equation equation){
        ptr_imesh = ptr_NUMesh;
        eq = equation ;
    }
    
    ~Problem(){delete ptr_imesh; }
    
    
    void solve();
    void solve_parallel(); // using thread BASE
    void solve_parallel_async(); //using async BONUS
};




