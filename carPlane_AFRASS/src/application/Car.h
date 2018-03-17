#ifndef INCCAR_H
#define INCCAR_H

/**
  @author F. Aubert
  **/

#include "GLTool.h"
#include "Vector3.h"
#include "Quaternion.h"

class Car {
  p3d::Vector3 _position;// la position de l'origine de la voiture (par rapport au repère du monde)
  p3d::Quaternion _orientation;// et son orientation (par rapport au repère du monde)

  double _velocity;
  double _acceleration;

  float _rotateWheel; // rotation roue
  float _steering; // rotation/essieu

public:
  virtual ~Car();
  Car();

  p3d::Vector3 position() {return _position;}
  p3d::Quaternion orientation() {return _orientation;}

  void drawWorld();

  void draw();

  void drawRim();
  void drawWheel();
  void drawAxle();
  void drawBody();

  void rotateWheel(double angle) {_rotateWheel+=angle;}

  void accelerate();
  void decelerate();
  void brake();
  void turnLeft();
  void turnRight();
  void move();

  void drawCube() {p3d::shaderLightPhong();p3d::drawCube();}
  void drawTorus() {p3d::shaderLightPhong();p3d::drawTorus();}
  void drawSphere() {p3d::shaderLightPhong();p3d::drawSphere();}
  void drawCone() {p3d::shaderLightPhong();p3d::drawCone();}
  void drawCylinder() {p3d::shaderLightPhong();p3d::drawCylinder();}

};

#endif // INCCAR_H

