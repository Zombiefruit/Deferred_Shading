// G-buffer renderer

#ifndef RENDER_H
#define RENDER_H


#include "wavefront.h"
#include "gpuProgram.h"
#include "gbuffer.h"


class Renderer {

  enum { SHADOW_GBUFFER, NUM_GBUFFERS };

  int        textureTypes[NUM_GBUFFERS];
  GPUProgram *pass1Prog, *pass2Prog;
  GBuffer    *gbuffer;

 public:

  int debug;

  Renderer( int windowWidth, int windowHeight ) {

    textureTypes[ SHADOW_GBUFFER ] = GL_R32F;

    gbuffer = new GBuffer( windowWidth, windowHeight, NUM_GBUFFERS, textureTypes );

    pass1Prog = new GPUProgram( "pass1.vert", "pass1.frag" );
    pass2Prog = new GPUProgram( "pass2.vert", "pass2.frag" );

    debug = 0;
  }

  ~Renderer() {
    delete gbuffer;
    delete pass2Prog;
    delete pass1Prog;
  }

  void reshape( int windowWidth, int windowHeight ) {
    delete gbuffer;
    gbuffer = new GBuffer( windowWidth, windowHeight, NUM_GBUFFERS, textureTypes );
  }

  void render( seq<wfModel *> &objs, mat4 &WCS_to_VCS, mat4 &WCS_to_CCS, vec3 &lightDir, vec3 &eyePosition );

  void incDebug() {
    debug = (debug+1) % 2;
  }

  bool debugOn() {
    return (debug > 0);
  }

  void makeStatusMessage( char *buffer ) {
    if (debug == 0)
      sprintf( buffer, "Program output" );
    else
      sprintf( buffer, "After pass %d", debug );
  }
};

#endif
