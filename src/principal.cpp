#include "mutacion.h"
#include "enfermedad.h"
#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;
	
	/** @brief lee un fichero de mutaciones, linea a linea
	@param[in] s nombre del fichero
  @param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
	@return true si la lectura ha sido correcta, false en caso contrario
	*/

bool load(conjunto &  cm, const string & s) {
 ifstream fe;
 string cadena;

 cout << "Abrimos "<< s << endl;
 fe.open(s.c_str(), ifstream::in);
 if (fe.fail()){
   cerr << "Error al abrir el fichero " << s << endl;
 } 
 else {
    //leo la cabecera del fichero (líneas que comienzan con #)
    do{ 
      getline(fe,cadena,'\n'); 
    }while (cadena.find("#")==0 && !fe.eof());

    //leo la tabla de mutaciones, una línea cada vez
    while ( !fe.eof() ){ 
        //cout << "leo:: "<< cadena << endl;
        // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
        mutacion mut = mutacion(cadena);
        // Insertar mutación en el conjunto
        cm.insert(mut);
        getline(fe,cadena,'\n');
    }
    fe.close();
    return true;
  } // else
  fe.close();
  return false;
 }
 void AEncontrarConString(string a_encontrar){
    bool encontrado;
    pair < conjunto::value_type, bool > par_encontrar = conjuntoMutaciones.find(a_encontrar);
    if(get<2>(par_encontrar)){
		mutacion = get<1>(par_encontrar);
    	cout << "\n" << mutacion << " y sus enfermedades asociadas son: ";
    	vector<enfermedad> enfermedades_mutacion = mutacion.getEnfermedad();
    	for(int i = 0; i < enfermedades_mutacion.size(); i++){
    		cout << enfermedades_mutacion.get(i) "\n";
    	}
    }
    else{
    	cout << "\nNo se ha encontrado la mutación.\n";
    }
 }
void AEncontrarConChar(string cromosoma, unsigned int posicion){
	bool encontrado;
    pair < conjunto::value_type, bool > par_encontrar = conjuntoMutaciones.find(cromosoma, posicion);
    if(get<2>(par_encontrar)){
    	mutacion = get<1>(par_encontrar);
		cout << "\n" << mutacion << " y sus enfermedades asociadas son: ";
		vector<enfermedad> enfermedades_mutacion = mutacion.getEnfermedad();
    	for(int i = 0; i < enfermedades_mutacion.size(); i++){
    		cout << enfermedades_mutacion.get(i) "\n";
    	}
    }
    else{
    	cout << "\nNo se ha encontrado la mutación.\n"
    }

}

int CalculaMutaciones(string numero_cromosoma){
	int nmutaciones = 0;									//Contador de  mutaciones de dicho cromosoma
	conjunto conjuntoMutaciones;							
	value_type mutacion = *conjuntoMutaciones.begin();
	bool nmmdec = false; 									//No hay más mutaciones de ese char
	bool fin_conjunto = false; 								//nos indica si el conjunto ha terminado

	while(!nmmdec && !fin_conjunto ){						
		if(mutacion.getChr() == numero_cromosoma){			//Comprobamos si estamos iterando sobre una mutacion con un cromosoma válido
			nmutaciones++;									//Añadimos dicha mutación al número total
	 	}
	nmmdec = mutacion.getChr() != numero_cromosoma || nmutaciones > 0;
	fin_conjunto = conjuntoMutaciones.upper_bound(mutacion) < conjuntoMutaciones.end();
	mutacion = *conjuntoMutaciones.upper_bound(mutacion);	//cargamos la siguiente mutacion
	}
}


int main(int argc, char *argv[]){

    conjunto conjuntoMutaciones;
    string query_str; 
    value_type mutacion;

    //Cargar las mutaciones en vectorSNPs
    load(conjuntoMutaciones, "clinvar_20160831.vcf");
    
    //Imprimir número de elementos almacenados en conjuntoMutaciones
    cout << "Lectura del fichero finalizada. Mutaciones cargadas: " << conjuntoMutaciones.size() << endl;  

    //Imprimir cuántas mutaciones están asociadas al cromosoma 1:
    string numero_cromosoma = "1";
    int numero_mutaciones_1 = CalculaMutaciones(numero_cromosoma);
    cout << "Mutaciones asociadas a Chr 1: " << numero_mutaciones_1 << endl; 

    /**@todo ¿Existe la mutación con ID "rs147165522"? Imprimir la mutación y las enfermedades asociadas */
    string id_a_encontrar = "rs147165522";
    AEncontrarConString( string id_a_encontrar);
    
    /**@todo ¿Existe la mutación en chr/pos "14"/67769578? Imprimir la mutación y las enfermedades asociadas */	
	string cromosoma_a_buscar = "14";
	unsigned int pos_a_buscar = 67769578;
	AEncontrarConChar(cromosoma_a_buscar, pos_a_buscar);
    
    /**@todo ¿Cómo podríamos calcular el número de mutaciones del cromosoma 3? (utiliza lower_bound / upper_bound) */
	numero_cromosoma = "3";
	int numero_mutaciones = CalculaMutaciones(numero_cromosoma);
	cout << "\nEl número de mutaciones del cromosoma 3 es: " << numero_mutaciones << "\n";

    /**@todo Analiza la eficiencia teórica y empírica de las operaciones find, insert y erase */

   return 0;
}
