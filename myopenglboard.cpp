#include "myopenglboard.h"


myOpenglBoard::myOpenglBoard(QWidget *parent)
    : QGLWidget(parent)
{

}

void myOpenglBoard::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {

        GLfloat tmp_x = GLfloat(GLfloat((this->mapFromGlobal(event->pos()).x()))/GLfloat(this->width()));
        GLfloat tmp_y = GLfloat(GLfloat((this->mapFromGlobal(event->pos()).y()))/GLfloat(this->height()));
        Tower->SetX(tmp_x);
        Tower->SetY(tmp_y);
        Tower->initVertices();
        qDebug()<<GLfloat((this->mapFromGlobal(event->pos()).x()))<<"  "<<GLfloat((this->mapFromGlobal(event->pos()).y()));



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
    delete Tower;
}
void myOpenglBoard::initializeGL()
{
    initializeOpenGLFunctions();
    qglClearColor(Qt::red);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
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
    colorAttr = m_program.attributeLocation("colorAttr");
    matrixUniform = m_program.uniformLocation("matrix");

    Tower = new plain_Tower(&m_program,vertexAttr,colorAttr);




}
void myOpenglBoard::paintGL(){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(!m_program.bind())
    {
        qWarning("Error while binding");
        return;
    }
QMatrix4x4 mtrx;

mtrx.ortho(-1.0f,1.0f,-1.0f,1.0f,1.0f,-1.0f);

mtrx.translate( 0.0f, 0.0f, -1.0f );

m_program.setUniformValue(matrixUniform,mtrx);
Tower->draw();
m_program.release();






}
void myOpenglBoard::resizeGL(int w, int h){

    glViewport(0,0,w,h);
}

