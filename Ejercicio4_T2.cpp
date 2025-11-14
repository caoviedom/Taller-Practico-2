#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// ==================== EJERCICIO 4: Numeros Complejos ====================

// Clase Complex: representa numeros complejos en forma binomial (a + bi)
class Complex {
private:
    double a, b;  // parte real e imaginaria

public:
    // Constructor
    Complex(double real = 0, double imag = 0) : a(real), b(imag) {}
    
    // Getters
    double getReal() const { return a; }
    double getImag() const { return b; }
    
    // Sobrecarga operador + para suma
    Complex operator+(const Complex& otro) const {
        return Complex(a + otro.a, b + otro.b);
    }
    
    // Sobrecarga operador - para resta
    Complex operator-(const Complex& otro) const {
        return Complex(a - otro.a, b - otro.b);
    }
    
    // Sobrecarga operador * para multiplicacion
    Complex operator*(const Complex& otro) const {
        return Complex(a*otro.a - b*otro.b, a*otro.b + b*otro.a);
    }
    
    // Sobrecarga operador / para division
    Complex operator/(const Complex& otro) const {
        double denominador = otro.a*otro.a + otro.b*otro.b;
        if (denominador == 0) {
            cout << "Error: division por cero!" << endl;
            return Complex(0, 0);
        }
        return Complex((a*otro.a + b*otro.b)/denominador, 
                      (b*otro.a - a*otro.b)/denominador);
    }
    
    // Calcula el modulo del numero complejo
    double modulo() const {
        return sqrt(a*a + b*b);
    }
    
    // Calcula el conjugado
    Complex conjugado() const {
        return Complex(a, -b);
    }
    
    // Imprime el numero complejo
    void imprimir() const {
        cout << fixed << setprecision(2);
        if (b >= 0)
            cout << a << " + " << b << "i";
        else
            cout << a << " - " << abs(b) << "i";
    }
};

// Clase Polar: representa numeros complejos en forma polar (r * e^(i*theta))
class Polar {
private:
    double r, theta;  // modulo y angulo

public:
    // Constructor
    Polar(double radio = 0, double angulo = 0) : r(radio), theta(angulo) {}
    
    // Constructor desde Complex
    Polar(const Complex& c) {
        double a = c.getReal();
        double b = c.getImag();
        r = sqrt(a*a + b*b);
        theta = atan2(b, a);
    }
    
    // Conversion a Complex
    Complex toComplex() const {
        return Complex(r * cos(theta), r * sin(theta));
    }
    
    // Getters
    double getRadio() const { return r; }
    double getAngulo() const { return theta; }
    
    // Imprime en forma polar
    void imprimir() const {
        cout << fixed << setprecision(2);
        cout << r << " * e^(i*" << theta << ")";
        cout << " = " << r << " * (cos(" << theta << ") + i*sin(" << theta << "))";
    }
    
    void imprimirGrados() const {
        double grados = theta * 180.0 / M_PI;
        cout << fixed << setprecision(2);
        cout << r << " * e^(i*" << grados << "°)";
    }
};

// Funcion auxiliar: acumula (suma) un array de numeros complejos
Complex acumula(Complex* arr, int n) {
    Complex suma(0, 0);
    for (int i = 0; i < n; i++)
        suma = suma + arr[i];
    return suma;
}

// Funcion para leer un numero complejo
Complex leerComplex(const string& nombre) {
    double real, imag;
    cout << "\nIngrese el numero complejo " << nombre << ":" << endl;
    cout << "Parte real: ";
    
    while(!(cin >> real)) {
        cin.clear();  // Limpia el estado de error
        cin.ignore(10000, '\n');  // Descarta la entrada incorrecta
        cout << "Entrada invalida. Ingrese un numero: ";
    }
    
    cout << "Parte imaginaria (solo el numero, sin 'i'): ";
    while(!(cin >> imag)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida. Ingrese un numero: ";
    }
    
    return Complex(real, imag);
}

// Funcion para leer un numero en forma polar
Polar leerPolar(const string& nombre) {
    double radio, angulo;
    int opcion;
    cout << "\nIngrese el numero complejo " << nombre << " en forma polar:" << endl;
    cout << "Radio (modulo): "; cin >> radio;
    cout << "1. Angulo en radianes" << endl;
    cout << "2. Angulo en grados" << endl;
    cout << "Opcion: "; cin >> opcion;
    cout << "Angulo: "; cin >> angulo;
    
    if (opcion == 2)
        angulo = angulo * M_PI / 180.0;
    
    return Polar(radio, angulo);
}

// Funcion para mostrar el menu
void mostrarMenu() {
    cout << "\n========== MENU DE OPCIONES ==========" << endl;
    cout << "1. Ingresar numero complejo C1 (forma binomial)" << endl;
    cout << "2. Ingresar numero complejo C2 (forma binomial)" << endl;
    cout << "3. Ingresar numero complejo en forma polar" << endl;
    cout << "4. Mostrar numeros actuales" << endl;
    cout << "5. Sumar C1 + C2" << endl;
    cout << "6. Restar C1 - C2" << endl;
    cout << "7. Multiplicar C1 * C2" << endl;
    cout << "8. Dividir C1 / C2" << endl;
    cout << "9. Modulo y conjugado de C1" << endl;
    cout << "10. Convertir C1 a forma polar" << endl;
    cout << "11. Acumular array de numeros complejos" << endl;
    cout << "0. Salir" << endl;
    cout << "=======================================" << endl;
    cout << "Opcion: ";
}

int main() {
    cout << "===============================================" << endl;
    cout << "  EJERCICIO 4: Numeros Complejos - POO en C++" << endl;
    cout << "===============================================" << endl;
    
    Complex C1(0, 0);
    Complex C2(0, 0);
    
    int opcion;
    bool continuar = true;
    
    while (continuar) {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                C1 = leerComplex("C1");
                cout << "C1 = "; C1.imprimir(); cout << endl;
                break;
            }
            
            case 2: {
                C2 = leerComplex("C2");
                cout << "C2 = "; C2.imprimir(); cout << endl;
                break;
            }
            
            case 3: {
                Polar p = leerPolar("P");
                cout << "\nForma polar: "; p.imprimir(); cout << endl;
                Complex c = p.toComplex();
                cout << "Forma binomial: "; c.imprimir(); cout << endl;
                break;
            }
            
            case 4: {
                cout << "\n--- Numeros Complejos Actuales ---" << endl;
                cout << "C1 = "; C1.imprimir(); cout << endl;
                cout << "C2 = "; C2.imprimir(); cout << endl;
                break;
            }
            
            case 5: {
                cout << "\n--- Suma de Complejos ---" << endl;
                cout << "C1 = "; C1.imprimir(); cout << endl;
                cout << "C2 = "; C2.imprimir(); cout << endl;
                Complex suma = C1 + C2;
                cout << "C1 + C2 = "; suma.imprimir(); cout << endl;
                break;
            }
            
            case 6: {
                cout << "\n--- Resta de Complejos ---" << endl;
                cout << "C1 = "; C1.imprimir(); cout << endl;
                cout << "C2 = "; C2.imprimir(); cout << endl;
                Complex resta = C1 - C2;
                cout << "C1 - C2 = "; resta.imprimir(); cout << endl;
                break;
            }
            
            case 7: {
                cout << "\n--- Multiplicacion de Complejos ---" << endl;
                cout << "C1 = "; C1.imprimir(); cout << endl;
                cout << "C2 = "; C2.imprimir(); cout << endl;
                Complex producto = C1 * C2;
                cout << "C1 * C2 = "; producto.imprimir(); cout << endl;
                break;
            }
            
            case 8: {
                cout << "\n--- Division de Complejos ---" << endl;
                cout << "C1 = "; C1.imprimir(); cout << endl;
                cout << "C2 = "; C2.imprimir(); cout << endl;
                Complex division = C1 / C2;
                cout << "C1 / C2 = "; division.imprimir(); cout << endl;
                break;
            }
            
            case 9: {
                cout << "\n--- Modulo y Conjugado de C1 ---" << endl;
                cout << "C1 = "; C1.imprimir(); cout << endl;
                cout << "Modulo |C1| = " << C1.modulo() << endl;
                Complex conj = C1.conjugado();
                cout << "Conjugado C1* = "; conj.imprimir(); cout << endl;
                break;
            }
            
            case 10: {
                cout << "\n--- Conversion a Forma Polar ---" << endl;
                cout << "C1 = "; C1.imprimir(); cout << endl;
                Polar polar(C1);
                cout << "Forma polar (radianes): "; polar.imprimir(); cout << endl;
                cout << "Forma polar (grados): "; polar.imprimirGrados(); cout << endl;
                break;
            }
            
            case 11: {
                cout << "\n--- Acumular Array de Complejos ---" << endl;
                int n;
                cout << "Cuantos numeros complejos desea ingresar? ";
                cin >> n;
                
                if (n <= 0 || n > 100) {
                    cout << "Cantidad invalida." << endl;
                    break;
                }
                
                Complex* arr = new Complex[n];
                for (int i = 0; i < n; i++) {
                    cout << "\nNumero " << (i+1) << ":" << endl;
                    arr[i] = leerComplex("");
                }
                
                Complex suma = acumula(arr, n);
                cout << "\nSuma de todos los numeros: ";
                suma.imprimir();
                cout << endl;
                
                delete[] arr;
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