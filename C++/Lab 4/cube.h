#pragma once

using namespace std;

#include <iostream>
#include <fstream>

class Cube {
    Cube_block ** ** data;
  
    char colors[27][7];

    void fill_with_zeros() {
        char color_1 = 'R';
        char color_2 = 'O';
        for (int X = 0; X < 3; X++)
            for (int Y = 0; Y < 3; Y++) {
                data[X][Y][0] -> Z0 = color_1;
                data[X][Y][2] -> Z1 = color_2;
            }

        color_1 = 'Y';
        color_2 = 'W';
        for (int X = 0; X < 3; X++)
            for (int Z = 0; Z < 3; Z++) {
                data[X][0][Z] -> Y0 = color_1;
                data[X][2][Z] -> Y1 = color_2;
            }

        color_1 = 'G';
        color_2 = 'B';
        for (int Y = 0; Y < 3; Y++)
            for (int Z = 0; Z < 3; Z++) {
                data[0][Y][Z] -> X0 = color_1;
                data[2][Y][Z] -> X1 = color_2;
            }
    }

    void cube_to_color_array() {
        int position = 0;
        for (int X = 0; X < 3; X++)
            for (int Y = 0; Y < 3; Y++)
                for (int Z = 0; Z < 3; Z++) {
                    memset(colors[position], 0, 7);
                    colors[position][0] = data[X][Y][Z] -> X0;
                    colors[position][1] = data[X][Y][Z] -> X1;
                    colors[position][2] = data[X][Y][Z] -> Y0;
                    colors[position][3] = data[X][Y][Z] -> Y1;
                    colors[position][4] = data[X][Y][Z] -> Z0;
                    colors[position][5] = data[X][Y][Z] -> Z1;
                    position++;
                }
    }

    void color_array_to_cube() {
        int position = 0;
        for (int X = 0; X < 3; X++)
            for (int Y = 0; Y < 3; Y++)
                for (int Z = 0; Z < 3; Z++) {
                    data[X][Y][Z] -> X0 = colors[position][0];
                    data[X][Y][Z] -> X1 = colors[position][1];
                    data[X][Y][Z] -> Y0 = colors[position][2];
                    data[X][Y][Z] -> Y1 = colors[position][3];
                    data[X][Y][Z] -> Z0 = colors[position][4];
                    data[X][Y][Z] -> Z1 = colors[position][5];
                    position++;
                }
    }

    static void rotate_list(Cube_block ** * side,
        const char * rotor_1, char * rotor_2) {
        bool rotor_inverted = rotor_1[1] == '-';
        Cube_block * temp;

        for (int i = 0; i < 2; i++)
            if (rotor_inverted) {
                temp = * (side[0]);
                for (int j = 0; j < 7; j++)
                    *
                    (side[j]) = * (side[j + 1]);
                *(side[7]) = temp;
            }

        else {
            temp = * (side[7]);
            for (int j = 7; j >= 1; j--)
                *
                (side[j]) = * (side[j - 1]);
            *(side[0]) = temp;
        }

        for (int k = 0; k < 8; k++)
            ( * (side[k])) -> rotate(rotor_2);
    }

    void rotate_Y_minus() {
        Cube_block ** side[8] = {
            &
            data[0][0][0],
            &
            data[1][0][0],
            &
            data[2][0][0],
            &
            data[2][0][1],
            &
            data[2][0][2],
            &
            data[1][0][2],
            &
            data[0][0][2],
            &
            data[0][0][1]
        };

        rotate_list(side, "Y-", "Y+");
    }

    void rotate_y_minus() {
        Cube_block ** side[8] = {
            &
            data[0][2][0],
            &
            data[1][2][0],
            &
            data[2][2][0],
            &
            data[2][2][1],
            &
            data[2][2][2],
            &
            data[1][2][2],
            &
            data[0][2][2],
            &
            data[0][2][1]
        };

        rotate_list(side, "Y-", "Y+");
    }

    void rotate_Y_plus() {
        Cube_block ** side[8] = {
            &
            data[0][0][0],
            &
            data[1][0][0],
            &
            data[2][0][0],
            &
            data[2][0][1],
            &
            data[2][0][2],
            &
            data[1][0][2],
            &
            data[0][0][2],
            &
            data[0][0][1]
        };

        rotate_list(side, "Y+", "Y-");
    }

    void rotate_y_plus() {
        Cube_block ** side[8] = {
            &
            data[0][2][0],
            &
            data[1][2][0],
            &
            data[2][2][0],
            &
            data[2][2][1],
            &
            data[2][2][2],
            &
            data[1][2][2],
            &
            data[0][2][2],
            &
            data[0][2][1]
        };

        rotate_list(side, "Y+", "Y-");
    }

    void rotate_X_minus() {
        Cube_block ** side[8] = {
            &
            data[0][0][0],
            &
            data[0][1][0],
            &
            data[0][2][0],
            &
            data[0][2][1],
            &
            data[0][2][2],
            &
            data[0][1][2],
            &
            data[0][0][2],
            &
            data[0][0][1]
        };

        rotate_list(side, "X-", "X+");
    }

    void rotate_x_minus() {
        Cube_block ** side[8] = {
            &
            data[2][0][0],
            &
            data[2][1][0],
            &
            data[2][2][0],
            &
            data[2][2][1],
            &
            data[2][2][2],
            &
            data[2][1][2],
            &
            data[2][0][2],
            &
            data[2][0][1]
        };

        rotate_list(side, "X-", "X+");
    }

    void rotate_X_plus() {
        Cube_block ** side[8] = {
            &
            data[0][0][0],
            &
            data[0][1][0],
            &
            data[0][2][0],
            &
            data[0][2][1],
            &
            data[0][2][2],
            &
            data[0][1][2],
            &
            data[0][0][2],
            &
            data[0][0][1]
        };

        rotate_list(side, "X+", "X-");
    }

    void rotate_x_plus() {
        Cube_block ** side[8] = {
            &
            data[2][0][0],
            &
            data[2][1][0],
            &
            data[2][2][0],
            &
            data[2][2][1],
            &
            data[2][2][2],
            &
            data[2][1][2],
            &
            data[2][0][2],
            &
            data[2][0][1]
        };

        rotate_list(side, "X+", "X-");
    }

    void rotate_Z_minus() {
        Cube_block ** side[8] = {
            &
            data[0][0][0],
            &
            data[1][0][0],
            &
            data[2][0][0],
            &
            data[2][1][0],
            &
            data[2][2][0],
            &
            data[1][2][0],
            &
            data[0][2][0],
            &
            data[0][1][0]
        };

        rotate_list(side, "Z-", "Z+");
    }

    void rotate_z_minus() {
        Cube_block ** side[8] = {
            &
            data[0][0][2],
            &
            data[1][0][2],
            &
            data[2][0][2],
            &
            data[2][1][2],
            &
            data[2][2][2],
            &
            data[1][2][2],
            &
            data[0][2][2],
            &
            data[0][1][2]
        };

        rotate_list(side, "Z-", "Z+");
    }

    void rotate_Z_plus() {
        Cube_block ** side[8] = {
            &
            data[0][0][0],
            &
            data[1][0][0],
            &
            data[2][0][0],
            &
            data[2][1][0],
            &
            data[2][2][0],
            &
            data[1][2][0],
            &
            data[0][2][0],
            &
            data[0][1][0]
        };

        rotate_list(side, "Z+", "Z-");
    }

    void rotate_z_plus() {
        Cube_block ** side[8] = {
            &
            data[0][0][2],
            &
            data[1][0][2],
            &
            data[2][0][2],
            &
            data[2][1][2],
            &
            data[2][2][2],
            &
            data[1][2][2],
            &
            data[0][2][2],
            &
            data[0][1][2]
        };

        rotate_list(side, "Z+", "Z-");
    }

    void construct() {
        data = new Cube_block ** * [3];
        for (int X = 0; X < 3; X++) {
            data[X] = new Cube_block ** [3];
            for (int Y = 0; Y < 3; Y++) {
                data[X][Y] = new Cube_block * [3];
                for (int Z = 0; Z < 3; Z++) {
                    char name[5];
                    name[0] = X + '0';
                    name[1] = Y + '0';
                    name[2] = Z + '0';
                    name[3] = 0;
                    data[X][Y][Z] = new Cube_block(name);
                }
            }
        }

        fill_with_zeros();
    }

    void deconstruct() {
        for (int X = 0; X < 3; X++) {
            for (int Y = 0; Y < 3; Y++) {
                for (int Z = 0; Z < 3; Z++) {
                    delete data[X][Y][Z];
                }

                delete data[X][Y];
            }

            delete[] data[X];
        }

        delete[] data;
    }

public:
    Cube() {
        construct();
        protocol = (char * ) malloc(1);
        protocol[0] = 0;
    }

    void save_to_file(char * input_filename) {
        ofstream stream(input_filename);
        cube_to_color_array();

        for (auto & color: colors) {
            stream << color << endl;
        }

        stream << protocol << endl;
        stream.close();
    }

    bool load_from_file(char * input_filename) {
        char buffer_row[2048];
        ifstream stream(input_filename);
        if (!stream.is_open()) {
            return false;
        }

        for (auto & color: colors) {
            stream.getline(color, 7);
        }

        stream.getline(buffer_row, sizeof(buffer_row));
        protocol = new char[strlen(buffer_row) + 1];
        strcpy(protocol, buffer_row);
        stream.close();

        color_array_to_cube();
        return true;
    }

    bool solving = false;

    void rotate(char * input_command) {
        if (strcmp(input_command, "X+") == 0) {
            rotate_X_plus();
        }

        if (strcmp(input_command, "X-") == 0) {
            rotate_X_minus();
        }

        if (strcmp(input_command, "x+") == 0) {
            rotate_x_plus();
        }

        if (strcmp(input_command, "x-") == 0) {
            rotate_x_minus();
        }

        if (strcmp(input_command, "Y+") == 0) {
            rotate_Y_plus();
        }

        if (strcmp(input_command, "Y-") == 0) {
            rotate_Y_minus();
        }

        if (strcmp(input_command, "y+") == 0) {
            rotate_y_plus();
        }

        if (strcmp(input_command, "y-") == 0) {
            rotate_y_minus();
        }

        if (strcmp(input_command, "Z+") == 0) {
            rotate_Z_plus();
        }

        if (strcmp(input_command, "Z-") == 0) {
            rotate_Z_minus();
        }

        if (strcmp(input_command, "z+") == 0) {
            rotate_z_plus();
        }

        if (strcmp(input_command, "z-") == 0) {
            rotate_z_minus();
        }

        modify_protocol(input_command);
    }

    void paint(int X0, int Y0, int cur_size) {
        int size_callback = cur_size * 2;
        int X1, Y1;

        X1 = X0 + size_callback;
        Y1 = Y0;
        for (int X = 0; X < 3; X++)
            for (int Z = 0; Z < 3; Z++)
                data[X][0][Z] -> paint(X1 + X, Y1 + Z, cur_size, "Y");

        X1 = X0;
        Y1 = Y0 + size_callback;
        for (int Y = 0; Y < 3; Y++)
            for (int Z = 0; Z < 3; Z++)
                data[2][Y][Z] -> paint(X1 + Z, Y1 + Y, cur_size, "X-");

        X1 = X0 + size_callback;
        Y1 = Y0 + size_callback;
        for (int X = 0; X < 3; X++)
            for (int Y = 0; Y < 3; Y++)
                data[X][Y][2] -> paint(X1 + X, Y1 + Y, cur_size, "Z-");

        X1 = X0 + 2 * size_callback;
        Y1 = Y0 + size_callback;
        for (int Y = 0; Y < 3; Y++)
            for (int Z = 0; Z < 3; Z++)
                data[0][Y][Z] -> paint(X1 + Z, Y1 + Y, cur_size, "X+");

        X1 = X0 + 3 * size_callback;
        Y1 = Y0 + size_callback;
        for (int X = 0; X < 3; X++)
            for (int Y = 0; Y < 3; Y++)
                data[X][Y][0] -> paint(X1 + X, Y1 + Y, cur_size, "Z+");

        X1 = X0 + size_callback;
        Y1 = Y0 + 2 * size_callback;
        for (int X = 0; X < 3; X++)
            for (int Z = 0; Z < 3; Z++)
                data[X][2][Z] -> paint(X1 + X, Y1 + Z, cur_size, "Y-");
    }

    char * protocol;

    void modify_protocol(char * buffer) {
        int length = strlen(buffer);
        int protocol_length = strlen(protocol);

        if (solving) {
            protocol = (char * ) realloc(protocol, protocol_length - length + 1);
            protocol[protocol_length - length] = 0;
            return;
        }

        protocol = (char * ) realloc(protocol, protocol_length + length + 1);
        strcpy( & protocol[protocol_length], buffer);
        optimize_protocol();
    }

    void optimize_protocol() const {
        int length = strlen(protocol);
        if (length < 4) return;
        if (protocol[length - 2] != protocol[length - 4]) return;
        if (protocol[length - 1] == protocol[length - 3]) return;
        protocol[length - 4] = 0;
    }

    int distance(Cube * other) {
            int result = 0;
            for (int X = 0; X < 3; X++)
                for (int Y = 0; Y < 3; Y++)
                    for (int Z = 0; Z < 3; Z++) {
                        int are_equal = 1;
                        if ((X == 1) || (Y == 1) || (Z == 1)) {
                            are_equal *= 2;
                        }

                        if (!Cube_block::Identical(data[X][Y][Z], other -> data[X][Y][Z]))
                            result += are_equal;
                    }

            return result;
        }

    ~Cube() {
        deconstruct();
        free(protocol);
    }
};
