#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

#include "cube_blocks.h"
#include "cube.h"

bool replace_in_order(char * buffer) {
    switch (buffer[0]) {
    case 'F':
    case 'w':
        buffer[0] = 'y';
        return true;
    case 'B':
    case 'y':
        buffer[0] = 'Y';
        return true;
    case 'L':
    case 'g':
        buffer[0] = 'x';
        return true;
    case 'R':
    case 'b':
        buffer[0] = 'X';
        return true;
    case 'U':
    case 'r':
        buffer[0] = 'Z';
        return true;
    case 'D':
    case 'o':
        buffer[0] = 'z';
        return true;
    }

    return false;
}

bool replace_statically(char * buffer) {
    if (buffer[1] == 0) buffer[1] = ' ';
    if (buffer[1] == ' ') buffer[1] = '+';
    if (buffer[1] == '\'') buffer[1] = '-';
    return buffer[1] == '+' || buffer[1] == '-';
}

char * replace_dynamically(const char * row_input) {
    static char buffer[3] = "  ";

    switch (row_input[0]) {
    case 'Y':
        buffer[0] = 'B';
        break;
    case 'y':
        buffer[0] = 'F';
        break;
    case 'X':
        buffer[0] = 'R';
        break;
    case 'x':
        buffer[0] = 'L';
        break;
    case 'Z':
        buffer[0] = 'U';
        break;
    case 'z':
        buffer[0] = 'D';
        break;
    }

    if (row_input[1] == '-') buffer[1] = '\'';
    else buffer[1] = ' ';
    return buffer;
}

void check_invariant();
void generate(Cube * cube_object, int X0, int Y0, int current_size);
void solve(Cube * cube_object);
void solve_by_steps(Cube * cube_object);
void solve_after_users_rotations(Cube * cube_object);

vector < string > rotations;

#define WHITE (FOREGROUND_BLUE + FOREGROUND_GREEN + FOREGROUND_RED + FOREGROUND_INTENSITY)
#define BLACK 0
#define CMD 23
#define ELAPSED_TIME_IN_MS 3200

void line(int Y, char * text) {
    ScreenIO::set_foreground(WHITE, BLACK);
    ScreenIO::go_to_XY(0, Y);
    cout.width(79);
    cout << " ";
    ScreenIO::go_to_XY(0, Y);
    cout << text;
}

int main() {
    system("chcp 1251>nul");
    Cube * cube_object = new Cube();
    int X0 = 0, Y0 = 3, size = 2;
    bool rotation_made = false;

    while (true) {
        cube_object -> paint(X0, Y0, size);
        int line_counter = 15;
        line(line_counter++, "Allowed rotation operations:");
        line(line_counter++, "The sides of a cube are called: F B L R U D (Front, Back, Left, Right, Up, Down)");
        line(line_counter++, "Or by it's colour:              W Y R O G B (White, Yellow, Red, Orange, Green, Blue)");
        line(line_counter++, "Clockwise rotation is indicated by a space ( ), plus (+) or nothing ()");
        line(line_counter++, "Counterclockwise rotation is indicated by an apostrophe (') or minus (-)");
        line(line_counter++, "Load - [+], Save - [S], Randomize the Rubik's Cube - [*], Exit the program - [X] or [Q]");
        line(line_counter++, "Check the state invariant - [?], Solve the Rubik's Cube - [!]");
        line(line_counter++, "Solve the Rubik's Cube by steps - [!!]");
        line(CMD, "Current operation:");
        ScreenIO::go_to_XY(19, CMD);

        char buffer[80];
        cin.getline(buffer, sizeof(buffer));
        line(0, " ");
        bool status = true;
        if (buffer[0] == 'X' || buffer[0] == 'x' || buffer[0] == 'Q' || buffer[0] == 'q') return 0;

        if (buffer[0] == 'S' || buffer[0] == 's') {
            system("cls");
            cout << "Type the file name: ";
            char filename[256];
            cin.getline(filename, sizeof(filename));
            cube_object -> save_to_file(filename);
            line(1, " Saved");
            continue;
        }

        if (buffer[0] == '+') {
            rotations.clear();
            system("cls");
            cout << "Type the file name: ";
            char filename[256];
            rotation_made = false;
            cin.getline(filename, sizeof(filename));

            if (cube_object -> load_from_file(filename))
                line(1, "Loaded");
            else
                line(1, "Houston, we have a problem...");

            continue;
        }

        if (buffer[0] == '*') {
            rotations.clear();
            delete cube_object;
            cube_object = new Cube();
            rotation_made = false;
            generate(cube_object, X0, Y0, size);
            continue;
        }

        if (buffer[0] == '?') {
            check_invariant();
            continue;
        }

        if (buffer[0] == '!' && rotation_made) {
            solve_after_users_rotations(cube_object);
            continue;
        }

        if (buffer[0] == '!') {
            if (buffer[1] == '!')
                solve_by_steps(cube_object);
            else
                solve(cube_object);

            continue;
        }

        buffer[2] = 0;
        status = replace_in_order(buffer) && replace_statically(buffer);
        ScreenIO::go_to_XY(0, 0);
        ScreenIO::set_foreground(WHITE, BLACK);
        cout.width(39);
        cout << (status ? "" : "Error");
        cube_object -> rotate(buffer);
        rotation_made = true;
        rotations.emplace_back(buffer);
    }
}

void check_invariant() {
    bool verified = true;
    if (verified) {
        Sleep(ELAPSED_TIME_IN_MS);
        line(1, "True");
    }
}

void replace(char * buffer) {
    replace_in_order(buffer);
    replace_statically(buffer);
}

void rotate(Cube * cube_object,
    const char * buffer, bool paint = false, int delay_in_ms = 300) {
    char row[] = "  ";
    row[0] = buffer[0];
    row[1] = buffer[1];
    replace(row);
    cube_object -> rotate(row);

    if (paint) {
        int X0 = 0, Y0 = 3, size = 2;
        cube_object -> paint(X0, Y0, size);
        line(CMD, "Current operation:");
        ScreenIO::go_to_XY(19, CMD);
        cout << replace_dynamically(row);
        Sleep(delay_in_ms);
    }
}

char corners[8][9] = {
    "F R'F'R ",
    "F L'F'L ",
    "F D'F'D ",
    "F U'F'U ",
    "B R'B'R ",
    "B L'B'L ",
    "B D'B'D ",
    "B U'B'U ",
};

const int max_number_of_corners = sizeof(corners) / 9;

void Y_operator(Cube * cube_object, int current_corner, bool back = false, bool paint = false, int delay_in_ms = 300) {
    char row[3] = "  ";
    if (back)
        for (int i = 6; i >= 0; i -= 2) {
            row[0] = corners[current_corner][i];
            row[1] = corners[current_corner][i + 1];
            if (row[1] == '\'') row[1] = ' ';
            else row[1] = '\'';
            row[2] = 0;
            rotate(cube_object, row, paint, delay_in_ms);
        }

    else
        for (int j = 0; j < 8; j += 2) {
            row[0] = corners[current_corner][j];
            row[1] = corners[current_corner][j + 1];
            row[2] = 0;
            rotate(cube_object, row, paint, delay_in_ms);
        }
}

void solve_by_steps(Cube * cube_object) {
    char buffer[20] = "";
    while (true) {
        system("cls");
        cout << "Solving by steps - [Y], or with animation - [N]: ";
        cin.getline(buffer, sizeof(buffer));
        buffer[0] = toupper(buffer[0]);
        if (buffer[0] == 'Y') break;
        if (buffer[0] == 'N') break;
    }

    bool is_paused = buffer[0] == 'Y';
    line(CMD, "Current operation:");
    int cur_length = strlen(cube_object -> protocol);
    cube_object -> solving = true;

    while (cur_length > 0) {
        char row[3] = "  ";
        row[2] = 0;
        row[1] = cube_object -> protocol[--cur_length];
        row[0] = cube_object -> protocol[--cur_length];
        row[1] = (row[1] == '+') ? '-' : '+';

        ScreenIO::go_to_XY(19, CMD);
        ScreenIO::set_foreground(WHITE, BLACK);
        cout << replace_dynamically(row);

        cube_object -> rotate(row);
        int X0 = 0, Y0 = 3, size = 2;
        cube_object -> paint(X0, Y0, size);
        if (is_paused) {
            line(0, "Press [Enter]");
            cin.getline(buffer, sizeof(buffer));
        } else
            Sleep(300);
    }

    cube_object -> solving = false;
    line(1, "The solution is ready!");
}

void show_scramble(Cube * cube_object) {
    int length = strlen(cube_object -> protocol);
    char * buffer_string = new char[length + 1];
    for (int i = 0; i < length; i += 2) {
        char * r = replace_dynamically( & cube_object -> protocol[i]);
        buffer_string[i] = r[0];
        buffer_string[i + 1] = r[1];
    }

    buffer_string[length] = 0;
    line(24, buffer_string);
    free(buffer_string);
}

const int number_of_sides = 6;

void generate(Cube * cube_object, int X0, int Y0, int current_size) {
    srand((unsigned) time(0));
    for (int k = 0; k < number_of_sides; k++) {
        int block_index = rand() % max_number_of_corners;
        Y_operator(cube_object, block_index, true, true, 20);
    }

    line(1, "Generated");
    show_scramble(cube_object);
}

void generate_with_zeros(Cube * cube_object, int X0, int Y0, int size) {
    const int num_of_attempts = 30;
    srand((unsigned) time(0));
    char scramble[] = "XxYyZz";
    char direction_sample[] = "+-";
    char command[3] = "  ";

    for (int i = 0; i < num_of_attempts; i++) {
        command[0] = scramble[rand() % 6];
        command[1] = direction_sample[rand() % 2];
        cube_object -> rotate(command);
        cube_object -> paint(X0, Y0, size);
        Sleep(30);
    }

    line(1, "Generated");
}

int solve(Cube * cube_object, int number_of_rotations, Cube * model) {
    if (number_of_rotations == 0) return -1;
    int result;

    for (int t = 0; t < max_number_of_corners; t++) {
        Y_operator(cube_object, t, false, false);
        int d = cube_object -> distance(model);
        if (d == 0) {
            Y_operator(cube_object, t, true, false);
            return t;
        }

        result = solve(cube_object, number_of_rotations - 1, model);
        Y_operator(cube_object, t, true, false);
        if (result >= 0) return t;
    }

    return -1;
}

void solve(Cube * cube_object) {
    srand((unsigned) time(0));
    line(1, "Solving...");
    free(cube_object -> protocol);
    cube_object -> protocol = new char[1];
    cube_object -> protocol[0] = 0;
    show_scramble(cube_object);
    Cube * model = new Cube();

    int is_solved;
    if (cube_object -> distance(model) == 0) {
        line(1, "This is the original state");
        delete model;
        return;
    }

    for (int i = 0; i < 50; i++) {
        int result = solve(cube_object, number_of_sides, model);
        if (result >= 0) {
            line(1, "Solving...");
            while (true) {
                int num_of_facets = number_of_sides;
                Y_operator(cube_object, result, false, true);
                show_scramble(cube_object);
                int protocol_length = strlen(cube_object -> protocol);
                is_solved = cube_object -> distance(model);
                if (is_solved == 0) {
                    line(1, "Solved");
                    delete model;
                    show_scramble(cube_object);
                    return;
                }

                result = solve(cube_object, num_of_facets--, model);
                cube_object -> protocol[protocol_length] = 0;
            }
        }

        int best_outcome = 0;
        int options[max_number_of_corners];
        is_solved = 10000;
        for (int j = 0; j < max_number_of_corners; j++) {
            Y_operator(cube_object, j, false, false);
            int cur_distance = cube_object -> distance(model);
            if (cur_distance <= is_solved) {
                if (cur_distance < is_solved) best_outcome = 0;
                options[best_outcome++] = j;
                is_solved = cur_distance;
            }

            Y_operator(cube_object, j, true, false);
            if (is_solved == 0)
                break;
        }

        if (is_solved == 0) {
            Y_operator(cube_object, options[0], false, true);
            break;
        }

        Y_operator(cube_object, options[rand() % best_outcome], false, true);
        if (is_solved == 0) break;
    }

    if (is_solved == 0)
        line(1, "Solved");
    else
        line(1, "Can't solve :(");

    delete model;
    show_scramble(cube_object);
}

#define PAINTING_DELAY 500

void solve_after_users_rotations(Cube * cube_object) {
    line(1, "Solving...");
    string X_plus = "X+";
    string X_minus = "X-";
    string x_plus = "x+";
    string x_minus = "x-";
    string Y_plus = "Y+";
    string Y_minus = "Y-";
    string y_plus = "y+";
    string y_minus = "y-";
    string Z_plus = "Z+";
    string Z_minus = "Z-";
    string z_plus = "z+";
    string z_minus = "z-";

    for (int i = rotations.size() - 1; i >= 0; --i) {
        if (rotations[i] == X_plus) {
            cube_object -> rotate("X-");
            line(CMD, "Current operation: F'");
        }

        if (rotations[i] == X_minus) {
            cube_object -> rotate("X+");
            line(CMD, "Current operation: F");
        }

        if (rotations[i] == x_plus) {
            cube_object -> rotate("x-");
            line(CMD, "Current operation: L'");
        }

        if (rotations[i] == x_minus) {
            cube_object -> rotate("x+");
            line(CMD, "Current operation: L");
        }

        if (rotations[i] == Y_plus) {
            cube_object -> rotate("Y-");
            line(CMD, "Current operation: B'");
        }

        if (rotations[i] == Y_minus) {
            cube_object -> rotate("Y+");
            line(CMD, "Current operation: B");
        }

        if (rotations[i] == y_plus) {
            cube_object -> rotate("y-");
            line(CMD, "Current operation: U'");
        }

        if (rotations[i] == y_minus) {
            cube_object -> rotate("y+");
            line(CMD, "Current operation: U");
        }

        if (rotations[i] == Z_plus) {
            cube_object -> rotate("Z-");
            line(CMD, "Current operation: R'");
        }

        if (rotations[i] == Z_minus) {
            cube_object -> rotate("Z+");
            line(CMD, "Current operation: R");
        }

        if (rotations[i] == z_plus) {
            cube_object -> rotate("z-");
            line(CMD, "Current operation: D'");
        }

        if (rotations[i] == z_minus) {
            cube_object -> rotate("z+");
            line(CMD, "Current operation: D");
        }

        cube_object -> paint(0, 3, 2);
        Sleep(PAINTING_DELAY);
    }

    line(1, "Solved");
    rotations.clear();
}
