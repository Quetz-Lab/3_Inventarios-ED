// 3_Inventario.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cmath>
#include <chrono>
#include <format>
#include <ctime>

using json = nlohmann::json;

//struct Producto {
//    std::string sku;
//    std::string nombre;
//    int precioCentavos;
//    int stock;
//    std::string emocion;
//};

//std::vector<Producto> cargarDesdeJSON(const std::string& archivo) {
//    std::ifstream in(archivo);
//    if (in.is_open()) {
//        std::cout << "File opened successfully." << std::endl;
//        json j; in >> j;
//
//        std::vector<Producto> productos;
//        for (const auto& item : j) {
//           
//
//            productos.push_back({
//                item["sku"].get<std::string>(),
//                item["nombre"].get<std::string>(),
//                item["precioCentavos"].get<int>(),
//                item["stock"].get<int>(),
//                item["emocion"].get<std::string>()
//                });
//        }
//        in.close(); // Cierra el archivo
//        return productos; // Luego retorna
//    }
//    else {
//        std::cout << "Error: Could not open the file." << std::endl;
//
//        return std::vector<Producto>();
//    }
//  
//
//   
//}

void mostrarFechaActual() {
    // time_t es un tipo para almacenar el tiempo del sistema
    time_t t = time(nullptr);

    // tm es una estructura que desglosa el tiempo en año, mes, día, etc.
    tm now;

    // localtime_s es la versión segura para convertir time_t a tm (en Windows/MSVC)
    // Para Linux/macOS, la forma tradicional es: tm* now_ptr = localtime(&t);
    localtime_s(&now, &t);

    std::cout << "📅 Fecha actual: ";
    // tm_mday es el día del mes
    std::cout << now.tm_mday << '/';
    // tm_mon es el mes desde 0 (enero=0), por eso sumamos 1
    std::cout << (now.tm_mon + 1) << '/';
    // tm_year es el número de años desde 1900, por eso sumamos 1900
    std::cout << (now.tm_year + 1900) << "\n";
}

//void mostrarHUD(const Producto& p) {
//    std::cout << "\n╔════════════════════════════╗\n";
//    std::cout << "║ Producto: " << p.nombre << "\n";
//    std::cout << "║ Precio: $" << std::fixed << std::setprecision(2) << static_cast<double>(p.precioCentavos) / 100 << "\n";
//    std::cout << "║ Stock: " << p.stock << "\n";
//    std::cout << "║ Emoción ligada: " << p.emocion << "\n";
//    std::cout << "╚════════════════════════════╝\n";
//}
//
//void aplicarDescuento(Producto& p, const std::string& tipo) {
//    if (tipo == p.emocion) {
//        std::cout << "🧠 Descuento aplicado por afinidad emocional!\n";
//        p.precioCentavos = static_cast<int>(std::round(p.precioCentavos * 0.75));
//    }
//    else {
//        std::cout << "😶 No hay resonancia emocional con ese tipo...\n";
//    }
//}
//
//void buscarSKU(std::vector<Producto>& productos, const std::string& sku) {
//    for (auto& p : productos) {
//        if (p.sku == sku) {
//            mostrarHUD(p);
//            std::cout << "¿Aplicar descuento emocional? (sí/no): ";
//            std::string respuesta; std::cin >> respuesta;
//            if (respuesta == "sí") {
//                std::cout << "🔮 Ingresa emoción: "; std::string emo; std::cin >> emo;
//                aplicarDescuento(p, emo);
//                mostrarHUD(p);
//            }
//            return;
//        }
//    }
//    std::cout << "⛔ Producto no encontrado.\n";
//}
//
//void mostrarTodos(const std::vector<Producto>& productos) {
//    for (const auto& p : productos) mostrarHUD(p);
//}
//
//void mostrarMenu() {
//    std::cout << "\n🔷 --- Fragmentos del Imposible --- 🔷\n";
//    std::cout << "1. Ver todos los productos\n";
//    std::cout << "2. Buscar por SKU\n";
//    std::cout << "3. Salir\n";
//    std::cout << "Selecciona: ";
//}
//

#define API_ENDPOINT "http://monsterballgo.com/api/inventario"

size_t writefunction(void* ptr, size_t size, size_t nmemb, void* userdata)
{
	std::cout << "Recibiendo data..." << std::endl;
	size_t totalSize = size * nmemb;
	std::string* str = static_cast<std::string*>(userdata);
	str->append(static_cast<char*>(ptr), totalSize);
	return totalSize;
}

int main() {
//    mostrarFechaActual(); // <-- LLAMADA A LA NUEVA FUNCIÓN
//    std::vector<Producto> productos = cargarDesdeJSON("productos.json");
//    int opcion;
//    do {
//        mostrarMenu();
//        std::cin >> opcion;
//
//        // AÑADIR ESTA VALIDACIÓN
//        if (std::cin.fail()) {
//            std::cout << "⛔ Entrada inválida. Por favor, ingresa un número.\n";
//            std::cin.clear(); // Limpia el flag de error de cin
//            // Descarta la entrada incorrecta del buffer
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            opcion = 0; // Asigna un valor por defecto para que el switch no falle
//        }
//        switch (opcion) {
//        case 1: mostrarTodos(productos); break;
//        case 2: 
//        {
//            std::cout << "🔍 Ingresar SKU: ";
//            std::string sku; std::cin >> sku;
//            buscarSKU(productos, sku);
//            break;
//        }
//        case 3: std::cout << "🌒 Cerrando el portal...\n"; break;
//        default: std::cout << "Opción inválida...\n";
//        }
//    } while (opcion != 3);
	std::cout << "Ejemplo de peticion GET con libcurl y procesamiento del JSON recibido" << std::endl;

	CURL* curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl)
	{
		std::string response;
		curl_easy_setopt(curl, CURLOPT_URL, API_ENDPOINT);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunction);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		// hacer la peticion GET
		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
		{
			std::cerr << "Error al hacer la peticion: " << curl_easy_strerror(res) << std::endl;
		}
		else
		{
			try
			{
				json j = json::parse(response);
				int n = j["resultados"].is_number() ? j["resultados"].get<int>() : 0;
				std::cout << "Items en inventario: " << j["resultados"] << std::endl;
				std::cout << "Resumen de items: " << std::endl;
				for (int i = 0; i < n; i++)
				{
					std::cout << j["inventario"][i]["sku"].get<std::string>() << " - "
						<< j["inventario"][i]["name"].get<std::string>() << std::endl;
				}
			}
			catch (json::exception& e)
			{
				std::cerr << "Error al parsear el JSON: " << e.what() << std::endl;
			}
		}

		curl_easy_cleanup(curl);
	}
    
}
