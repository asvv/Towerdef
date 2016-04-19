#ifndef MYOPENGLBOARD_H
#define MYOPENGLBOARD_H
#include "plain_tower.h"


class myOpenglBoard : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    myOpenglBoard();
    ~myOpenglBoard();

   explicit myOpenglBoard(QWidget *parent = 0);
   void mousePressEvent(QMouseEvent*);
private:
    void initializeGL();
    void paintGL();
    void resizeGL(int, int);
    plain_Tower *Tower;
    QOpenGLShaderProgram m_program;

    int vertexAttr;
    int colorAttr;
    int matrixUniform;

};

#endif // MYOPENGLBOARD_H
