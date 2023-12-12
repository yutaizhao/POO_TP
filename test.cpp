#include "gtest/gtest.h"
#include "Problem.h"


TEST(UnitaryTest,MeshTest){
    
    UniformMesh um{};
    IMesh* mesh = &um;
    (*mesh).get_tmp_init();
    
}

TEST(UnitaryTest,ProblemTest){
    
    Equation eq;
    UniformMesh* ptr_UMesh = new UniformMesh{0,2,0.1,0,10,0.1};
    Problem p_uni{ptr_UMesh,eq};
    p_uni.solve();
    
    NonUniformMesh* ptr_NUMesh = new NonUniformMesh{};
    Problem p_nuni{ptr_NUMesh,eq};
    
    //BONUS
    UniformMesh* ptr_UMesh_null =nullptr;
    Problem p_uni_null{ptr_UMesh_null,eq};
    p_uni_null.solve();
    
}

TEST(UnitaryTest,EquationTest){
    
    /*
     ici, on ne peut pas tester le cas où Equation::compute est appelée avec un IMesh*=nullptr,
     comme compute a ete modifie aprees le tp2, allant prendre Variable comme args
     mais Variable est aussi construit avec IMesh
     Sinon on doit aussi faire une gestion d'erreur pour Variable
     */
    
    UniformMesh* ptr_UMesh = new UniformMesh{0,2,0.1,0,10,0.1};
    IMesh* imesh = ptr_UMesh;
    Variable u_n{imesh, "hi"};
    Variable u_np1{imesh, "hi"};
    Equation eq;
    Variable var{imesh,"hi"};
    float lam = 1;
    float mu = 1;
    float pi = 3.14;
    auto f = [lam,mu,pi](float xi){return (1/(lam*sqrt(2*pi)))*exp(-pow((xi - mu),2)/(2*pow(lam,2)));};
    eq.compute(imesh,u_n, u_np1);
    eq.compute_initial_condition(imesh,var,f);
    eq.compute_for_scheme<Upwind>(imesh,u_n,u_np1);
    eq.compute_for_scheme<LaxWendroff>(imesh,u_n,u_np1);
    
}

