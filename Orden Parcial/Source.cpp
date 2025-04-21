#include "Interfaz.h"
#include "Logica.h"

int main() {
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        cin.ignore(); // limpiar buffer

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
    } while (opcion > 4 && opcion < 0);

    return 0;
}

/*

Pienso integrar una API para obtener cursos universitarios reales, es por
eso que agregue más mallas curriculares de carrera, pero veremos si es factible
mi pequeña ideita waza 

Bookie-

*/