#include "gtest/gtest.h"
#include "Problem.h"


TEST(UnitaryTest,MeshTest){
    UniformMesh um{};
    IMesh &mesh = um;
    mesh.get_tmp_init();
}

TEST(UnitaryTest,ProblemTest){
    
    UniformMesh unimesh{1,5,0.5,1,10,1};
    Problem p_uni{unimesh};
    p_uni.solve();
    
}

TEST(UnitaryTest,VariableTest){
    UniformMesh unimesh{1,5,0.5,1,10,1};
    Problem p_uni{unimesh};
    Variable var{&unimesh};
}

TEST(MainFunctionTest,EquationTest){
}

