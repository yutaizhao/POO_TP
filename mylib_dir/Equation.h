#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class IMesh{
    public:
    virtual float get_tmp_init()const{return -1;};
    virtual float get_tmp_fin() const{return -1;};
    virtual float get_dt() const{return -1;};
    virtual float get_pos_init()const {return -1;};
    virtual float get_pos_fin()const {return -1;};
    virtual float get_dx() const{return -1;};
    int x_size()const{return (get_pos_fin()-get_pos_init())/get_dx();}
    int x_i(int i)const{return get_pos_init()+ get_dx()*i;}
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
    std::vector<float> vect; //donne les solutions avec x fixe et t varie
    
    public :
    Variable(IMesh* imesh){
        int n = (*imesh).x_size();
        var_ptr_imesh = imesh;
        vect.reserve(n);
        fill(vect.begin(), vect.end(), -1);
        
    };
    
    float& operator[](int i){
        return vect[i];
    }
    
    std::vector<float> u_n ; //donne les solutions avec t fixe et x varie
    std::vector<float> u_np1 ; //

};

class Equation{
    float a = 0;
    public :
    void compute(IMesh* imesh, std::vector<float> & u_n, std::vector<float> & u_np1);//
    void compute_initial_condition(IMesh* imesh,Variable & v); //donne U_0 = U(X_0,t_n)
};
