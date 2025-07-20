#pragma once

#include <iostream>
#include <unordered_map>

using namespace std;

template<typename T>
class ComponentManager {
public:
    static unordered_map<int, T> components;

    static void add(int ID, T component) {
        components[ID] = component;
    }
    static T& get(int ID) {
        return components[ID];
    }
    static bool exists(int ID) {
        return components.find(ID) != components.end();
    }
};