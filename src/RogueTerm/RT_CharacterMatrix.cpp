#include "RogueTerm/RT_CharacterMatrix.h"

RT_CharacterMatrix::RT_CharacterMatrix(int _columns, int _rows) {
    columns = _columns;
    rows = _rows;

    matrix = new char*[columns];
    for(int i = 0; i < rows; i++) {
        matrix[i] = new char[rows];
    }
}

RT_CharacterMatrix::~RT_CharacterMatrix() {
    
}