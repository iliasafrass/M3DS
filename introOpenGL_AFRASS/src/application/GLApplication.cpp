#include "GLApplication.h"

#include <iostream>

using namespace std;

GLApplication::~GLApplication() {
}

GLApplication::GLApplication() {
  /*
    _trianglePosition = {
    -0.8,-0.5,0.0, // vertex 0
    -0.2,-0.5,0.0, // 1
    -0.5,0.5,0.0,  // 2

    0.2,0.5,0.0,  // 3
    0.8,0.5,0.0,  // 4
    0.5,-0.5,0.0  // 5
  };


  _trianglePosition = {
     -0.8,-0.5,0.0, // vertex 0 anciennement vertex 0
     0.8,0.5,0.0,  // 1 anciennement 4
     -0.5,0.5,0.0,  // 2 anciennement 2
     -0.2,-0.5,0.0, // 3 anciennement 1
     0.5,-0.5,0.0,  // 4 anciennement 5
     0.2,0.5,0.0  // 5 anciennement 3
   };


  _trianglePosition = {
     -0.8,-0.8,0.0,
     0.8,0.8,0.0,
     0.0,0.2,0.0,
     -0.8,0.8,0.0,
     0.8,-0.8,0.0,
   };


  _trianglePosition = {
      -0.8,-0.8,0.0,
      -0.6,0.8,0.0,
      -0.4,-0.6,0.0,
      -0.2,0.6,0.0,
      0.0,-0.8,0.0,
      0.2,0.8,0.0,
      0.4,-0.6,0.0,
      0.6,0.6,0.0,
      0.8,-0.8,0.0
    };
    */
    _trianglePosition = {
        -0.8,-0.8,0.0,
        -0.8,0.8,0.0,
        -0.5,-0.8,0.0,
        -0.5,0.8,0.0,
        -0.2,-0.8,0.0,
        -0.2,0.8,0.0,
        0.1,-0.8,0.0,
        0.1,0.8,0.0
      };

  _elementData = {0,3,2,2,1,4};

  _inverser = false;
  _coeff = 1;
  _cte = 0.03;

  /*
  // tous les sommets à rouge :
    _triangleColor.clear();
    for(unsigned int i=0;i<9;++i) {
      _triangleColor.push_back(1);
      _triangleColor.push_back(0);
      _triangleColor.push_back(0);
      _triangleColor.push_back(1);
    }
*/
    //initStrip(40,-0.8,0.8,-0.8,0.8);

    //initRing(50,0.2,0.5);
    /*
  _triangleColor = {
    0.3,0.0,0.6,1,
    0.3,0.0,0.6,1,
    0.0,0.9,0.0,1,
    0.0,0.5,0.6,1,
    0.0,0.5,0.6,1,
    0.9,0.0,0.0,1
  };
*/
    _trianglePosition = { // rectangle tracé avec TRIANGLE_STRIP
        -0.6,-0.8,0,
        -0.6,0.8,0,
        0.6,-0.8,0,
        0.6,0.8,0
      };
      _triangleColor = { // tous les sommets en rouge
        1,0,0,1,
        1,0,0,1,
        1,0,0,1,
        1,0,0,1,
      };
      /*
      _triangleTexCoord = { // coordonnées de texture en chaque sommet
        0,1,
        0,0,
        1,1,
        1,0
      };
     */

      //l’image "à l’endroit"
      _triangleTexCoord = { // coordonnées de texture en chaque sommet
        0,0,
        0,1,
        1,0,
        1,1
      };

      /*
      //  la moitié de l’image
      _triangleTexCoord = { // coordonnées de texture en chaque sommet
        0,0,
        0,1,
        0.5,0,
        0.5,1
      };
      */
      initRing(50,0.15,0.5);
}


void GLApplication::initStrip(int nbSlice,float xmin,float xmax,float ymin,float ymax){
    _trianglePosition.clear();
     _triangleColor.clear();

    float dx = (xmax-xmin)/nbSlice;
    float x = xmin;
    float z = 0;
    float dColor;

    for(int i = 0; i < nbSlice; i++){

        dColor = (float)i/(float)(nbSlice-1);

        _triangleColor.push_back(0);
        _triangleColor.push_back(dColor);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1);

        _trianglePosition.push_back(x);
        _trianglePosition.push_back(ymin);
        _trianglePosition.push_back(z);

        _trianglePosition.push_back(x);
        _trianglePosition.push_back(ymax);
        _trianglePosition.push_back(z);

        _triangleColor.push_back(0);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1-dColor);
        _triangleColor.push_back(1);

        x+=dx;
    }
}

void GLApplication::initRing(int nbSlice,float r0,float r1){
    _trianglePosition.clear();
    _triangleColor.clear();
    _triangleTexCoord.clear();

    float x0,y0,x1,y1;
    float z = 0;
    float dTheta = 2*3.14159/nbSlice;
    float theta = 0;
    float dColor;


    for(int i = 0; i <= nbSlice; i++){
        dColor = (float)i/(float)(nbSlice-1);
        x0 = r0 * cos(theta);
        y0 = r0 * sin(theta);
        x1 = r1 * cos(theta);
        y1 = r1 * sin(theta);

        _triangleColor.push_back(0);
        _triangleColor.push_back(dColor);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1);

        _trianglePosition.push_back(x0);
        _trianglePosition.push_back(y0);
        _trianglePosition.push_back(z);



        _trianglePosition.push_back(x1);
        _trianglePosition.push_back(y1);
        _trianglePosition.push_back(z);



        _triangleColor.push_back(0);
        _triangleColor.push_back(0);
        _triangleColor.push_back(1-dColor);
        _triangleColor.push_back(1);

        /*-----------------------------Question 30----------------------------------*/
        /*
        float xi = 0.0;
        float slice = 1.0/nbSlice;
        _triangleTexCoord.push_back(xi);
        _triangleTexCoord.push_back(1);
        _triangleTexCoord.push_back(xi);
        _triangleTexCoord.push_back(0);
        xi += slice;
        */
        /*---------------------------------------------------------------------------*/


        /*-----------------------------Question 31----------------------------------*/
        float dr0 = r0;
        float dr1 = r1;

        while(dr0>1){
            dr0/=10;
        }
        while(dr1>1){
            dr1/=10;
        }

        float dx0,dy0,dx1,dy1;

        dx0 = 0.5 + (dr0 * cos(theta));
        dy0 = 0.5 + (dr0 * sin(theta));
        dx1 = 0.5 + (dr1 * cos(theta));
        dy1 = 0.5 + (dr1 * sin(theta));
        _triangleTexCoord.push_back(dx0);
        _triangleTexCoord.push_back(dy0);
        _triangleTexCoord.push_back(dx1);
        _triangleTexCoord.push_back(dy1);
        /*-------------------------------------------------------------------*/

        theta += dTheta;
    }


}




/** ********************************************************************** **/
void GLApplication::initialize() {
  // appelée 1 seule fois à l'initialisation du contexte
  // => initialisations OpenGL
  glClearColor(1,1,1,1);

  glLineWidth(2.0);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);


  _shader0=initProgram("simple");


  initTriangleBuffer();
  initTriangleVAO();
  initTexture();


}

void GLApplication::resize(int width,int height) {
  // appelée à chaque dimensionnement du widget OpenGL
  // (inclus l'ouverture de la fenêtre)
  // => réglages liés à la taille de la fenêtre
  glViewport(0,0,width,height);
  // ...
}

void GLApplication::update() {
  // appelée toutes les 20ms (60Hz)
  // => mettre à jour les données de l'application
  // avant l'affichage de la prochaine image (animation)
  // ...

  //-----l'animation-----//
/*
  if(!_inverser){
         _coeff -=_cte;
         if(_coeff<=0)
             _inverser = !_inverser;
     }else{
         _coeff +=_cte;
         if(_coeff>=1)
             _inverser = !_inverser;
     }
*/
}

void GLApplication::draw() {
  // appelée après chaque update
  // => tracer toute l'image
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(_shader0);
  glBindVertexArray(_triangleVAO);


  glUniform1f(glGetUniformLocation(_shader0,"coeff"),_coeff);
  //glDrawArrays(GL_TRIANGLES,0,6);

  //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

  //glDrawArrays(GL_TRIANGLES,0,9);
  //glDrawArrays(GL_TRIANGLE_STRIP,0,_trianglePosition.size()/3);

  glActiveTexture(GL_TEXTURE0); // on travaille avec l'unité de texture 0
  // dans l'instruction suivante, _textureId correspond à l'image "lagoon.jpg"; cf GLApplication::initTexture pour l'initialisation de _textureId
  glBindTexture(GL_TEXTURE_2D,_textureId); // l'unité de texture 0 correspond à la texture _textureId
  // (le fragment shader manipule des unités de textures et non les identifiants de texture directement)
  glUniform1f(glGetUniformLocation(_shader0,"textureUnit"),0); // on affecte la valeur du sampler2D du fragment shader à l'unité de texture 0.

  glDrawArrays(GL_TRIANGLE_STRIP,0,_trianglePosition.size()/3);

  glBindVertexArray(0);
  glUseProgram(0);




  snapshot(); // capture opengl window if requested
}

/** ********************************************************************** **/
/** i = button number, s = button text
 */
void GLApplication::leftPanel(int i,const std::string &s) {
  cout << "GLApplication : button clicked " << i << " " << s << endl;
  /*
  switch (i) {
    case 0:menu0();break;
    case 1:menu1();break;
  }
  */
}




/** *********************************************************** **/
GLuint GLApplication::initProgram(const std::string &filename) {
  GLuint program;
  int infoLength; // for message error

  string vertexSource=p3d::readTextFile(filename+".vert");
  string fragmentSource=p3d::readTextFile(filename+".frag");

  program=glCreateProgram();
  GLuint vertexShader=glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
  glAttachShader(program,vertexShader);
  glAttachShader(program,fragmentShader);

  const char *source;
  source=vertexSource.c_str();
  glShaderSource(vertexShader,1,&source,NULL);
  source=fragmentSource.c_str();
  glShaderSource(fragmentShader,1,&source,NULL);

  GLint ok;
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&ok);
  if (!ok) {
    glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH,&infoLength);
    cout << "=============================" << endl;
    cout << "GLSL Error : " << endl;
    char *info=new char[infoLength];
    glGetShaderInfoLog(vertexShader,infoLength,NULL,info);
    cout << info;
    cout << endl;
    delete info;
    throw ErrorD("Vertex Shader compilation error");
  }

  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&ok);
  if (!ok) {
    glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH,&infoLength);
    cout << "=============================" << endl;
    cout << "GLSL Error : " << endl;
    char *info=new char[infoLength];
    glGetShaderInfoLog(fragmentShader,infoLength,NULL,info);
    cout << info;
    cout << endl;
    delete info;
    throw ErrorD("Vertex Shader compilation error");
  }

  glBindAttribLocation(program,0,"position");
  glBindAttribLocation(program,1,"color");
  glBindAttribLocation(program,2,"texCoord");


  glLinkProgram(program);
  glGetProgramiv(program,GL_LINK_STATUS,&ok);
  if (!ok) {
    char *info=new char[infoLength];
    glGetProgramInfoLog(program,infoLength,NULL,info);
    cout << "Info Log :" << endl;
    cout << info;
    cout << endl;
    delete info;
    throw ErrorD("Program Shader : link error (varyings ok ?)");
  }

  return program;
}


void GLApplication::initTexture() {
    QImage img;
    img.load("../media/lagoon.jpg");
    img=img.convertToFormat(QImage::Format_ARGB32).mirrored();

    glGenTextures(1,&_textureId);
    glBindTexture(GL_TEXTURE_2D,_textureId);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img.width(),img.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img.bits());



    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
}


void GLApplication::initTriangleBuffer() {

  glGenBuffers(1,&_trianglePositionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER,_trianglePositionBuffer);
  glBufferData(GL_ARRAY_BUFFER,_trianglePosition.size()*sizeof(float),_trianglePosition.data(),GL_STATIC_DRAW);

  glGenBuffers(1,&_triangleColorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER,_triangleColorBuffer);
  glBufferData(GL_ARRAY_BUFFER,_triangleColor.size()*sizeof(float),_triangleColor.data(),GL_STATIC_DRAW);

  glGenBuffers(1,&_elementBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,_elementData.size()*sizeof(float),_elementData.data(),GL_STATIC_DRAW);

  glGenBuffers(1,&_triangleTexCoordBuffer);
  glBindBuffer(GL_ARRAY_BUFFER,_triangleTexCoordBuffer);
  glBufferData(GL_ARRAY_BUFFER,_triangleTexCoord.size()*sizeof(float),_triangleTexCoord.data(),GL_STATIC_DRAW);
}


void GLApplication::initTriangleVAO() {
  glGenVertexArrays(1,&_triangleVAO);
  glBindVertexArray(_triangleVAO);

  glBindBuffer(GL_ARRAY_BUFFER,_trianglePositionBuffer);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

  glBindBuffer(GL_ARRAY_BUFFER,_triangleColorBuffer);
  glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,0,0);


  glBindBuffer(GL_ARRAY_BUFFER,_triangleTexCoordBuffer);
  glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,0);


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);


  glBindVertexArray(0);
}



