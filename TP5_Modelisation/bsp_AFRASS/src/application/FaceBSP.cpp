#include "FaceBSP.h"
#include "GLTool.h"
#include "ObjectBSP.h"
#include <math.h>

using namespace p3d;
using namespace std;

/**
* @author Fabrice Aubert
*/

/** ********************************************************
  Trois méthodes à compléter pour le TP : sign, intersection et separe

*/


/// détermine le coté du point P par rapport à la face (le résultat de type ESign peut être SIGN_MINUS or SIGN_PLUS)
ESign FaceBSP::sign(const Vector3 &p) const {
  /// méthodes utiles :
  /// - _tabVertex[i]->point() : vous donnera les coordonnées (de type Vector3) du sommet i-ième sommet de la face (i commence à 0)
  /// - _normal : vous donnera la normale (de type Vector3) de la face
  /// - v1.dot(v2) : produit scalaire entre 2 Vector3
  /// - Vector3 v(p1,p2) : construit v avec p2-p1. On peut également faire directement v=p2-p1


  ESign res=SIGN_NONE;

  // TODO : A COMPLETER
  //Exercice3Q1
  if(_tabVertex.size() > 0)
      if(Vector3(_tabVertex[0]->point(), p).dot(_normal) >= 0)
          res = SIGN_PLUS;
      else
          res = SIGN_MINUS;

  return res;
}


/// Donne le point d'intersection avec le segment [p1p2] (précondition p1 et p2 de signes distincts par rapport à this)
Vector3 FaceBSP::intersection(const Vector3 &p1,const Vector3 &p2) const {
  /// il suffit de résoudre AI.n=0 (plan (A,n)) et I=p1+k*p1p2 (droite donnée par (p1,p2))
  /// - point(i) : vous donne les coordonnées (type Vector3) du sommet i de la facette
  /// - normal() : vous donne la normale de la facette (type Vector3)
  /// - quelques opérateurs sur les Vector3 peuvent être utiles. Exemple : u=b-a, p=a+k*u, etc (avec a,b,p et u de type Vector3)
  /// - u1.dot(u2) : produit scalaire

  Vector3 res;

  // TODO : A COMPLETER
  Vector3 A = point(0);
  Vector3 u(p1,p2);


  //pour la résolution des équation voir le readme
  double scalAp1 = Vector3(A, p1).dot(normal());
  double scalU = u.dot(normal());
  if (fabs(scalU) < 0.01 ) //question4
     return (p1 + p2) / 2;

  double k = - scalAp1 / scalU;

  if ( fabs(k) < 0.01) //question4
      return p1;

  res = p1 + k * u;



  return res;
}


/// coupe la facette this selon f (i.e. this est découpée par le plan porteur de f) :
/// précondition : this doit être **convexe**
void FaceBSP::separe(const FaceBSP &f) {
  /// - il faut séparer les sommets de this dans les tableaux vertexNegative et vertexPositive (algo de séparation vu en cours)
  ///   - VertexBSP *a=_tabVertex[i] vous donne le i-ième sommet de la face this.
  ///   - _tabVertex.size() vous donne le nombre de sommet de this.
  ///   - vertexNegative.push_back(v) ajoutera le sommet v à vertexNegative (simil. pour vertexPositive).
  /// - lors d'une intersection :
  ///   - il faut créer un nouveau sommet : utilisez VertexBSP *inter=createVertex(un_vector3) qui crée le VertexBSP à partir d'un point.
  ///                                      NE PAS faire de inter=new VertexBSP() (gestion mémoire assurée par createVertex)
  ///   - pour avoir un éclairage correct (comme sur les images du sujet), il faut également calculer la normale du nouveau sommet inter créé :
  ///     il suffit de faire inter->interpolateNormal(*v1,*v2); où v1 et v2 sont les deux VertexBSP * qui ont provoqué l'intersection
  vector<VertexBSP *> vertexNegative;
  vector<VertexBSP *> vertexPositive;
  vertexNegative.clear();
  vertexPositive.clear();

// TODO : à compléter

  //exercice4q1

    VertexBSP *oldV = nullptr;
    VertexBSP *v = _tabVertex[0];

    //1er point
    switch (f.sign(v->point())) {
    case SIGN_PLUS:
        vertexPositive.push_back(v);
        break;
    case SIGN_MINUS:
        vertexNegative.push_back(v);
        break;
    default:
        break;
    }


    //suite des points et découpe si besoin est
    for(int i = 1; i < _tabVertex.size(); i++) {
        oldV = v;
        v = _tabVertex[i];

        if(f.sign(oldV->point()) != f.sign(v->point())) {
            VertexBSP *inter=createVertex(f.intersection(oldV->point(), v->point()));
            inter->interpolateNormal(*oldV, *v);
            vertexPositive.push_back(inter);
            vertexNegative.push_back(inter);
        }

        switch (f.sign(v->point())) {
        case SIGN_PLUS:
            vertexPositive.push_back(v);
            break;
        case SIGN_MINUS:
            vertexNegative.push_back(v);
            break;
        default:
            break;
        }

    }

    //pour la fermeture
    oldV = v;
    v = _tabVertex[0];

    if(f.sign(oldV->point()) != f.sign(v->point())) {
        VertexBSP *inter=createVertex(f.intersection(oldV->point(), v->point()));
        inter->interpolateNormal(*oldV, *v);
        vertexPositive.push_back(inter);
        vertexNegative.push_back(inter);
    }


// A LAISSER à la fin ! (construction des faces selon les tableaux de points)
  createFace(vertexNegative,vertexPositive);
  if ((_facePositive==NULL) && (_faceNegative==NULL)) throw ErrorD("Face découpée en rien du tout (ni plus, ni moins)");

}

/** ************************************************************************ */
/** ************************************************************************ */
FaceBSP::~FaceBSP() {
}


void FaceBSP::createFace(const vector<VertexBSP *> &moins,const vector<VertexBSP *> &plus) {
  if (moins.empty()) {
    _faceNegative=NULL;
    _facePositive=this;
  }
  else if (plus.empty()) {
    _facePositive=NULL;
    _faceNegative=this;
  }
  else {
    this->copyVertexFrom(plus);
    _facePositive=this;
    _faceNegative=createFace(moins);
  }
}

void FaceBSP::copyVertexFrom(const vector<VertexBSP *> &liste ) {
  _tabVertex.clear();
  for(unsigned int i=0;i<liste.size();i++) {
    _tabVertex.push_back(liste[i]);
  }
}

FaceBSP *FaceBSP::createFace(const vector<VertexBSP *> &liste) {
  if (liste.empty())
    return NULL;
  else {
    FaceBSP *res;
    res=_owner->createFace();
    for(unsigned int i=0; i<liste.size(); i++) {
      res->add(liste[i]);
    }
    res->normal(this->normal());
    return res;
  }
}


FaceBSP::FaceBSP(ObjectBSP *owner) {
  _owner=owner;
  _owner->add(this);
  _tabVertex.clear();
  _markDelete=false;

  _faceNegative=NULL;
  _facePositive=NULL;
}

VertexBSP *FaceBSP::createVertex(const Vector3 &p) {
  VertexBSP *res=_owner->createVertex(p);
  return res;
}


void FaceBSP::addDraw() {
  addDrawFill();
  addDrawWire();
}

void FaceBSP::addDrawFill() {
  for(unsigned int i=1; i<_tabVertex.size()-1; ++i) {
    _owner->_drawPtsFill.push_back(_tabVertex[0]->point());
    _owner->_drawNormalFill.push_back(_tabVertex[0]->normal());
    _owner->_drawPtsFill.push_back(_tabVertex[i]->point());
    _owner->_drawNormalFill.push_back(_tabVertex[i]->normal());
    _owner->_drawPtsFill.push_back(_tabVertex[i+1]->point());
    _owner->_drawNormalFill.push_back(_tabVertex[i+1]->normal());
  }
}

void FaceBSP::addDrawWire() {
  _owner->_drawPtsWire.push_back(_tabVertex[0]->point());
  for(unsigned int i=1; i<_tabVertex.size(); ++i) {
    _owner->_drawPtsWire.push_back(_tabVertex[i]->point());
    _owner->_drawPtsWire.push_back(_tabVertex[i]->point());
  }
  _owner->_drawPtsWire.push_back(_tabVertex[0]->point());
}

void FaceBSP::add(VertexBSP *v) {
//  if (_tabVertex.empty() || (((_tabVertex[0]->point().distance2(v->point())>0.0000001) && ((_tabVertex[_tabVertex.size()-1]->point().distance2(v->point())>0.000001)))))
  _tabVertex.push_back(v);
}



