#include "Problem.h"




int main(int argc, char** argv){
    
    // dir for results u_n
    auto res = mkdir("../data",0777);
    
    Timer prog{};
    
    prog.start();
    
    if(argc!=9){perror("8 agrs reguired: [t_ini] [t_final] [dt] [x_min] [x_max] [dx] [Maillage Type] [Parallelisme] \n");}
    
    float tii = std::stof(argv[1]);
    float tfi = std::stof(argv[2]);
    float dti = std::stof(argv[3]);
    float xii = std::stof(argv[4]);
    float xfi = std::stof(argv[5]);
    float dxi = std::stof(argv[6]);
    char* type = argv[7];
    int parallel = std::stoi(argv[8]);
    
    enum class TypeMaillage {Uniform, NonUniform};
    std::map<std::string, TypeMaillage> dic {{"uniform",TypeMaillage::Uniform},{"non-uniform",TypeMaillage::NonUniform}};
    
    switch (dic[type]) {
        case TypeMaillage::Uniform: {
            
            /*
             UniformMesh* ptr_UMesh = new UniformMesh{tii,tfi,dti,xii,xfi,dxi};
             Equation eq;
             Problem p_uni{ptr_UMesh,eq};
             delete ptr_UMesh;
             */
            
            Problem p_uni{tii,tfi,dti,xii,xfi,dxi};
            //this could be written in swtich case but not complicating life
            if(parallel == 0) {
                p_uni.solve();
            }else if(parallel == 1){
                p_uni.solve_parallel();
            }else if(parallel == 2){
                p_uni.solve_parallel_async();
            }
            break;
        }
            /*
             This is only for BONUS, do nothing.
             Warning during compilation is due to empty NonUniformMesh methods
             */
            
        case TypeMaillage::NonUniform: {
            
            /*
             NonUniformMesh* ptr_NUMesh = new NonUniformMesh{};
             delete ptr_NUMesh;
             */
                Problem p_nuni{};
                break;
            
            }
        }
            
    prog.stop();
    prog.print("This program took :");
    
    if(res != 0){
        std::cout << "Attention : " << std::endl;
        std::cout << "-> Directory data existed..." << std::endl;
        std::cout << "-> existed data was not over-written..." << std::endl;
        std::cout << "-> delete directory to save new data..." << std::endl;
    }
    
    return 0;
}
