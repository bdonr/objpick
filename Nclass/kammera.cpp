#include "kammera.h"
#include <iostream>

glm::vec3 Kammera::getEye() const
{
    return eye;
}

void Kammera::setEye(const glm::vec3 &value)
{
    eye = value;
}

glm::vec3 Kammera::getCenter() const
{
    return center;
}

void Kammera::setCenter(const glm::vec3 &value)
{
    center = value;
}

glm::vec3 Kammera::getUp() const
{
    return up;
}

void Kammera::setUp(const glm::vec3 &value)
{
    up = value;
}

glm::mat4 Kammera::getProjektionsMatrix() const
{
    return projektionsMatrix;
}

void Kammera::setProjektionsMatrix(const glm::mat4 &value)
{
    projektionsMatrix = value;
}

glm::mat4 Kammera::getLookAt() const
{
    return lookAt;
}

void Kammera::setLookAt(const glm::mat4 &value)
{
    lookAt = value;
}

glm::mat4 Kammera::getProjektionsMatrixZentrall() const
{
    return projektionsMatrixZentrall;
}

void Kammera::setProjektionsMatrixZentrall(const glm::mat4 &value)
{
    projektionsMatrixZentrall = value;
}

glm::vec2 Kammera::getFenster() const
{
    return fenster;
}

void Kammera::setFenster(const glm::vec2 &value)
{
    fenster = value;
}

float Kammera::getX() const
{
    return x;
}

void Kammera::setX(float value)
{
    x = value;
}

float Kammera::getY() const
{
    return y;
}

void Kammera::setY(float value)
{
    y = value;
}

float Kammera::getZ() const
{
    return z;
}

void Kammera::setZ(float value)
{
    z = value;
}

float Kammera::getR() const
{
    return r;
}

void Kammera::setR(float value)
{
    r = value;
}

float Kammera::getL() const
{
    return l;
}

void Kammera::setL(float value)
{
    l = value;
}

float Kammera::getB() const
{
    return b;
}

void Kammera::setB(float value)
{
    b = value;
}

float Kammera::getT() const
{
    return t;
}

void Kammera::setT(float value)
{
    t = value;
}

float Kammera::getF() const
{
    return f;
}

void Kammera::setF(float value)
{
    f = value;
}

float Kammera::getN() const
{
    return n;
}

void Kammera::setN(float value)
{
    n = value;
}

void Kammera::renew(){

    //--------------------------------------------------
    //paralelprojektion? matrix, normalized device coordinates ?
    projektionsMatrix = glm::mat4(glm::vec4(2/(r-l),0,0,-((r+l)/(r-l))),
                                  glm::vec4(0,2/(t-b),0,-((t+b)/(t-b))),
                                  glm::vec4(0,0,-2/(f-n),-((f+n)/(f-n))),
                                  glm::vec4(0,0,0,1));
    projektionsMatrixZentrall = glm::mat4(glm::vec4((2*n)/(r-l),0,(r+l)/(r-l),0),
                                          glm::vec4(0,(2*n)/(t-b),(t+b)/(t-b),0),
                                          glm::vec4(0,0,-((f+n)/(f-n)),-((2*f*n)/(f-n))),
                                          glm::vec4(0,0,-1,0));
    //--------------------------------------------------

}

Kammera::Kammera()
{
    x = 0;
    y = 0;
    z = -1.0;
    rotationX = 1;
    rotationY = 1,5;
    r = 1;
    l = -1;
    t = 1;
    b = -1;
    n = 1;
    f = -1;
    setFenster(glm::vec2(400,400));
    //--------------------------------------------------
    //paralelprojektion? matrix, normalized device coordinates ?
    projektionsMatrix = glm::mat4(glm::vec4(2/(r-l),0,0,-((r+l)/(r-l))),
                                  glm::vec4(0,2/(t-b),0,-((t+b)/(t-b))),
                                  glm::vec4(0,0,-2/(f-n),-((f+n)/(f-n))),
                                  glm::vec4(0,0,0,1));
    projektionsMatrixZentrall = glm::mat4(glm::vec4((2*n)/(r-l),0,(r+l)/(r-l),0),
                                          glm::vec4(0,(2*n)/(t-b),(t+b)/(t-b),0),
                                          glm::vec4(0,0,-((f+n)/(f-n)),-((2*f*n)/(f-n))),
                                          glm::vec4(0,0,-1,0));
    //--------------------------------------------------

    eye = glm::vec3(0,0,1.0);
    center = glm::vec3(0,0,0);
    up = glm::vec3(0,1.0,0);

    w = (center - eye);
    w = glm::normalize(w);

    v = up;
    v = glm::normalize(v);

    u = glm::cross(v,w);

    v = glm::cross(w,u);
    u = glm::normalize(u);
    v = glm::normalize(v);

lookAt = constructLookAt();

}

void Kammera::reset()
{
    x = 0;
    y = 0;
    z = -1;
    rotationX = 1;
    rotationY = 1,5;
    eye = glm::vec3(0,0,1.0);
    center = glm::vec3(0,0,0);
    up = glm::vec3(0,1.0,0);

    w = (center - eye);
    w = glm::normalize(w);

    v = up;
    v = glm::normalize(v);

    u = glm::cross(v,w);

    v = glm::cross(w,u);
    u = glm::normalize(u);
    v = glm::normalize(v);

lookAt = constructLookAt();

}

glm::mat4 Kammera::constructLookAt(){
    glm::mat4 temp = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                               glm::vec4(v.x,v.y,v.z,0),
                               glm::vec4(w.x,w.y,w.z,0),
                               glm::vec4(x,y,z,1));
    std::cout<<"const look at "<< w.x<<" "<<w.y<<" "<<w.z<<std::endl;
    return temp;
}

void Kammera::moveKammW(){
    z = z +0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Kammera::moveKammA()
{
    x = x -0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Kammera::moveKammS()
{
    z = z -0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Kammera::moveKammD()
{
    x = x +0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Kammera::moveKammUpY()
{
    y = y +0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}

void Kammera::moveKammDownX()
{
    y = y -0.1;
    lookAt = glm::mat4(glm::vec4(u.x,u.y,u.z,0),
                       glm::vec4(v.x,v.y,v.z,0),
                       glm::vec4(w.x,w.y,w.z,0),
                       glm::vec4(x,y,z,1));
}
/**
 *
 *
 *
**/
void Kammera::RotateKammLeft()
{
    std::cout<<"rota L"<<rotationX<<" "<<rotationY<<std::endl;
    rotationX = rotationX - 0.03;
    rotationY = rotationY - 0.03;

    eye = glm::vec3(0,0,0);
    center = glm::vec3(glm::sin(rotationX),0,glm::cos(rotationY));
    up = glm::vec3(0,1.0,0);

    w = (center -eye);
    w = glm::normalize(w);

    v = up;
    v = glm::normalize(v);

    u = glm::cross(v,w);

    v = glm::cross(w,u);
    u = glm::normalize(u);
    v = glm::normalize(v);

    lookAt = constructLookAt();
}

void Kammera::RotateKammRight()
{
    std::cout<<"rota L"<<rotationX<<" "<<rotationY<<std::endl;
    rotationX = rotationX + 0.03;
    rotationY = rotationY + 0.03;

    eye = glm::vec3(0,0,0);
    center = glm::vec3(glm::sin(rotationX),0,glm::cos(rotationY));
    up = glm::vec3(0,1.0,0);

    w = (center -eye);
    w = glm::normalize(w);

    v = up;
    v = glm::normalize(v);

    u = glm::cross(v,w);

    v = glm::cross(w,u);
    u = glm::normalize(u);
    v = glm::normalize(v);

    lookAt = constructLookAt();
}

// rotation der kammera um ein punkt, mit blick auf diesen punkt
//    rotation = rotation - 0.02;

//    eye = glm::vec3(0,0,1.0);
//    center = glm::vec3(glm::sin(rotation),0,glm::cos(rotation));
//    up = glm::vec3(0,1.0,0);

//    w = (center - eye);
//    w = glm::normalize(w);

//    v = up;
//    v = glm::normalize(v);

//u = glm::cross(v,w);

//v = glm::cross(w,u);
//u = glm::normalize(u);
//v = glm::normalize(v);

//lookAt = constructLookAt();
