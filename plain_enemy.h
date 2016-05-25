#ifndef PLAIN_ENEMY_H
#define PLAIN_ENEMY_H

#include "plain_tower.h"
class plain_enemy
{
public:
    plain_enemy(const plain_enemy&);
    ~plain_enemy();
    plain_enemy();
    plain_enemy(QOpenGLShaderProgram* p, int va, int ta, int tu);
    void BuildTower();
    void initVertices();
    void initTextures();
    void draw();
    void SetX(GLfloat);
    void SetY(GLfloat);
    GLfloat GetX();
    GLfloat GetY();
    GLfloat GetSize();
    std::vector<std::vector<qreal>>& GetForumlas();
    void SetPointList(const std::vector<QPoint>&);

private:
    QOpenGLTexture* m_texture;
    GLfloat m_X;
    GLfloat m_Y;
    GLfloat m_Size;
    QOpenGLShaderProgram* program;
    int VertexAttr;
    int TextureAttr;
    int TextureUniform;
    std::vector<float> vertices;
    std::vector<float> texture_coords;
    std::vector<QPoint> PointList;
    std::vector<std::vector<qreal>> Formulas;



    void CalcFormulas();



};

#endif // PLAIN_ENEMY_H
