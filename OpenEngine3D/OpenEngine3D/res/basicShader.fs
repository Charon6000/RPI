#version 120

varying vec2 texCoord0;

uniform sampler2D diffuse;


void main()
{
<<<<<<< HEAD
	gl_FragColor = texture2D(diffuse, texCoord0); //vec4(1.0, 0.0, 0.0, 1.0);
=======
	gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
>>>>>>> origin
}