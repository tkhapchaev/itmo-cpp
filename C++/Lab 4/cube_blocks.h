#pragma once

#include "screenio.h"

class Cube_block {
private:
    void rotate_X_plus() {
        char temp = Y0;
        Y0 = Z0;
        Z0 = Y1;
        Y1 = Z1;
        Z1 = temp;
    }

    void rotate_X_minus() {
        char temp = Z0;
        Z0 = Y0;
        Y0 = Z1;
        Z1 = Y1;
        Y1 = temp;
    }

    void rotate_Y_plus() {
        char temp = Z1;
        Z1 = X0;
        X0 = Z0;
        Z0 = X1;
        X1 = temp;
    }

    void rotate_Y_minus() {
        char temp = X0;
        X0 = Z1;
        Z1 = X1;
        X1 = Z0;
        Z0 = temp;
    }

    void rotate_Z_plus() {
        char temp = X1;
        X1 = Y1;
        Y1 = X0;
        X0 = Y0;
        Y0 = temp;
    }

    void rotate_Z_minus() {
        char temp = Y1;
        Y1 = X1;
        X1 = Y0;
        Y0 = X0;
        X0 = temp;
    }

public:
    char name[5];
    char X0 = '?', X1 = '?';
    char Y0 = '?', Y1 = '?';
    char Z0 = '?', Z1 = '?';

    Cube_block(char * name) {
        strcpy(this -> name, name);
    }

    void set_color(const char * direction, char color) {
        if (direction[0] == 'X')
            if (direction[1] == '+') X0 = color;
            else X1 = color;

        if (direction[0] == 'Y')
            if (direction[1] == '+') Y0 = color;
            else Y1 = color;

        if (direction[0] == 'Z')
            if (direction[1] == '+') Z0 = color;
            else Z1 = color;
    }

    char get_color(const char * direction) const {
        if (direction[0] == 'X')
            if (direction[1] == '+') return X0;
            else return X1;

        if (direction[0] == 'Y')
            if (direction[1] == '+') return Y0;
            else return Y1;

        if (direction[0] == 'Z')
            if (direction[1] == '+') return Z0;
            else return Z1;

        return '?';
    }

    void rotate(const char * command) {
        if (command[0] == 'X' && command[1] == '+') rotate_X_plus();
        if (command[0] == 'X' && command[1] == '-') rotate_X_minus();
        if (command[0] == 'Y' && command[1] == '+') rotate_Y_plus();
        if (command[0] == 'Y' && command[1] == '-') rotate_Y_minus();
        if (command[0] == 'Z' && command[1] == '+') rotate_Z_plus();
        if (command[0] == 'Z' && command[1] == '-') rotate_Z_minus();
    }

    virtual void paint(int input_X, int input_Y, int size, char * axis) {
        char color;
        switch (axis[0]) {
        case 'X':
            if (axis[1] == '-') color = X1;
            else color = X0;
            break;
        case 'Y':
            if (axis[1] == '-') color = Y1;
            else color = Y0;
            break;
        case 'Z':
            if (axis[1] == '-') color = Z1;
            else color = Z0;
            break;
        }

        ScreenIO::set_color(input_X, input_Y, color);
    }

    static bool Identical(Cube_block * block_1, Cube_block * block_2) {
            if (block_1 -> X0 != block_2 -> X0) return false;
            if (block_1 -> X1 != block_2 -> X1) return false;
            if (block_1 -> Y0 != block_2 -> Y0) return false;
            if (block_1 -> Y1 != block_2 -> Y1) return false;
            if (block_1 -> Z0 != block_2 -> Z0) return false;
            if (block_1 -> Z1 != block_2 -> Z1) return false;
            return true;
        }

    ~Cube_block() = default;
};
