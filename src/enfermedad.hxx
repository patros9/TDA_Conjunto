/** @brief fichero de implementacion de la clase enfermedad
*/

/*******************************************************************************/
// Constructores.
/*******************************************************************************/
enfermedad::enfermedad(){
    setName( "Ehlers-Danlos_syndrome\x2c_type_4" );
    setID( "C0268338" );
    setDatabase( "MedGen:OMIM:ORPHA:SNOMED_CT" );
}

enfermedad::enfermedad(const string & name, const string & ID, const string & database){
    setName( name );
    setID( ID );
    setDatabase( database );
}

/*******************************************************************************/
// Métodos para modificar a las variables privadas.
/*******************************************************************************/
void enfermedad::setName( const string & name ) {
    this->name = name;
}
void enfermedad::setID( const string & ID ) {
    this->ID = ID;
}
void enfermedad::setDatabase( const string & database ) {
    this->database = database;
}
 
/*******************************************************************************/
// Métodos para consultar a las variables privadas.
/*******************************************************************************/
string enfermedad::getName( ) const {
    return name;
}
string enfermedad::getID( ) const {
    return ID;
}
string enfermedad::getDatabase( ) const {
    return database;
}
 
/*******************************************************************************/
// Sobrecarga de operadores.    
/*******************************************************************************/
enfermedad& enfermedad::operator=( const enfermedad & e ) {
    if ( this != &e )
    {
        setName( e.getName() );
        setID( e.getID() );
        setDatabase( e.getDatabase() );
    }
    return *this;
}

bool enfermedad::operator== ( const enfermedad & e ) const {

    // Si queremos que el operador compruebe los datos.
    bool equal = ( getName() == e.getName()         ) &&
                 ( getID() == e.getID()             ) &&
                 ( getDatabase() == e.getDatabase() );

    return equal;
    // Si queremos que el operador compruebe si son el mismo objeto.
    //return ( this == *e );
}
bool enfermedad::operator!= ( const enfermedad & e ) const {

    bool equal = ( getName() == e.getName()         ) &&
                 ( getID() == e.getID()             ) &&
                 ( getDatabase() == e.getDatabase() );

    return (!equal);
    //return ( this != *e );
}

bool enfermedad::operator< ( const enfermedad & e ) const {
    
    bool es_menor = true;
    int tamano_minimo;
    string nombre_actual;
    string nombre_otro;

    nombre_actual             = getName();
    nombre_otro             = e.getName();

    // Si son iguales, devuelve false directamente.
    if( nombre_actual == nombre_otro )
        return false;

    // Buscamos que nombre tiene el menor tamaño.
    if ( nombre_actual.size() < nombre_otro.size() )
        tamano_minimo = nombre_actual.size();
    else
        tamano_minimo = nombre_otro.size();

    for ( int i = 0; i < tamano_minimo; i++ )
        if ( nombre_actual[i] > nombre_otro[i] )
            es_menor = false;

    return es_menor;    
}


ostream& operator<< ( ostream& os, const enfermedad & e){

    string string_enfermedad = e.toString();
    os << string_enfermedad;

    return os;
}

/*******************************************************************************/
// Otros metodos.    
/*******************************************************************************/
bool enfermedad::nameContains(const string & str) const{
 	bool encontrado;

 	if ( name.find( str )  == string::npos )
 		encontrado = false;
 	else
 		encontrado = true;

 	return encontrado;
}

string enfermedad::toString( ) const {
    string str;

    str = "Name: " + getName() + "   ID: " + getID() + "  Database: " + getDatabase();

    return str;
}