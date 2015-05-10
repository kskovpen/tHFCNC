// ignore memory errors
{
   gSystem->CompileMacro("AtlasStyle.C","k","libAtlasStyle");
   gSystem->CompileMacro("AtlasUtils.C","k","libAtlasUtils");
   gApplication->Terminate();
}
