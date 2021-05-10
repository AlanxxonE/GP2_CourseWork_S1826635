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
    //Multiplying an everchaning variable provides a vivid neon color to pop up at any given spatial position
    vec3 neonColor = sin(previousColor.x + vec3(3.985,1.653,4.000) * u_speedColor);

    return neonColor;
}

//Method that returns a single deterministic float value based on the canvas resolution
float randomLineDirection(in vec2 canvasValue) 
{
    //Having fract and sin to generate a chaotic value upon the wave, using the dot method to have single value outcome from vector multiplication
    return fract(sin(dot(canvasValue.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

//Method that based on the tile Index on the grid will apply a different tile value causing the neon lines obtain different orientations
vec2 truchetPatternTiles(in vec2 tileValue, in float tileOrientation)
{
    //A different orientation is generated as a dynamic value is added every call
    tileOrientation = fract(((tileOrientation + (u_speedColor / 2.0))*2.0));

    //Since the Index provided is picked at random the pattern takes place, as based on it a different value is applied on the Index tile
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
    //The GL coordinates based on the canvas size where operations will take place
    vec2 canvasValue = gl_FragCoord.xy / u_lineSize;

    //Amount of tiles in the table
    canvasValue *= 20.0;

    //After grid dimensions, separation and orientation of each individual tile is set
    vec2 tableTileValue = floor(canvasValue);  
    vec2 tableDivisionValue = fract(canvasValue);  

    //Method call for the creation of the pattern on the grid
    vec2 tile = truchetPatternTiles(tableDivisionValue, randomLineDirection(tableTileValue));

    //Variable that holds the color value of the shaped lines
    float linesColor = 0.0;

    //This assignment manages the shaping of the diagonal and vertical lines
    linesColor = smoothstep(tile.x - 0.1, tile.x * 0.893, tile.y) - smoothstep(tile.x - 0.1, tile.x + 0.1, tile.y);

    //A center point is set based on the dimensions of the previously declared canvas
    vec2 toCenter = vec2(0.5, 0.5) - canvasValue;

    //In order to have an angle that the neon colors can spread upon
    float angle = atan(toCenter.y, toCenter.x);

    //The final GL color assignment based on the mixture of the texture of the model and the lines pattern
    //The latter displaying the different neon colors, rotating on a set angle, everything fracted for a sharper outcome
    gl_FragColor = fract(mix(texture2D(diffuse, texCoord0), vec4(vec3(linesColor * vec4(neonColors(vec3(1.0 * angle, 1.0, 1.0)), 1.0)), 1.0), 0.5));
}
