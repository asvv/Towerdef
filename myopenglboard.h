#ifndef MYOPENGLBOARD_H
#define MYOPENGLBOARD_H
#include "plain_tower.h"
#include "background.h"
#include "plain_enemy.h"
#include <QTimer>


class myOpenglBoard : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    myOpenglBoard();
    ~myOpenglBoard();

   explicit myOpenglBoard(QWidget *parent = 0);
   void mousePressEvent(QMouseEvent*);

private slots:
   void SlotMove();

private:
   bool CheckBoard(int& x, int& y);
    std::vector<plain_Tower> tower_vctr;
    QTimer Timer;

    void initializeGL();
    void paintGL();
    void resizeGL(int, int);


    void initTruthTable();
    bool** TruthTable;

    QColor** ColorMap;
    QColor TowerSlot;
    QColor Road;

    plain_Tower *Tower;
    background* Background;
    plain_enemy* Enemy;


    QOpenGLShaderProgram m_program;
    int vertexAttr;
    int textureAttr;
    int textureUniform;
    int matrixUniform;
    qreal CalulateX();

     void Move();
    int Counter;
};

#endif // MYOPENGLBOARD_H
