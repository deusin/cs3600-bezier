#pragma once
#include "glm/glm.hpp"
#include "GL/freeglut.h"

class Bezier
{
public:
    glm::vec2 Points[4];
    float ControlPointRadius = 10.0;
    float red, green, blue;
    bool selected = false;

    Bezier(float startingX, float startingY)
    {
        glm::vec2 right;
        right.x = 100;
        right.y = 0;

        Points[0].x = startingX;
        Points[0].y = startingY;

        Points[1] = Points[0] + right;
        Points[2] = Points[1] + right;
        Points[3] = Points[2] + right;

        red = 0.3;
        green = 0.8;
        blue = 0.5;
    }

    int IsPicked(glm::vec2 clickPoint)
    {
        for (size_t j = 0; j < 4; j++)
        {
            glm::vec2 res = clickPoint - Points[j];
            float len = glm::length(res);

            if (len < ControlPointRadius)
            {
                return j;
            }
        }
        return -1;
    }

    glm::vec2 Evaluate(float t)
    {
        glm::vec2 res;
        res.x = Points[0].x * (1 - t) * (1 - t) * (1 - t) + 3 * Points[1].x * (1 - t) * (1 - t) * t + 3 * Points[2].x * (1 - t) * t * t + Points[3].x * t * t * t;
        res.y = Points[0].y * (1 - t) * (1 - t) * (1 - t) + 3 * Points[1].y * (1 - t) * (1 - t) * t + 3 * Points[2].y * (1 - t) * t * t + Points[3].y * t * t * t;
        return res;
    }

    void DrawCurve()
    {
        glColor3d(red, green, blue);
        glBegin(GL_LINE_STRIP);

        glVertex2d(Points[0].x, Points[0].y);

        for (size_t i = 1; i < 20; i++)
        {
            glm::vec2 mid = Evaluate((1.0 / 20.0) * i);
            glVertex2d(mid.x, mid.y);
        }

        glVertex2d(Points[3].x, Points[3].y);

        glEnd();
    }

    void DrawControlPoints()
    {
        glColor3d(red, green, blue);
        for (size_t p = 0; p < 4; p++)
        {
            glBegin(GL_POLYGON);
            for (int i = 0; i < 32; i++)
            {
                double theta = (double)i / 32.0 * 2.0 * 3.1415926;
                double x = Points[p].x + ControlPointRadius * cos(theta);
                double y = Points[p].y + ControlPointRadius * sin(theta);
                glVertex2d(x, y);
            }
            glEnd();

        }
    }
};