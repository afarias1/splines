#ifndef CS40RAYTRACER_H
#define CS40RAYTRACER_H

#include <vector>
#include <string>
#include <QHash>      //Qt Dictionary
#include <QString>    //Appease QT with its strings
#include "scene.h"
#include "material.h"
#include "rgbColor.h"

namespace cs40{

class RayTracer{

public:
    RayTracer();
    ~RayTracer();

    /* parse an input file given by a filename and build the global
     * scene object from the parsed input */
    void parseFile(const std::string& fname);

    /* Do the raytracing */
    void trace();

    /* Save output image */
    void save();

private:
    cs40::Scene m_scene;
    QHash<QString, vec3> m_colors;

    /* Hash table mapping material names to material structs.
     * materials["current_"] is a special entry refering to the
     * current material. The current material is applied to all newly
     * created objects */
    QHash<QString, cs40::Material> m_materials;

    /* parse a single line in the input file consisting of the given
     * vector of whitespace-delimited words. Non comment non blank lines
     * are of the form <commandname> [arguments] */
    void parseLine(const std::vector<std::string>& words);

    /* parse a material command in the vector words,
     * using m_materials to load/store/modify current and other maps */
    void parseMat(const std::vector<std::string>& words);

    /* convert from 0-1 rgb space to 0-255 */
    cs40::RGBColor convertColor(const vec3& clr);

};

}
#endif // RAYTRACER_H
