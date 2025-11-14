#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// ==================== EJERCICIO 1: Vector3D ====================
class Vector3D {
private:
    double x, y, z;

public:
    // Constructor que inicializa las coordenadas del vector
    Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    
    // Calcula la magnitud del vector usando la fórmula: √(x² + y² + z²)
    double magnitud() const {
        return sqrt(x*x + y*y + z*z);
    }
    
    // Normaliza el vector (vector unitario en la misma dirección)
    Vector3D normalizar() const {
        double mag = magnitud();
        if (mag == 0) {
            cout << "Advertencia: No se puede normalizar un vector nulo." << endl;
            return Vector3D(0, 0, 0);
        }
        return Vector3D(x/mag, y/mag, z/mag);
    }
    
    // Sobrecarga del operador + para suma de vectores
    Vector3D operator+(const Vector3D& otro) const {
        return Vector3D(x + otro.x, y + otro.y, z + otro.z);
    }
    
    // Sobrecarga del operador - para resta de vectores
    Vector3D operator-(const Vector3D& otro) const {
        return Vector3D(x - otro.x, y - otro.y, z - otro.z);
    }
    
    // Sobrecarga del operador * para producto escalar
    double operator*(const Vector3D& otro) const {
        return x*otro.x + y*otro.y + z*otro.z;
    }
    
    // Imprime las coordenadas del vector
    void imprimir() const {
        cout << "(" << fixed << setprecision(2) << x << ", " 
             << y << ", " << z << ")" << endl;
    }
    
    // Getters para acceder a las coordenadas
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
};

// Función para leer un vector desde el teclado
Vector3D leerVector(const string& nombre) {
    double x, y, z;
    cout << "\nIngrese las coordenadas del " << nombre << ":" << endl;
    cout << "x: "; cin >> x;
    cout << "y: "; cin >> y;
    cout << "z: "; cin >> z;
    return Vector3D(x, y, z);
}

// Función para mostrar el menú de opciones
void mostrarMenu() {
    cout << "\n========== MENU DE OPCIONES ==========" << endl;
    cout << "1. Calcular magnitud de un vector" << endl;
    cout << "2. Normalizar un vector" << endl;
    cout << "3. Sumar dos vectores" << endl;
    cout << "4. Restar dos vectores" << endl;
    cout << "5. Producto escalar de dos vectores" << endl;
    cout << "6. Mostrar vectores actuales" << endl;
    cout << "7. Ingresar nuevos vectores" << endl;
    cout << "0. Salir" << endl;
    cout << "=======================================" << endl;
    cout << "Opcion: ";
}

int main() {
    cout << "===============================================" << endl;
    cout << "    EJERCICIO 1: Vector3D - POO en C++" << endl;
    cout << "===============================================" << endl;
    
    // Leer dos vectores del usuario
    Vector3D v1 = leerVector("Vector 1");
    Vector3D v2 = leerVector("Vector 2");
    
    int opcion;
    bool continuar = true;
    
    while (continuar) {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                cout << "\n--- Magnitud de Vector 1 ---" << endl;
                cout << "Vector 1: "; v1.imprimir();
                cout << "Magnitud: " << fixed << setprecision(4) 
                     << v1.magnitud() << endl;
                break;
            }
            
            case 2: {
                cout << "\n--- Normalizacion de Vector 1 ---" << endl;
                cout << "Vector original: "; v1.imprimir();
                Vector3D normalizado = v1.normalizar();
                cout << "Vector normalizado: "; normalizado.imprimir();
                cout << "Magnitud del normalizado: " 
                     << normalizado.magnitud() << endl;
                break;
            }
            
            case 3: {
                cout << "\n--- Suma de Vectores ---" << endl;
                cout << "Vector 1: "; v1.imprimir();
                cout << "Vector 2: "; v2.imprimir();
                Vector3D suma = v1 + v2;
                cout << "Resultado: "; suma.imprimir();
                break;
            }
            
            case 4: {
                cout << "\n--- Resta de Vectores ---" << endl;
                cout << "Vector 1: "; v1.imprimir();
                cout << "Vector 2: "; v2.imprimir();
                Vector3D resta = v1 - v2;
                cout << "Resultado (V1 - V2): "; resta.imprimir();
                break;
            }
            
            case 5: {
                cout << "\n--- Producto Escalar ---" << endl;
                cout << "Vector 1: "; v1.imprimir();
                cout << "Vector 2: "; v2.imprimir();
                double producto = v1 * v2;
                cout << "Producto escalar: " << producto << endl;
                
                // Información adicional sobre el ángulo entre vectores
                double mag1 = v1.magnitud();
                double mag2 = v2.magnitud();
                if (mag1 > 0 && mag2 > 0) {
                    double cosAngulo = producto / (mag1 * mag2);
                    double angulo = acos(cosAngulo) * 180.0 / M_PI;
                    cout << "Ángulo entre vectores: " << angulo << "°" << endl;
                }
                break;
            }
            
            case 6: {
                cout << "\n--- Vectores Actuales ---" << endl;
                cout << "Vector 1: "; v1.imprimir();
                cout << "Vector 2: "; v2.imprimir();
                break;
            }
            
            case 7: {
                v1 = leerVector("Vector 1");
                v2 = leerVector("Vector 2");
                cout << "\n¡Vectores actualizados!" << endl;
                break;
            }
            
            case 0: {
                cout << "\n¡Gracias por usar el programa!" << endl;
                continuar = false;
                break;
            }
            
            default:
                cout << "\nOpcion invalida. Intente nuevamente." << endl;
        }
    }
    
    return 0;
}