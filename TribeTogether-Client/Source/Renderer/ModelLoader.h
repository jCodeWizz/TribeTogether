#pragma once

#include "Renderer.h"
#include <vector>
#include <iostream>

bool LoadModel(const std::string& path, std::vector<TT::Vertex>& vertices, std::vector<uint32_t>& indices);
