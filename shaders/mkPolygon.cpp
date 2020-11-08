/*
Based on the shader code given in the tutorial,
http://fundza.com/rfm/osl/regular_polygon/index.html
  
Malcolm Kesson
Sept 6 2019
*/
#include <ai.h>
#include <cstring>

// The sdk does not appear to implement the standart RenderMan style "mix" function.
// Consequently, we implement here!
AtRGB mix(AtRGB c1, AtRGB c2, float alpha)
{
  return c1 * (1.0 - alpha) + c2 * alpha;
}

AI_SHADER_NODE_EXPORT_METHODS(SampleMethods);

namespace
{
enum paramIndex
{
  k_numSides,
  k_innerRadius,
  k_lineWidth,
  k_baseColor,
  k_patternColor
};
};

node_parameters
{
  AiParameterFlt("numSides", 5);
  AiParameterFlt("innerRadius", 0.25);
  AiParameterFlt("lineThickness", 0.02);

  AiParameterRGB("baseColor", 0.7f, 0.7f, 0);
  AiParameterRGB("patternColor", 0.7f, 0, 0);
}

shader_evaluate
{
  float numSides = AiShaderEvalParamFlt(k_numSides);
  float innerRadius = AiShaderEvalParamFlt(k_innerRadius);
  float lineWidth = AiShaderEvalParamFlt(k_lineWidth);
  AtRGB base = AiShaderEvalParamRGB(k_baseColor);
  AtRGB pat = AiShaderEvalParamRGB(k_patternColor);

  // 1   Convert the 'uv' to polar coordinates
  //     Note: positive theta is clockwise.
  float theta = atan2(sg->v - 0.5, sg->u - 0.5); // -PI to PI radians
  if (theta < 0.0)
    theta += AI_PITIMES2; //  0 to 2PI radians

  // 2   Find the "segment" in which the current shading point is located.
  float interior = AI_PITIMES2 / numSides;
  float segment = floor(theta / interior);

  // 3   Find the angle to (counter) rotate the current shading point.
  //     Note: positive rotation is anti-clockwise.
  float rotation = segment * interior + interior / 2;

  // 4   Apply a 'Z' rotation to find the x offset
  float delta_u = sg->u - 0.5,
        delta_v = 0.5 - sg->v;
  float x_offset = delta_u * cos(rotation) - delta_v * sin(rotation);

  // 5   Use the x value of the 'Z' rotation to determine the
  //     "proximity" of the current shading point to a polygon edge.
  //     Using the smoothstep function twice ensures "proximity" is in
  //     the range 0.0 to 1.0.
  float proximity = AiSmoothStep(innerRadius - lineWidth / 2, innerRadius, x_offset) *
                    (1.0 - AiSmoothStep(innerRadius, innerRadius + lineWidth / 2, x_offset));

  // 6   Finally, use "proximity" to output the appropriate color.
  sg->out.RGB() = mix(base, pat, proximity);
}

node_loader
{
  if (i > 0)
    return false;
  node->methods = SampleMethods;
  node->output_type = AI_TYPE_RGB;
  node->name = "mkPolygon";
  node->node_type = AI_NODE_SHADER;
  strcpy(node->version, AI_VERSION);
  return true;
}

// The remaining macros can be left "empty"
node_initialize
{
  //    AiMsgSetConsoleFlags(AI_LOG_DEBUG);
}
node_update {}
node_finish {}