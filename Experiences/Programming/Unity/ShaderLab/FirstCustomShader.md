# First Custom Shader in Unity

I learned about vertex shader and fragment shader in OpenGL during my university. I figured it would be a good experience to get my hands on Unity ShaderLab. To clarify, I didn't have any clear goal in mind but just playing around while learning. Which means there probably should have better implementation/visual effect somewhere online.

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/Programming/Unity/ShaderLab/GIF/FadeOut.gif?raw=true"/>

To create above effect, I used 2 noise textures to randomize if the processing pixel should go in which directions.

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/Experiences/Programming/Unity/ShaderLab/GIF/Heart.gif?raw=true"/>

Instead of animation or put one sprite on top of another, I combine both textures with a parameter. This created the above effect.

[Code](/Experiences/Programming/Unity/ShaderLab/FirstShader)
