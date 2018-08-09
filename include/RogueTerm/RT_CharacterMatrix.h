/**
 * Header file for the character matrix class
 */
#pragma once

class RT_CharacterMatrix {
    private:
        char **matrix;
        int columns, rows;
    public:
        RT_CharacterMatrix(int _columns, int _rows);
        ~RT_CharacterMatrix();
};