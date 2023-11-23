#include "gtest/gtest.h"
#include "Problem.h"


TEST(UnitaryTest,MeshTest){
    UniformMesh um{};
    IMesh &mesh = um;
    mesh.get_tmp_init();
}

TEST(UnitaryTest,ProblemTest){
    
    UniformMesh unimesh{0,2,0.1,0,10,0.1};
    Problem p_uni{&unimesh};
    p_uni.solve();
}

TEST(UnitaryTest,EquationTest){
    UniformMesh unimesh{0,2,0.1,0,10,0.1};
    IMesh* imesh = &unimesh;
    std::vector<float> u_n = {0,0,0,0,0};
    std::vector<float> u_np1 = {0,0,0,0,0};
    Equation eq;
    Variable var{&unimesh};
    auto f = [](float lam, float mu, float pi, float xi){return (1/(lam*sqrt(2*pi)))*exp(-pow((xi - mu),2)/(2*pow(lam,2)));};
    eq.compute(imesh,u_n, u_np1);
    eq.compute_initial_condition(imesh,var,f);
    eq.compute_for_scheme<Upwind>(0.5,imesh,u_n,u_np1);
    eq.compute_for_scheme<LaxWendroff>(0.5,imesh,u_n,u_np1);
    
}

TEST(UnitaryTest,VariableTest){
    UniformMesh unimesh{0,2,0.1,0,10,0.1};
    Problem p_uni{&unimesh};
    Variable var{&unimesh};
}


