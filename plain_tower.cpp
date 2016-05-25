#include "plain_tower.h"

plain_Tower::plain_Tower(const plain_Tower &other)
    :
      program(other.program),
      m_texture(other.m_texture),
      TextureAttr(other.TextureAttr),
      TextureUniform(other.TextureUniform),
      VertexAttr(other.VertexAttr),
      m_X(other.m_X),
      m_Y(other.m_Y),
      m_Size(other.m_Size)
{

    initVertices();
    initTextures();


    QImage tmp( "C:/Users/Duras/Desktop/Tower Defence/Texture/rectx.png","PNG" );
    tmp = tmp.mirrored();
    tmp = tmp.convertToFormat(QImage::Format_ARGB32);

    QImage trans(tmp.size(),QImage::Format_ARGB32);
    trans.fill(qRgba(0,0,0,0));
    QPainter p(&trans);
    p.drawImage(0,0,tmp);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //tmp = QGLWidget::convertToGLFormat(trans);
    m_texture = new QOpenGLTexture(trans);


    glEnd();
}

plain_Tower::~plain_Tower()
{

    delete m_texture;
}

plain_Tower::plain_Tower(QOpenGLShaderProgram* p, int va, int ta, int tu)
    :
    program(p),
    VertexAttr(va),
    TextureAttr(ta),
    TextureUniform(tu),
    m_X(0.0f),
    m_Y(0.0f),
    m_Size(64.0f)
{

initVertices();
initTextures();





QImage tmp( "C:/Users/Duras/Desktop/Tower Defence/Texture/rectx.png","PNG" );
tmp = tmp.mirrored();
tmp = tmp.convertToFormat(QImage::Format_ARGB32);

QImage trans(tmp.size(),QImage::Format_ARGB32);
trans.fill(qRgba(0,0,0,0));
QPainter pp(&trans);
pp.drawImage(0,0,tmp);

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


//tmp = QGLWidget::convertToGLFormat(trans);
m_texture = new QOpenGLTexture(trans);
glEnd();



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
    vertices[3] = m_X + m_Size;// * (64.0/128.0);
    vertices[4] = m_Y;
    vertices[5] = 0.0f;

    // 2
    vertices[6] = m_X;
    vertices[7] = m_Y +m_Size * 2;
    vertices[8] = 0.0f;

    // 3
    vertices[9] =  m_X;
    vertices[10] = m_Y +m_Size * 2;
    vertices[11] = 0.0f;

    // 4
    vertices[12] = m_X  +m_Size ;//* 0.5;
    vertices[13] = m_Y;
    vertices[14] = 0.0f;

    // 5
    vertices[15] = m_X+m_Size;// * 0.5;
    vertices[16] = m_Y+m_Size * 2;
    vertices[17] = 0.0f;
}

void plain_Tower::initTextures()
{
    texture_coords.resize(12);

    // 0
    texture_coords[0] = 0.0f;
    texture_coords[1] = 0.0f;

    // 1
    texture_coords[2] = 1.0f;
   texture_coords[3] = 0.0f;

    // 2
    texture_coords[4] = 0.0f;
    texture_coords[5] = 1.0f;

    // 3
    texture_coords[6] = 0.0f;
    texture_coords[7] = 1.0f;

    // 4
    texture_coords[8] = 1.0f;
    texture_coords[9] = 0.0f;

    // 5
   texture_coords[10] = 1.0f;
    texture_coords[11] = 1.0f;




}

void plain_Tower::draw()
{
    m_texture->bind();

    program->setAttributeArray(VertexAttr,vertices.data(),3);
    program->setAttributeArray(TextureAttr,texture_coords.data(),2);
    program->setUniformValue(TextureUniform,0);

    program->enableAttributeArray(VertexAttr);
    program->enableAttributeArray(TextureAttr);

    glDrawArrays(GL_TRIANGLES,0,6);

    program->disableAttributeArray(VertexAttr);
    program->disableAttributeArray(TextureAttr);

}

void plain_Tower::SetX(GLfloat x)
{
    m_X =x;
    initVertices();

}

void plain_Tower::SetY(GLfloat y)
{

    m_Y = 768-y;
    //m_Y = y;
    initVertices();
}

GLfloat plain_Tower::GetX()
{
    return m_X;
}

GLfloat plain_Tower::GetY()
{
    return m_Y;

}

GLfloat plain_Tower::GetSize()
{
    return m_Size;

}


