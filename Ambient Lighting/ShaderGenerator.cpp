#include "ShaderGenerator.h"

#include <iostream>

ShaderGenerator::ShaderGenerator()
{
}


ShaderGenerator::~ShaderGenerator()
{
}



string ShaderGenerator::convert2GLSL(string infile, string outfile){
	if (outfile == " ")
		outfile = infile + ".g";
	std::string cmd = "java -jar tools/Convert.jar " + infile + " -g " + outfile;
	system(cmd.c_str());
	return outfile;
}


string ShaderGenerator::convert2HLSL(string infile, string outfile){
	if (outfile == " ")
		outfile = infile + ".g";
	std::string cmd = "java -jar tools/Convert.jar " + infile + " -h " + outfile;
	system(cmd.c_str());
	return outfile;
}