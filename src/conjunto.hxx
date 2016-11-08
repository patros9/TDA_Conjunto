/*******************************************************************************/
// Constructores.
/*******************************************************************************/
conjunto::conjunto( ){
	vm.clear();
}

conjunto::conjunto ( const conjunto & d ){
	this->vm = d.vm;
}

/*******************************************************************************/
// Métodos de busqueda en el conjunto.
/*******************************************************************************/
pair<conjunto::value_type,bool>  conjunto::find ( const string & chr, const unsigned int & pos ) const {

	conjunto::value_type m;
	pair<conjunto::value_type,bool> par( m, false );

	for ( unsigned i = 0; i < vm.size() && !par.second; i++ )
	{
		if( vm[ i ].getChr() == chr && vm[ i ].getPos() == pos )
		{
			par.first = vm[ i ];
			par.second = true;
		}
	}

	return par; 
}

pair<conjunto::value_type,bool>  conjunto::find ( const string & ID ) const {

	conjunto::value_type m;
	pair<conjunto::value_type,bool> par( m, false );

	for ( unsigned i = 0; i < vm.size() && !par.second; i++ )
	{
		if( vm[ i ].getID() == ID )
		{
			par.first = vm[ i ];
			par.second = true;
		}
	}

	return par; 
}

pair<conjunto::value_type,bool>  conjunto::find ( const conjunto::value_type & e ) const {

	conjunto::value_type m;
	pair<conjunto::value_type,bool> par( m, false );

	for ( unsigned i = 0; i < vm.size() && !par.second; i++ )
	{
		if( vm[ i ].getID() == e.getID() )
		{
			par.first = vm[ i ];
			par.second = true;
		}
	}

	return par; 
}

conjunto::size_type conjunto::count ( const string & chr, const unsigned int & pos ) const {

	conjunto::size_type cuenta = 0;

	for ( unsigned i = 0; i < vm.size(); i++ )
	{
		if( vm[ i ].getChr() == chr && vm[ i ].getPos() == pos )
			cuenta++;
	}

	return cuenta;
}

conjunto::size_type conjunto::count (const string & ID) const {

	conjunto::size_type cuenta = 0;

	for ( unsigned i = 0; i < vm.size(); i++ )
	{
		if( vm[ i ].getID() == ID )
			cuenta++;
	}

	return cuenta;
}

conjunto::size_type conjunto::count (const conjunto::value_type & e) const {

	conjunto::size_type cuenta = 0;

	for ( unsigned i = 0; i < vm.size(); i++ )
	{
		if( vm[ i ].getID() == e.getID() )
			cuenta++;
	}

	return cuenta;
}

/*******************************************************************************/
// Métodos para insertar y borrar datos.
/*******************************************************************************/
bool conjunto::insert( const conjunto::value_type & e) {

	pair<conjunto::value_type,bool> par = find ( e );
	bool existe_ya = par.second;

	if( !existe_ya )
		vm.push_back( e );

	return existe_ya;
}

bool conjunto::erase( const string & chr, const unsigned int & pos ) {

	bool deleted = false;

	for ( unsigned i = 0; i < vm.size(); i++ )
	{
		if( vm[ i ].getChr() == chr && vm[ i ].getPos() == pos )
		{
			vm.erase( vm.begin() + i );
			deleted = true;
		}
	}

	return deleted;
}
bool conjunto::erase( const string & ID ) {

	bool deleted = false;

	for ( unsigned i = 0; i < vm.size(); i++ )
	{
		if( vm[ i ].getID() == ID )
		{
			vm.erase( vm.begin() + i );
			deleted = true;
		}
	}

	return deleted;
}
bool conjunto::erase( const conjunto::value_type & e ) {

	bool deleted = false;

	for ( unsigned i = 0; i < vm.size(); i++ )
	{
		if( vm[ i ].getID() == e.getID() )
		{
			vm.erase( vm.begin() + i );
			deleted = true;
		}
	}

	return deleted;
}

void conjunto::clear(){
	vm.clear();
}

conjunto::size_type conjunto::size() const {

	conjunto::size_type size = vm.size();

	return size;
}

bool conjunto::empty() const {
	return vm.empty();
}

conjunto & conjunto::operator=( const conjunto & org ){

    if ( this != &org )
		this->vm = org.vm;

    return *this;
}

conjunto::iterator conjunto::begin () {

	conjunto::iterator inicio = vm.begin();

	return inicio;
}

conjunto::iterator conjunto::end () {

	conjunto::iterator final = vm.end();

	return final;
}

conjunto::const_iterator conjunto::cbegin () const {

	conjunto::const_iterator inicio = vm.cbegin();

	return inicio;
}

conjunto::const_iterator conjunto::cend () const {

	conjunto::const_iterator final = vm.cend();

	return final;
}

conjunto::iterator conjunto::lower_bound (const string & chr, const unsigned int & pos) {

	conjunto::iterator lower = begin();

	while ( (*lower).getChr() != chr && (*lower).getPos() != pos && lower != end() ) {
		lower++; 
	}

	lower--;
	
	return lower;
}

conjunto::iterator conjunto::lower_bound (const conjunto::value_type & e) {

	conjunto::iterator lower = begin();

	while ( (*lower) != e && lower != end() ) {
		lower++; 
	}+

	lower--;

	return lower;
}

conjunto::iterator conjunto::upper_bound (const string & chr, const unsigned int & pos) {
	
	conjunto::iterator upper = begin();

	do { upper++; } 
	while ( (*upper).getChr() != chr && (*upper).getPos() != pos && upper != end() );

	return upper;
}
conjunto::iterator conjunto::upper_bound (const conjunto::value_type & e) {
	
	conjunto::iterator upper = begin();

	do { upper++; } 
	while ( (*upper) != e && upper != end() );

	return upper;
}

bool conjunto::cheq_rep( ) const {

	bool invariante_correcto = true;
	string chromosoma[] = {
		"1", "2", "3", "4", "5", "6", 
		"7", "8", "9", "10", "11", "12", 
		"13", "14", "15", "16", "17", "18", 
		"19", "20", "21", "22", "X", "Y", "MT"
	};

	string chr1;
	string chr2;

	for( unsigned i = 0; i < vm.size() && invariante_correcto; i++ )
	{
		chr1 = vm[ i ].getChr();
		chr2 = vm[ i + 1 ].getChr();

    	if ( ( stoi(chr1) < 1 || stoi(chr1) > 22 ) && chr1 != "X" && chr1 != "Y" && chr1 != "MT" )
    		invariante_correcto = false;
	}
	for( unsigned i = 0; i < vm.size()-1 && invariante_correcto; i++ )
	{
		chr1 = vm[i].getChr();
		chr2 = vm[i+1].getChr();

	  	if ( chr1 == chr2 && vm[i].getPos() >= vm[i+1].getPos() )
    		invariante_correcto = false;

    	if ( chr1 != chr2 )
    	{
    		unsigned num_chr1 = 0, num_chr2 = 0;
    		unsigned chromosoma_size = 25;
    		for ( unsigned j = 0; j < chromosoma_size && num_chr1 != 0 && num_chr2 != 0; j++ )
    		{
    			if ( chr1 == chromosoma[ j ] )
    				num_chr1 = j;
    			if ( chr2 == chromosoma[ j ] )
    				num_chr2 = j;
    		}
    		if ( num_chr1 <= num_chr2 )
    			invariante_correcto = false;
    	}

	}

	return invariante_correcto;
}


ostream &  operator << ( ostream & sal, const conjunto & C ) {

	string salida = "";

	for ( unsigned i = 0; i < C.size(); i++ )
		salida += C.vm[ i ].toString();

	sal << salida;

	return sal;
}