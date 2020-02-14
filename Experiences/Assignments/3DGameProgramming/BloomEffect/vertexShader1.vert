attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec2 vTexCoord;

varying vec2 fTexCoord;
varying vec4 fColor;

uniform mat4 uMvpMatrix;

uniform float Factor1;
uniform int mode;

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
	
	// mat4 R = rotationMatrix(vec3(0.0, 1.0, 0.0), sin(Factor1 * 2.0) * 10.0 * vPosition.y , sin(Factor1 * 2.0) * 4.0);
	mat4 R; // = rotationMatrix(vec3(0.0, 1.0, 1.0), sin(Factor1 * 2.0) * 10.0, 1.0);

	mat4 T;
	mat4 Sk;
	mat4 S;

	if(mode == 1)
	{
		T = translationMatrix(sin(Factor1) * 5.0 * abs( sin(vPosition.z * 2.0 + Factor1) ), abs( sin(vPosition.x + Factor1 * 10.0) ) -  5.0, sin(Factor1 * 2.0) * 5.0 * abs( sin(vPosition.y * 2.0 + Factor1)) );
		S = scaleMatrix(abs( sin(Factor1) ) * 2.0 , abs( sin(Factor1) ) * 2.0 , abs( sin(Factor1) ) * 2.0 );

		gl_Position = uMvpMatrix * T * S * vPosition;
	}
	else if(mode == 2)
	{
		T = translationMatrix( sin(vPosition.x * Factor1 * 10.0)  , 0.0 , 0.0);
		R = rotationMatrix(vec3(0.0, 0.0, 1.0), sin(Factor1) * 2.0, 1.0);
		Sk = skewMatrix(sin(Factor1 * 4.0) * vPosition.y, 0.0, 0.0);

		gl_Position = uMvpMatrix * R * Sk * T * vPosition;
	}
	else if(mode == 3)
	{
		T = translationMatrix( sin(Factor1 * 5.0 * vPosition.y ) * vPosition.y, 0.0 , cos(Factor1 * 5.0 *vPosition.y) );
		S = scaleMatrix(1.0 , sin(Factor1 * 5.0  ) * vPosition.y  , 1.0);

		gl_Position = uMvpMatrix * T * S * vPosition;
	}
	else
	{
		gl_Position = uMvpMatrix * vPosition;
	}
	
}