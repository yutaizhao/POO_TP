#include "Mesh.h"

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
    
    float& operator[](int i){return vect[i];}
    
    auto begin(){return vect.begin();}
    
    auto end(){return vect.end();}
    
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
        //avoid out of bound index
        u_np1[0] =u_n[0] - CFL* (u_n[0]-0) ;
    }
};

class LaxWendroff{
    public :
    static void update(float a, IMeshPtr imesh, Variable& u_n, Variable& u_np1 ){
        for(int i =1; i< (*imesh).x_size();++i){
            u_np1[i] =u_n[i] - a*((*imesh).get_dt()/(2*(*imesh).get_dx()))*(u_n[i+1] - u_n[i-1]) + pow(a,2)*(pow((*imesh).get_dt(),2)/(2*pow((*imesh).get_dx(),2)))*(u_n[i+1] - 2*u_n[i] + u_n[i-1]);
            
        }
        //avoid out of bound index
        u_np1[0] =u_n[0] - a*((*imesh).get_dt()/(2*(*imesh).get_dx()))*(u_n[1] - 0) + pow(a,2)*(pow((*imesh).get_dt(),2)/(2*pow((*imesh).get_dx(),2)))*(u_n[1] - 2*u_n[0] + 0);
        u_np1[(*imesh).x_size()] =u_n[(*imesh).x_size()] - a*((*imesh).get_dt()/(2*(*imesh).get_dx()))*(0 - u_n[(*imesh).x_size()-1]) + pow(a,2)*(pow((*imesh).get_dt(),2)/(2*pow((*imesh).get_dx(),2)))*(0 - 2*u_n[(*imesh).x_size()] + u_n[(*imesh).x_size()-1]);
    }
};
