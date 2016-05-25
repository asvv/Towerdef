#include "background.h"

background::background()
    :
program(0),
VertexAttr(0),
TextureAttr(0),
TextureUniform(0),
m_X(0.0f),
m_Y(0.0f),
m_Size(0.0f)
{

}


background::~background()
{

    delete m_texture;
}

background::background(QOpenGLShaderProgram* p, int va, int ta, int tu)
    :
    program(p),
    VertexAttr(va),
    TextureAttr(ta),
    TextureUniform(tu),
    m_X(0),
    m_Y(0),
    m_Size(786432.0f)
{
initTextures();
initVertices();
b.load("C:/Users/Duras/Desktop/Tower Defence/Texture/bcg.png","PNG");
b = b.convertToFormat(QImage::Format_RGB888);


m_texture = new QOpenGLTexture( b.mirrored() );




}



void background::initVertices()
{
    vertices.resize(18);

    // 0
   vertices[0] = m_X;
    vertices[1] = m_Y;
    vertices[2] = 0.0f;

    // 1
    vertices[3] = (m_X + m_Size)*(1024.0f/768.0f);
    vertices[4] = m_Y;
    vertices[5] = 0.0f;

    // 2
    vertices[6] = m_X;
    vertices[7] = (m_Y +m_Size)*0.75f;
    vertices[8] = 0.0f;

    // 3
    vertices[9] =  m_X;
    vertices[10] = (m_Y +m_Size)*0.75f;
    vertices[11] = 0.0f;

    // 4
    vertices[12] = (m_X + m_Size)*(1024.0f/768.0f);
    vertices[13] = m_Y;
    vertices[14] = 0.0f;

    // 5
    vertices[15] = (m_X + m_Size)*(1024.0f/768.0f);
    vertices[16] = (m_Y +m_Size)*0.75f;
    vertices[17] = 0.0f;
}

void background::initTextures()
{
    texture_coords.resize(12);

    // 0
   texture_coords[0] = 0.0f;
    texture_coords[1] = 0.0f;

    // 1
    texture_coords[2] = 1024.0f;
   texture_coords[3] = 0.0f;

    // 2
    texture_coords[4] = 0.0f;
    texture_coords[5] = 768.0f;

    // 3
    texture_coords[6] = 0.0f;
    texture_coords[7] = 768.0f;

    // 4
    texture_coords[8] = 1024.0f;
    texture_coords[9] = 0.0f;

    // 5
   texture_coords[10] = 1024.0f;
    texture_coords[11] = 768.0f;





}

void background::draw()
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

void background::SetX(GLfloat x)
{
    m_X =x;
    initVertices();

}

void background::SetY(GLfloat y)
{
    m_Y = 768- y;
    initVertices();
}

GLfloat background::GetX()
{
    return m_X;
}

GLfloat background::GetY()
{
    return m_Y;

}

GLfloat background::GetSize()
{
    return m_Size;

}

QImage &background::GetImage()
{
    return b;

}

void background::initPixBoard(QColor **_Board)
{
    PixMap.load("C:/Users/Duras/Desktop/Tower Defence/Texture/map.png","PNG");
    PixMap = PixMap.convertToFormat(QImage::Format_RGB888);


    for (int i = 0 ; i <1024 ; i++)
    {
       for (int j = 0 ; j <768 ; j++)
        {

           QColor clrCurrent( PixMap.pixel(i,j) );
           _Board[i][j] = clrCurrent;
           if(clrCurrent == Qt::green)
           {
               QPoint* tmp = new QPoint(i,j);
               PointList.push_back(*tmp);
               delete tmp;

           }




       }
    }






}
