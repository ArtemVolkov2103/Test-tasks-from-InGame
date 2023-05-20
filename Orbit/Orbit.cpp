#include<Windows.h>
#include<glut.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#pragma comment(lib, "freeglut.lib")
//#pragma comment(lib, "glu32.lib")
//#include <imgui.h>
//#include "imgui_impl_glfw.h"
//#include <glfw3.h>
//#include <imgui_impl_opengl3.h>

int sliderValue = 50;

int sec = 10;
static float planet = 0.0;

float _Angle = 0.0;
float _moveLeftRight = 0.0;
float X = -5.0, Z = 150.0;
float X_2 = 0.0, Z_2 = -1.0;
float Y = 3.0;
int _moveForeBack = 0;
int moveUp = 0;
int _width, _height;
float fb = 0.8;

/*
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    ImGui_ImplGlfw_InitForOpenGL;
}

void sliderCallback(int value)
{
    sliderValue = value;
}

void drawImGui()
{
    ImGui::SliderInt("Slider", &sliderValue, 0, 100);

    ImGui::Text("Slider Value: %d", sliderValue);
}

void update()
{
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    drawImGui();

    glutPostRedisplay();
}*/

GLuint LoadTextureImageFile(const char* filename)
{
    GLuint texture = 0;
    int width, height;
    BYTE* data = NULL;
    FILE* file;

    fopen_s(&file, filename, "rb");

    if (&file == NULL) return 0;

    width = 512;
    height = 512;

    data = (BYTE*)malloc(width * height * 3);

    fread(data, width * height * 3, 1, file);
    fclose(file);

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_BGRA_EXT, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);


    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_TEXTURE_ENV_COLOR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    free(data);

    return texture;

}


void FreeCreatedTexture(GLuint texture)
{
    glDeleteTextures(1, &texture);
}


void Init_OpenGL()
{
    glClearColor(0.0, 0.0, 0.1, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
}


void Draw_Space()
{
    GLuint texture = LoadTextureImageFile("textures/stars.bmp");

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    //top
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-500.0, 300.0, -500.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(500.0, 300.0, -500.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(500.0, 300.0, 500.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-500.0, 300.0, 500.0);
    glEnd();

    //front
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-500.0, 300.0, -500.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(500.0, 300.0, -500.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(500.0, -300.0, -500.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-500.0, -300.0, -500.0);
    glEnd();

    //left
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-500.0, 300.0, -500.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-500.0, 300.0, 500.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-500.0, -300.0, 500.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-500.0, -300.0, -500.0);
    glEnd();

    //right
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(500.0, 300.0, -500.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(500.0, 300.0, 500.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(500.0, -300.0, 500.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(500.0, -300.0, -500.0);
    glEnd();

    //back
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-500.0, 300.0, 500.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(500.0, 300.0, 500.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(500.0, -300.0, 500.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-500.0, -300.0, 500.0);
    glEnd();

    //bottom
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-500.0, -300.0, -500.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(500.0, -300.0, -500.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(500.0, -300.0, 500.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-500.0, -300.0, 500.0);
    glEnd();

}


void Draw_Moon()
{
    GLuint texture;
    GLUquadric* quad;
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    texture = LoadTextureImageFile("textures/moon.bmp");
    glBindTexture(GL_TEXTURE_2D, texture);
    quad = gluNewQuadric();
    gluQuadricTexture(quad, 1);
    glTranslatef(120.0, 0.0, 0.0);
    //glRotatef(-90, 1.0, 0.0, 0.0);
    gluSphere(quad, 5.0, 70, 70);
    FreeCreatedTexture(texture);
    glPopMatrix();
}

void Moving_Left_Right_Direction(float angle)
{
    X_2 = sin(angle);
    Z_2 = -cos(angle);
    glLoadIdentity();
    gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);
}

void Moving_Foreword_Backword_Direction(int loc)
{
    X = X + loc * (X_2)*fb;
    Z = Z + loc * (Z_2)*fb;
    glLoadIdentity();
    gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);
}


void Display_Scene()
{

    if (_moveForeBack)
    {
        Moving_Foreword_Backword_Direction(_moveForeBack);
    }

    if (_moveLeftRight)
    {
        _Angle += _moveLeftRight;
        Moving_Left_Right_Direction(_Angle);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint texture = LoadTextureImageFile("textures/earth.bmp");

    GLUquadric* quad;

    glPushMatrix();

    Draw_Space();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    quad = gluNewQuadric();
    gluQuadricTexture(quad, 40);

    glTranslatef(0.0, 0.0, 0.0);

    glRotatef(-90, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)planet, 0.0, 0.0, 1.0);
    gluSphere(quad, 30.0, 100, 100);

    FreeCreatedTexture(texture);

    Draw_Moon();

    glPopMatrix();

    glutSwapBuffers();

    planet += 0.5f;

}


void Keyboard_function(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        exit(EXIT_SUCCESS);
    }
}

void Key_Pressed(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
    {
        _moveLeftRight = -0.02;
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        _moveLeftRight = 0.02;
    }
    else if (key == GLUT_KEY_UP)
    {
        _moveForeBack = 3;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        _moveForeBack = -3;
    }
    else if (key == GLUT_KEY_UP && key == GLUT_KEY_LEFT)
    {
        _moveLeftRight = -0.02;
    }
    else if (key == GLUT_KEY_UP && key == GLUT_KEY_RIGHT)
    {
        _moveLeftRight = 0.02;
    }
    else if (key == GLUT_KEY_PAGE_UP)
    {
        Y += 2.0;
        glLoadIdentity();
        gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);
        glutPostRedisplay();
    }
    else if (key == GLUT_KEY_PAGE_DOWN)
    {
        Y -= 2.0;
        glLoadIdentity();
        gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);
        glutPostRedisplay();
    }

}


void Key_Released(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if (_moveLeftRight < 0.0f)
            _moveLeftRight = 0.0f;
        break;

    case GLUT_KEY_RIGHT:
        if (_moveLeftRight > 0.0f)
            _moveLeftRight = 0.0f;
        break;

    case GLUT_KEY_UP:
        if (_moveForeBack > 0)
            _moveForeBack = 0;

        break;

    case GLUT_KEY_DOWN:
        if (_moveForeBack < 0)
            _moveForeBack = 0;
        break;
    }
}


void RotatePlanets(int value)
{
    glutPostRedisplay();
    glutTimerFunc(sec, RotatePlanets, 0);
}


void Reshape_Function(int width, int height)
{
    float app_aspcet = (float)16 / (float)9;

    int currWidth = glutGet(GLUT_WINDOW_WIDTH);
    int currHeight = glutGet(GLUT_WINDOW_HEIGHT);

    float window_aspcet = (float)currWidth / (float)currHeight;

    if (window_aspcet > app_aspcet)
    {
        int width = (int)((float)currWidth * app_aspcet / window_aspcet + 0.5f);
        glViewport((currWidth - width) / 2, 0, width, currHeight);
    }
    else
    {
        int height = (int)((float)currHeight * window_aspcet / app_aspcet + 0.5f);
        glViewport(0, (currHeight - height) / 2, currWidth, height);
    }

    if (height == 0)
        height = 1;

    _width = width;
    _height = height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, app_aspcet, 1.0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);

}


int main(int argc, char** argv)
{
    MessageBox(NULL, TEXT("Вперед\t\t = \tUP\nНазад\t\t = \tDOWN\nВлево\t\t = \tLEFT\nВправо\t\t = \tRIGHT\nВверх\t\t = \tPAGE UP\nВниз\t\t = \tPAGE DOWN\nВыход\t\t = \tESC"), TEXT("Управление камерой:"), MB_OK);
    /*
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);*/

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //glutInitWindowSize(1280, 720);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Orbit");
    glutFullScreen();

    glutIgnoreKeyRepeat(1);
    glutDisplayFunc(Display_Scene);
    glutKeyboardFunc(Keyboard_function);
    glutSpecialFunc(Key_Pressed);
    glutSpecialUpFunc(Key_Released);
    glutReshapeFunc(Reshape_Function);
    Init_OpenGL();
    glutTimerFunc(0, RotatePlanets, 0);
 


    //ImGui::CreateContext();
    //ImGui::SetCurrentContext();
    //ImGui::Render();

    //init();
    // attach the update function to the idle event
    //glutIdleFunc(update);

    glutMainLoop();
    return(0);
}
