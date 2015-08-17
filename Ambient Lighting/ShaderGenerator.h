#pragma once

#include<string>
using namespace std;
class ShaderGenerator
{
public:
	ShaderGenerator();
	~ShaderGenerator();

	string convert2GLSL(string infile, string outfile = "");
	string convert2HLSL(string infile, string outfile = "");
};

