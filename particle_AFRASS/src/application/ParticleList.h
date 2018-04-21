#ifndef PARTICULELIST_H
#define PARTICULELIST_H

#include "Particle.h"
#include "Texture.h"
#include <vector>
#include <list>

enum EParticleMode {PARTICLE_POINT,PARTICLE_SPHERE};

class ParticleList : public std::vector<Particle *> {
  public:
    ParticleList();
    virtual ~ParticleList();

    void initState(Particle *p);


    void computeForce();

    void euler(double dt);

    void add(Particle *p);

    void draw();
    void particleMode(EParticleMode mode) {_particleMode=mode;}
    EParticleMode particleMode() {return _particleMode;}


    void updateLife();

    void collisionGround();

    void birthRate(double nb);

    void texture(p3d::Texture *t);

    void drawData();

    void maxi(unsigned int nb);

    void link(unsigned int i,unsigned int j);

    unsigned int nbParticle();

    void startTime();

  protected:
  private:

  std::list<Particle *> _freeList;
  double _nbLatent;
  double _lastTime;
  double _nbpersec;
  p3d::Texture *_texture;
  unsigned int _nbMaxi;

  EParticleMode _particleMode;
  Particle *_tabParticle;
};

#endif // PARTICULELIST_H

