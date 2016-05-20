#include "myopenglboard.h"


myOpenglBoard::myOpenglBoard(QWidget *parent)
    : QGLWidget(parent),
      TowerSlot(63,72,204),
      Road(0,0,0)
{
    this->setFixedSize(1024,768);
      connect(&Timer,SIGNAL(timeout()),this,SLOT(SlotMove()));
    Timer.start(1);


}

void myOpenglBoard::mousePressEvent(QMouseEvent *event)
{
  if(event->button() == Qt::LeftButton)
    {
        Tower = new plain_Tower(&m_program,vertexAttr,textureAttr,textureUniform);


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

void myOpenglBoard::SlotMove()
{


    //Enemy->SetX(Enemy->GetX()+1.0f);
   // Enemy->SetX(Enemy->GetX()+1.0f);
    updateGL();


}



bool myOpenglBoard::CheckBoard(int& x, int& y)
{

if (ColorMap[x][y]==TowerSlot)
{
while(ColorMap[x][y]!=Qt::white)
{
    x--;
}
while(ColorMap[x][y]!=Qt::white)
{
    y++;
}



 QColor tmp(255,255,255);
//x = x-(x%64);
//y = (y-(y%80))+80;
qDebug() << x <<"  " <<y << "  ";

for(int i = x ; i < x+64 ; i++)
{
    for (int j = y ; j>y-80;j--)
    {

        ColorMap[i][j] = Qt::black;
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
    makeCurrent();
    delete Enemy;
    doneCurrent();
}
void myOpenglBoard::initializeGL()
{
    initializeOpenGLFunctions();
    initTruthTable();
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
    Background->initPixBoard(ColorMap);

    Enemy = new plain_enemy(&m_program,vertexAttr,textureAttr,textureUniform);
    Enemy->SetX(0.0f);
    Enemy->SetY(768.0f);






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




Background->draw();
Enemy->draw();


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

/*TruthTable = new bool*[1024];
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
}*/

    ColorMap = new QColor*[1024];
    for (int i = 0; i <1024 ; i++ )
    {
        ColorMap[i] = new QColor[768];

    }

    for (int i = 0 ; i <1024 ; i++)
    {
       for (int j = 0 ; j <768 ; j++)
        {

           //QColor clr(0,0,0);
           ColorMap[i][j] = Qt::white;


       }
    }




}




