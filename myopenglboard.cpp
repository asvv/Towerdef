#include "myopenglboard.h"


myOpenglBoard::myOpenglBoard(QWidget *parent)
    : QGLWidget(parent)
{

}

void myOpenglBoard::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //Tower = new plain_Tower(&m_program,vertexAttr,textureAttr,textureUniform);


        GLfloat tmp_x = GLfloat((this->mapFromParent(event->pos()).x()));
        GLfloat tmp_y =   GLfloat((this->mapFromParent(event->pos()).y()));

        //Tower->SetX((tmp_x)-512);
        //Tower->SetY(-(tmp_y)+334);


        Tower->SetX(0);
        Tower->SetY(0);

        //Tower->initVertices();
      //  Tower->initTextures();
        //tower_vctr.push_back(*Tower);
        //Tower->draw();

        //delete Tower;
       qDebug()<<(tmp_x)-512<<"  "<<-(tmp_y)+334;




    }






    updateGL();




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
}
void myOpenglBoard::initializeGL()
{
    initializeOpenGLFunctions();
   // initTruthTable();
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

    Tower = new plain_Tower(&m_program,vertexAttr,textureAttr,textureUniform);






}
void myOpenglBoard::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT );

    if(!m_program.bind())
    {
        qWarning("Error while binding");
        return;
    }


QMatrix4x4 mtrx;
//mtrx.ortho(-512.0f,512.0f,-384.0f,384.0f,1.0f,-1.0f);
mtrx.ortho(-0.5f,0.5f,-0.5f,0.5f,1.0f,-1.0f);
m_program.setUniformValue(matrixUniform,mtrx);


/*if(tower_vctr.size()>0)
{
 for(unsigned int i = 0;i<tower_vctr.size();i++)
 {
   tower_vctr[i].draw();

 }

}*/
Tower->draw();
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




