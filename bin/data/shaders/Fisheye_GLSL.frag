///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2003, ATI Technologies, Inc., All rights reserved.
//
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose and without fee is hereby granted,
// provided that the above copyright notice appear in all copies and derivative
// works and that both the copyright notice and this permission notice appear in
// support documentation, and that the name of ATI Technologies, Inc. not be used
// in advertising or publicity pertaining to distribution of the software without
// specific, written prior permission.
//
///////////////////////////////////////////////////////////////////////////////

#define EPSILON 0.000011

// vertex to fragment shader io
varying vec2 texcoord0;
varying vec2 texdim0;

// globals
uniform float lensradius;
uniform float signcurvature;

// samplers
uniform sampler2DRect tex0;

// entry point
void
main()
{
    float curvature = abs(signcurvature);
    float extent = lensradius;
    float optics = extent / log2(curvature * extent + 1.0) / 1.4427;
    vec2 normalizeTD = texcoord0/texdim0;
    vec2 PP = normalizeTD - vec2(0.5,0.5);
    float P0 = PP[0];
    float P1 = PP[1];
    float radius = sqrt(P0 * P0 + P1 * P1);
    
    float cosangle = P0 / radius;
    float sinangle = P1 / radius;
    
    float rad1, rad2, newradius;
    rad1 = (exp2((radius / optics) * 1.4427) - 1.0) / curvature;
    rad2 = optics * log2(1.0 + curvature * radius) / 1.4427;
    newradius = signcurvature > 0.0 ? rad1 : rad2;
    
    vec2 FE = vec2(newradius * cosangle + 0.5,newradius * sinangle + 0.5);
    FE = radius <= extent ? FE : normalizeTD;
    FE = curvature < EPSILON ? normalizeTD : FE;
    
    gl_FragColor = texture2DRect(tex0, FE*texdim0);
}
