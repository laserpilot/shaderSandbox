#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofTexture tex1;
    ofTexture tex2;
    ofFbo       chromaFbo;      //For storing the FBO contents of the chromatic abberation shader
    ofFbo       brcosaFbo;      //For storing the FBO contents of brcosa shader
    ofShader bloomShader;       //Bloom shader (from OF forums)
    ofShader blurShader;        //So-so Gaussian Blur
    ofShader brcosaShader;      //Brightness, Contrast, Saturation adjustments
    ofShader chromaShader;      //Poor mans chromatic abberation
    ofShader fishShader;        //Fisheye
    ofShader rotaShader;        //Shader from jit.rota allowing you to zoom, rotate, offset a texture
    ofShader carToPolShader;    //Cartesian to polar shader
    ofShader wobbleShader;      //Wobbulation displacement
    ofShader lumaShader;        //Luma Keying
    ofShader radialShader;      //RadialBlur
    
    int camWidth;
    int camHeight;
    ofVideoGrabber vidGrabber;
};
