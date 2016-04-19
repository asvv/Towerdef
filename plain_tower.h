#ifndef PLAIN_TOWER_H
#define PLAIN_TOWER_H
#include <QDebug>
#include <QOpenGLFunctions>
#include <QGLWidget>
#include <QtOpenGL>
#include "GL/glu.h"
#include <vector>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class plain_Tower:
        public QObject
{


public:
    plain_Tower();
    plain_Tower(QOpenGLShaderProgram* p, int va, int ca);
    void BuildTower();
    void initVertices();
    void initColors();
    void draw();
    void SetX(GLfloat);
    void SetY(GLfloat);
    GLfloat GetX();
    GLfloat GetY();

private:
    GLfloat m_X;
    GLfloat m_Y;
    GLfloat m_Size;
    QOpenGLShaderProgram* program;
    int VertexAttr;
    int ColorAttr;
    std::vector<float> vertices;
    std::vector<float> colors;






};

#endif // PLAIN_TOWER_H
