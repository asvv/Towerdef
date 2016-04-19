#include "plain_tower.h"

plain_Tower::plain_Tower(QOpenGLShaderProgram* p,int va,int ca)
    :
    program(p),
    VertexAttr(va),
    ColorAttr(ca),
    m_X(0.0f),
    m_Y(0.0f),
    m_Size(0.10f)
{
initVertices();
initColors();
}


void plain_Tower::BuildTower()
{







}


void plain_Tower::initVertices()
{
    vertices.resize(18);

    // 0
   vertices[0] = m_X;
    vertices[1] = m_Y;
    vertices[2] = 0.0f;

    // 1
    vertices[3] = m_X + m_Size;
    vertices[4] = m_Y;
    vertices[5] = 0.0f;

    // 2
    vertices[6] = m_X;
    vertices[7] = m_Y +m_Size;
    vertices[8] = 0.0f;

    // 3
    vertices[9] =  m_X;
    vertices[10] = m_Y +m_Size;
    vertices[11] = 0.0f;

    // 4
    vertices[12] = m_X  +m_Size;
    vertices[13] = m_Y;
    vertices[14] = 0.0f;

    // 5
    vertices[15] = m_X+m_Size;
    vertices[16] = m_Y+m_Size;
    vertices[17] = 0.0f;
}

void plain_Tower::initColors()
{
    colors.resize(18);

    colors[0] = 0.0f;
    colors[1] = 1.0f;
    colors[2] = 0.0f;

    colors[3] = 0.0f;
    colors[4] = 1.0f;
    colors[5] = 0.0f;

    colors[6] = 0.0f;
    colors[7] = 1.0f;
    colors[8] = 0.0f;

    colors[9] = 0.0f;
    colors[10] = 1.0f;
    colors[11] = 0.0f;

    colors[12] = 0.0f;
    colors[13] = 1.0f;
    colors[14] = 0.0f;

    colors[15] = 0.0f;
    colors[16] = 1.0f;
    colors[17] = 0.0f;



}

void plain_Tower::draw()
{
    program->setAttributeArray(VertexAttr,vertices.data(),3);
    program->setAttributeArray(ColorAttr,colors.data(),3);

    program->enableAttributeArray(VertexAttr);
    program->enableAttributeArray(ColorAttr);

    glDrawArrays(GL_TRIANGLES,0,6);

    program->disableAttributeArray(VertexAttr);
    program->disableAttributeArray(ColorAttr);

}

void plain_Tower::SetX(GLfloat x)
{
    m_X =x;

}

void plain_Tower::SetY(GLfloat y)
{
    m_Y = y;

}

GLfloat plain_Tower::GetX()
{
    return m_X;
}

GLfloat plain_Tower::GetY()
{
    return m_Y;

}


