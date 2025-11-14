#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

class Ficha {
public:
    int ladoA, ladoB;
    Ficha(int a, int b) : ladoA(a), ladoB(b) {}
    void mostrar() const {
        cout << "[" << ladoA << "|" << ladoB << "]";
    }
    int puntaje() const {
        return ladoA + ladoB;
    }
};

class Jugador {
public:
    string nombre;
    vector<Ficha> fichas;
    int puntaje;
    int victorias;
    Jugador(string n) : nombre(n), puntaje(0), victorias(0) {}

    void mostrarFichas() const {
        cout << "Fichas de " << nombre << ": ";
        for (size_t i = 0; i < fichas.size(); ++i) {
            cout << i << ":";
            fichas[i].mostrar();
            cout << " ";
        }
        cout << endl;
    }
    int sumaPintas() const {
        int suma = 0;
        for (const Ficha& f : fichas)
            suma += f.puntaje();
        return suma;
    }
};

class JuegoDomino {
    vector<Jugador> jugadores;
    vector<Ficha> mesa;
    vector<Ficha> banco;
    int turno;
    int totalRondas;

public:
    JuegoDomino(int cantidadJugadores) : turno(0), totalRondas(0) {
        crearBanco();
        agregarJugadores(cantidadJugadores);
        repartirFichas();
    }

    void mostrarInstrucciones() const {
        cout << "---- BIENVENIDO AL DOMINO CLASICO ----\n";
        cout << "Reglas basicas:\n";
        cout << "- El juego usa 28 fichas unicas de domino (doble-6).\n";
        cout << "- Cada jugador recibe 7 fichas si son 2 a 4 jugadores.\n";
        cout << "- El objetivo es quedarse sin fichas o que el resto no pueda jugar.\n";
        cout << "- En tu turno, seleccionas una de tus fichas que coincida con un extremo de la mesa.\n";
        cout << "- Si tu ficha puede jugarse en ambos extremos, puedes elegir.\n";
        cout << "- Si nadie puede jugar (bloqueo), gana el jugador con menos suma de pintas en la mano.\n";
        cout << "- El marcador registra las victorias acumuladas de cada jugador tras cada ronda.\n";
        cout << "----------------------------------------\n\n";
    }

    void crearBanco() {
        banco.clear();
        for (int i = 0; i <= 6; ++i)
            for (int j = i; j <= 6; ++j)
                banco.push_back(Ficha(i, j));
        srand(time(0));
        random_shuffle(banco.begin(), banco.end());
    }

    void agregarJugadores(int cantidad) {
        for (int i = 0; i < cantidad; ++i) {
            cout << "Nombre del jugador " << i + 1 << ": ";
            string nombre;
            cin >> nombre;
            jugadores.push_back(Jugador(nombre));
        }
    }

    void repartirFichas() {
        for (int i = 0; i < 7; ++i) {
            for (size_t j = 0; j < jugadores.size(); ++j) {
                jugadores[j].fichas.push_back(banco.back());
                banco.pop_back();
            }
        }
    }

    void mostrarMesa() const {
        cout << "Mesa: ";
        for (const Ficha& f : mesa) f.mostrar();
        cout << "\n";
        if (!mesa.empty()) {
            cout << "Extremos de la mesa: " << mesa.front().ladoA << " y " << mesa.back().ladoB << endl;
        }
    }

    struct OpcionesColocacion {
        bool puedeIzq, puedeDer;
    };

    OpcionesColocacion opcionesPara(const Ficha& f) const {
        if (mesa.empty()) return {true, true};
        int extremoIzq = mesa.front().ladoA;
        int extremoDer = mesa.back().ladoB;
        bool izq = (f.ladoA == extremoIzq || f.ladoB == extremoIzq);
        bool der = (f.ladoA == extremoDer || f.ladoB == extremoDer);
        return {izq, der};
    }

    bool ponerFicha(int idFicha, Jugador& jugador) {
        Ficha f = jugador.fichas[idFicha];
        OpcionesColocacion op = opcionesPara(f);

        if (mesa.empty()) {
            mesa.push_back(f);
            jugador.fichas.erase(jugador.fichas.begin() + idFicha);
            return true;
        }

        int extremoIzq = mesa.front().ladoA;
        int extremoDer = mesa.back().ladoB;

        int eleccion = -1;
        if (op.puedeIzq && op.puedeDer) {
            cout << "Puedes colocar la ficha por la cola (" << extremoIzq << ") o por la punta (" << extremoDer << ").\n";
            cout << "Ingrese 0 para cola, 1 para punta: ";
            cin >> eleccion;
        } else if (op.puedeIzq) {
            eleccion = 0;
        } else if (op.puedeDer) {
            eleccion = 1;
        } else {
            return false;
        }

        if (eleccion == 0) { // Cola - izquierda
            if (f.ladoA == extremoIzq)
                mesa.insert(mesa.begin(), Ficha(f.ladoB, f.ladoA));
            else if (f.ladoB == extremoIzq)
                mesa.insert(mesa.begin(), f);
            jugador.fichas.erase(jugador.fichas.begin() + idFicha);
            return true;
        } else if (eleccion == 1) { // Punta - derecha
            if (f.ladoA == extremoDer)
                mesa.push_back(f);
            else if (f.ladoB == extremoDer)
                mesa.push_back(Ficha(f.ladoB, f.ladoA));
            jugador.fichas.erase(jugador.fichas.begin() + idFicha);
            return true;
        }
        return false;
    }

    void ronda() {
        bool rondaActiva = true;
        int jugadoresSinMov = 0;
        while (rondaActiva) {
            Jugador& actual = jugadores[turno];
            mostrarMesa();
            actual.mostrarFichas();

            bool puede = false;
            for (const Ficha& f : actual.fichas) {
                OpcionesColocacion op = opcionesPara(f);
                if (op.puedeIzq || op.puedeDer) puede = true;
            }

            if (!puede) {
                cout << actual.nombre << " no puede jugar esta vez.\n";
                jugadoresSinMov++;
            } else {
                int idFicha = -1;
                do {
                    cout << "Seleccione la ficha a jugar (indice): ";
                    cin >> idFicha;
                    if (idFicha >= 0 && idFicha < (int)actual.fichas.size()) {
                        OpcionesColocacion op = opcionesPara(actual.fichas[idFicha]);
                        if (op.puedeIzq || op.puedeDer)
                            break;
                    }
                    cout << "Seleccion invalida. ";
                } while (true);

                ponerFicha(idFicha, actual);
                jugadoresSinMov = 0;

                if (actual.fichas.empty()) {
                    cout << actual.nombre << " ha colocado todas sus fichas y gana la ronda!\n";
                    actual.victorias++;
                    rondaActiva = false;
                }
            }
            turno = (turno + 1) % jugadores.size();
            if (jugadoresSinMov == (int)jugadores.size()) {
                cout << "Nadie puede jugar. Ronda finalizada por bloqueo.\n";
                // Calcular ganador por menos pintas
                int menor = jugadores[0].sumaPintas();
                int ganador = 0;
                bool empate = false;
                for (size_t i = 1; i < jugadores.size(); ++i) {
                    int pintas = jugadores[i].sumaPintas();
                    if (pintas < menor) {
                        menor = pintas;
                        ganador = i;
                        empate = false;
                    } else if (pintas == menor) {
                        empate = true;
                    }
                }
                if (!empate) {
                    cout << "El ganador de la ronda por menos pintas es " 
                         << jugadores[ganador].nombre << " con " 
                         << menor << " pintas!\n";
                    jugadores[ganador].victorias++;
                } else {
                    cout << "Empate: mas de un jugador tiene la menor cantidad de pintas (" << menor << ").\n";
                }
                rondaActiva = false;
            }
        }
        totalRondas++;
        mostrarMarcador();
        reiniciarRonda();
    }

    void mostrarMarcador() const {
        cout << "\nMarcador tras " << totalRondas << " rondas:\n";
        for (const Jugador& j : jugadores)
            cout << j.nombre << " - Victorias: " << j.victorias << endl;
        cout << endl;
    }

    void reiniciarRonda() {
        mesa.clear();
        for (size_t i = 0; i < jugadores.size(); ++i)
            jugadores[i].fichas.clear();
        crearBanco();
        repartirFichas();
    }

    void jugar() {
        mostrarInstrucciones();
        while (true) {
            ronda();
            cout << "Desea jugar otra ronda? (s/n): ";
            char respuesta;
            cin >> respuesta;
            if (respuesta != 's') break;
        }
    }
};

int main() {
    int nJugadores;
    cout << "Cuantos jugadores (2-4)?: ";
    cin >> nJugadores;
    while (nJugadores < 2 || nJugadores > 4) {
        cout << "Numero invalido. Intenta de nuevo (2-4): ";
        cin >> nJugadores;
    }
    JuegoDomino juego(nJugadores);
    juego.jugar();
    cout << "Gracias por jugar!\n";
    return 0;
}
