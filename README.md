# TDA_Conjunto
**Sesion 3. Practicas de Estructura de Datos UGR.**
Tipo de dato abstracto conjunto de mutaciones.

Estructura de la clase:

Cano Gutiérrez, Carlos

Implementación:

Juan Jose Martín Cara\
Rafael Sanjuan Aguilera\
Pablo Torres Rosel

## Función de abstracción

dado C =(vector<mutaciones> vm ) ==> Conjunto BD;

Un objeto abstracto, BD, representando una colección ORDENADA de mutaciones según chr/pos, se instancia en
la clase conjunto como un vector ordenado de mutaciones.

## Invariante de la Representación. 
Propiedades que debe cumplir cualquier objeto\
BD.size() == C.vm.size();\
Para todo i, 0 <= i < C.vm.size() se cumple\
C.vm[i].chr está en ("1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "
16", "17", "18", "19", "20", "21", "22", "X", "Y", "MT")
C.vm[i].pos > 0;
Para todo i, 0 <= i < C.vm.size()-1 se cumple:
a) si C.vm[i].chr == C.vm[i+1].chr, entonces: C.vm[i].pos < C.vm[i+1].pos
b) si C.vm[i].chr != C.vm[i+1].chr, entonces C.vm[i].chr < C.vm[i+1].chr
(donde el orden para el número de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT")