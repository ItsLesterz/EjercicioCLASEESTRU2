#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Producto {
    int id;
    string nombre;
    int categoria;
    double precio;
    int pasillo;
    int estante;
};

const int kLongitudCampo = 20;

vector<string> dividir(const string& str, char delimitador) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimitador)) {
        tokens.push_back(token);
    }
    return tokens;
}

void csv_a_json(const string& archivo_csv, const string& archivo_json) {
    ifstream entrada(archivo_csv);
    ofstream salida(archivo_json);
    string linea;
    vector<Producto> productos;
    while (getline(entrada, linea)) {
        vector<string> campos = dividir(linea, ',');
        Producto producto = {
                stoi(campos[0]), // id
                campos[1], // nombre
                stoi(campos[2]), // categoria
                stod(campos[3]), // precio
                stoi(campos[4]), // pasillo
                stoi(campos[5]) // estante
        };
        productos.push_back(producto);
    }
    salida << "[";
    for (size_t i = 0; i < productos.size(); i++) {
        salida << "{";
        salida << "\"ID\": " << productos[i].id << ", ";
        salida << "\"Nombre\": \"" << productos[i].nombre << "\", ";
        salida << "\"Categoria\": " << productos[i].categoria << ", ";
        salida << "\"Precio\": " << fixed << setprecision(2) << productos[i].precio << ", ";
        salida << "\"Pasillo\": " << productos[i].pasillo << ", ";
        salida << "\"Estante\": " << productos[i].estante;
        salida << "}";
        if (i != productos.size() - 1) {
            salida << ",";
        }
    }
    salida << "]";
}

void csv_a_fijo(const string& archivo_csv, const string& archivo_fijo) {
    ifstream entrada(archivo_csv);
    ofstream salida(archivo_fijo);
    string linea;
    while (getline(entrada, linea)) {
        vector<string> campos = dividir(linea, ',');
        int id = stoi(campos[0]);
        string nombre = campos[1];
        int categoria = stoi(campos[2]);
        double precio = stod(campos[3]);
        int pasillo = stoi(campos[4]);
        int estante = stoi(campos[5]);
        salida << setw(kLongitudCampo) << id;
        salida << setw(kLongitudCampo) << nombre;
        salida << setw(kLongitudCampo) << categoria;
        salida << setw(kLongitudCampo) << fixed << setprecision(2) << precio;
        salida << setw(kLongitudCampo) << pasillo;
        salida << setw(kLongitudCampo) << estante;
        salida << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <archivo_csv> [-json | -fijo]" << endl;
        return 1;
    }
    string archivo_csv = argv[1];
    string modo = argv[2];
    if (modo == "-json") {
        string archivo_json = archivo_csv.substr(0, archivo_csv.size() - 4) + ".json";
        csv_a_json(archivo_csv, archivo_json);
    }
    else if (modo == "-fixed") {
        string archivo_arreglado = archivo_csv.substr(0, archivo_csv.size() - 4) + ".fixed";
        csv_a_fijo(archivo_csv, archivo_arreglado);
    }
    else {
        cerr << "Not supproted mode: " << modo << endl;
        return 1;
    }
    return 0;
}