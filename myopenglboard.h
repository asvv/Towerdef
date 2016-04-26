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
    std::vector<plain_Tower> tower_vctr;
    void initializeGL();
    void paintGL();
    void resizeGL(int, int);
    plain_Tower *Tower;
    QOpenGLShaderProgram m_program;
    void initTruthTable();
    bool** TruthTable;
    int vertexAttr;
    int textureAttr;
    int textureUniform;
    int matrixUniform;

};

#endif // MYOPENGLBOARD_H
