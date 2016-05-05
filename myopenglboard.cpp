#include "myopenglboard.h"


myOpenglBoard::myOpenglBoard(QWidget *parent)
    : QGLWidget(parent)
{
    this->setFixedSize(1024,768);

}

void myOpenglBoard::mousePressEvent(QMouseEvent *event)
{
  if(event->button() == Qt::LeftButton)
    {
        Tower = new plain_Tower(&m_program,vertexAttr,textureAttr,textureUniform);


        /*GLfloat tmp_x = GLfloat((this->mapFromParent(event->pos()).x()));
        GLfloat tmp_y =   GLfloat((this->mapFromParent(event->pos()).y()));
        tmp_x =  tmp_x - 512;
        tmp_y = -tmp_y + 324;*/

       int a = event->x();
       int b = event->y();


     if  (CheckBoard(a,b))
     {
      Tower->SetX(GLfloat(a));
      Tower->SetY(GLfloat(b));
       tower_vctr.push_back(*Tower);
     }

        delete Tower;






    }
  if(event->button() == Qt::RightButton)
  {

qDebug()<<tower_vctr.size();


  /*for (int i = 0 ; i<1024 ; i++)
  {
      for (int j = 0 ; j < 768; j++)
      {

         if(TruthTable[i][j] == true)
             qDebug()<<1;
         else
             qDebug()<<0;


      }



  }*/




  }






    updateGL();


}



bool myOpenglBoard::CheckBoard(int& x, int& y)
{


if (TruthTable[x][y]==false)
{
x = x-(x%64);
y = (y-(y%64))+64;
qDebug() << x <<"  " <<y << "  ";

for(int i = x ; i < x+64 ; i++)
{
    for (int j = y-64; j<y;j++)
    {

        TruthTable[i][j] = true;
    }





}


    return true;


}
return false;




}
myOpenglBoard::myOpenglBoard()
    :
      QGLWidget()

{
}

myOpenglBoard::~myOpenglBoard()
{

    for(int i  = 0 ; i<1024 ; i++)
    {
        delete[] TruthTable[i];
    }
    delete[] TruthTable;
    makeCurrent();
    delete Tower;
    doneCurrent();
    makeCurrent();
    delete Background;
    doneCurrent();
}
void myOpenglBoard::initializeGL()
{
    initializeOpenGLFunctions();
    initTruthTable();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
     qglClearColor(Qt::red);

    QOpenGLShader vShader(QOpenGLShader::Vertex);
    vShader.compileSourceFile(":/Shaders/vShader.glsl");
    QOpenGLShader fShader(QOpenGLShader::Fragment);
    fShader.compileSourceFile(":/Shaders/fShader.glsl");

    m_program.addShader(&vShader);
    m_program.addShader(&fShader);
    if(!m_program.link())
    {
        qWarning("Error while linking shader program");
        return;

    }
    vertexAttr = m_program.attributeLocation("vertexAttr");
    textureAttr = m_program.attributeLocation("textureAttr");
    textureUniform = m_program.uniformLocation("textureUniform");
    matrixUniform = m_program.uniformLocation("matrix");

    Background = new background(&m_program,vertexAttr,textureAttr,textureUniform);
    Background->SetX(0.0f);
    Background->SetY(768.0f);






}
void myOpenglBoard::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!m_program.bind())
    {
        qWarning("Error while binding");
        return;
    }

QMatrix4x4 mtrx;

mtrx.setToIdentity();

mtrx.ortho(0.0f,1024.0f,0.0f,768.0f,-1.0f,1.0f);





m_program.setUniformValue(matrixUniform,mtrx);


//-512.0f -384.0f

Background->draw();



if(tower_vctr.size()>0)
{
 for(unsigned int i = 0;i<tower_vctr.size();i++)
 {
   tower_vctr[i].draw();

 }

}


m_program.release();






}
void myOpenglBoard::resizeGL(int w, int h){

  glViewport(0,0,w,h);




}

void myOpenglBoard::initTruthTable()
{

TruthTable = new bool*[1024];
for (int i = 0; i <1024 ; i++ )
{
    TruthTable[i] = new bool[768];

}

for (int i = 0 ; i <1024 ; i++)
{
   for (int j = 0 ; j <768 ; j++)
    {

       TruthTable[i][j] = false;

   }
}

}




