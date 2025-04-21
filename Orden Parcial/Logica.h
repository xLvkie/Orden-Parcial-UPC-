#ifndef LOGICA_H
#define LOGICA_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

void generarMallaCurricular() {
    //las constantes no cambian con el tiempo a comparación de las varibles
    const int totalCursos = 50;
    const int totalCiclos = 10;
    const int cursosPorCiclo = 5;
    vector<string> cursos; //arreglo
    map<string, vector<string>> prerrequisitos; //diccionario
    vector<vector<string>> niveles; //arreglo de arreglos
    int indiceCurso = 0;

    // Generar los 50 cursos [C1; C50]
    for (int i = 1; i <= totalCursos; ++i) {
        cursos.push_back("C" + to_string(i));
    }

    // Semilla de tiempo, srand((unsigned)time(0)); es otra forma de escribirlo
    srand(time(NULL));

    // Asigna los cursos a los ciclos y prerrequisitos básicos
    for (int ciclo = 1; ciclo <= totalCiclos; ++ciclo) {
        vector<string> cicloCursos;
        for (int j = 0; j < cursosPorCiclo; ++j) {
            if (indiceCurso < totalCursos) {
                string curso = cursos[indiceCurso];
                cicloCursos.push_back(curso);
                //Omitimos el ciclo 1, ya que los cursos C1, C2, C3, C4 y C5 no tiene prerrequisitos
                if (ciclo != 1)
                    prerrequisitos[curso] = { curso };
                else
                    prerrequisitos[curso] = { "No hay Prerrequisitos" };

                ++indiceCurso;
            }
        }
        niveles.push_back(cicloCursos);
    }

    // Asigna prerrequisitos para los cursos C6 - C50
    for (int ciclo = 1; ciclo < totalCiclos; ++ciclo) {
        for (const string& curso : niveles[ciclo]) {
            const vector<string>& candidatos = niveles[ciclo - 1];
            int prerreqCount = rand() % 3;
            vector<string> seleccionados = candidatos;
            random_shuffle(seleccionados.begin(), seleccionados.end());
            seleccionados.resize(min(prerreqCount, (int)seleccionados.size()));

            prerrequisitos[curso].insert(
                prerrequisitos[curso].end(),
                seleccionados.begin(),
                seleccionados.end()
            );
        }
    }

    // Asigna aleatoriamente que los cursos C1 - C45 sean prerrequisitos de 0, 1 o 2 cursos
    for (int ciclo = 0; ciclo < totalCiclos - 1; ++ciclo) {
        for (const string& curso : niveles[ciclo]) {
            int puedeSerPrerrequisito = rand() % 3;
            if (puedeSerPrerrequisito > 0) {
                vector<string> candidatos;
                for (int siguienteCiclo = ciclo + 1; siguienteCiclo < totalCiclos; ++siguienteCiclo) {
                    candidatos.insert(candidatos.end(), niveles[siguienteCiclo].begin(), niveles[siguienteCiclo].end());
                }

                random_shuffle(candidatos.begin(), candidatos.end());
                vector<string> asignados(candidatos.begin(), candidatos.begin() + min(puedeSerPrerrequisito, (int)candidatos.size()));

                for (const string& c : asignados) {
                    prerrequisitos[c].push_back(curso);
                }
            }
        }
    }

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
            if (prerrequisitos[curso].size() == 1 && i > 0) {
                cout << "SOLO UN CURSO\n";
            }
        }
        cout << endl;
    }

    cout << "Presione ENTER para regresar al menu...";
    cin.ignore();
    cin.get();
}

#endif