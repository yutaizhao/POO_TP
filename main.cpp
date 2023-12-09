#include "Problem.h"




int main(int argc, char** argv){
    
    Timer prog{};
    
    prog.start();
    
    if(argc!=8){perror("not enough args");}
    
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
            Problem p_uni{tii,tfi,dti,xii,xfi,dxi};
            
            //this is a swtich case but yea.....we all understand :)
            if(parallel == 0) {
                p_uni.solve();
            }else if(parallel == 1){
                p_uni.solve_parallel();
            }else if(parallel == 2){
                p_uni.solve_parallel_async();
            }
            
            break;
            
        }
        case TypeMaillage::NonUniform: {
            Problem p_nuni{};
            p_nuni.solve();
            break;
        }
    }
    
    prog.stop();
    
    prog.print("This program took :");
    
    return 0;
}
