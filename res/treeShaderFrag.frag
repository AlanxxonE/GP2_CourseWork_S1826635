#version 120

#ifdef GL_ES
precision highp float;
#endif

varying vec2 texCoord0;
varying vec3 normalsPass;

uniform sampler2D diffuse;

uniform vec2 u_lineSize;

uniform float u_speedColor;

vec3 hsb2rgb( in vec3 c )
{
    vec3 rgb = sin(c.x + vec3(3.985,1.653,4.000) * u_speedColor);
    return rgb;
}

void main()
{
    vec2 st = gl_FragCoord.xy / u_lineSize;

    vec2 toCenter = vec2(0.5,0.5)-st;
    float angle = atan(toCenter.y,toCenter.x);


    gl_FragColor = mix(texture2D(diffuse, texCoord0) , vec4(hsb2rgb(vec3(1.0 * angle,1.0,1.0)),1.0), 0.1);

	//vec2 st = gl_FragCoord.xy / u_lineSize;
	//gl_FragColor = mix(texture2D(diffuse, texCoord0) , vec4(0.0,st.y,sin(st.x * u_speedColor), 0.5) , 0.1);
	//gl_FragColor = texture2D(diffuse, texCoord0) * vec4(abs(sin(u_speedColor)), abs(sin(u_speedColor * 4.0)), abs(sin(u_speedColor / 2.0)), 0.5);
}
