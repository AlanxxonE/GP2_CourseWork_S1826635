#version 120

#ifdef GL_ES
precision highp float;
#endif

varying vec2 texCoord0;
varying vec3 normalsPass;

uniform sampler2D diffuse;

uniform vec2 u_lineSize;

uniform float u_speedColor;

void main()
{
	vec2 st = gl_FragCoord.xy / u_lineSize;
	gl_FragColor = vec4(st.x,0.0,sin(st.y * u_speedColor),1.0);
	//gl_FragColor = texture2D(diffuse, texCoord0) * vec4(abs(sin(u_speedColor)), abs(sin(u_speedColor * 4.0)), abs(sin(u_speedColor / 2.0)), 0.5);
}
