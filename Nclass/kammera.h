#ifndef KAMMERA_H
#define KAMMERA_H
#include "glm/glm.hpp"
#include "vector"

class Kammera
{
private:
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
    glm::vec3 u;
    glm::vec3 v;
    glm::vec3 w;
    glm::mat4 projektionsMatrix;
    glm::mat4 projektionsMatrixZentrall;
    glm::mat4 lookAt;
    float x;
    float y;
    float z;
    float rotationX;
    float rotationY;

    float r;
    float l;
    float b;
    float t;
    float f;
    float n;

    glm::vec2 fenster;
public:
    Kammera();
    void renew();
    void reset();
    glm::mat4 constructLookAt();
    glm::vec3 getEye() const;
    void setEye(const glm::vec3 &value);
    glm::vec3 getCenter() const;
    void setCenter(const glm::vec3 &value);
    glm::vec3 getUp() const;
    void setUp(const glm::vec3 &value);
    glm::mat4 getProjektionsMatrix() const;
    void setProjektionsMatrix(const glm::mat4 &value);
    glm::mat4 getLookAt() const;
    void setLookAt(const glm::mat4 &value);
    void moveKammW();
    void moveKammA();
    void moveKammS();
    void moveKammD();
    void moveKammUpY();
    void moveKammDownX();
    void RotateKammLeft();
    void RotateKammRight();

    glm::mat4 getProjektionsMatrixZentrall() const;
    void setProjektionsMatrixZentrall(const glm::mat4 &value);
    glm::vec2 getFenster() const;
    void setFenster(const glm::vec2 &value);
    float getX() const;
    void setX(float value);
    float getY() const;
    void setY(float value);
    float getZ() const;
    void setZ(float value);
    float getR() const;
    void setR(float value);
    float getL() const;
    void setL(float value);
    float getB() const;
    void setB(float value);
    float getT() const;
    void setT(float value);
    float getF() const;
    void setF(float value);
    float getN() const;
    void setN(float value);
};

#endif // KAMMERA_H
