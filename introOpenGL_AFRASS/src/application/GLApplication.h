#ifndef GLAPPLICATION_H
#define GLAPPLICATION_H


#include "GLWidget.h"
#include "Tools.h"

#include <string>

class GLApplication : public GLWidget {
  Q_OBJECT  
public:
  GLApplication();
  virtual ~GLApplication();


  /** ***** **/
  /** GLApplication must implement these methods : */
  virtual void initialize();
  virtual void update();
  virtual void draw();
  virtual void resize(int width,int height);
  /** ***** **/
  virtual void leftPanel(int i, const std::string &s);
  virtual QSize sizeHint() const {return QSize(1000,1000);}
  /** ***** **/
  GLuint initProgram(const std::string &filename);
  void initTriangleBuffer();
  void initTriangleVAO();
  void initTexture();

  void initStrip(int nbSlice,float xmin,float xmax,float ymin,float ymax);
  void initRing(int nbSlice,float r0,float r1);

private:
  std::vector<float> _trianglePosition;
  std::vector<float> _triangleColor;
  std::vector<float> _triangleTexCoord;

  GLuint _trianglePositionBuffer;
  GLuint _triangleColorBuffer;
  GLuint _triangleTexCoordBuffer;
  GLuint _elementBuffer;

  std::vector<unsigned int> _elementData;

  float _coeff;
  boolean _inverser;
  float _cte;

  GLuint _triangleVAO;
  GLuint _shader0;
  GLuint _textureId;



};

#endif // GLAPPLICATION_H

