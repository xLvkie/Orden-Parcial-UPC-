#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

int main() {
    const int totalCursos = 50;
    const int totalCiclos = 10;
    const int cursosPorCiclo = 5;
    vector<string> cursos; //arreglo
    map<string, vector<string>> prerrequisitos; //diccionario
    vector<vector<string>> niveles; // arreglo de arreglos
    int indiceCurso = 0;

    // Generar cursos C1 hasta C50
    for (int i = 1; i <= totalCursos; ++i) {
        cursos.push_back("C" + to_string(i));
    }

    srand((unsigned int)time(nullptr)); // Para números aleatorios

    // Asignar cursos a ciclos y prerrequisitos básicos
    for (int ciclo = 1; ciclo <= totalCiclos; ++ciclo) {
        vector<string> cicloCursos;
        for (int j = 0; j < cursosPorCiclo; ++j) {
            if (indiceCurso < totalCursos) {
                string curso = cursos[indiceCurso];
                cicloCursos.push_back(curso);

                if (ciclo != 1) {
                    prerrequisitos[curso] = { curso };
                }
                else {
                    prerrequisitos[curso] = { "No hay Prerrequisitos" };
                }

                ++indiceCurso;
            }
        }
        niveles.push_back(cicloCursos);
    }

    // Asignar prerrequisitos para cursos C6 - C50
    for (int ciclo = 1; ciclo < totalCiclos; ++ciclo) {
        for (const string& curso : niveles[ciclo]) {
            const vector<string>& candidatos = niveles[ciclo - 1];
            int prerreqCount = rand() % 3; // 0, 1 o 2

            // Copiar y mezclar los candidatos
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

    // Asignar aleatoriamente que los cursos C1 - C45 sean prerrequisitos de 0, 1 o 2 cursos
    for (int ciclo = 0; ciclo < totalCiclos - 1; ++ciclo) {
        for (const string& curso : niveles[ciclo]) {
            int puedeSerPrerrequisito = rand() % 3; // 0, 1 o 2
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

    // Imprimir resultados
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

    return system("pause");
}
