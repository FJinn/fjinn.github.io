attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec2 vTexCoord;

varying vec2 fTexCoord;
varying vec4 fColor;
 
void main()
{               
	fColor = vColor;
	// texture multiply or divide or reverse(-)
	fTexCoord = vTexCoord;

	// + = zoom out and pic will be at top right
	// - = zoom in to top right
	gl_Position = vPosition;
}      