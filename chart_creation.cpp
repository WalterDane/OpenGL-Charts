#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <array>

int window_size = 500;
int point_size = 5;
int line_size = 6;
int min_num = 0;
int max_num = 0;
int scale_factor = 0;

void draw_point(vector<int>& points)
{
    ofstream output("output.txt");
    if (output.is_open())
    {
        for (int i = 0; i < points.size(); i++)
        {
            output << "draw_point " << point_size << " " << 500 / points.size() * (i + 1) << " " << points[i] * scale_factor << endl;
        }
    }
    output.close();
}

void draw_line(vector<int>& points)
{
    ofstream output("output.txt");
    if (output.is_open())
    {
        for (int i = 0; i <= points.size() - 2; i++)
        {
            output << "draw_line " << line_size << " "
                << 500 / points.size() * (i + 1)
                << " " << points[i] * scale_factor
                << " " << 500 / points.size() * (i + 2)
                << " " << points[i + 1] * scale_factor << endl;
        }
    }
    output.close();
}


void draw_polygon(vector<int>& points, string& chart_type)
{
    ofstream output("output.txt");
    if (output.is_open())
    {
        if (chart_type == "column")
        {
            for (int i = 0; i < points.size(); i++)
            {
                output << "draw_polygon " << ((500 / points.size()) * (i + 1)) - 12 << " " << points[i] * scale_factor << " " << (500 / points.size() * (i + 1)) + 12 << " " << points[i] * scale_factor << " " << ((500 / points.size() * (i + 1))) + 12 << " " << 0 << " " << ((500 / points.size()) * (i + 1)) - 12 << " " << 0 << " " << endl;
            }
        }
        if (chart_type == "area")
        {
            {
                for (int i = 0; i < points.size() - 2; i++)
                {
                    output << "draw_polygon " << ((500 / points.size()) * (i + 1)) << " " << 0 << " "
                        << ((500 / points.size()) * (i + 1)) << " " << points[i] * scale_factor << " "
                        << ((500 / points.size()) * (i + 2)) << " " << points[i + 1] * scale_factor << " "
                        << ((500 / points.size()) * (i + 2)) << " " << 0 << endl;
                }
            }
        }
    }
    output.close();
}

int main(int argc, char* argv[])
{
    string data_file;
    string chart_type;
    cout << "Enter the name of your data file (make sure it's provided in the same directory). Please provide the .txt extension: ";
    cin >> data_file;
    cout << "What kind of chart would you like to create (point, column, line, area): ";
    cin >> chart_type;

    string values;
    ifstream file;
    file.open(data_file);
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            values = line; //Get the first
            file.close();
        }
    }
    else cout << "Unable to open file";

    vector<int> points;
    stringstream ss(values);
    string intermediate;

    while (getline(ss, intermediate, ' '))
    {
        points.push_back(stoi(intermediate));
    }

    //find the min_num_numimum and max_numimum values for scaling to window size
    max_num = points[0];
    min_num = points[0];
    for (int i = 1; i < points.size(); i++)
    {
        if (points[i] > max_num)
        {
            max_num = points[i];
        }

        if (points[i] < min_num)
        {
            min_num = points[i];
        }
    }
    cout << "Max: " << max_num << endl;
    cout << "Min: " << min_num << endl;
    scale_factor = window_size / max_num;

    if (chart_type == "point")
    {
        for (int i = 0; i < points.size() - 1; i++)
        {
            draw_point(points);
        }
    }
    if (chart_type == "line")
    {
        for (int i = 0; i < points.size() - 1; i++)
        {
            draw_line(points);
        }
    }
    if (chart_type == "column")
    {
        for (int i = 0; i < points.size() - 1; i++)
        {
            draw_polygon(points, chart_type);
        }
    }
    if (chart_type == "area")
    {
        for (int i = 0; i < points.size() - 1; i++)
        {
            draw_polygon(points, chart_type);
        }
    }

    cout << "Please run the opengl program to display the chart" << endl;
}