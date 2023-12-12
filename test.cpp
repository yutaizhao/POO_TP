#include "gtest/gtest.h"
#include "Problem.h"


TEST(UnitaryTest,MeshTest){
    UniformMesh um{};
    IMesh &mesh = um;
    mesh.get_tmp_init();
}

TEST(UnitaryTest,ProblemTest){
    
    UniformMesh unimesh{0,2,0.1,0,10,0.1};
    Problem p_uni{0,2,0.1,0,10,0.1};
    p_uni.solve();
}

TEST(UnitaryTest,EquationTest){
    std::shared_ptr<UniformMesh> unimesh = std::make_shared<UniformMesh>(0,2,0.1,0,10,0.1);
    std::shared_ptr<IMesh> imesh = unimesh;
    Variable u_n{unimesh, "hi"};
    Variable u_np1{unimesh, "hi"};
    Equation eq;
    Variable var{unimesh,"hi"};
    float lam = 1;
    float mu = 1;
    float pi = 3.14;
    auto f = [lam,mu,pi](float xi){return (1/(lam*sqrt(2*pi)))*exp(-pow((xi - mu),2)/(2*pow(lam,2)));};
    eq.compute(imesh,u_n, u_np1);
    eq.compute_initial_condition(imesh,var,f);
    eq.compute_for_scheme<Upwind>(imesh,u_n,u_np1);
    eq.compute_for_scheme<LaxWendroff>(imesh,u_n,u_np1);
    
}

TEST(UnitaryTest,VariableTest){
    std::shared_ptr<UniformMesh> unimesh = std::make_shared<UniformMesh>(0,2,0.1,0,10,0.1);
    Problem p_uni{0,2,0.1,0,10,0.1};
    Variable var{unimesh, "hi"};
}


