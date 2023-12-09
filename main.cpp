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
    
    /*
     Pour créer notre Problem dans le programme principal, 
     nous lui passerons à la construction une instance de la classe équation et
     un pointeur de UniformMesh qu'il stockera dans son pointeur de IMesh.
     Il sera responsable de la mémoire de ce pointeur, ce sera donc à lui d'appeler le delete.
     Vous veillerez à ce que le pointeur ne puisse pas être nul,
     en bloquant les constructions ou affectations par copie.
     
     I will use raw pointer for UniformMesh as demanded in Tp2 in last versions
     But in previous ones i used smart pointer
     */
    
    switch (dic[type]) {
        case TypeMaillage::Uniform: {
            
            UniformMesh* ptr_UMesh = new UniformMesh{tii,tfi,dti,xii,xfi,dxi};
            Equation eq;
            Problem p_uni{ptr_UMesh,eq};
            
            //this par could be written in swtich case but yea..... complicating life
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
            /*
             FATAL : This is only for BONUS do not run it !!!
             Warning during compilation is due to empty NonUniformMesh methods 
             */
            
            NonUniformMesh* ptr_NUMesh = new NonUniformMesh{};
            Equation eq;
            Problem p_nuni{ptr_NUMesh,eq};
            p_nuni.solve();
            break;
        }
    }
    
    prog.stop();
    
    prog.print("This program took :");
    
    return 0;
}
