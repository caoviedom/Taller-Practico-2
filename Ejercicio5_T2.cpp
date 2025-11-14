#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

// ==================== CLASE CTermino ====================
class CTermino {
private:
    double coeficiente;
    int exponente;

public:
    // Constructor: iniciado a 0 por omision
    CTermino(double coef = 0, int exp = 0) : coeficiente(coef), exponente(exp) {}
    
    // Acceder al coeficiente de un termino
    double getCoeficiente() const {
        return coeficiente;
    }
    
    void setCoeficiente(double coef) {
        coeficiente = coef;
    }
    
    // Acceder al exponente de un termino
    int getExponente() const {
        return exponente;
    }
    
    void setExponente(int exp) {
        exponente = exp;
    }
    
    // Obtener la cadena de caracteres equivalente a un termino
    // Formato: {±}7x^4
    string toString() const {
        stringstream ss;
        
        // Si el coeficiente es 0, retornar cadena vacia
        if (coeficiente == 0) return "";
        
        // Signo
        if (coeficiente > 0)
            ss << "+";
        else
            ss << "-";
        
        // Coeficiente (valor absoluto)
        double coefAbs = abs(coeficiente);
        if (coefAbs != 1 || exponente == 0)
            ss << coefAbs;
        
        // Variable y exponente
        if (exponente > 0) {
            ss << "x";
            if (exponente > 1)
                ss << "^" << exponente;
        }
        
        return ss.str();
    }
    
    // Imprimir el termino
    void imprimir() const {
        cout << toString();
    }
};

// ==================== CLASE CPolinomio ====================
class CPolinomio {
private:
    CTermino* terminos;  // Array dinamico de terminos
    int numTerminos;     // Numero actual de terminos
    int capacidad;       // Capacidad del array

    // Redimensionar el array si es necesario
    void redimensionar() {
        capacidad *= 2;
        CTermino* nuevoArray = new CTermino[capacidad];
        for (int i = 0; i < numTerminos; i++)
            nuevoArray[i] = terminos[i];
        delete[] terminos;
        terminos = nuevoArray;
    }
    
    // Ordenar terminos por exponente descendente
    void ordenar() {
        for (int i = 0; i < numTerminos - 1; i++) {
            for (int j = i + 1; j < numTerminos; j++) {
                if (terminos[i].getExponente() < terminos[j].getExponente()) {
                    CTermino temp = terminos[i];
                    terminos[i] = terminos[j];
                    terminos[j] = temp;
                }
            }
        }
    }

public:
    // Constructor: iniciado con cero terminos por omision
    CPolinomio() : numTerminos(0), capacidad(10) {
        terminos = new CTermino[capacidad];
    }
    
    // Destructor
    ~CPolinomio() {
        delete[] terminos;
    }
    
    // Constructor de copia
    CPolinomio(const CPolinomio& otro) : numTerminos(otro.numTerminos), 
                                          capacidad(otro.capacidad) {
        terminos = new CTermino[capacidad];
        for (int i = 0; i < numTerminos; i++)
            terminos[i] = otro.terminos[i];
    }
    
    // Operador de asignacion
    CPolinomio& operator=(const CPolinomio& otro) {
        if (this != &otro) {
            delete[] terminos;
            numTerminos = otro.numTerminos;
            capacidad = otro.capacidad;
            terminos = new CTermino[capacidad];
            for (int i = 0; i < numTerminos; i++)
                terminos[i] = otro.terminos[i];
        }
        return *this;
    }
    
    // Obtener el numero de terminos que tiene actualmente el polinomio
    int getNumeroTerminos() const {
        return numTerminos;
    }
    
    // Asignar un termino a un polinomio
    // Si el termino existe, se sumaran los coeficientes
    // Si el coeficiente es nulo, no se realizara ninguna operacion
    void asignarTermino(const CTermino& termino) {
        double coef = termino.getCoeficiente();
        int exp = termino.getExponente();
        
        // Si el coeficiente es nulo, no hacer nada
        if (coef == 0) return;
        
        // Buscar si ya existe un termino con ese exponente
        for (int i = 0; i < numTerminos; i++) {
            if (terminos[i].getExponente() == exp) {
                // Sumar coeficientes
                double nuevoCoef = terminos[i].getCoeficiente() + coef;
                terminos[i].setCoeficiente(nuevoCoef);
                
                // Si el nuevo coeficiente es 0, eliminar el termino
                if (nuevoCoef == 0) {
                    for (int j = i; j < numTerminos - 1; j++)
                        terminos[j] = terminos[j + 1];
                    numTerminos--;
                }
                return;
            }
        }
        
        // Si no existe, agregar nuevo termino
        if (numTerminos >= capacidad)
            redimensionar();
        
        terminos[numTerminos] = termino;
        numTerminos++;
        ordenar();
    }
    
    // Sumar dos polinomios
    CPolinomio operator+(const CPolinomio& otro) const {
        CPolinomio resultado;
        
        // Agregar todos los terminos del primer polinomio
        for (int i = 0; i < numTerminos; i++)
            resultado.asignarTermino(terminos[i]);
        
        // Agregar todos los terminos del segundo polinomio
        for (int i = 0; i < otro.numTerminos; i++)
            resultado.asignarTermino(otro.terminos[i]);
        
        return resultado;
    }
    
    // Multiplicar dos polinomios
    CPolinomio operator*(const CPolinomio& otro) const {
        CPolinomio resultado;
        
        for (int i = 0; i < numTerminos; i++) {
            for (int j = 0; j < otro.numTerminos; j++) {
                double nuevoCoef = terminos[i].getCoeficiente() * 
                                  otro.terminos[j].getCoeficiente();
                int nuevoExp = terminos[i].getExponente() + 
                              otro.terminos[j].getExponente();
                
                CTermino nuevoTermino(nuevoCoef, nuevoExp);
                resultado.asignarTermino(nuevoTermino);
            }
        }
        
        return resultado;
    }
    
    // Obtener la cadena equivalente al polinomio
    // Formato: 4x^3 + 3x^2 - 2x + 7
    string toString() const {
        if (numTerminos == 0) return "0";
        
        stringstream ss;
        for (int i = 0; i < numTerminos; i++) {
            string termStr = terminos[i].toString();
            if (!termStr.empty()) {
                if (i == 0 && termStr[0] == '+')
                    ss << termStr.substr(1);  // Omitir el + inicial
                else
                    ss << termStr;
            }
        }
        
        string resultado = ss.str();
        return resultado.empty() ? "0" : resultado;
    }
    
    // Imprimir el polinomio
    void imprimir() const {
        cout << toString();
    }
    
    // Generar polinomio aleatorio
    void generarAleatorio(int gradoMax, int numTerminosMax) {
        // Limpiar polinomio actual
        numTerminos = 0;
        
        // Determinar numero de terminos aleatorio
        int cantidad = 1 + rand() % numTerminosMax;
        
        for (int i = 0; i < cantidad; i++) {
            // Coeficiente aleatorio entre -10 y 10 (excluyendo 0)
            double coef = (rand() % 20) - 10;
            if (coef == 0) coef = 1;
            
            // Exponente aleatorio entre 0 y gradoMax
            int exp = rand() % (gradoMax + 1);
            
            CTermino termino(coef, exp);
            asignarTermino(termino);
        }
    }
};

// ==================== FUNCIONES AUXILIARES ====================

void leerPolinomio(CPolinomio& poli, const string& nombre) {
    cout << "\n--- Ingresar polinomio " << nombre << " ---" << endl;
    int numTerminos;
    cout << "Cuantos terminos tiene el polinomio? ";
    cin >> numTerminos;
    
    for (int i = 0; i < numTerminos; i++) {
        double coef;
        int exp;
        cout << "\nTermino " << (i+1) << ":" << endl;
        cout << "  Coeficiente: "; cin >> coef;
        cout << "  Exponente: "; cin >> exp;
        
        CTermino termino(coef, exp);
        poli.asignarTermino(termino);
    }
    
    cout << "\nPolinomio ingresado: ";
    poli.imprimir();
    cout << endl;
}

void mostrarMenu() {
    cout << "\n========== MENU DE OPCIONES ==========" << endl;
    cout << "1. Ingresar polinomio P(x) manualmente" << endl;
    cout << "2. Ingresar polinomio Q(x) manualmente" << endl;
    cout << "3. Generar polinomio P(x) aleatorio" << endl;
    cout << "4. Generar polinomio Q(x) aleatorio" << endl;
    cout << "5. Mostrar polinomios actuales" << endl;
    cout << "6. Agregar un termino a P(x)" << endl;
    cout << "7. Agregar un termino a Q(x)" << endl;
    cout << "8. Calcular P(x) + Q(x)" << endl;
    cout << "9. Calcular P(x) * Q(x)" << endl;
    cout << "10. Resolver ecuacion: P(x) + Q(x) = R(x)" << endl;
    cout << "0. Salir" << endl;
    cout << "=======================================" << endl;
    cout << "Opcion: ";
}

int main() {
    srand(time(0));  // Inicializar semilla aleatoria
    
    cout << "===============================================" << endl;
    cout << "  EJERCICIO 5: Ecuaciones Algebraicas - POO" << endl;
    cout << "===============================================" << endl;
    
    CPolinomio P, Q, R;
    
    int opcion;
    bool continuar = true;
    
    while (continuar) {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                P = CPolinomio();  // Resetear P
                leerPolinomio(P, "P(x)");
                break;
            }
            
            case 2: {
                Q = CPolinomio();  // Resetear Q
                leerPolinomio(Q, "Q(x)");
                break;
            }
            
            case 3: {
                cout << "\n--- Generar P(x) Aleatorio ---" << endl;
                int gradoMax, numTerminos;
                cout << "Grado maximo: "; cin >> gradoMax;
                cout << "Numero maximo de terminos: "; cin >> numTerminos;
                
                P = CPolinomio();
                P.generarAleatorio(gradoMax, numTerminos);
                cout << "P(x) = "; P.imprimir(); cout << endl;
                break;
            }
            
            case 4: {
                cout << "\n--- Generar Q(x) Aleatorio ---" << endl;
                int gradoMax, numTerminos;
                cout << "Grado maximo: "; cin >> gradoMax;
                cout << "Numero maximo de terminos: "; cin >> numTerminos;
                
                Q = CPolinomio();
                Q.generarAleatorio(gradoMax, numTerminos);
                cout << "Q(x) = "; Q.imprimir(); cout << endl;
                break;
            }
            
            case 5: {
                cout << "\n--- Polinomios Actuales ---" << endl;
                cout << "P(x) = "; P.imprimir(); cout << endl;
                cout << "Q(x) = "; Q.imprimir(); cout << endl;
                if (R.getNumeroTerminos() > 0) {
                    cout << "R(x) = "; R.imprimir(); cout << endl;
                }
                break;
            }
            
            case 6: {
                cout << "\n--- Agregar termino a P(x) ---" << endl;
                cout << "P(x) actual = "; P.imprimir(); cout << endl;
                double coef;
                int exp;
                cout << "Coeficiente: "; cin >> coef;
                cout << "Exponente: "; cin >> exp;
                
                CTermino termino(coef, exp);
                P.asignarTermino(termino);
                
                cout << "P(x) nuevo = "; P.imprimir(); cout << endl;
                break;
            }
            
            case 7: {
                cout << "\n--- Agregar termino a Q(x) ---" << endl;
                cout << "Q(x) actual = "; Q.imprimir(); cout << endl;
                double coef;
                int exp;
                cout << "Coeficiente: "; cin >> coef;
                cout << "Exponente: "; cin >> exp;
                
                CTermino termino(coef, exp);
                Q.asignarTermino(termino);
                
                cout << "Q(x) nuevo = "; Q.imprimir(); cout << endl;
                break;
            }
            
            case 8: {
                cout << "\n--- Suma de Polinomios ---" << endl;
                cout << "P(x) = "; P.imprimir(); cout << endl;
                cout << "Q(x) = "; Q.imprimir(); cout << endl;
                CPolinomio suma = P + Q;
                cout << "P(x) + Q(x) = "; suma.imprimir(); cout << endl;
                break;
            }
            
            case 9: {
                cout << "\n--- Multiplicacion de Polinomios ---" << endl;
                cout << "P(x) = "; P.imprimir(); cout << endl;
                cout << "Q(x) = "; Q.imprimir(); cout << endl;
                CPolinomio producto = P * Q;
                cout << "P(x) * Q(x) = "; producto.imprimir(); cout << endl;
                break;
            }
            
            case 10: {
                cout << "\n--- Resolver Ecuacion: P(x) + Q(x) = R(x) ---" << endl;
                cout << "P(x) = "; P.imprimir(); cout << endl;
                cout << "Q(x) = "; Q.imprimir(); cout << endl;
                
                // Calcular automaticamente R(x) = P(x) + Q(x)
                R = P + Q;
                
                cout << "\nResolviendo la ecuacion..." << endl;
                cout << "R(x) = P(x) + Q(x)" << endl;
                cout << "R(x) = "; R.imprimir(); cout << endl;
                
                cout << "\nLa ecuacion ha sido resuelta y R(x) guardado!" << endl;
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