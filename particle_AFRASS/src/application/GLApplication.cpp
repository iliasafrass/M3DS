/**

  @author F. Aubert
  **/


#include "GLApplication.h"
#include "GLTool.h"
#include <iostream>


using namespace std;
using namespace p3d;

/// dtor
///
GLApplication::~GLApplication() {

}


/// ctor
GLApplication::GLApplication() {
  _leftPanelMenu << "Particle" << "Sphere" << "Animate";


  _frustum=0.1;
  _camera.frustum(-_frustum,_frustum,-_frustum,_frustum,0.3,1000);
  _camera.position(Vector3(0,0,10));
  _camera.lookAt(Vector3(0,0,0),Vector3(0,1,0));

  _animate=true;



  initParticle(PARTICLE_POINT);
  _engine.particleList(&_particleList);

  // Ajout de plans (gérés par la détection de collision) :
  // le sol :
  _engine.addPlane(new Plane(Vector3(0,-3,0),Vector3(0,1,0)));

  // des "murs" (non visibles)


  _engine.addPlane(new Plane(Vector3(-4,0,0),Vector3(1,0,0)));
  _engine.addPlane(new Plane(Vector3(4,0,0),Vector3(-1,0,0)));
  _engine.addPlane(new Plane(Vector3(0,0,-4),Vector3(0,0,1)));
  _engine.addPlane(new Plane(Vector3(0,0,4),Vector3(0,0,-1)));




}


void GLApplication::initParticle(EParticleMode mode) {
  _particleList.particleMode(mode);
  if (mode==PARTICLE_POINT) {
    _particleList.birthRate(5);
    _particleList.maxi(2000);
  }
  else if (mode==PARTICLE_SPHERE) {
    _particleList.birthRate(5);
    _particleList.maxi(2000);
  }
}


void GLApplication::initialize() {
  // appelée 1 seule fois à l'initialisation du contexte
  // => initialisations OpenGL

  glClearColor(1,1,1,1);

  glLineWidth(4);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearDepth(1);

  initGLTool();
  glPointSize(4.0);


  _particleTexture.read("lightmap.png");
  _particleTexture.setAlpha(Vector4(0,0,0,0),0.0,0.1);

  _particleList.texture(&_particleTexture);



  _groundTexture.read("mosaic_pierre.jpg");
  _groundTexture.generateMipmap();


}



/** ***************************************************************************
resize
  **/


void GLApplication::resize(int width,int height) {
  // appelée à chaque dimensionnement du widget OpenGL
  // (inclus l'ouverture de la fenêtre)
  // => réglages liés à la taille de la fenêtre
  _camera.viewport(0,0,width,height);
}





void GLApplication::update() {
  updateCamera();

  if (mouseRight()) {
    bool ok=_camera.windowToRayWorld(Vector2(mouseX(),mouseY()),&_windRay);
    _engine.enableWind(_windRay);
  }
  else {
    _engine.disableWind();
  }
  if (_animate) _engine.update();


  if (keyPressed(Qt::Key_Space)) {
  }
}

void GLApplication::leftPanel(int i,const std::string &s) {
  cout << "GLApplication : button clicked " << i << " " << s << endl;
  switch(i) {
  case 0:
    initParticle(PARTICLE_POINT);
    break;
  case 1:
    initParticle(PARTICLE_SPHERE);
    break;
  case 2:
    _animate=!_animate;
    _particleList.startTime();
    break;
  }

}

void GLApplication::updateCamera() {
  if (mouseLeft()) {
    Vector3 center=_camera.pointTo(Coordinate_Local,Vector3(0,0,0));
    Vector3 vertical=Vector3(0,1,0);
    _camera.translate(center,Coordinate_Local);
    _camera.rotate(-deltaMouseX()/2.0,vertical,Coordinate_World);
    _camera.rotate(deltaMouseY()/2.0,Vector3(1,0,0),Coordinate_Local);
    _camera.translate(-center,Coordinate_Local);
  }
  if (left()) _camera.left(0.3);
  if (right()) _camera.right(0.3);
  if (forward()) _camera.forward(0.3);
  if (backward()) _camera.backward(0.3);
  if (accelerateWheel()) {
    _frustum*=1.05;
    _camera.frustum(-_frustum,_frustum,-_frustum,_frustum,0.3,1000);
  }
  if (decelerateWheel()) {
    _frustum/=1.05;
    _camera.frustum(-_frustum,_frustum,-_frustum,_frustum,0.3,1000);
  }
}




void GLApplication::draw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  p3d::apply(_camera);


  drawGround();
  _engine.draw();


  glUseProgram(0);

  snapshot(); // capture opengl window if requested

}

/** ********************************************************************************
 *
 *
**/



void GLApplication::drawGround() {
  p3d::modelviewMatrix.push();
  p3d::textureMatrix.push();
  p3d::textureMatrix.scale(135,135,135);
  p3d::modelviewMatrix.translate(0,-3,0);
  p3d::modelviewMatrix.scale(10,10,10);
  p3d::ambientColor=Vector4(0.1,0.1,0.1,1.0);
  p3d::shaderTextureLight();
  p3d::drawGround(_groundTexture);
  p3d::textureMatrix.pop();
  p3d::modelviewMatrix.pop();
}







