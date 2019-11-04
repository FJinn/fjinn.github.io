attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec2 vTexCoord;

varying vec2 fTexCoord;
varying vec4 fColor;

mat4 rotationMatrix(vec3 axis, float angle, float scale)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4((oc * axis.x * axis.x + c) * scale,           (oc * axis.x * axis.y - axis.z * s) * scale,  (oc * axis.z * axis.x + axis.y * s) * scale,  0.0,
                (oc * axis.x * axis.y + axis.z * s) * scale,           (oc * axis.y * axis.y + c) * scale,  (oc * axis.y * axis.z - axis.x * s) * scale,  0.0,
                (oc * axis.z * axis.x - axis.y * s) * scale,  (oc * axis.y * axis.z + axis.x * s) * scale,           (oc * axis.z * axis.z + c) * scale,  0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

mat4 translationMatrix(float x, float y, float z)
{
	return mat4( 1.0, 0.0, 0.0, 0.0,
				 0.0, 1.0, 0.0, 0.0,
				 0.0, 0.0, 1.0, 0.0,
				   x,   y,   z, 1.0	
									);
}

mat4 skewMatrix(float x, float y, float z)
{
	return mat4(   1.0,   x,   x, 0.0,
				   y,   1.0,   y, 0.0,
				   z,   z,   1.0, 0.0,
				 0.0, 0.0, 0.0, 1.0	
									);
}

mat4 scaleMatrix(float x, float y, float z)
{
	return mat4( x, 0.0, 0.0, 0.0,
				 0.0, y, 0.0, 0.0,
				 0.0, 0.0, z, 0.0,
				 0.0, 0.0, 0.0, 1.0	
									);
}

void main()
{
	fColor = vColor;
	fTexCoord = vTexCoord;
	
	gl_Position = vPosition;
}