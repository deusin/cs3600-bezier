#include "GL/freeglut.h"
#include "bezier.h"
#include <vector>
#include <glm/glm.hpp>

// Global Variables
double screen_x = 800;
double screen_y = 600;
double t = 0.0;
bool loopExit = false;
int timeSinceStart;
int oldTimeSinceStart = 0;
int deltaTime;

int selectedBezier = -1;
int selectedControlPoint = -1;
std::vector<Bezier> curves;


void DrawRectangle(double x1, double y1, double x2, double y2)
{
    glBegin(GL_QUADS);
    glVertex2d(x1, y1);
    glVertex2d(x2, y1);
    glVertex2d(x2, y2);
    glVertex2d(x1, y2);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //redSlider.Draw();
    //greenSlider.Draw();
    //blueSlider.Draw();

    //glColor3d(redSlider.GetValue(), greenSlider.GetValue(), blueSlider.GetValue());
    //glColor3d(1.0, 0.4, 0.2);
    //DrawRectangle(10, 160, screen_x - 10, screen_y - 10);

    //glColor3d(0, 0, 0);

    //int red = (int)(redSlider.GetValue() * 255);
    //std::stringstream ss;
    //ss << red;
    //DrawText(screen_x - 90, 130, ss.str().c_str());

    //int green = (int)(greenSlider.GetValue() * 255);
    //std::stringstream ss2;
    //ss2 << green;
    //DrawText(screen_x - 90, 80, ss2.str().c_str());

    //int blue = (int)(blueSlider.GetValue() * 255);
    //std::stringstream ss3;
    //ss3 << blue;
    //DrawText(screen_x - 90, 30, ss3.str().c_str());

    for (size_t i = 0; i < curves.size(); i++)
    {
        curves[i].DrawControlPoints();
    }

    glutSwapBuffers();
}

void reshape(int w, int h)
{
	// Reset our global variables to the new width and height.
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	// Set the projection mode to 2D orthographic, and set the world coordinates:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);

}

#pragma region Keyboard

// This callback function gets called by the Glut
// system whenever a key is pressed.
void asciiKeyboardDown(unsigned char c, int x, int y)
{
    switch (c)
    {
    case 27: // escape character means to quit the program
        exit(0);
        break;
    default:
        return; // if we don't care, return without glutPostRedisplay()
    }
    //camera->ProcessKeyboard(deltaTime);
    //glutPostRedisplay();
}

void asciiKeyboardUp(unsigned char c, int x, int y)
{
    switch (c)
    {

    default:
        return; // if we don't care, return without glutPostRedisplay()
    }
    //camera->ProcessKeyboard(deltaTime);
    //glutPostRedisplay();
}

#pragma endregion Keyboard

#pragma region Mouse
// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouseButton(int mouse_button, int state, int x, int y)
{
    glm::vec2 clickPoint;
    clickPoint.x = x;
    clickPoint.y = screen_y - y;

    if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        for (size_t i = 0; i < curves.size(); i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                glm::vec2 res = clickPoint - curves[i].Points[j];
                float len = glm::length(res);
                
                if (len < curves[i].ControlPointRadius)
                {
                    selectedBezier = i;
                    selectedControlPoint = j;
                }
            }
        }
    }
    if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        selectedBezier = -1;
        selectedControlPoint = -1;
    }
    if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
    }
    if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
    {
    }
    glutPostRedisplay();
}

void mouseMove(int x, int y)
{
    if (selectedBezier != -1)
    {
        curves[selectedBezier].Points[selectedControlPoint].x = x;
        curves[selectedBezier].Points[selectedControlPoint].y = screen_y - y;
    }

}

void mouseWheel(int wheel, int direction, int x, int y)
{
    //wheel: the wheel number, if the mouse has only a wheel this will be zero.
    //direction : a + / -1 value indicating the wheel movement direction
    //x, y : the window mouse coordinates
}

#pragma endregion Mouse

void InitializeMyStuff()
{
    Bezier b1(40, 40);
    curves.push_back(b1);
}

void update(int deltaTime)
{
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screen_x, screen_y);
    glutInitWindowPosition(10, 10);

    int fullscreen = 0;
    if (fullscreen)
    {
        glutGameModeString("800x600:32");
        glutEnterGameMode();
    }
    else
    {
        glutCreateWindow("Bezier");
    }

    // callbacks for display
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // callbacks for input

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(asciiKeyboardDown);
    glutKeyboardUpFunc(asciiKeyboardUp);
    //glutSpecialFunc(pressKey);
    //glutSpecialUpFunc(releaseKey);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    //glutPassiveMotionFunc(mousePassiveMove);
    glutMouseWheelFunc(mouseWheel);

    glClearColor(0, 0, 0, 1);
    InitializeMyStuff();

    while (!loopExit)
    {
        // Get Delta Time for calculations
        timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
        deltaTime = timeSinceStart - oldTimeSinceStart;
        oldTimeSinceStart = timeSinceStart;

        glutMainLoopEvent();
        update(deltaTime);
        glutPostRedisplay();
    }

    return 0;
}
