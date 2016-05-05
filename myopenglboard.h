#ifndef MYOPENGLBOARD_H
#define MYOPENGLBOARD_H
#include "plain_tower.h"
#include "background.h"


class myOpenglBoard : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    myOpenglBoard();
    ~myOpenglBoard();

   explicit myOpenglBoard(QWidget *parent = 0);
   void mousePressEvent(QMouseEvent*);
private:
   bool CheckBoard(int& x, int& y);
    std::vector<plain_Tower> tower_vctr;
    void initializeGL();
    void paintGL();
    void resizeGL(int, int);
    plain_Tower *Tower;
    background* Background;
    QOpenGLShaderProgram m_program;
    void initTruthTable();
    bool** TruthTable;
    int vertexAttr;
    int textureAttr;
    int textureUniform;
    int matrixUniform;

};

#endif // MYOPENGLBOARD_H
