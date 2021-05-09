#version 120

//Define the quality bar of rendering the outcome of the shader
#ifdef GL_ES
precision highp float; //high value
#endif

//Vectors that vary based on the changes of the vertices inside the game
varying vec2 texCoord0;
varying vec3 normalsPass;

//Variable that specifies the information of which texture is provided for the shader
uniform sampler2D diffuse;

//Uniform that provides a canvas size to set the amount of tiles where the neon lines will be implemented
uniform vec2 u_lineSize;

//Uniform that provides an ever growing counter to give the time value for animating the outcome of functions
uniform float u_speedColor;

//Method that provides the HSB color spectrum, enabling the neon colors to be related to the canvas spatial coordinates 
vec3 neonColors( in vec3 previousColor )
{
    //Multiplying an everchaning variable provides a vivid neon color to pop up at any given spacial position
    vec3 neonColor = sin(previousColor.x + vec3(3.985,1.653,4.000) * u_speedColor);

    return neonColor;
}

//Method that returns a single deterministic float value based on the canvas resolution
float randomLineDirection(in vec2 canvasValue) 
{
    //Having fract and sin to generate a chaotic value upon the wave, using the dot method to have single value outcome from vector multiplication
    return fract(sin(dot(canvasValue.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

vec2 truchetPatternTiles(in vec2 tileValue, in float tileOrientation)
{
    tileOrientation = fract(((tileOrientation + (u_speedColor / 2.0))*2.0));

    if (tileOrientation > 0.75) 
    {
        tileValue = vec2(1.0) - tileValue;
    } 
    else if (tileOrientation > 0.5) 
    {
        tileValue = vec2(1.0-tileValue.x,tileValue.y);
    } 
    else if (tileOrientation > 0.25) 
    {
        tileValue = 1.0-vec2(1.0-tileValue.x,tileValue.y);
    }

    return tileValue;
}

void main()
{
    vec2 canvasValue = gl_FragCoord.xy / u_lineSize;

    //Amount of tiles in the table
    canvasValue *= 20.0;

    vec2 tableTileValue = floor(canvasValue);  
    vec2 tableDivisionValue = fract(canvasValue);  

    vec2 tile = truchetPatternTiles(tableDivisionValue, randomLineDirection(tableTileValue));

    float color = 0.0;

    color = smoothstep(tile.x - 0.1, tile.x * 0.893, tile.y) - smoothstep(tile.x - 0.1, tile.x + 0.1, tile.y);

    vec2 toCenter = vec2(0.5, 0.5) - canvasValue;
    float angle = atan(toCenter.y, toCenter.x);

    gl_FragColor = fract(mix(texture2D(diffuse, texCoord0), vec4(vec3(color * vec4(neonColors(vec3(1.0 * angle, 1.0, 1.0)), 1.0)), 1.0), 0.5));
}
