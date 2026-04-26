#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(t) Sleep(t * 1000)
#define CLEAR_SCREEN() system("cls")
#else
#include <unistd.h>
#define SLEEP(t) sleep(t)
#define CLEAR_SCREEN() system("clear")
#endif

#define HEIGHT 50
#define WIDTH 100
#define VIEW_MIN 0.0
#define VIEW_MAX 50.0

int make_screen_array(char *screen_buffer);
int draw_symbol(int ball_x, int ball_y, char *screen_buffer, char symbol);
double ask_data(char *question);
int *calc_y_bounds(double slope, double y_intercept);
int draw_Graph(double slope, double y_intercept);
int draw_max_min_scale(int *bounds, char *screen_buffer);
int drawParabola(double a, double b, double c);
int slope();
int parabola();


int main() {

    int choice = (int)ask_data("1 for Linear, 2 for Parabola");

    switch(choice) {
        case 1:
        slope();
        break;

        case 2:
        parabola();
        break;

        default :
        printf("Invalid choice, please choose again.");
        break;
    }

    SLEEP(5); 
    CLEAR_SCREEN();
    printf("\x1b[?25h"); 

    return 0;
}

int slope() {
    double slope = ask_data("Enter Slope:");
    double y_intercept = ask_data("y_intercept:");

    printf("\x1b[8;%d;%dt", HEIGHT + 2, WIDTH + 5); 
    printf("\x1b[?25l"); 
    CLEAR_SCREEN();

    draw_Graph(slope, y_intercept);

    return 0;
}

int parabola() {
    double a = ask_data("a (curvature)");
    double b = ask_data("b (slope)");
    double c = ask_data("c (intercept)");

    CLEAR_SCREEN();

    drawParabola(a, b, c);

    return 0;
} 

// SCREEN BUFFER
int make_screen_array(char *screen_buffer) {
    int i = 0;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen_buffer[i++] = ' ';
        }
        screen_buffer[i++] = '\n';
    }
    screen_buffer[i] = '\0';
    return 0;
}

int draw_symbol(int x, int y, char *screen_buffer, char symbol) {
    // Invert Y for screen coordinates (0 is bottom)
    int screen_y = (HEIGHT - 1) - y;
    
    if (x < 0 || x >= WIDTH || screen_y < 0 || screen_y >= HEIGHT) {
        return 1;
    }
 
    int location = screen_y * (WIDTH + 1) + x;
    screen_buffer[location] = symbol;
    return 0;
}

// GIMMME THAT DATA
double ask_data(char *question) {
    while (1) {
        char input_buffer[64];
        printf("Enter %s: ", question);
        fgets(input_buffer, 64, stdin);

        char *temp_pointer;
        double output = strtod(input_buffer, &temp_pointer);

        if (temp_pointer != input_buffer) {
            return output;
        } else {
            printf("Please enter a valid number!\n");
        }
    }
}

// CALCULATE THE BOUNDS
int *calc_y_bounds(double slope, double y_intercept) {
    int *arr = malloc(2 * sizeof(int));
    arr[0] = INT_MAX;
    arr[1] = INT_MIN;

    for (int i = 0; i < WIDTH; i++) {
        int y = (int)(slope * i + y_intercept);
        if (y > arr[1]) arr[1] = y;
        if (y < arr[0]) arr[0] = y;
    }
    return arr;
}

// DRAW THE GRAPHS
int draw_Graph(double slope, double y_intercept) {
    char *screen_buffer = malloc((WIDTH + 1) * HEIGHT + 1);
    make_screen_array(screen_buffer);
    int *bounds = calc_y_bounds(slope, y_intercept);

    // Plot X-axis using Fixed View
    double x_axis_r = (0.0 - VIEW_MIN) / (VIEW_MAX - VIEW_MIN);
    int x_axis_location = (int)((HEIGHT - 1) * x_axis_r);
    
    if (x_axis_location < 0) x_axis_location = 0;
    if (x_axis_location >= HEIGHT) x_axis_location = HEIGHT - 1;
    
    for (int i = 0; i < WIDTH; i++) {
        draw_symbol(i, x_axis_location, screen_buffer, '-');
    }

    // Plot Line using Fixed View
    for (int i = 0; i < WIDTH; i++) {
        double y = slope * i + y_intercept;
        
        // Normalize based on VIEW_MIN/MAX
        int normal_y = (int)((HEIGHT - 1) * ((y - VIEW_MIN) / (VIEW_MAX - VIEW_MIN)));

        // Only draw if it's actually on the screen
        if (normal_y >= 0 && normal_y < HEIGHT) {
            draw_symbol(i, normal_y, screen_buffer, 'o');
        }
    }

    draw_max_min_scale(bounds, screen_buffer);

    free(screen_buffer);
    free(bounds);
    return 0;
}

int draw_max_min_scale(int *bounds, char *screen_buffer) {
    char min_s[20], max_s[20];
    sprintf(min_s, "%d", bounds[0]);
    sprintf(max_s, "%d", bounds[1]);

    // Copy Max to top-left (location 0)
    memcpy(screen_buffer, max_s, strlen(max_s));
    
    // Copy Min to bottom-left
    int min_loc = (HEIGHT - 1) * (WIDTH + 1);
    memcpy(&screen_buffer[min_loc], min_s, strlen(min_s));

    printf("\x1b[H%s", screen_buffer); 
    fflush(stdout);
    return 0;
}

// --------------- QUADRATIC ------------ //
int drawParabola(double a, double b, double c) {
    char *screen_buffer = malloc((WIDTH + 1) * HEIGHT + 1);
    make_screen_array(screen_buffer);
    int *bounds = calc_y_bounds(a, b);

    // Plot X-axis using Fixed View
    double x_axis_r = (0.0 - VIEW_MIN) / (VIEW_MAX - VIEW_MIN);
    int x_axis_location = (int)((HEIGHT - 1) * x_axis_r);
    
    if (x_axis_location < 0) x_axis_location = 0;
    if (x_axis_location >= HEIGHT) x_axis_location = HEIGHT - 1;
    
    for (int i = 0; i < WIDTH; i++) {
        draw_symbol(i, x_axis_location, screen_buffer, '-');
    }

    // Plot Line using Fixed View
    for (int i = 0; i < WIDTH; i++) {
        double y = (a * i * i) + (b * i) + c;
        
        // Normalize based on VIEW_MIN/MAX
        int normal_y = (int)((HEIGHT - 1) * ((y - VIEW_MIN) / (VIEW_MAX - VIEW_MIN)));

        // Only draw if it's actually on the screen
        if (normal_y >= 0 && normal_y < HEIGHT) {
            draw_symbol(i, normal_y, screen_buffer, 'o');
        }
    }

    draw_max_min_scale(bounds, screen_buffer);

    free(screen_buffer);
    free(bounds);
    return 0;
}