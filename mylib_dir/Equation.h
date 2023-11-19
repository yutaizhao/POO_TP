#include <iostream>
#include <vector>

class IMesh{
    public:
    virtual float get_tmp_init()const{return -1;};
    virtual float get_tmp_fin() const{return -1;};
    virtual float get_dt() const{return -1;};
    virtual float get_pos_init()const {return -1;};
    virtual float get_pos_fin()const {return -1;};
    virtual float get_dx() const{return -1;};
    int x_size()const{return (get_pos_init()-get_pos_fin())/get_dx();}
    
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


class Equation{
    public :
    void compute(IMesh* imesh)const;
};



class Variable{
    
    IMesh* var_ptr_imesh = nullptr;
    std::vector<float> vect;
    float u_n = 0;
    float u_np1 = 0;
    
    int n = (*var_ptr_imesh).x_size();
    
    public :
    Variable(IMesh& imesh){
        
        vect.reserve(n);
        fill(vect.begin(), vect.end(), 0);
    };
    
    float& operator[](int i){
        return vect[i];
    }
};

