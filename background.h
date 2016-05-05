#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <plain_tower.h>


class background
{
public:
    background();
    ~background();
    background(QOpenGLShaderProgram* p, int va, int ta, int tu);
    void BuildTower();
    void initVertices();
    void initTextures();
    void draw();
    void SetX(GLfloat);
    void SetY(GLfloat);
    GLfloat GetX();
    GLfloat GetY();
    GLfloat GetSize();
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
};

#endif // BACKGROUND_H
