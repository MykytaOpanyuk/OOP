#include "prism.h"

Prism::Prism(GLfloat size): Figure()
{
    this->size = size;
    pos = QVector3D(0,0,0);
    type = 0;

    points = {
        -1, 0,  0,
        -0.5, sqrt(3)/2, 0,
        +0.5, sqrt(3)/2, 0,
        1,  0,  0,
        +0.5, -sqrt(3)/2, 0,
        -0.5, -sqrt(3)/2, 0,

        -1, 0,  1,
        -0.5, sqrt(3)/2, 1,
        +0.5, sqrt(3)/2, 1,
        1,  0,  1,
        +0.5, -sqrt(3)/2, 1,
        -0.5, -sqrt(3)/2, 1,

        -1, 0,  0,
        -0.5, sqrt(3)/2, 0,
        -1, 0,  1,
        -0.5, sqrt(3)/2, 1,

         -0.5, sqrt(3)/2, 0,
         +0.5, sqrt(3)/2, 0,
         -0.5, sqrt(3)/2, 1,
         +0.5, sqrt(3)/2, 1,

         +0.5, sqrt(3)/2, 0,
         1,  0,  0,
         +0.5, sqrt(3)/2, 1,
         1,  0,  1,

         1,  0,  0,
         +0.5, -sqrt(3)/2, 0,
         1,  0,  1,
         +0.5, -sqrt(3)/2, 1,

        +0.5, -sqrt(3)/2, 0,
        -0.5, -sqrt(3)/2, 0,
        +0.5, -sqrt(3)/2, 1,
        -0.5, -sqrt(3)/2, 1,

        -0.5, -sqrt(3)/2, 0,
        -1, 0,  0,
        -0.5, -sqrt(3)/2, 1,
        -1, 0,  1,
    };

    indices ={
        0,1,5,
        1,2,4,
        4,5,1,
        2,3,4,
        6,7,11,
        7,8,10,
        10,11,7,
        8,9,10,
        12,13,14,
        14,15,13,
        16,17,18,
        18,19,17,
        20,21,22,
        22,23,21,
        24,25,26,
        26,27,25,
        28,29,30,
        30,31,29,
        32,33,34,
        34,35,33

    };

    //for (int i = 0; i <6; i++)
        //setPlaneColor(i, QColor(150,150,150));
    setPlaneColor(0, QColor(255,0,0));
    setPlaneColor(1, QColor(0,255,0));
    setPlaneColor(2, QColor(0,0,255));
    setPlaneColor(3, QColor(255,255,0));
    setPlaneColor(4, QColor(0,255,255));
    setPlaneColor(5, QColor(255,0,255));
    setPlaneColor(6, QColor(0,22,255));
    setPlaneColor(7, QColor(105,0,255));


    recalcTransform();
}

void Prism::setPlaneColor(uint num, const QColor &color)
{
    Figure::setPlaneColor(num, color);
    if ((num == 0) || (num == 1))
        for (int i = 0; i < 18; i = i + 3) {
            vertexColors[num*18+i] = color.red();
            vertexColors[num*18+i+1] = color.green();
            vertexColors[num*18+i+2] = color.blue();
        }
    else
        for (int i = 0; i < 12; i = i + 3) {
            vertexColors[num*12+i] = color.red();
            vertexColors[num*12+i+1] = color.green();
            vertexColors[num*12+i+2] = color.blue();
        }
}

void Prism::recalcTransform()
{
    Figure::recalcTransform();
    transform.scale(size);
}

void Prism::draw()
{
    glPushMatrix();
    glMultMatrixf(transform.constData());

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT , 0, points.data());
    glColorPointer(3, GL_UNSIGNED_BYTE, 0, vertexColors);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, indices.data());

    glDisableClientState(GL_COLOR_ARRAY);
    if (selected) {
        glColor3f(1,1,1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, indices.data());
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void Prism::drawGeometryOnly()
{
    glPushMatrix();
    glMultMatrixf(transform.constData());

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT , 0, points.data());
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, indices.data());
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void Prism::rainbow()
{
    for (int i = 0; i < 108; i = i + 3) {
        int r = rand() % 3;
        vertexColors[i] = 255*(r == 0);
        vertexColors[i+1] = 255*(r == 1);
        vertexColors[i+2] = 255*(r == 2);
    }

}
