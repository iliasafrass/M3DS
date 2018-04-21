#include "ParticleList.h"

#include "Texture.h"

#include <ctime>
#include <cstdlib>

#include "GLTool.h"

using namespace std;
using namespace p3d;


/** random number in [a,b] **/
double randDouble(double a, double b) {
  double c=double(rand())/RAND_MAX;
  return c*(b-a)+a;
}

/** random number in [0,1] **/
double randUnit() {
  return double(rand())/RAND_MAX;
}



/** Données initiales d'une particule
**/
void ParticleList::initState(Particle *p) {

  if (_particleMode==PARTICLE_POINT) {
    p->position(Vector3(randDouble(-1,1),randDouble(-1,1),0));
    p->velocity(2.0*Vector3(randDouble(-1,1),randDouble(0,5),randDouble(-1,1)));
    p->timeOfLife(randDouble(4,10)); // entre 4 et 10 secondes
    p->mass(1.0);

    p->color(randDouble(0,1),randDouble(0,1),0.8);
  }
  else if (_particleMode==PARTICLE_SPHERE) {
    //Exercice3Question1
    p->position(Vector3(randDouble(-1,1),5.0,randDouble(-1,1)));
    p->velocity(Vector3(0.0, 0.0, 0.0));

    //p->position(Vector3(0,0,0));
    //p->velocity(Vector3(0,0,0));
    p->timeOfLife(randDouble(4,10)); // entre 4 et 10 secondes
    p->mass(1.0);

    p->color(randDouble(0,1),randDouble(0,1),0.8);
  }

}



ParticleList::ParticleList() {
  //ctor
  clear();
  _lastTime=clock()/CLOCKS_PER_SEC;  // time 0
  _nbMaxi=2000;                      // nb live particles (no more than _nbMaxi at once)
  _freeList.clear();                 // dead particles (new particles are re-born from this list)
  _particleMode=PARTICLE_POINT;      // _modeParticle = PARTICLE_POINT or PARTICLE_SPHERE
  _tabParticle=NULL;                 //
  _texture=NULL;
}

ParticleList::~ParticleList() {
  //dtor
  delete[] _tabParticle;
}








void ParticleList::add(Particle *p) {
  push_back(p);
}


void ParticleList::texture(Texture *t) {
  _texture=t;
}


void ParticleList::draw() {

  _texture->bind();


  for(unsigned int i=0;i<size();i++) {
    if ((*this)[i]->alive()) {
      if (_particleMode==PARTICLE_POINT) {
        (*this)[i]->drawPoint();
      }
      else if (_particleMode==PARTICLE_SPHERE) {
        (*this)[i]->drawSphere();
      }
    }
  }

}

void ParticleList::birthRate(double nb) {
  _nbpersec=nb;
}

void ParticleList::updateLife() {
  double elapsed=double(clock())/CLOCKS_PER_SEC-_lastTime;
  _nbLatent+=elapsed*_nbpersec;
  while ((_nbLatent>=1) && (_freeList.size()>0)) {
    Particle *newp;
    newp=_freeList.front();
    _freeList.pop_front();
    initState(newp);
    newp->birth(); // set birthdate
    _nbLatent-=1;
  }
  _lastTime+=elapsed;


  unsigned int nbAlive=0;
  for(unsigned int i=0;i<size();i++) {
    if ((*this)[i]->alive()) {
      (*this)[i]->updateLife();
      if ((*this)[i]->dead()) {
        _freeList.push_back((*this)[i]);
      }
      nbAlive++;
    }
  }
}

void ParticleList::drawData() {
  for(unsigned int i=0;i<size();i++) {
    Particle *p=(*this)[i];
    glColor3f(0,0,1);
    p3d::drawArrow(p->position(),Vector3(2.0*p->velocity()),0.2,"","Vitesse");
    glColor3f(0,1,0);
    if (p->force().length()>0.1)
    p3d::drawArrow(p->position(),Vector3(10.0*p->force()),0.2,"","Force");
  }
}

void ParticleList::maxi(unsigned int nb) {
  clear();
  _nbMaxi=nb;
  _freeList.clear();
  delete[] _tabParticle;
  _tabParticle=new Particle[nb];
  for(unsigned int i=0;i<nb;i++) {
    this->push_back(_tabParticle+i);
    _freeList.push_back(_tabParticle+i);
  }
}

unsigned int ParticleList::nbParticle() {
  return size()-_freeList.size();
}


void ParticleList::link(unsigned int i,unsigned int j) {
  i=0;
  j=0;
}


void ParticleList::startTime() {
  _lastTime=clock()/CLOCKS_PER_SEC;
}


