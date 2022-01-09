
/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 palette[60]; // matrices des 60 bones
} skin;



////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	mat4 mvp = sm.projectionMatrix * modelViewMatrix;
	mat4 boneModel = skin.palette[int(boneIndices[0])];

	vec4 pos = boneModel * vec4(inputPosition, 1.0);
	gl_Position = mvp * pos;

	vec3 localNormal = mat3(boneModel) * normal; 
	outNormal = mat3(mvp) * localNormal;
}