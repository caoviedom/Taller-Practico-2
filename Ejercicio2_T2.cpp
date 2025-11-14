#include <iostream>
#include <iomanip>
using namespace std;

// ==================== EJERCICIO 2: Matriz ====================
class Matriz {
private:
    int n;
    double** datos;

public:
    // Constructor: crea matriz cuadrada n x n
    Matriz(int tam) : n(tam) {
        datos = new double*[n];
        for (int i = 0; i < n; i++) {
            datos[i] = new double[n];
            for (int j = 0; j < n; j++)
                datos[i][j] = 0;
        }
    }
    
    // Destructor: libera memoria dinamica
    ~Matriz() {
        for (int i = 0; i < n; i++)
            delete[] datos[i];
        delete[] datos;
    }
    
    // Constructor de copia
    Matriz(const Matriz& otra) : n(otra.n) {
        datos = new double*[n];
        for (int i = 0; i < n; i++) {
            datos[i] = new double[n];
            for (int j = 0; j < n; j++)
                datos[i][j] = otra.datos[i][j];
        }
    }
    
    // Operador de asignacion
    Matriz& operator=(const Matriz& otra) {
        if (this != &otra) {
            // Liberar memoria actual
            for (int i = 0; i < n; i++)
                delete[] datos[i];
            delete[] datos;
            
            // Copiar nueva matriz
            n = otra.n;
            datos = new double*[n];
            for (int i = 0; i < n; i++) {
                datos[i] = new double[n];
                for (int j = 0; j < n; j++)
                    datos[i][j] = otra.datos[i][j];
            }
        }
        return *this;
    }
    
    // Sobrecarga operador () para indexacion
    double& operator()(int i, int j) {
        return datos[i][j];
    }
    
    const double& operator()(int i, int j) const {
        return datos[i][j];
    }
    
    // Calcula la transpuesta de la matriz
    Matriz transpuesta() const {
        Matriz resultado(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                resultado(j, i) = datos[i][j];
        return resultado;
    }
    
    // Multiplicacion de matrices
    Matriz operator*(const Matriz& otra) const {
        Matriz resultado(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    resultado(i, j) += datos[i][k] * otra(k, j);
        return resultado;
    }
    
    // Imprime la matriz con formato
    void imprimir() const {
        for (int i = 0; i < n; i++) {
            cout << "  ";
            for (int j = 0; j < n; j++)
                cout << setw(10) << fixed << setprecision(2) << datos[i][j] << " ";
            cout << endl;
        }
    }
    
    // Metodo para llenar matriz con valores aleatorios
    void llenarAleatoria() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                datos[i][j] = rand() % 10;
    }
    
    // Metodo para llenar matriz identidad
    void llenarIdentidad() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                datos[i][j] = (i == j) ? 1.0 : 0.0;
    }
    
    int getTamanio() const { return n; }
};

// Funcion para leer una matriz desde el teclado
void leerMatriz(Matriz& m) {
    int n = m.getTamanio();
    cout << "\nIngrese los elementos de la matriz " << n << "x" << n << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Elemento [" << i << "][" << j << "]: ";
            double valor;
            cin >> valor;
            m(i, j) = valor;
        }
    }
}

// Funcion para mostrar el menu
void mostrarMenu() {
    cout << "\n========== MENU DE OPCIONES ==========" << endl;
    cout << "1. Ingresar Matriz A manualmente" << endl;
    cout << "2. Ingresar Matriz B manualmente" << endl;
    cout << "3. Generar Matriz A aleatoria" << endl;
    cout << "4. Generar Matriz B aleatoria" << endl;
    cout << "5. Crear Matriz Identidad" << endl;
    cout << "6. Mostrar matrices actuales" << endl;
    cout << "7. Calcular transpuesta de A" << endl;
    cout << "8. Calcular transpuesta de B" << endl;
    cout << "9. Multiplicar A * B" << endl;
    cout << "10. Multiplicar B * A" << endl;
    cout << "0. Salir" << endl;
    cout << "=======================================" << endl;
    cout << "Opcion: ";
}

int main() {
    cout << "===============================================" << endl;
    cout << "    EJERCICIO 2: Matriz - POO en C++" << endl;
    cout << "===============================================" << endl;
    
    int tamanio;
    cout << "\nIngrese el tamano de las matrices cuadradas (n x n): ";
    cin >> tamanio;
    
    if (tamanio <= 0 || tamanio > 10) {
        cout << "Tamano invalido. Debe estar entre 1 y 10." << endl;
        return 1;
    }
    
    Matriz A(tamanio);
    Matriz B(tamanio);
    
    cout << "\nMatrices creadas de tamano " << tamanio << "x" << tamanio << endl;
    cout << "Inicializadas con ceros." << endl;
    
    int opcion;
    bool continuar = true;
    
    while (continuar) {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                cout << "\n--- Ingresar Matriz A ---" << endl;
                leerMatriz(A);
                cout << "Matriz A actualizada!" << endl;
                break;
            }
            
            case 2: {
                cout << "\n--- Ingresar Matriz B ---" << endl;
                leerMatriz(B);
                cout << "Matriz B actualizada!" << endl;
                break;
            }
            
            case 3: {
                cout << "\n--- Generar Matriz A Aleatoria ---" << endl;
                A.llenarAleatoria();
                cout << "Matriz A:" << endl;
                A.imprimir();
                break;
            }
            
            case 4: {
                cout << "\n--- Generar Matriz B Aleatoria ---" << endl;
                B.llenarAleatoria();
                cout << "Matriz B:" << endl;
                B.imprimir();
                break;
            }
            
            case 5: {
                cout << "\n--- Crear Matriz Identidad ---" << endl;
                cout << "1. Aplicar a Matriz A" << endl;
                cout << "2. Aplicar a Matriz B" << endl;
                cout << "Opcion: ";
                int sub;
                cin >> sub;
                if (sub == 1) {
                    A.llenarIdentidad();
                    cout << "Matriz A es ahora identidad:" << endl;
                    A.imprimir();
                } else if (sub == 2) {
                    B.llenarIdentidad();
                    cout << "Matriz B es ahora identidad:" << endl;
                    B.imprimir();
                }
                break;
            }
            
            case 6: {
                cout << "\n--- Matrices Actuales ---" << endl;
                cout << "Matriz A:" << endl;
                A.imprimir();
                cout << "\nMatriz B:" << endl;
                B.imprimir();
                break;
            }
            
            case 7: {
                cout << "\n--- Transpuesta de A ---" << endl;
                cout << "Matriz A original:" << endl;
                A.imprimir();
                Matriz At = A.transpuesta();
                cout << "\nMatriz A transpuesta:" << endl;
                At.imprimir();
                break;
            }
            
            case 8: {
                cout << "\n--- Transpuesta de B ---" << endl;
                cout << "Matriz B original:" << endl;
                B.imprimir();
                Matriz Bt = B.transpuesta();
                cout << "\nMatriz B transpuesta:" << endl;
                Bt.imprimir();
                break;
            }
            
            case 9: {
                cout << "\n--- Multiplicacion A * B ---" << endl;
                cout << "Matriz A:" << endl;
                A.imprimir();
                cout << "\nMatriz B:" << endl;
                B.imprimir();
                Matriz resultado = A * B;
                cout << "\nResultado A * B:" << endl;
                resultado.imprimir();
                break;
            }
            
            case 10: {
                cout << "\n--- Multiplicacion B * A ---" << endl;
                cout << "Matriz B:" << endl;
                B.imprimir();
                cout << "\nMatriz A:" << endl;
                A.imprimir();
                Matriz resultado = B * A;
                cout << "\nResultado B * A:" << endl;
                resultado.imprimir();
                break;
            }
            
            case 0: {
                cout << "\nGracias por usar el programa!" << endl;
                continuar = false;
                break;
            }
            
            default:
                cout << "\nOpcion invalida. Intente nuevamente." << endl;
        }
    }
    
    return 0;
}