/*
Malcolm Kesson
Sept 7 2019
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
  k_minHeight,
  k_maxHeight,
  k_min_color,
  k_max_color,
  k_mode,
  k_matrix
};
};

static const char *space_mode[] = {"Object", "World", "User", NULL};

node_parameters
{
  AiParameterFlt("minHeight", 1.0f);
  AiParameterFlt("maxHeight", 3.0f);
  AiParameterRGB("minColor", 0.7f, 0.7f, 0);
  AiParameterRGB("maxColor", 0.7f, 0, 0);
  AiParameterEnum("spaceName", 0, space_mode);
  AiParameterMtx("matrixInput", AI_M4_IDENTITY);
}

shader_evaluate
{
  float minH = AiShaderEvalParamFlt(k_minHeight);
  float maxH = AiShaderEvalParamFlt(k_maxHeight);
  AtRGB minC = AiShaderEvalParamRGB(k_min_color);
  AtRGB maxC = AiShaderEvalParamRGB(k_max_color);
  int mode = AiShaderEvalParamEnum(k_mode);
  float blend, height;

  switch (mode)
  {
  case 0:
    height = sg->Po.y; // object space
    break;
  case 1:
    height = sg->P.y; // world space
    break;
  default:
    AtMatrix m = *AiShaderEvalParamMtx(k_matrix); // user space
    AtMatrix mm = AiM4Invert(m);
    AtVector transformedP = AiM4PointByMatrixMult(mm, sg->P);
    height = transformedP.y;
    break;
  }
  blend = AiSmoothStep(minH, maxH, height);
  sg->out.RGB() = mix(minC, maxC, blend);
}

node_loader
{
  if (i > 0)
    return false;
  node->methods = SampleMethods;
  node->output_type = AI_TYPE_RGB;
  node->name = "mkColorByHeight";
  node->node_type = AI_NODE_SHADER;
  strcpy(node->version, AI_VERSION);
  return true;
}

// The remaining macros can be left "empty"
node_initialize {}
node_update {}
node_finish {}