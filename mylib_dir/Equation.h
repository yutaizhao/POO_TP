#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <concepts>
#include <type_traits>
#include <string>
#include <map>
#include <fstream>

static const float CFL = 0.5;

class IMesh{
    public:
    virtual float get_tmp_init()const{return -1;};
    virtual float get_tmp_fin() const{return -1;};
    virtual float get_dt() const{return -1;};
    virtual float get_pos_init()const {return -1;};
    virtual float get_pos_fin()const {return -1;};
    virtual float get_dx() const{return -1;};
    int x_size()const{return (get_pos_fin()-get_pos_init())/get_dx();}
    float x_i(int i)const{return get_pos_init()+ get_dx()*i;}
    virtual ~IMesh() = default;
};

class UniformMesh : public IMesh{
    private :
    float t_ini = 0;
    float t_final = 1;
    float dt = 0.5;
    float x_min = 0;
    float x_max = 5;
    float dx = 2;
    public:
    UniformMesh() = default;
    UniformMesh(float ti,float tf,float td,float xi,float xf,float xd){
         t_ini = ti;
         t_final = tf;
         dt = td;
         x_min = xi;
         x_max = xf;
         dx = xd;
    }
    
    float get_tmp_init() const override  ;
    float get_tmp_fin() const override ;
    float get_dt() const override ;
    float get_pos_init() const override  ;
    float get_pos_fin() const override ;
    float get_dx()const override  ;
};

class NonUniformMesh : public IMesh{
    private :
    float t_ini = 0;
    float t_final = 1;
    float dt = 0.5;
    float x_min = 0;
    float x_max = 5;
    float dx = 2;
    public:
    float get_tmp_init() const override  ;
    float get_tmp_fin() const override ;
    float get_dt() const override ;
    float get_pos_init() const override  ;
    float get_pos_fin() const override ;
    float get_dx()const override  ;
};



class Variable{
    IMesh* var_ptr_imesh = nullptr;
    
    
    public :
    std::vector<float> vect; //donne les solutions avec x fixe et t varie
    Variable(IMesh* imesh){
        int n = (*imesh).x_size();
        var_ptr_imesh = imesh;
        vect.resize(n+1,-1);
        
    };
    
    float& operator[](int i){
        return vect[i];
    }
    
    std::vector<float> u_n ; //donne les solutions avec t fixe et x varie
    std::vector<float> u_np1 ; //
    std::vector<float> u_ref ;
    
    std::vector<std::string> m_name = {"Upwind","sol exacte"};
    
    void print(int t){
        //data load
        std::ofstream data("../data/Variable_u_np1_"+std::to_string(t)+".data");
        
        std::cout << m_name[0] <<";"<< m_name[1] << std::endl;
        data << m_name[0] <<";"<< m_name[1] << std::endl;
        for (int i= 0;  i<= (*var_ptr_imesh).x_size();++i) {
            std::cout << u_np1[i] << ";" << u_ref[i] << std::endl;
            data << u_np1[i] << ";" << u_ref[i] <<  std::endl;
        }
        data.close();
    }
};

//https://en.cppreference.com/w/cpp/language/constraints
//https://en.cppreference.com/w/cpp/types/is_object
//https://en.cppreference.com/w/cpp/types/is_function
//https://www.jianshu.com/p/826c6c80d089
//https://en.cppreference.com/w/cpp/compiler_support
class Equation{
    public :
    float a = -1 ; //= CFL*(*imesh).get_dx()/(*imesh).get_dt();
    void compute(IMesh* imesh, std::vector<float>& u_n, std::vector<float>& u_np1);//
    void compute_exact_solution (IMesh* imesh, Variable & v, float t);
    
    template<typename T>
    /*
    concept hasop =  std::is_function<T>::value;
    template<hasop T>
     */
    void compute_initial_condition(IMesh* imesh,Variable & v,T f); //donne U_0 = U(X_0,t_n)
    
    template<class C>
    /*
    concept hasupdate = requires(C aclass){aclass::update();};
    template<hasupdate C>
     */
    void compute_for_scheme(float a, IMesh* imesh, std::vector<float>& u_n, std::vector<float>& u_np1){
        C::update( a, imesh, u_n, u_np1);
    }
};


template<typename T>
/*
concept hasop =  std::is_function<T>::value;
template<hasop T>
 */
void Equation::compute_initial_condition(IMesh* imesh,Variable& v,T f){
    for(int i =0; i<= (*imesh).x_size();++i){
        float mu = ((*imesh).get_pos_fin() - (*imesh).get_pos_init())/2;
        float lam = 10*(*imesh).get_dx();
        float xi = (*imesh).x_i(i);
        float pi = 4*atan(1);
        v[i] = f(lam,mu,pi,xi);
    }
}


class Upwind{
    public :
    static void update(float a, IMesh* imesh, std::vector<float>& u_n, std::vector<float>& u_np1 ){
        for(int i =1; i<= (*imesh).x_size();++i){
            u_np1[i] =u_n[i] - CFL*(u_n[i] - u_n[i-1]); //CFL = a*dt/dx = 0.5
        }
        u_np1[0] =u_n[0] - CFL* (u_n[1]-0) ;
        u_n = u_np1;
    }
};

class LaxWendroff{
    public :
    static void update(float a, IMesh* imesh, std::vector<float>& u_n, std::vector<float>& u_np1 ){
        for(int i =1; i< (*imesh).x_size();++i){
            u_np1[i] =u_n[i] - a*((*imesh).get_dt()/(2*(*imesh).get_dx()))*(u_n[i+1] - u_n[i-1]) + pow(a,2)*(pow((*imesh).get_dt(),2)/(2*pow((*imesh).get_dx(),2)))*(u_n[i+1] + 2*u_n[i] - u_n[i-1]);
            
        }
        u_np1[0] =u_n[0] - a*((*imesh).get_dt()/(2*(*imesh).get_dx()))*(u_n[1] - 0) + pow(a,2)*(pow((*imesh).get_dt(),2)/(2*pow((*imesh).get_dx(),2)))*(u_n[1] + 2*u_n[0] - 0);
        u_np1[(*imesh).x_size()] =u_n[(*imesh).x_size()] - a*((*imesh).get_dt()/(2*(*imesh).get_dx()))*(0 - u_n[(*imesh).x_size()-1]) + pow(a,2)*(pow((*imesh).get_dt(),2)/(2*pow((*imesh).get_dx(),2)))*(0+ 2*u_n[(*imesh).x_size()] - u_n[(*imesh).x_size()-1]);
        u_n = u_np1;
    }
};
