#include <ai.h>
#include <cstring>

AI_SHADER_NODE_EXPORT_METHODS(SampleMethods);

namespace
{
enum paramIndex
{
  k_base_color,
  k_pat_color,
  k_pat_offset,
  k_pat_mode
};
};
static const char *uv_mode[] = {"U", "V", NULL};

node_parameters
{
  AiParameterRGB("baseColor", 0.7f, 0.7f, 0);
  AiParameterRGB("patternColor", 0.7f, 0, 0);
  AiParameterFlt("patternOffset", 0.5);
  AiParameterEnum("patternMode", 0, uv_mode);
}

shader_evaluate
{
  AtRGB base = AiShaderEvalParamRGB(k_base_color);
  AtRGB pat = AiShaderEvalParamRGB(k_pat_color);
  float offset = AiShaderEvalParamFlt(k_pat_offset);
  int mode = AiShaderEvalParamEnum(k_pat_mode);
  if (mode == 0)
    sg->out.RGB() = (sg->u >= offset) ? pat : base;
  else
    sg->out.RGB() = (sg->v >= offset) ? pat : base;
}

node_loader
{
  if (i > 0)
    return false;
  node->methods = SampleMethods;
  node->output_type = AI_TYPE_RGB;
  node->name = "mkParamDemo";
  node->node_type = AI_NODE_SHADER;
  strcpy(node->version, AI_VERSION);
  return true;
}

// The remaining macros can be left "empty"
node_initialize {}
node_update {}
node_finish {}