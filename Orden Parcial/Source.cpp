#include "Interfaz.h"
#include "Logica.h"

int main() {
    srand(time(NULL));
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        cin.ignore();

        switch (opcion) {
        case 1:
            generarMallaCurricular();
            break;
        case 2:
            generarMallaCurricular();
            break;
        case 3:
            generarMallaCurricular();
            break;
        case 4:
            system("cls");
            cout << "Saliendo del programa...\n";
            cout << "Presione ENTER para continuar...";
            cin.get();
            break;
        }
    } while (opcion != 4);

    return 0;
}

/*

NOTA 1:
Pienso integrar una API para obtener cursos universitarios reales, es por
eso que agregue más mallas curriculares de carrera, pero veremos si es factible
mi pequeña ideita waza 

Bookie-

NOTA 2:
Cuando se genera una malla curricular sera tal que asi
Ciclo 7:
C31 (Prerrequisitos: C31, C29, ETC)
para leerlo desde una anotación matematico es de la forma
(C29, C31) C29 esta relacionado con C31 -> c29 R c31

*/
