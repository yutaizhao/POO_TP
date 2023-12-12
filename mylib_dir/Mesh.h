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
#include <sys/stat.h>

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
    /*
     private :
     float t_ini = 0;
     float t_final = 1;
     float dt = 0.5;
     float x_min = 0;
     float x_max = 5;
     float dx = 2;
     */
public://will get warning
    float get_tmp_init() const override{}
    float get_tmp_fin() const override{}
    float get_dt() const override{}
    float get_pos_init() const override{}
    float get_pos_fin() const override {}
    float get_dx()const override{}
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
