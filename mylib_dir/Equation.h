#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <concepts>
#include <type_traits>
#include <string>
#include <map>
#include <fstream>
#include <numeric>
#include <chrono>
#include <ratio>
#include <thread>
#include <execution>
#include <future>

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
    
    auto begin(){
        return vect.begin();
    }
    
    auto end(){
        return vect.end();
    }
    
    void print(int t);
    
};

class Equation{
    public :
    float a = -1 ; //= CFL*(*imesh).get_dx()/(*imesh).get_dt();
    
    void compute_exact_solution (IMeshPtr imesh, Variable & u_ref, float t);
    
    
    void compute(IMeshPtr imesh, Variable& u_n, Variable& u_np1);//
    
    template<typename T>
    void compute_initial_condition(IMeshPtr imesh,Variable & v,T f); //U_0 = U(X_0,t_n)
    
    template<typename C>
    void compute_for_scheme(IMeshPtr imesh, Variable& u_n, Variable& u_np1);
};


template<typename T>
/*
 doesnt work for Apple clang:
 concept hasop =  std::is_function<T>::value;
 template<hasop T>
 */
void Equation::compute_initial_condition(IMeshPtr imesh,Variable& v,T f){
     
    int i = 0 ;
    std::for_each(v.begin(), v.end(), [&i,imesh,f](auto& vi) {vi = f((*imesh).x_i(i)); ++i;});
    //std::execution::seq, for original/sequential
    //std::execution::par, doesnt work for Apple clang
    //2nd way to code : for_each for index i and capture v,f， but in this case i need iota => won't improve the program ?
    
}


template<typename C>
/*
 doesnt work for Apple clang:
 concept hasupdate = requires(C aclass){aclass::update();};
 template<hasupdate C>
 */
void Equation::compute_for_scheme(IMeshPtr imesh, Variable& u_n, Variable& u_np1){
    C::update( a, imesh, u_n, u_np1);
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


class Timer{
    //https://en.cppreference.com/w/cpp/chrono
    //https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
    std::chrono::time_point<std::chrono::high_resolution_clock> time_point_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> time_point_end;
    
public:
    void start(){time_point_start = std::chrono::high_resolution_clock::now();}
    void stop(){time_point_end = std::chrono::high_resolution_clock::now();}
    void print(std::string smth){
        const std::chrono::duration<double, std::milli> res = time_point_end - time_point_start;
        std::cout << smth << std::endl;
        std::cout << res.count() << "ms" << std::endl;
    }
};
