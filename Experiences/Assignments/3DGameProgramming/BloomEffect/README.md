# -> [Bloom Effect](/Experiences/Assignments/3DGameProgramming/BloomEffect/fragmentShader1.frag) <-

<img src="https://github.com/FJinn/fjinn.github.io/blob/master/Assignments/3DGameProgramming/Images/BloomEffect.gif?raw=true" width="800" height="450" />

Bloom effect created using fragment shader with 2 framebuffers and blur effect.

Vertex shader is used for moving, rotating, and deforming objects/boxes.

Framebuffers are used to create the bloom effect through fragment shader. 

The idea behind is to render the blur effect on one framebuffer, while the other is used for occlude/control the frame/picture based on color. The combined result of both framebuffers will be the bloom effect showed above.
