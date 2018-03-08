#version 130

in vec3 position;
//in vec3 color;
in vec3 normal;

out vec3 fColor;

uniform mat4 projection;
uniform mat4 transform;
uniform vec3 lightPostion;  //position de la source lumineuse
uniform vec3 diffuseColor;

void main() {


  vec4 eyePosition=vec4(position,1); // passage en coordonnées homogènes
  eyePosition=transform*eyePosition; // application de la rotation
  vec4 clipPosition=projection*eyePosition; // transformation par la matrice de projection
  //vec4 clipPosition=vec4(position,1);
  gl_Position=clipPosition; // gl_Position doit être donné en clip coordinates

  //fColor=color;

 /*
  vec3 N = normal;
  vec3 L = lightPostion-position; //L= source-sommet
  N = normalize(N);
  L = normalize(L);
  float intensity = max(dot(N,L),0.0);
  //question23
  //fColor = vec3(intensity,intensity,intensity);
  //question23
  fColor=intensity*diffuseColor;
  */

  //Question25
  //rotation aux vecteurs
   vec4 N = transform*vec4(normal, 0);
   // L = L-P pour que la lumière ne tourne pas avec l'objet et reste fixe
   vec4 L = transform*vec4(lightPostion, 0)-vec4(position, 0);
   N = normalize(N);
   L = normalize(L);
   float intensity = max(dot(N,L), 0.0);
   fColor = intensity * diffuseColor;

}
