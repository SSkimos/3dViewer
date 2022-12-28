#include "myglwidget.h"
#include "../model/s21_data_structure.h"
#include "../model/s21_parse_obj.h"
#include "../model/s21_affin_p.h"
#include <iostream>

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setGeometry(400, 200, 800, 600);
}

void MyGLWidget::initializeGL(void) {
    glEnable(GL_DEPTH_TEST); // включаю буффер глубины (хранит в себе расстояние от камеры до отрисовки)
}

void MyGLWidget::paintGL(void) {

    glClearColor(0, 1, 0, 0); // настраиваю цвет окна

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST); // очищаю буффер цвета и буффер глубины (каждый тик)

    glMatrixMode(GL_MODELVIEW); // указываю тип матрицы
    glLoadIdentity(); // загружаю матрицу в стек


    //glRotatef(90, 0, 0, 1); // вращаю матрицу 90 - угол, остльное это оси
    glTranslatef(0, 0, -2);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    drawCube(0.5);
    // блок, где я рисую треугольник
//    glVertexPointer(3, GL_FLOAT, 0, &arr);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glColor3d(1, 0, 0); // изменяю цвет треугольника
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    glDisableClientState(GL_VERTEX_ARRAY);

//    glBegin(GL_TRIANGLES); // устаревшая форма записи для старперов
//    // 3 - пространство, d - double
//    glVertex3d(0, 0, -1.5);
//    glVertex3d(0, 1, -1.5);
//    glVertex3d(1, 0, -1.5);
//    glEnd();
}

void MyGLWidget::resizeGL(int width, int height) {

    glViewport(0, 0, width, height); // задаю размер окна

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // загружаю едининчную матрицу

    // (-1 1 по x) (-1 1 по y) (1 расстояние от камеры до передней плоскости) (2 растоняние от камеры до задней плоскости)
    // glOrtho(-1, 1, -1, 1, 1, 2); // преобразую матрицу в ортогональную проекцию
    glFrustum(-1, 1, -1, 1, 1, 3); // преобразую матрицу в перспективную проекцию (область видимости объема)
}

void MyGLWidget::drawCube(float a) {
    float ver_cub[] = {
        -a, -a, a,     a, -a, a,        a, a, a,     -a, a, a, // передняя
        a, -a, -a,    -a, -a, -a,     -a, a, -a,     a, a, -a, // задняя
        -a, -a, -a,    -a, -a, a,     -a, a, a,     -a, a, -a, // левая
        a, -a, a,    a, -a, -a,     a, a, -a,     a, a, a, // правая
        -a, -a, a,    a, -a, a,     a, -a, -a,     -a, -a, -a, // нижняя
        -a, a, a,    a, a, a,     a, a, -a,     -a, a, -a, // верхняя
    };
    float color_arr[] {
        1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,
        0, 0, 1,    0, 0, 1,    0, 0, 1,    0, 0, 1,
        1, 1, 0,    1, 1, 0,    1, 1, 0,    1, 1, 0,
        0, 1, 1,    0, 1, 1,    0, 1, 1,    0, 1, 1,
        1, 0, 1,    1, 0, 1,    1, 0, 1,    1, 0, 1,
        1, 0.5, 0.5,    1, 0.5, 0.5,    1, 0.5, 0.5,    1, 0.5, 0.5
    };
    glVertexPointer(3, GL_FLOAT, 0, &ver_cub);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void MyGLWidget::mousePressEvent(QMouseEvent * mo) {
    mPos = mo->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent * mo) {
    xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
    yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
    update();
}
