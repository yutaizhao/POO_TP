# POO_TP

## les fichiers principaux sont organises de la maniere suivante

```bash
├──mylib_dir
│   ├──Problem.h
│   ├──Problem.cpp
│   ├──Mesh.h
│   ├──Mesh.cpp
│   ├──Equation.h
│   ├──Equation.cpp
│   └──CMakeLists.txt
├──old_my_data
│   ├──data
│   ├──perfor_result.txt
│   └──plot.png
├──data
├──Problem.h
├──plot-simulation.gp
├──plot.png
├──main.cpp
├──test.cpp
└──CMakeLists.txt
```
mylib_dir : contient les fichiers libs
Problem.h/cpp : definissent la classe `Probleme` et ses membres
Mesh.h/cpp : definissent les classes `IMesh`, `UniformMesh`, `NonUniformMesh` et leurs membres
Equation.h/cpp : definissent les classes `Equation`,`Variable`,`Upwind`,`LaxWendroff` et leurs membres

old_my_data : contient les resultats de la resolution, le graphe que j'ai obtenu ainsi que les preformances
data : contient les resultats de la resolution apres l'execution du programme
plot-simulation.gp : un script pour faire le graphe
main.cpp : fonction main
test.cpp : tests unitaires 

## Remarques  

### Execution 

le programmee s'execute de la maniere suivante : 
```bash
./prog_exe [t_ini] [t_final] [dt] [x_min] [x_max] [dx] [Maillage Type] [Parallelisme]
```
le parametre [Maillage Type] peut etre : `uniform` ou `non-uniform`
le parametre [Parallelisme] peut etre : 
`0` : solve sequentiel  
`1` : solve parallel
`2` : solve parallel avec async

par eexemple : 
```bash
./prog_exe 0 2 0.1 0 10 0.1 uniform 0
```

### Questions Bonus

Ayant eu des meesages d'erreur et d'apres https://en.cppreference.com/w/cpp/compiler_support
On voit que `concept` et `std::execution::par` ne peuvent pas etre utilisé par un programme compile par Apple clang
Mais les codes sont bien mis en commentaire.

## Script  

appelé `plot-simulation.gp` , requis le repretoire `data` avec les resultats.
taper 

```bash
gnuplot plot-simulation.gp 
```

pour faire le graphe

ATTENTION : ne pas deplacer ce script `plot-simulation.gp` et `data` !

## References

Les references pour coder la fonctionalite de `concept` :
https://en.cppreference.com/w/cpp/language/constraints
https://en.cppreference.com/w/cpp/types/is_object
https://en.cppreference.com/w/cpp/types/is_function
https://www.jianshu.com/p/826c6c80d089
https://en.cppreference.com/w/cpp/compiler_support
Les references pour coder la class `Timer` :
https://en.cppreference.com/w/cpp/chrono
https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
