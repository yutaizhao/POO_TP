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
    
    IMeshPtr var_ptr_imesh;
    
    public :
    std::vector<float> vect; //donne les solutions avec x fixe et t varie
    Variable(IMeshPtr imesh){
        int n = (*imesh).x_size();
        var_ptr_imesh = imesh;
        vect.resize(n+1,-1);
    };
    
    float& operator[](int i){
        return vect[i];
    }
    
    std::vector<float> u_n ; //donne les solutions avec t fixe et x varie
    std::vector<float> u_np1 ; //
    
    std::vector<float> u_n_2nd_order;
    std::vector<float> u_np1_2nd_order;
    
    std::vector<float> u_ref ;
    
    std::map<std::string,std::function<void()>> m_name;
    
    template<typename T>
        void registerClass(const std::string& className, float a) {
            m_name[className] = [&]() { T().update(a,var_ptr_imesh,u_n,u_np1); };
        }

    void print(int t){
        //data load
            std::ofstream data("../data/Variable_u_np1_"+std::to_string(t)+".data");
            std::cout << "Upwind" <<";"<< "Solexacte" << std::endl;
            data << "Upwind" <<";"<< "Solexacte" << std::endl;
            
                for (int i= 0;  i<= (*var_ptr_imesh).x_size();++i) {
                    std::cout << u_np1[i] << ";" << u_ref[i] << std::endl;
                    data << u_np1[i] << ";" << u_ref[i] <<  std::endl;
                }
                data.close();

        }
};

class Equation{
    public :
    float a = -1 ; //= CFL*(*imesh).get_dx()/(*imesh).get_dt();
    
    void compute_exact_solution (IMeshPtr imesh, Variable & v, float t);
    
    
    template<class C>
    void compute(IMeshPtr imesh, std::vector<float>& u_n, std::vector<float>& u_np1);//
    
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
    void compute_for_scheme(float a, IMeshPtr imesh, std::vector<float>& u_n, std::vector<float>& u_np1){
        C::update( a, imesh, u_n, u_np1);
    }
};

template<class C>
void Equation::compute(IMeshPtr imesh, std::vector<float>& u_n, std::vector<float>& u_np1){
    for (float x = (*imesh).get_pos_init(); x<=(*imesh).get_pos_fin(); x=x+(*imesh).get_dx()){
        std::cout << "-- at x_i = " << x <<std::endl;
    }
    compute_for_scheme<C>(a,imesh,u_n,u_np1);
}


template<typename T>
/*
concept hasop =  std::is_function<T>::value;
template<hasop T>
 */
void Equation::compute_initial_condition(IMeshPtr imesh,Variable& v,T f){
    for(int i =0; i<= (*imesh).x_size();++i){
        float mu = ((*imesh).get_pos_fin() - (*imesh).get_pos_init())/2;
        float lam = 10*(*imesh).get_dx();
        float xi = (*imesh).x_i(i);
        float pi = 4*atan(1);
        v[i] = f(lam,mu,pi,xi);
        v.u_n[i] = v[i];
        v.u_n_2nd_order[i] = v[i];
    }
}


class Upwind{
    public :
    static void update(float a, IMeshPtr imesh, std::vector<float>& u_n, std::vector<float>& u_np1 ){
        for(int i =1; i<= (*imesh).x_size();++i){
            u_np1[i] =u_n[i] - CFL*(u_n[i] - u_n[i-1]); //CFL = a*dt/dx = 0.5
        }
        u_np1[0] =u_n[0] - CFL* (u_n[1]-0) ;
        u_n = u_np1;
    }
};

class LaxWendroff{
    public :
    static void update(float a, IMeshPtr imesh, std::vector<float>& u_n, std::vector<float>& u_np1 ){
        for(int i =1; i< (*imesh).x_size();++i){
            u_np1[i] =u_n[i] - a*((*imesh).get_dt()/(2*(*imesh).get_dx()))*(u_n[i+1] - u_n[i-1]) + pow(a,2)*(pow((*imesh).get_dt(),2)/(2*pow((*imesh).get_dx(),2)))*(u_n[i+1] + 2*u_n[i] - u_n[i-1]);
            
        }
        u_np1[0] =u_n[0] - a*((*imesh).get_dt()/(2*(*imesh).get_dx()))*(u_n[1] - 0) + pow(a,2)*(pow((*imesh).get_dt(),2)/(2*pow((*imesh).get_dx(),2)))*(u_n[1] + 2*u_n[0] - 0);
        u_np1[(*imesh).x_size()] =u_n[(*imesh).x_size()] - a*((*imesh).get_dt()/(2*(*imesh).get_dx()))*(0 - u_n[(*imesh).x_size()-1]) + pow(a,2)*(pow((*imesh).get_dt(),2)/(2*pow((*imesh).get_dx(),2)))*(0+ 2*u_n[(*imesh).x_size()] - u_n[(*imesh).x_size()-1]);
        u_n = u_np1;
    }
};
