#pragma once

#include <Windows.h>
#include <iostream>

#define BACKGROUND_WHITE (BACKGROUND_RED + BACKGROUND_GREEN + BACKGROUND_BLUE)
#define BACKGROUND_YELLOW (BACKGROUND_RED + BACKGROUND_GREEN)

class ScreenIO {
public:
    ScreenIO() = default;

    inline static void go_to_XY(int input_X, int input_Y) {
        COORD screen;
        HANDLE handle_output = GetStdHandle(STD_OUTPUT_HANDLE);
        screen.X = input_X;
        screen.Y = input_Y;
        SetConsoleCursorPosition(handle_output, screen);
    }

    inline static void set_foreground(int foreground, int background) {
        HANDLE handle_output = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle_output, foreground + background);
    }

    inline static void set_color(int color, int HighLight = BACKGROUND_INTENSITY) {
        HANDLE handle_output = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle_output, color + HighLight);
        cout << " ";
    }

    inline static void set_color(char cur_color) {
        switch (cur_color) {
        case 'B':
            set_color(BACKGROUND_BLUE);
            break;
        case 'W':
            set_color(BACKGROUND_WHITE);
            break;
        case 'R':
            set_color(BACKGROUND_RED);
            break;
        case 'G':
            set_color(BACKGROUND_GREEN);
            break;
        case 'Y':
            set_color(BACKGROUND_YELLOW);
            break;
        case 'O':
            set_color(BACKGROUND_YELLOW, 0);
            break;

        default:
            set_color(0);
            break;
        }
    }

    inline static void set_color(int input_X, int input_Y, char color) {
        go_to_XY(2 * input_X, input_Y);
        set_color(color);
    }

    ~ScreenIO() = default;
};
