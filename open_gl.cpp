#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <array>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string>
using namespace std;

int buffer = 16;
//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, 532, 0, 500);
}

//---------------------------------------
// Set Color Function
// This command sets the color of the graphics program
// All objects drawn after this command will be displayed with this color 
// Using the set_color command will override other set_color commands
// The color values for R, G, B are floating point values between 0 and 1, where 0 = black and 1 = full color
//---------------------------------------
void set_color(float red, float green, float blue)
{
    glColor3f(red, green, blue);
}

//---------------------------------------
// Draw Point Function
// This command draws a point of the specified size at the specified location.
// Size value should be an integer between 1 and 10. 
// The x,y coordinates should be integers between [0..width-1] and [0..height-1] respectively.
//---------------------------------------
void draw_point(int size, int x, int y)
{
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex2f(x, y + buffer);
    glEnd();
}

void draw_line(int width, int x1, int y1, int x2, int y2)
{
        glLineWidth(width);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
}

void draw_polygon(vector<int>& polygon_values)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i <= polygon_values.size() - 1; i += 2)
    {
        glVertex2f(polygon_values[i] + buffer, polygon_values[i + 1] + buffer);
    }
    glEnd();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //draw the lines for the chart
    set_color(1.0, 1.0, 1.0);
    draw_line(1, 10, 16, 516, 16);
    draw_line(1, 10, 62, 516, 62);
    draw_line(1, 10, 108, 516, 108);
    draw_line(1, 10, 154, 516, 154);
    draw_line(1, 10, 200, 516, 200);
    draw_line(1, 10, 246, 516, 246);
    draw_line(1, 10, 292, 516, 292);
    draw_line(1, 10, 338, 516, 338);
    draw_line(1, 10, 384, 516, 384);
    draw_line(1, 10, 430, 516, 430);
    draw_line(1, 10, 476, 516, 476);
    draw_line(1, 16, 10, 16, 484);

    ifstream file;
    file.open("output.txt");
    string line;
    vector<string> input; //input is the output from first program
    if (file.is_open())
    {
        while (getline(file, line))
        {
            input.push_back(line);
        }
        file.close();
    }
    else cout << "Unable to open file";

    for (int i = 0; i < input.size(); i++)
    {
        vector<string> tokens;
        stringstream ss(input[i]);
        string intermediate;

        while (getline(ss, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }

        if (tokens[0] == "set_color")
        {
            cout << "calling set_color function" << endl;
            vector<float> rgb_values;
            for (int i = 1; i <= tokens.size() - 1; i++)
            {
                rgb_values.push_back(stof(tokens[i]));
            }
            set_color(rgb_values[0], rgb_values[1], rgb_values[2]);
        }
        if (tokens[0] == "draw_line")
        {
            cout << "calling draw_line function" << endl;
            vector<int> line_values;
            for (int i = 1; i <= tokens.size() - 1; i++)
            {
                line_values.push_back(stoi(tokens[i]));
            }
            draw_line(line_values[0], line_values[1], line_values[2] + buffer, line_values[3], line_values[4] + buffer);
        }
        if (tokens[0] == "draw_point")
        {
            vector<int> point_values;
            for (int i = 1; i <= tokens.size() - 1; i++)
            {
                point_values.push_back(stoi(tokens[i]));
            }
            draw_point(point_values[0], point_values[1], point_values[2]);
        }
        if (tokens[0] == "draw_polygon")
        {
            cout << "calling draw_polygon function" << endl;
            vector<int> polygon_values;
            for (int i = 1; i <= tokens.size() - 1; i++)
            {
                polygon_values.push_back(stoi(tokens[i]));
            }
            draw_polygon(polygon_values);
        }
    }
    glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char* argv[])
{
    glutInit(&argc, argv); //initializes the system
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //requests properties for the window
    glutInitWindowSize(516, 500);
    glutInitWindowPosition(250, 250);
    glutCreateWindow("Chart"); //creates the window with the title simple
    glutDisplayFunc(display); //display callback

    init(); //set OpenGL state

    glutMainLoop(); //enter event loop

    return 0;
}