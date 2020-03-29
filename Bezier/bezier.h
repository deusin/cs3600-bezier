#pragma once
#include "glm/glm.hpp"
#include "GL/freeglut.h"

class Bezier
{
public:
    glm::vec2 Points[4];
    float ControlPointRadius = 10.0;

    Bezier(float startingX, float startingY)
    {
        glm::vec2 right;
        right.x = 40;
        right.y = 0;

        Points[0].x = startingX;
        Points[0].y = startingY;

        Points[1] = Points[0] + right;
        Points[2] = Points[1] + right;
        Points[3] = Points[2] + right;
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

    //glm::vec2 Evaluate(float t)
    //{

    //}

    void DrawCurve()
    {

    }

    void DrawControlPoints()
    {
        glColor3d(0.3, 0.8, 0.5);
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