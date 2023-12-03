#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <concepts>
#include <type_traits>
#include <string>
#include <map>
#include <fstream>
#include <execution>

class IMesh;
using IMeshPtr  = std::shared_ptr<IMesh>;
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
    
    std::string m_name ;
    IMeshPtr var_ptr_imesh;
    std::vector<float> vect; //donne les solutions avec t fixe et x[i] varie
    
    public :
   
    Variable(IMeshPtr imesh, std::string name){
        int n = (*imesh).x_size();
        var_ptr_imesh = imesh;
        vect.resize(n+1,-1);
        m_name = name;
    };
    
    float& operator[](int i){
        return vect[i];
    }
    
    void print(int t){
        //data load
            std::ofstream data("../data/Variable_"+m_name+"_"+std::to_string(t)+".data");
            std::cout << m_name << std::endl;
            data << m_name << std::endl;
            for (int i= 0;  i<= (*var_ptr_imesh).x_size();++i) {
                std::cout << vect[i] << std::endl;
                data << vect[i] <<  std::endl;
            }
            data.close();
        }
};

class Equation{
    public :
    float a = -1 ; //= CFL*(*imesh).get_dx()/(*imesh).get_dt();
    
    void compute_exact_solution (IMeshPtr imesh, Variable & u_ref, float t);
    
    
    template<class C>
    void compute(IMeshPtr imesh, Variable& u_n, Variable& u_np1);//
    
    template<typename T>
    /*
    concept hasop =  std::is_function<T>::value;
    template<hasop T>
     */
    void compute_initial_condition(IMeshPtr imesh,Variable & v,T f); //donne U_0 = U(X_0,t_n)
    
    template<class C>
    /*
    concept hasupdate = requires(C aclass){aclass::update();};
    template<hasupdate C>
     */
    void compute_for_scheme(IMeshPtr imesh, Variable& u_n, Variable& u_np1){
        a = CFL*(*imesh).get_dx()/(*imesh).get_dt();
        C::update( a, imesh, u_n, u_np1);
    }
};

template<class C>
void Equation::compute(IMeshPtr imesh, Variable& u_n, Variable& u_np1){
    for (float x = (*imesh).get_pos_init(); x<=(*imesh).get_pos_fin(); x=x+(*imesh).get_dx()){
        std::cout << "-- at x_i = " << x <<std::endl;
    }
    compute_for_scheme<C>(imesh,u_n,u_np1);
    u_n = u_np1;
}


template<typename T>
/*
concept hasop =  std::is_function<T>::value;
template<hasop T>
 */
void Equation::compute_initial_condition(IMeshPtr imesh,Variable& v,T f){
    float mu = ((*imesh).get_pos_fin() - (*imesh).get_pos_init())/2;
    float sig = 10*(*imesh).get_dx();
    float pi = 4*atan(1);
    
    for(int i =0; i<= (*imesh).x_size();++i){
        float xi = (*imesh).x_i(i);
        v[i] = f(sig,mu,pi,xi);
    }
}


class Upwind{
    public :
    static void update(float a, IMeshPtr imesh, Variable& u_n, Variable& u_np1 ){
        for(int i =1; i<= (*imesh).x_size();++i){
            u_np1[i] =u_n[i] - CFL*(u_n[i] - u_n[i-1]); //CFL = a*dt/dx = 0.5
        }
        u_np1[0] =u_n[0] - CFL* (u_n[1]-0) ;
    }
};

class LaxWendroff{
    public :
    static void update(float a, IMeshPtr imesh, Variable& u_n, Variable& u_np1 ){
        for(int i =1; i< (*imesh).x_size();++i){
            u_np1[i] =u_n[i] - a*((*imesh).get_dt()/(2*(*imesh).get_dx()))*(u_n[i+1] - u_n[i-1]) + pow(a,2)*(pow((*imesh).get_dt(),2)/(2*pow((*imesh).get_dx(),2)))*(u_n[i+1] - 2*u_n[i] + u_n[i-1]);
            
        }
        u_np1[0] =u_n[0] - a*((*imesh).get_dt()/(2*(*imesh).get_dx()))*(u_n[1] - 0) + pow(a,2)*(pow((*imesh).get_dt(),2)/(2*pow((*imesh).get_dx(),2)))*(u_n[1] - 2*u_n[0] + 0);
        u_np1[(*imesh).x_size()] =u_n[(*imesh).x_size()] - a*((*imesh).get_dt()/(2*(*imesh).get_dx()))*(0 - u_n[(*imesh).x_size()-1]) + pow(a,2)*(pow((*imesh).get_dt(),2)/(2*pow((*imesh).get_dx(),2)))*(0 - 2*u_n[(*imesh).x_size()] + u_n[(*imesh).x_size()-1]);
    }
};
