#ifndef LOADER_HPP
#define LOADER_HPP

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
//#ifdef USE_ASSIMP // don't use this #define, it's only for me (it AssImp fails to compile on your machine, at least all the other tutorials still work)

// Include AssImp
//#include "assimp/Importer.hpp"      // C++ importer interface
//#include "assimp/scene.h"           // Output data structure
//#include "assimp/postprocess.h"     // Post processing flags

// #include "glm.hpp"
#include "Bomberman.hpp"

bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs, 
	std::vector<glm::vec3> & out_normals
);


#endif