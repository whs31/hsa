//
// Created by whs31 on 11/1/2023.
//

#pragma once

#include <format>
#include <iostream>

#define printLn(...) std::cout << std::format(__VA_ARGS__) << std::endl
