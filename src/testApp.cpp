#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //CHECK ALL SHADER PERMISSIONS BEFORE RELEASING
    
    camWidth=640;
    camHeight = 480;

    vidGrabber.initGrabber(camWidth, camHeight);
    
    tex1.setTextureWrap(GL_REPEAT, GL_REPEAT);
    tex1.allocate(400,400,GL_RGB,GL_RGBA);

    brcosaFbo.allocate(320, 240, GL_RGBA);
    brcosaFbo.begin();
    ofClear(0, 0, 0,0); //Clear the FBO
    brcosaFbo.end();
    
    chromaFbo.allocate(320, 240, GL_RGBA);
    chromaFbo.begin();
    ofClear(0, 0, 0,0); //Clear the FBO
    chromaFbo.end();
    
    cout<<"Load BLOOM"<<endl;
    bloomShader.load( "shaders/bloom_GLSL"); //Loads both frag and vert if they are named correctly
    cout<<"Load BRCOSA"<<endl;
    brcosaShader.load( "shaders/brcosa_GLSL");
    cout<<"Load CHROMA"<<endl;
    chromaShader.load("shaders/ChromaAb_GLSL");
    cout<<"Load BLUR"<<endl;
    blurShader.load("shaders/Gauss_GLSL");
    cout<<"Load FISHEYE"<<endl;
    fishShader.load("shaders/Fisheye_GLSL");
    cout<<"Load ROTA"<<endl;
    rotaShader.load("shaders/Rota_GLSL");
    cout<<"Load CARTOPOL"<<endl;
    carToPolShader.load("shaders/CarToPol_GLSL");
    cout<<"Load WOBBLE"<<endl;
    wobbleShader.load("shaders/Wobble_GLSL");
    cout<<"Load LUMAKEY"<<endl;
    lumaShader.load("shaders/LumaKey_GLSL");
    cout<<"Load RADIAL"<<endl;
    radialShader.load("shaders/Radial_GLSL");
}

//--------------------------------------------------------------
void testApp::update(){
    vidGrabber.update();
    
    if (vidGrabber.isFrameNew()) {
        tex1=vidGrabber.getTextureReference();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackgroundGradient(ofColor::gray, ofColor::black);
    
    ///BLOOM BLOOM BLOOM------------------------
    ofEnableNormalizedTexCoords(); //This lets you do 0-1 range instead of 0-640 (in pixels)
    tex1.bind();
    bloomShader.begin();
    bloomShader.setUniformTexture("tex0", tex1, 0);
    bloomShader.setUniform1f("bloom", 5*sin(ofGetElapsedTimef()));

    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
     glTexCoord2f(1,0); glVertex3f(320,0,0);
     glTexCoord2f(1,1); glVertex3f(320,240,0);
     glTexCoord2f(0,1); glVertex3f(0,240,0);
    
    glEnd();
    bloomShader.end();
    tex1.unbind();

    ///BRCOSA BRCOSA BRCOSA----------------------
    //Brightness/Contrast/Saturation
    tex1.bind();
    brcosaShader.begin();
    brcosaShader.setUniformTexture("tex0", tex1, 0);
    brcosaShader.setUniform1f("contrast", 1.0);
    brcosaShader.setUniform1f("brightness", 1.0);
    brcosaShader.setUniform1f("saturation", 5*sin(ofGetElapsedTimef()));
    brcosaShader.setUniform1f("alpha", 1.0);

    ofPushMatrix();
        ofTranslate(320,0);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(0,0,0);
        glTexCoord2f(1,0); glVertex3f(320,0,0);
        glTexCoord2f(1,1); glVertex3f(320,240,0);
        glTexCoord2f(0,1); glVertex3f(0,240,0);
        glEnd();
    ofPopMatrix();
    brcosaShader.end();
    tex1.unbind();
    
    ///ChromaAbberation----------------------------
    tex1.bind();
    chromaShader.begin();
    chromaShader.setUniformTexture("tex", tex1, 0);
    chromaShader.setUniform2f("windowSize", 320, 240);
    chromaShader.setUniform1f("offsetALL", 10*sin(ofGetElapsedTimef()));
    

    ofPushMatrix();
    ofTranslate(640,0);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(320,0,0);
    glTexCoord2f(1,1); glVertex3f(320,240,0);
    glTexCoord2f(0,1); glVertex3f(0,240,0);
    glEnd();
    ofPopMatrix();
    chromaShader.end();
    tex1.unbind();
    
    ///GAUSSIAN----------------------------------
    tex1.bind();
    blurShader.begin();
    blurShader.setUniformTexture("image", tex1, 0);
    blurShader.setUniform2f("width", 7*sin(ofGetElapsedTimef()),7*sin(ofGetElapsedTimef()));
    
    ofPushMatrix();
    ofTranslate(0, 240);
    
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(0,0,0);
        glTexCoord2f(1,0); glVertex3f(320,0,0);
        glTexCoord2f(1,1); glVertex3f(320,240,0);
        glTexCoord2f(0,1); glVertex3f(0,240,0);
    glEnd();
    
    ofPopMatrix();
    blurShader.end();
    tex1.unbind();
    
    ///FISHEYE-----------------------------------
    tex1.bind();
    fishShader.begin();
    fishShader.setUniformTexture("tex0", tex1, 0);
    fishShader.setUniform1f("signcurvature", 3+1.5*sin(ofGetElapsedTimef()));
    fishShader.setUniform1f("lensradius", 2);
    
    ofPushMatrix();
    ofTranslate(320, 240);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(320,0,0);
    glTexCoord2f(1,1); glVertex3f(320,240,0);
    glTexCoord2f(0,1); glVertex3f(0,240,0);
    glEnd();
    ofPopMatrix();
    fishShader.end();
    tex1.unbind();
    
    ///Rota--------------------------------------
    //NOT WORKING YET

    tex1.bind();
    rotaShader.begin();
    rotaShader.setUniformTexture("tex0", tex1, 0);
    rotaShader.setUniform2f("anchor", 0.5,0.5);
    rotaShader.setUniform1i("boundmode", 2);
    rotaShader.setUniform2f("zoom", sin(ofGetElapsedTimef()),sin(ofGetElapsedTimef()));
    rotaShader.setUniform1f("theta", 3.1415*sin(ofGetElapsedTimef()));
    
    ofPushMatrix();
    ofTranslate(320, 480);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(320,0,0);
    glTexCoord2f(1,1); glVertex3f(320,240,0);
    glTexCoord2f(0,1); glVertex3f(0,240,0);
    glEnd();
    ofPopMatrix();
    rotaShader.end();
    tex1.unbind();

    ///CarToPol-----------------------------------
    tex1.bind();
    carToPolShader.begin();
    carToPolShader.setUniformTexture("tex0", tex1, 0);
    carToPolShader.setUniform2f("scale", ofMap(sin(ofGetElapsedTimef()), -1, 1, 0.5, 1.0),ofMap(sin(ofGetElapsedTimef()), -1, 1, 0.5, 1.0));
    carToPolShader.setUniform2f("origin", ofMap(sin(ofGetElapsedTimef()), -1, 1, 0,0.25),ofMap(sin(ofGetElapsedTimef()), -1, 1, 0, 0.25));
    
    ofPushMatrix();
    ofTranslate(0, 480);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(320,0,0);
    glTexCoord2f(1,1); glVertex3f(320,240,0);
    glTexCoord2f(0,1); glVertex3f(0,240,0);
    glEnd();
    ofPopMatrix();
    carToPolShader.end();
    tex1.unbind();
    
    ///WOBBLE--------------------------------------
    tex1.bind();
    wobbleShader.begin();
    wobbleShader.setUniformTexture("image", tex1, 0);
    wobbleShader.setUniform2f("amp", 10,10); //These settings are finicky. Be careful with your ranges
    wobbleShader.setUniform2f("freq", .04+(.2*sin(ofGetElapsedTimef())),.04+(.2*sin(ofGetElapsedTimef())));
    wobbleShader.setUniform1f("radius", 15+(80*sin(ofGetElapsedTimef())));
    
    ofPushMatrix();
    ofTranslate(640, 240);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(320,0,0);
    glTexCoord2f(1,1); glVertex3f(320,240,0);
    glTexCoord2f(0,1); glVertex3f(0,240,0);
    glEnd();
    ofPopMatrix();
    wobbleShader.end();
    tex1.unbind();
    
    ///LumaMask-------------------------------------
    //Not Working yet
    tex1.bind();
    lumaShader.begin();
    //This is meant to blend between two textures. Not set up yet
    lumaShader.setUniformTexture("tex0", tex1, 0);
    lumaShader.setUniformTexture("tex1", tex1, 0);
    lumaShader.setUniform4f("lumcoeff", 0.299,0.587,0.114,0); //wouldn't change this...
    lumaShader.setUniform1f("luma", 0.25);
    lumaShader.setUniform1f("fade", 0.25);
    lumaShader.setUniform1f("tol", 1+(0.5*sin(ofGetElapsedTimef())));
    
    ofPushMatrix();
    ofTranslate(640, 480);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(320,0,0);
    glTexCoord2f(1,1); glVertex3f(320,240,0);
    glTexCoord2f(0,1); glVertex3f(0,240,0);
    glEnd();
    ofPopMatrix();
    lumaShader.end();
    tex1.unbind();
    
    ///BRCOSA FBO-------------------------------------
    //This is not drawn anywhere...it is just drawn into an FBO which is then used by the bloom+brcosa shader
    brcosaFbo.begin();
    ofClear(0, 0, 0,0);
    tex1.bind();
    brcosaShader.begin();
    brcosaShader.setUniformTexture("tex0", tex1, 0);
    brcosaShader.setUniform1f("contrast", 1.0);
    brcosaShader.setUniform1f("brightness", 1.0);
    brcosaShader.setUniform1f("saturation", 5*sin(ofGetElapsedTimef()));
    brcosaShader.setUniform1f("alpha", 1.0);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(320,0,0);
    glTexCoord2f(1,1); glVertex3f(320,240,0);
    glTexCoord2f(0,1); glVertex3f(0,240,0);
    glEnd();
    brcosaShader.end();
    tex1.unbind();
    brcosaFbo.end();

    ///BRCOSA FBO Processed by Bloom shader-------------------------------------
    ofTexture fboTex1;
    fboTex1 = brcosaFbo.getTextureReference(); //I did it this way because using it as brcosaFbo.getTextureReference().bind() wasnt working correctly
    //Mix brcosa with bloom
    fboTex1.bind();
    bloomShader.begin();
    bloomShader.setUniformTexture("tex0", fboTex1, 0);
    bloomShader.setUniform1f("bloom", -5*sin(ofGetElapsedTimef()));
    
    ofPushMatrix();
    ofTranslate(960,0);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(320,0,0);
    glTexCoord2f(1,1); glVertex3f(320,240,0);
    glTexCoord2f(0,1); glVertex3f(0,240,0);
    glEnd();
    ofPopMatrix();
    fboTex1.unbind();
    bloomShader.end();
    
    ///ChromaAb FBO-------------------------------------
    //This is not drawn anywhere...it is just drawn into an FBO which is then used by the bloom+brcosa shader
    chromaFbo.begin();
    ofClear(0, 0, 0,0);
    tex1.bind();
    chromaShader.begin();
    chromaShader.setUniformTexture("tex", tex1, 0);
    chromaShader.setUniform2f("windowSize", 320, 240);
    chromaShader.setUniform1f("offsetALL", 60*sin(ofGetElapsedTimef()));
    
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(320,0,0);
    glTexCoord2f(1,1); glVertex3f(320,240,0);
    glTexCoord2f(0,1); glVertex3f(0,240,0);
    glEnd();
    chromaShader.end();
    tex1.unbind();
    chromaFbo.end();
    
    
    ///BRCOSA FBO Processed by Bloom shader-------------------------------------
    ofTexture fboTex2;
    fboTex2 = chromaFbo.getTextureReference(); //I did it this way because using it as brcosaFbo.getTextureReference().bind() wasnt working correctly
    //Mix brcosa with bloom
    
    fboTex2.bind();
    wobbleShader.begin();
    wobbleShader.setUniformTexture("image", fboTex2, 0);
    wobbleShader.setUniform2f("amp", 10,10); //These settings are finicky. Be careful with your ranges
    wobbleShader.setUniform2f("freq", .02+(.1*cos(ofGetElapsedTimef())),.2+(.1*cos(ofGetElapsedTimef())));
    wobbleShader.setUniform1f("radius", 15+(80*sin(ofGetElapsedTimef())));
    
    ofPushMatrix();
    ofTranslate(960, 240);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(0,0,0);
    glTexCoord2f(1,0); glVertex3f(320,0,0);
    glTexCoord2f(1,1); glVertex3f(320,240,0);
    glTexCoord2f(0,1); glVertex3f(0,240,0);
    glEnd();
    ofPopMatrix();
    wobbleShader.end();
    fboTex2.unbind();
    
    //RADIAL BLUR
    tex1.bind();
    radialShader.begin();
        radialShader.setUniformTexture("tex0", tex1, 0);
        radialShader.setUniform2f("origin", 0.5*sin(ofGetElapsedTimef()), 0.5*cos(ofGetElapsedTimef()));
        radialShader.setUniform2f("width", 0.5*sin(ofGetElapsedTimef()),0.5*sin(ofGetElapsedTimef()));
        ofPushMatrix();
            ofTranslate(960,480);
            glBegin(GL_QUADS);
                glTexCoord2f(0,0); glVertex3f(0,0,0);
                glTexCoord2f(1,0); glVertex3f(320,0,0);
                glTexCoord2f(1,1); glVertex3f(320,240,0);
                glTexCoord2f(0,1); glVertex3f(0,240,0);
            glEnd();
        ofPopMatrix();
    radialShader.end();
    tex1.unbind();
    
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Bloom", 20,20);
    ofDrawBitmapString("BrCoSa", 340,20);
    ofDrawBitmapString("Chromatic Abberation", 660,20);
    ofDrawBitmapString("Not really Gauss Blur", 20,260);
    ofDrawBitmapString("Fish Eye", 340,260);

    ofDrawBitmapString("CarToPol", 20,500);
    ofDrawBitmapString("Wobble", 660,260);
    ofDrawBitmapString("Bloom+BRCOSA", 980,20);
    ofDrawBitmapString("Wobble+ChromaAb", 980,260);
    ofDrawBitmapString("Radial Blur", 980,500);
    ofDrawBitmapString("Jit.rota", 340,500);
    
    ofSetColor(255, 0, 0);
    ofDrawBitmapString("LumaKey", 660,500);
    ofSetColor(255, 255, 255);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}