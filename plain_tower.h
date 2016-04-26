#ifndef PLAIN_TOWER_H
#define PLAIN_TOWER_H
#include <QDebug>
#include <QOpenGLFunctions>
#include <QGLWidget>
#include <QtOpenGL>
#include "GL/glu.h"
#include <vector>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class plain_Tower
      // :public QObject
{


public:
    plain_Tower(const plain_Tower&);
    ~plain_Tower();
    plain_Tower();
    plain_Tower(QOpenGLShaderProgram* p, int va, int ta, int tu);
    void BuildTower();
    void initVertices();
    void initTextures();
    void draw();
    void SetX(GLfloat);
    void SetY(GLfloat);
    GLfloat GetX();
    GLfloat GetY();
    GLfloat GetSize();
private:
    QOpenGLTexture* m_texture;
    GLfloat m_X;
    GLfloat m_Y;
    GLfloat m_Size;
    QOpenGLShaderProgram* program;
    int VertexAttr;
    int TextureAttr;
    int TextureUniform;
    std::vector<float> vertices;
    std::vector<float> texture_coords;






};

#endif // PLAIN_TOWER_H
