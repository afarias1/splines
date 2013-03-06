#include <iostream>
#include <fstream>
#include "raytracer.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <QHash>      //Qt Dictionary
#include <QString>    //Appease QT with its strings
#include "view.h"     //image, eye properties
#include "shape.h"    //base class for hitable objects
#include "light.h"    //basic light struct (pos, intensity)
#include "parser.h"   //helper functions for reading input file

#include "rgbImage.h"
#include "ray.h"
#include "scene.h"


using namespace std;
using namespace cs40;


RayTracer::RayTracer(){
    /* do nothing? */
}

RayTracer::~RayTracer(){
    /* do nothing? */
}

void RayTracer::trace(){
    /* do something! */
}

void RayTracer::save(){
    View vw = m_scene.view;

    RGBImage img(vw.nrows, vw.ncols, convertColor(vw.background));

    //TODO: ray trace away!

    img.saveAs(m_scene.view.fname, true);
    cout << "Saved result to " << m_scene.view.fname << endl;
}

/* convert from 0-1 rgb space to 0-255 */
RGBColor RayTracer::convertColor(const vec3& clr){
    int r,g,b;
    r=(int)(255*clr.x());
    g=(int)(255*clr.y());
    b=(int)(255*clr.z());
    return RGBColor(r,g,b);
}

void RayTracer::parseFile(const string& fname){
    ifstream infile;
    infile.open(fname.c_str());

    if(!infile.good()){
        cout << "error opening file " << fname << endl;
        return;
    }

    int lno = 1; //line number
    string line; //current line
    vector<string> words;


    while(!infile.eof()){
        getline(infile, line);
        //cout << lno << ": " << line.length() << " " << line <<  endl;
        words = split(line);
        if(words.size()>0){
            try{
                parseLine(words);
            }
            catch(parser_error e){
                cout << "Error on line " << lno << ": " << line << endl;
                cout << e.what() << endl;
            }
        }
        lno++;
    }

    infile.close();
}

void RayTracer::parseLine(const vector<string>& words){
    string cmd = words[0];
    if(cmd == "output"){
        checksize(words,1);
        m_scene.view.fname = words[1];
    }
    else if (cmd == "outsize"){
        checksize(words,2);
        m_scene.view.nrows = parseInt(words[1]);
        m_scene.view.ncols = parseInt(words[2]);
    }
    else if (cmd == "eye"){
        checksize(words,3);
        m_scene.view.eye = parseVec3(words,1);
    }
    else if (cmd == "background"){
        checksize(words,3);
        m_scene.view.background = parseVec3(words,1);
    }
    else if (cmd == "color"){
        checksize(words,4);
        //add named color to map
        m_colors[words[1].c_str()]=parseVec3(words,2);
    }
    else if (cmd == "mat"){
        //either mat cmd name or mat cmd r g b
        checksize(words,2,4);
        parseMat(words, m_materials); //this gets complicated
    }
    else if (cmd == "sphere"){
        checksize(words, 4);
        //use current material as material for sphere
        //get rid of this error after you parse the sphere
        throw parser_error("Parse your own sphere");
    }
    else if (cmd == "rectangle"){
        checksize(words, 9);
        //use current material as material for rect
        throw parser_error("Parse your own rectangle");
    }
    else if (cmd == "amblight"){
        checksize(words,1);
        m_scene.ambient = parseFloat(words[1]);
    }
    else if (cmd == "light"){
        checksize(words,4);

        //Light l;
        throw parser_error("Parse your own light");
        //m_scene.lights.push_back(l);
    }
    else{
        throw parser_error("Unknown command: "+cmd);
    }
}

/* parse a material command in the vector words, 
 * using matmap to load/store/modify current and other maps */
void RayTracer::parseMat(const vector<string>& words,
              QHash<QString,Material>& matmap){
    string subcmd = words[1];
    if(subcmd == "save"){
        matmap[words[2].c_str()] = matmap[QString("current_")];
    }
    else if(subcmd == "load"){
        if(m_materials.contains(words[2].c_str())){
            matmap["current_"]=m_materials[words[2].c_str()];
        }
        else{
            throw parser_error("No color " + words[2] + " found");
        }
    }
    else if(subcmd != "amb" && subcmd != "diff" && subcmd != "spec"){
        throw parser_error("Unknown material subcommand: " + subcmd);
    }
    else{
        //looks like mat <type> <name> or mat <type> r g b
        //where <type> is amb, diff, or spec
        vec3 clr;
        if(words.size()>3 ){ //mat <type> r g b
            clr = parseVec3(words, 2);
        }
        else{ //mat <type> name, where name refers to existing color
            string clrname = words[2];
            if(m_colors.contains(clrname.c_str())){
                clr=m_colors[clrname.c_str()];
            }
            else{
                throw parser_error("No color " + clrname + " found");
            }
        }
        if(subcmd=="amb"){matmap["current_"].ambient=clr;}
        else if(subcmd=="diff"){matmap["current_"].diffuse=clr;}
        else if(subcmd=="spec"){matmap["current_"].specular=clr;}
    }
}
