All shaders are the property of their original creators!

This is meant purely as an exercise/tutorial in using shaders for image processing in openFrameworks. I had a great learning experience putting this together, so I figured I'd share in case someone else was interested in playing with them.

I got most of my image processing experience with Jitter, so most shaders were lifted or modified from the Cycling '74 Jitter core, but I stayed away from any of the Cycling '74 copyright shaders. Most of these are either ones you could modify from the Orange book, or are from the OF forum.

Examples Include:

- Gauss Blur (eh..sorta)
- Wobble
- Rota (resize/rotate/manipulate a texture via a shader)
- RGB channel shift
- Bloom (currently broken)
- BRCOSA (brightness, contrast, saturation)
- Luma Key (broken)
- Bloom+BRCOSA (via FBO) (broken)
- Wobble+ChromaAbberation (via FBO)
- Fisheye
- Cartesian to Polar

![Screengrab](https://raw.github.com/laserpilot/shaderSandbox/master/screengrab.png)

