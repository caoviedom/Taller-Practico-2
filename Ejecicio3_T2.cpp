#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// ==================== EJERCICIO 3: Polinomio ====================
class Polinomio {
private:
    int grado;
    double* coeficientes;

public:
    // Constructor: crea polinomio de grado n
    Polinomio(int g) : grado(g) {
        coeficientes = new double[grado + 1];
        for (int i = 0; i <= grado; i++)
            coeficientes[i] = 0;
    }
    
    // Destructor: libera memoria dinamica
    ~Polinomio() {
        delete[] coeficientes;
    }
    
    // Constructor de copia
    Polinomio(const Polinomio& otro) : grado(otro.grado) {
        coeficientes = new double[grado + 1];
        for (int i = 0; i <= grado; i++)
            coeficientes[i] = otro.coeficientes[i];
    }
    
    // Operador de asignacion
    Polinomio& operator=(const Polinomio& otro) {
        if (this != &otro) {
            delete[] coeficientes;
            grado = otro.grado;
            coeficientes = new double[grado + 1];
            for (int i = 0; i <= grado; i++)
                coeficientes[i] = otro.coeficientes[i];
        }
        return *this;
    }
    
    // Establece un coeficiente
    void setCoeficiente(int i, double valor) {
        if (i >= 0 && i <= grado)
            coeficientes[i] = valor;
    }
    
    double getCoeficiente(int i) const {
        if (i >= 0 && i <= grado)
            return coeficientes[i];
        return 0;
    }
    
    int getGrado() const { return grado; }
    
    // Evalua el polinomio en un valor x
    double evaluar(double x) const {
        double resultado = 0;
        double potencia = 1;
        for (int i = 0; i <= grado; i++) {
            resultado += coeficientes[i] * potencia;
            potencia *= x;
        }
        return resultado;
    }
    
    // Sobrecarga operador + para suma de polinomios
    Polinomio operator+(const Polinomio& otro) const {
        int maxGrado = max(grado, otro.grado);
        Polinomio resultado(maxGrado);
        for (int i = 0; i <= maxGrado; i++) {
            double c1 = (i <= grado) ? coeficientes[i] : 0;
            double c2 = (i <= otro.grado) ? otro.coeficientes[i] : 0;
            resultado.coeficientes[i] = c1 + c2;
        }
        return resultado;
    }
    
    // Sobrecarga operador * para multiplicacion de polinomios
    Polinomio operator*(const Polinomio& otro) const {
        Polinomio resultado(grado + otro.grado);
        for (int i = 0; i <= grado; i++)
            for (int j = 0; j <= otro.grado; j++)
                resultado.coeficientes[i + j] += coeficientes[i] * otro.coeficientes[j];
        return resultado;
    }
    
    // Imprime el polinomio en forma estandar
    void imprimir() const {
        bool primero = true;
        bool hayTerminos = false;
        
        for (int i = grado; i >= 0; i--) {
            if (coeficientes[i] != 0) {
                hayTerminos = true;
                
                // Signo
                if (!primero) {
                    if (coeficientes[i] > 0)
                        cout << " + ";
                    else
                        cout << " - ";
                } else if (coeficientes[i] < 0) {
                    cout << "-";
                }
                
                // Coeficiente
                double coef = abs(coeficientes[i]);
                if (coef != 1 || i == 0)
                    cout << coef;
                
                // Variable y exponente
                if (i > 0) cout << "x";
                if (i > 1) cout << "^" << i;
                
                primero = false;
            }
        }
        
        if (!hayTerminos) cout << "0";
        cout << endl;
    }
    
    // Deriva el polinomio y devuelve un nuevo objeto Polinomio
    Polinomio derivar() const {
        if (grado == 0) return Polinomio(0);
        
        Polinomio resultado(grado - 1);
        for (int i = 1; i <= grado; i++)
            resultado.coeficientes[i - 1] = coeficientes[i] * i;
        return resultado;
    }
};

// Funcion para leer un polinomio desde el teclado
void leerPolinomio(Polinomio& p) {
    int grado = p.getGrado();
    cout << "\nIngrese los coeficientes del polinomio de grado " << grado << ":" << endl;
    cout << "(desde el termino independiente hasta el de mayor grado)" << endl;
    
    for (int i = 0; i <= grado; i++) {
        cout << "Coeficiente de x^" << i << ": ";
        double coef;
        cin >> coef;
        p.setCoeficiente(i, coef);
    }
}

// Funcion para mostrar el menu
void mostrarMenu() {
    cout << "\n========== MENU DE OPCIONES ==========" << endl;
    cout << "1. Ingresar Polinomio P(x)" << endl;
    cout << "2. Ingresar Polinomio Q(x)" << endl;
    cout << "3. Mostrar polinomios actuales" << endl;
    cout << "4. Evaluar P(x) en un valor" << endl;
    cout << "5. Evaluar Q(x) en un valor" << endl;
    cout << "6. Sumar P(x) + Q(x)" << endl;
    cout << "7. Multiplicar P(x) * Q(x)" << endl;
    cout << "8. Derivar P(x)" << endl;
    cout << "9. Derivar Q(x)" << endl;
    cout << "10. Crear nuevos polinomios" << endl;
    cout << "0. Salir" << endl;
    cout << "=======================================" << endl;
    cout << "Opcion: ";
}

int main() {
    cout << "===============================================" << endl;
    cout << "   EJERCICIO 3: Polinomio - POO en C++" << endl;
    cout << "===============================================" << endl;
    
    int gradoP, gradoQ;
    
    cout << "\nIngrese el grado del polinomio P(x): ";
    cin >> gradoP;
    
    cout << "Ingrese el grado del polinomio Q(x): ";
    cin >> gradoQ;
    
    if (gradoP < 0 || gradoQ < 0 || gradoP > 20 || gradoQ > 20) {
        cout << "Grados invalidos. Deben estar entre 0 y 20." << endl;
        return 1;
    }
    
    Polinomio P(gradoP);
    Polinomio Q(gradoQ);
    
    cout << "\nPolinomios creados (inicializados en cero)." << endl;
    
    int opcion;
    bool continuar = true;
    
    while (continuar) {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                cout << "\n--- Ingresar Polinomio P(x) ---" << endl;
                leerPolinomio(P);
                cout << "P(x) = "; P.imprimir();
                break;
            }
            
            case 2: {
                cout << "\n--- Ingresar Polinomio Q(x) ---" << endl;
                leerPolinomio(Q);
                cout << "Q(x) = "; Q.imprimir();
                break;
            }
            
            case 3: {
                cout << "\n--- Polinomios Actuales ---" << endl;
                cout << "P(x) = "; P.imprimir();
                cout << "Q(x) = "; Q.imprimir();
                break;
            }
            
            case 4: {
                cout << "\n--- Evaluar P(x) ---" << endl;
                cout << "P(x) = "; P.imprimir();
                cout << "Ingrese el valor de x: ";
                double x;
                cin >> x;
                double resultado = P.evaluar(x);
                cout << "P(" << x << ") = " << resultado << endl;
                break;
            }
            
            case 5: {
                cout << "\n--- Evaluar Q(x) ---" << endl;
                cout << "Q(x) = "; Q.imprimir();
                cout << "Ingrese el valor de x: ";
                double x;
                cin >> x;
                double resultado = Q.evaluar(x);
                cout << "Q(" << x << ") = " << resultado << endl;
                break;
            }
            
            case 6: {
                cout << "\n--- Suma de Polinomios ---" << endl;
                cout << "P(x) = "; P.imprimir();
                cout << "Q(x) = "; Q.imprimir();
                Polinomio suma = P + Q;
                cout << "P(x) + Q(x) = "; suma.imprimir();
                break;
            }
            
            case 7: {
                cout << "\n--- Multiplicacion de Polinomios ---" << endl;
                cout << "P(x) = "; P.imprimir();
                cout << "Q(x) = "; Q.imprimir();
                Polinomio producto = P * Q;
                cout << "P(x) * Q(x) = "; producto.imprimir();
                break;
            }
            
            case 8: {
                cout << "\n--- Derivada de P(x) ---" << endl;
                cout << "P(x) = "; P.imprimir();
                Polinomio derivada = P.derivar();
                cout << "P'(x) = "; derivada.imprimir();
                break;
            }
            
            case 9: {
                cout << "\n--- Derivada de Q(x) ---" << endl;
                cout << "Q(x) = "; Q.imprimir();
                Polinomio derivada = Q.derivar();
                cout << "Q'(x) = "; derivada.imprimir();
                break;
            }
            
            case 10: {
                cout << "\nIngrese el nuevo grado del polinomio P(x): ";
                cin >> gradoP;
                cout << "Ingrese el nuevo grado del polinomio Q(x): ";
                cin >> gradoQ;
                
                if (gradoP >= 0 && gradoQ >= 0 && gradoP <= 20 && gradoQ <= 20) {
                    P = Polinomio(gradoP);
                    Q = Polinomio(gradoQ);
                    cout << "Nuevos polinomios creados!" << endl;
                } else {
                    cout << "Grados invalidos." << endl;
                }
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