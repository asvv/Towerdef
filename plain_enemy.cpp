#include "plain_enemy.h"
#include <QThread>
#include "plain_enemy.h"

plain_enemy::plain_enemy(const plain_enemy &other)
    :
      program(other.program),
      m_texture(other.m_texture),
      TextureAttr(other.TextureAttr),
      TextureUniform(other.TextureUniform),
      VertexAttr(other.VertexAttr),
      m_X(other.m_X),
      m_Y(other.m_Y),
      m_Size(other.m_Size),
      Index(other.Index)

{

    initVertices();
    initTextures();
    m_texture = new QOpenGLTexture( QImage( "C:/Users/Duras/Desktop/Tower Defence/Texture/enemy.png","PNG" ).mirrored() );
}

plain_enemy::~plain_enemy()
{

    delete m_texture;
}

plain_enemy::plain_enemy(QOpenGLShaderProgram* p, int va, int ta, int tu)
    :
    program(p),
    VertexAttr(va),
    TextureAttr(ta),
    TextureUniform(tu),
    m_X(0.0f),
    m_Y(0.0f),
    m_Size(20.0f),
    Index(0)
{

initVertices();
initTextures();
m_texture = new QOpenGLTexture( QImage( "C:/Users/Duras/Desktop/Tower Defence/Texture/enemy.png","PNG" ) );

}




void plain_enemy::initVertices()
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

void plain_enemy::initTextures()
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

void plain_enemy::draw()
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

void plain_enemy::SetX(GLfloat x)
{
    m_X =x;
    initVertices();

}

void plain_enemy::SetY(GLfloat y)
{

    m_Y = 768-y;
    //m_Y = y;
    initVertices();
}

GLfloat plain_enemy::GetX()
{
    return m_X;
}

GLfloat plain_enemy::GetY()
{
    return 768-m_Y;

}

GLfloat plain_enemy::GetSize()
{
    return m_Size;

}

std::vector<std::vector<qreal> > &plain_enemy::GetForumlas()
{
    return Formulas;

}

void plain_enemy::CalcFormulas()
{
    Formulas.resize(PointList.size()-2);





    for(uint i = 0 ; i<PointList.size()-2;i++)
    {
        QTransform Matrix(  qreal(PointList[i].x()*PointList[i].x()), qreal(PointList[i].x()), qreal(1),
                            qreal(PointList[i+1].x()*PointList[i+1].x()), qreal(PointList[i+1].x()), qreal(1),
                            qreal(PointList[i+2].x()*PointList[i+2].x()), qreal(PointList[i+2].x()), qreal(1));
       qreal* V = new qreal[3]
        {
        qreal(PointList[i].y()),
        qreal(PointList[i+1].y()),
        qreal(PointList[i+2].y())

        };


    Matrix = Matrix.inverted();



      qreal* M = new qreal[9]
        {
        Matrix.m11(),Matrix.m12(),Matrix.m13(),
        Matrix.m21(),Matrix.m22(),Matrix.m23(),
        Matrix.m31(),Matrix.m32(),Matrix.m33()


        };

      QGenericMatrix<3,3,qreal> GenMatrix(M);

      QGenericMatrix<1,3,qreal> Vector(V);



      QGenericMatrix<1,3,qreal> tmp(GenMatrix*Vector);
      qreal* Result;
      Result = tmp.data();






      for(int j  = 0; j < 3 ; j++)
      {
        Formulas[i].resize(3);
        Formulas[i][j] = Result[j];




      }




    }



CalcRoad();


}

void plain_enemy::CalcRoad()
{

    qreal to_y=0.0;
     int x = 0;
    for(auto i = 0 ; i < PointList.size()-2 ; i++)
    {

        x = PointList[i].x();

      //  qDebug()<<x;
      //  qDebug()<<PointList.size();
      //  qDebug()<<Formulas.size();
        while(int(to_y)!=PointList[i+1].y())
        {


             to_y = (Formulas[i][0]*qreal(x*x))+(Formulas[i][1]*qreal(x))+Formulas[i][2];
             Road.push_back(to_y);
             x++;


         }





    }



}

void plain_enemy::SetPointList(const std::vector<QPoint> & v)
{
    PointList = v;
   CalcFormulas();


}

void plain_enemy::Move()
{



/*for(auto i = 0 ; i < PointList.size()-1;i++ )
{

    uint x =0;
   while(!(this->GetX() == PointList[i+1].x() && this->GetY() == PointList[i+1].y())){





       x++;
     this->SetY(int((Formulas[i][0]*qreal(x*x))+(Formulas[i][1]*qreal(x))+Formulas[i][2]));
     this->SetX(x);

       Sleep(50);




    }

}*/





}

bool plain_enemy::CheckIndex()
{

    if(this->Index==this->Road.size()-1)
        return false;
    return true;

}



