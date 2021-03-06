/** @brief fichero de implementacion de la clase mutacion
    @file mutacion.hxx
*/

/*******************************************************************************/
// Constructores.
/*******************************************************************************/
mutacion::mutacion( ) {
    setID       ( "rs786201005"  );
    setChr      ( "1" ); 
    setPos      ( 1014143 ); 
    setCommon   ( false );
}

mutacion::mutacion ( const mutacion& m ) {
    Copiar( m );
}

mutacion::mutacion( const string & str ) {

    size_t inicio=0;
    size_t encontrado;
    string variable_string;
     
    // Chr
    encontrado=str.find("\t",inicio);
    setChr(str.substr(0,encontrado));
    inicio=encontrado+1;
    // Pos
    encontrado=str.find("\t",inicio);
    variable_string=str.substr(inicio,encontrado-inicio);
    setPos(stoi(variable_string));
    inicio=encontrado+1;
    // ID
    encontrado=str.find("\t",inicio);
    setID(str.substr(inicio,encontrado-inicio));
    inicio=encontrado+1;
    // Ref_alt  
    encontrado=str.find("\t",inicio);
    addRef_alt(str.substr(inicio,encontrado-inicio));
    inicio=encontrado+1;
    // ALT
    encontrado=str.find("\t",inicio);
    addRef_alt(str.substr(inicio,encontrado-inicio));
    inicio=encontrado+1;
    // Genes
    string delimitador="GENEINFO=";
    encontrado=str.find(delimitador,inicio) + delimitador.size();
    size_t fin_genes= str.find(";",encontrado);
    addGenes(str.substr(encontrado,fin_genes-encontrado)); // separarlos XXXX:XXXX en vector?!
    //  CAF
     
    delimitador= "CAF=";
    encontrado=str.find(delimitador,0) +delimitador.size();

    if(str.find(delimitador,0)==std::string::npos)
    {
        addCaf(0);
    }
    else
    {
        size_t fin_caf = str.find(";",encontrado+1);
        string caf_string = str.substr(encontrado,fin_caf-encontrado);
         // separarlos X.xxx,X.xxx en vector?!
        //float caf_float = stof(caf_string);
        addCaf(caf_string);
         
         
        /*
        delimitador= "CAF=";
        encontrado=str.find(delimitador,0) + delimitador.size();
        fin_caf = str.find(";",encontrado+1);
        size_t inicio_caf = str.find(",",str.find(delimitador,0));
        caf_string = caf_string.substr(inicio_caf,fin_caf-inicio_caf);
        caf_float = stof(caf_string);
        addCaf(caf_float);
        */
    }
     
     
    // enfermedad
    string name_enfermedad;
    string id_enfermedad;
    string database_enfermedad;
    delimitador = "CLNDBN=" ;
    encontrado=str.find(delimitador,0) + delimitador.size();
    size_t fin_name=str.find(";",encontrado+1);
    name_enfermedad=str.substr(encontrado,fin_name-encontrado);
     
    delimitador="CLNDSDBID=";
    encontrado=str.find(delimitador,0) + delimitador.size();
    size_t fin_id=str.find(";",encontrado);
    id_enfermedad=str.substr(encontrado,fin_id-encontrado);
     
    delimitador="CLNDSDB=";
    encontrado=str.find(delimitador,0) + delimitador.size();
    size_t fin_database=str.find(";",encontrado);
    database_enfermedad=str.substr(encontrado,fin_database-encontrado);
    enfermedad enfermedad1(name_enfermedad,id_enfermedad,database_enfermedad);
    addEnfermedad(enfermedad1);
     
    // CLNSIG
    delimitador = "CLNSIG=" ;
    encontrado=str.find(delimitador,0) + delimitador.size();
    size_t fin_clnsig = str.find(";",encontrado);
    addClnsig(str.substr(encontrado, fin_clnsig-encontrado));
     
    // Common
    delimitador = "COMMON=" ;
    encontrado=str.find(delimitador,0) + delimitador.size();
    if(encontrado!= std::string::npos){
        if(str.substr(encontrado,1)=="0")
            setCommon(0);
        else
            setCommon(1);
    }
    else
        setCommon(0);
}

/*******************************************************************************/
// Métodos para modificar a las variables privadas.
/*******************************************************************************/
void mutacion::setID(const string & id){
    this->ID = id;
}
void mutacion::setChr(const string & chr){
    if( ( stoi( chr ) >= 1 && stoi( chr ) <= 22 ) || chr == "X" || chr == "Y" || chr == "MT" )
        this->chr = chr;
    else
        cerr << "(ERROR) Intento de asignacion a chr ( setChr ) invalido\n";
}
void mutacion::setPos(const unsigned int & pos){
    this->pos = pos;
}
void mutacion::setRef_alt( const vector<string> & ref_alt ){
    bool is_valid = true;
    string str;

    for ( unsigned i = 0; i < ref_alt.size(); i++ )
    {
        str = ref_alt[i];
        for ( unsigned j = 0; j < str.size(); j++ )
        {
            if( str[j] != 'A' && str[j] != 'C' && str[j] != 'G' && str[j] != 'T' )
                is_valid = false;
        }
    }

    if ( is_valid )
        this->ref_alt = ref_alt;
    else 
        cerr << "(ERROR) Intento de asignacion a ref_alt ( setRef_alt ) invalido.\n";
}
void mutacion::setGenes (const vector<string> & genes){
    this->genes = genes;
}  
void mutacion::setCommon (const bool & common){
    this->common = common;
}
void mutacion::setCaf (const vector<float> & caf){
    this->caf = caf;
}
void mutacion::setEnfermedades (const vector<enfermedad> & enfermedades){
    this->enfermedades = enfermedades;
}
void mutacion::setClnsig (const vector<int> & clnsig){
    this->clnsig = clnsig;
}  

void mutacion::addClnsig(string local_clnsig){
    clnsig.push_back( stoi(local_clnsig) );
}
 
void mutacion::addEnfermedad(enfermedad nueva){
    enfermedades.push_back(nueva);
}
 
void mutacion::addCaf(string frec){
    float local_caf = stof("frec");
    caf.push_back(local_caf);
}
 
void mutacion::addGenes(string gen){
    genes.push_back(gen);
}  
 
void mutacion::addRef_alt(string add){
    ref_alt.push_back(add);
}
 
void mutacion::asignarCommon(string comun){
    //if(comun == "0")
    //    setCommon(false);
    //else if(comun == "1")
     //   setCommon(true);
    //else
    //    cout << "Error common";
    setCommon(1);
}

/*******************************************************************************/
// Métodos para consultar a las variables privadas.
/*******************************************************************************/
string mutacion::getID( ) const { return ID; }
string mutacion::getChr( ) const { return chr; }
unsigned int mutacion::getPos( ) const { return pos; }
const vector<string> & mutacion::getRef_alt () const { return ref_alt; }
const vector<string> & mutacion::getGenes () const { return genes; }
bool mutacion::getCommon () const{  return common; }
const vector<float> & mutacion::getCaf () const { return caf; }
const vector<enfermedad> & mutacion::getEnfermedades () const { return enfermedades; }
const vector<int> & mutacion::getClnsig () const { return clnsig; }
  
/*******************************************************************************/
// Sobrecarga de operadores.    
/*******************************************************************************/
mutacion & mutacion::operator= ( const mutacion & m ) {

    if ( this != &m )
        Copiar( m );

    return *this;
}

bool mutacion::operator== ( const mutacion & m ) const {
    bool equal = ( getID()           == m.getID()           ) &&
                 ( getChr()          == m.getChr()          ) &&
                 ( getPos()          == m.getPos()          ) &&
                 ( getRef_alt()      == m.getRef_alt()      ) &&
                 ( getGenes()        == m.getGenes()        ) &&
                 ( getCommon()       == m.getCommon()       ) &&
                 ( getCaf()          == m.getCaf()          ) &&
                 ( getEnfermedades() == m.getEnfermedades() ) &&
                 ( getClnsig()       == m.getClnsig()       );

    return equal;
}

bool mutacion::operator!= ( const mutacion & m ) const {
    bool equal = ( getID()           == m.getID()           ) &&
                 ( getChr()          == m.getChr()          ) &&
                 ( getPos()          == m.getPos()          ) &&
                 ( getRef_alt()      == m.getRef_alt()      ) &&
                 ( getGenes()        == m.getGenes()        ) &&
                 ( getCommon()       == m.getCommon()       ) &&
                 ( getCaf()          == m.getCaf()          ) &&
                 ( getEnfermedades() == m.getEnfermedades() ) &&
                 ( getClnsig()       == m.getClnsig()       );

    return !equal;
}


bool mutacion::operator<(const mutacion & m) const {

    bool es_menor = false;

    if ( m.getChr() > getChr() )
        es_menor = true;
    else if ( m.getChr() == getChr() && m.getPos() > getPos() )
        es_menor = true;
    /*else if ( m.getChr() < getChr() )
        es_menor = false;
    else if ( m.getChr() == getChr() && m.getPos() < getPos() )
        es_menor = false;
    else if ( m.getChr() == getChr() && m.getPos() == getPos() )
        es_menor = false;*/

    return es_menor;    
}

/*******************************************************************************/
// Otros metodos.    
/*******************************************************************************/
void mutacion::Copiar( const mutacion & m ) {
    setID (           m.getID()           );
    setChr (          m.getChr()          );
    setPos (          m.getPos()          );
    setRef_alt (      m.getRef_alt()      );
    setGenes (        m.getGenes()        );
    setCommon (       m.getCommon()       );
    setCaf (          m.getCaf()          );
    setEnfermedades ( m.getEnfermedades() );
    setClnsig (       m.getClnsig()       );
}

string mutacion::toString( ) const {

    string str;
 
    str = "Chr: " + getChr();
    str += "    ";
    str += "Pos: " + to_string( getPos() );
    str += "    ";
    str += "ID: " + getID();
    str += "    ";
   
    str += "Ref_alt: ";
    vector<string> ref_alt = getRef_alt();
    for ( unsigned i = 0; i < ref_alt.size(); i++ )
        str += ref_alt.at( i ) + " ";
    str += "    ";
 
    str += "Genes: ";
    vector<string> genes = getGenes();
    for ( unsigned i = 0; i < genes.size(); i++ )
        str += genes.at( i ) + " ";
    str += "    ";
   
 
    str += " Common: " + to_string( getCommon() );
 
    str += " Caf " ;
     vector<float> caf = getCaf();
    for ( unsigned i = 0; i < caf.size(); i++ ) {
        str += to_string(caf.at( i ));
        str += " ";
    }
    str += "    ";
   
    str += "enfermedades: ";
    vector<enfermedad> enfermedades = getEnfermedades();
    for ( unsigned i = 0; i < enfermedades.size(); i++ ){
        string prueba;
        prueba=enfermedades[i].toString();
        str += prueba;
    }
    str += "    ";
 
    str += "Clnsig: ";
    vector<int> clnsig = getClnsig();
    for ( unsigned i = 0; i < clnsig.size(); i++ )
        str += to_string(clnsig.at( i )) + " ";
 
    str += "\n";
 
    return str;
}


string mutacion::busca (string &str,size_t inicio, string delimitador_final){
    string token;
    size_t fin;
    if( inicio != str.size() ){
        do{
        fin = str.find(delimitador_final,fin);
        if(fin == str.size()){
            fin = str.size() ; // -1?
        }
        }while(fin < inicio);
        token = str.substr(inicio,fin);
    }
    if(inicio == str.size()){
        token = "";
    }
 
return token;
}
 
void mutacion::colocar(string & token, int indice){ //Comprobar si el string está bien pasado
    if(indice == 0)
        setChr(token);
    if(indice == 1)
        setPos(stoi(token));
    if(indice == 2)
        setID(token);
    if(indice == 3)
        addRef_alt(token);
    if(indice == 4){
        size_t final_sub , inicio_sub = 0;
        size_t delimiter = token.find(",");
        for(int i = 0; (final_sub = token.find(delimiter)) >= token.size() ; i++){
            addRef_alt(token.substr(inicio_sub, final_sub));
            inicio_sub = final_sub + delimiter;
        }
    }
 
}

ostream& operator<< ( ostream& os, const mutacion & m ){

    string string_mutacion = m.toString();
    os << string_mutacion;

    return os;
}
