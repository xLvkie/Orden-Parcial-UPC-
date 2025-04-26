#ifndef LOGICA_H
#define LOGICA_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>

using namespace std;

void generarMallaCurricular() {
    //las constantes no cambian
    const int totalCursos = 50;
    const int totalCiclos = 10;
    const int cursosPorCiclo = 5;
    vector<string> cursos; //vector de cursos {"c1", "c2", "c3", ..., "c50"}
    map<string, vector<string>> prerrequisitos; //estructura que guarda pares clave-valor p[clave] = {valor}
    vector<vector<string>> niveles;//vector de vectores tipo strings n = { {"1" , "2"} , {...} ... {...} }
    int indiceCurso = 0;

    // Generar los 50 cursos [C1; C50]
    for (int i = 1; i <= totalCursos; ++i) {
        cursos.push_back("C" + to_string(i)); //mandamos datos al vector cursos 
    }

    // ----
    // Asigna los cursos a los ciclos y prerrequisitos básicos
    for (int ciclo = 1; ciclo <= totalCiclos; ++ciclo) {
        vector<string> cicloCursos;
        for (int j = 0; j < cursosPorCiclo; ++j) { 
            if (indiceCurso < totalCursos) { // index < 50
                string curso = cursos[indiceCurso]; //c1, c2 ...
                cicloCursos.push_back(curso); // {"c1" , "c2" ... "c5"
                //Omitimos el ciclo 1, ya que los cursos C1, C2, C3, C4 y C5 no tiene prerrequisitos

                /*
           
                 Este apartado es donde se da la relación reflexiva aRa
                 prereequisitos["cn"] = {"cn"}; --> aRa
                 solo que en este caso omitimos los cursos el 1er ciclo

                */

                if (ciclo != 1)
                    prerrequisitos[curso] = { curso };
                else
                    prerrequisitos[curso] = { "No hay Prerrequisitos" };

                ++indiceCurso;
            }
        }
        /*

         Agregamos al vector de vectores 'niveles' el vector 'cicloCursos'
         hasta su ultima actualización del bucle for numero 2, luego volvemos
         al primer for donde su inicialización lo incrementamos en 1 y se vuelve
         a inicializar el vector cicloCursos.

        */

        niveles.push_back(cicloCursos);
    }

    // ----
    // Asigna prerrequisitos para los cursos C6 - C50
    for (int ciclo = 1; ciclo < totalCiclos; ++ciclo) { //omitimos el ciclo 1 ya que este no cuenta con prerrequisitos
        for (const string& curso : niveles[ciclo]) {
            /*
            
             Lo que hace este for() es recorrer cada curso uno por uno de
             los cursos del nivel[ciclo], asi hasta que se cambie el valor de ciclo

             niveles[1] = {c6, c7 ... c10}
            
            */

            const vector<string>& candidatos = niveles[ciclo - 1]; //candidatos para ser prerrequisitos de cursos posteriores
            int prerreqCount = rand() % 3; // 0, 1, 3
            vector<string> seleccionados = candidatos; //copia canditados a seleccionados
            random_shuffle(seleccionados.begin(), seleccionados.end()); //mezcla aleatoriamente el vector seleccionados de inicio(begin) a fin(end)
            seleccionados.resize(min(prerreqCount, (int)seleccionados.size())); //cambia el tamaño del vector seleccionados en base a 'prerreqCount' y el tamaño del vector

            /*
            
             Agregamos los prerrequisitos del 'curso' (2do for) a la
             estructura clave-valor 'prerrequisitos'
            
             Por ejemplos sea curso = "c6" (esto seria su clave tipo string)
             prerrequisitos["c6"].insert(
             prerrequisitos["c6"].end(), -> posición en la cual agregamos los valores, siendo este caso el final de map
                seleccionados.begin(), -> inicio del Dominio de seleccionados (desde que elemento)
                seleccionados.end() -> fin del Dominio de seleccionaods (hasta que elemento)
             )
            
            */


            prerrequisitos[curso].insert(
                prerrequisitos[curso].end(),
                seleccionados.begin(),
                seleccionados.end()
            );
        }
    }

    // ----
    // Asigna aleatoriamente que los cursos C1 - C45 sean prerrequisitos de 0, 1 o 2 cursos
    for (int ciclo = 0; ciclo < totalCiclos - 1; ++ciclo) { //tomamdos todos los ciclos, salvo el ultimo ya que estos no pueden ser prerrequisitos de otros cursos
        for (const string& curso : niveles[ciclo]) {

            /*

             Lo que hace este for() es recorrer cada curso uno por uno de
             los cursos del nivel[ciclo], asi hasta que se cambie el valor de ciclo

             niveles[0] = {c1, c2 ... c5}

           */

            int puedeSerPrerrequisito = rand() % 3; // 0, 1, 3
            /*
             
             Digamos que 'curso' = "c1", if (puedeSerPrerrequisito > 0)
             quiere decir que, sí 'puedeSerPrerrequisito' es mayor a 0, entonces
             "c1" (curso) sera prerrequisto de otros 'int puedeSerPrerrequisito'
             por ejemplo: c1 es prerrequisto de c7, c9, etc.
            
            */

            if (puedeSerPrerrequisito > 0) {

                /*
                 
                 Buscamos candidatos a "c1" para que sea prerrequisito en cursos posteriores
                 para ello en el vector candidatos insertamos cursos de ciclos posteriores 
                 por ejemplo si estamos en el ciclo 1, entonces buscara candidatos de ciclos posteriores
                 (ciclo 2 hasta el ciclo 10)
                
                */


                vector<string> candidatos;
                for (int siguienteCiclo = ciclo + 1; siguienteCiclo < totalCiclos; ++siguienteCiclo) {
                    candidatos.insert(candidatos.end(), niveles[siguienteCiclo].begin(), niveles[siguienteCiclo].end());
                }

                //una vez el vector candidatos obtenga todos sus valores los mezclamos aleatoriamente (random_shuffle)
                random_shuffle(candidatos.begin(), candidatos.end());
                //luego escogemos tantos cursos podamos según el valor de 'puedeSerPrerrequisito'
                vector<string> asignados(candidatos.begin(), candidatos.begin() + min(puedeSerPrerrequisito, (int)candidatos.size()));

                //finalmente asignamos mediante el vector asignados como prerrequsitos
                for (const string& c : asignados) {
                    prerrequisitos[c].push_back(curso);
                }
            }
        }
    }

    // ---
    // Imprimimos por consola
    system("cls");
    cout << "Orden de cursos por ciclo y sus prerrequisitos:\n\n";
    for (int i = 0; i < niveles.size(); ++i) {
        cout << "Ciclo " << i + 1 << ":\n";
        for (const string& curso : niveles[i]) {
            cout << "  " << curso << " (Prerrequisitos: ";
            const vector<string>& prereqs = prerrequisitos[curso];
            for (size_t j = 0; j < prereqs.size(); ++j) {
                cout << prereqs[j];
                if (j < prereqs.size() - 1) cout << ", ";
            }
            cout << ")\n";
        }
        cout << endl;
    }

    cout << "Presione ENTER para regresar al menu...";
    cin.ignore();
    cin.get();
}

#endif