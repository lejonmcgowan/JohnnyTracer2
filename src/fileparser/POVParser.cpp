//
// Created by lejonmcgowan on 10/5/16.
//

#include <core/utils/UnitUtils.h>

#include <fstream>
#include <algorithm>
#include <scene/SceneElemMod.h>
#include <iostream>
#include "POVParser.h"

void errorAndExit(std::string what, int exitCode = 1)
{
    std::cout << what << std::endl;
    assert(false);
}

const std::vector<char> specialChars = {'{', '}', '<', '>', ','};

const std::vector<std::string> keywords =
    {
        "camera",
        "light_source",
        "translate",
        "rotate",
        "scale",
        "box",
        "plane",
        "sphere",
        "triangle",
        "pigment",
        "color",
        "rgb",
        "rgbf",
        "finish",
        "ambient",
        "diffuse",
        "specular",
        "roughness",
        "reflection",
        "refraction",
        "ior",
        "location",
        "up",
        "right",
        "look_at"
    };

const std::vector<std::string> cameraModTokens =
    {
        "location",
        "up",
        "right",
        "look_at"
    };

const std::vector<std::string> shapeModTokens =
    {
        "translate",
        "rotate",
        "scale",
        "pigment",
        "finish"
    };

const std::vector<std::string> finishModTokens =
    {
        "ambient",
        "diffuse",
        "specular",
        "roughness",
        "reflection",
        "refraction",
        "ior"
    };

std::string parseWord(std::string word, std::istream& stream)
{
    char nextChar;
    while (stream.get(nextChar) && (isalpha(nextChar) || nextChar == '_'))
        word += nextChar;

    if (!(stream.rdstate() & std::ifstream::eofbit))
        stream.putback(nextChar);

    return word;
}

std::string parseNum(std::string wordNum, std::istream& stream)
{
    int decsLeft = 0;
    //for exponents
    int eLeft = 0;
    char nextChar;

    while (stream.get(nextChar) &&
            (isdigit(nextChar)
            || nextChar == '.'
            || nextChar == 'e')
            || nextChar == '-')
    {
        wordNum += nextChar;
        if(nextChar == '.')
            decsLeft++;
        else if(nextChar == 'e')
            eLeft++;
        else if(nextChar == '-' && eLeft < 1)
            errorAndExit("invalid negative number");
    }
    if(eLeft > 1)
        errorAndExit("Too many e's");
    if(decsLeft > 1)
        errorAndExit("too many negatives");

    if (!(stream.rdstate() & std::ifstream::eofbit))
        stream.putback(nextChar);

    return wordNum;
}

void parseSingleCommentFromStream(std::istream& stream)
{
    char nextChar;
    bool eof;
    do
    {
        eof = stream.get(nextChar).rdstate();
    }
    while (nextChar != '\n' && !eof);
}

void parseMultiCommentFromStream(std::istream& stream)
{
    char nextChar;
    bool eof;
    do
    {
        eof = stream.get(nextChar).rdstate();
    }
    while (nextChar != '*' && !eof);
    if (!eof)
    {
        stream.get(nextChar);
        if (nextChar != '/')
            parseMultiCommentFromStream(stream);
    }
}

SceneElemMod getVectorMod(const std::vector<std::string>& tokens, int& iter, std::string modName)
{
    assert(tokens[iter] == "<" && "Invalid Vector block");
    iter++;
    std::vector<double> nums;
    while (iter < tokens.size() && tokens[iter] != ">")
    {
        double num = atof(tokens[iter].c_str());
        nums.push_back(num);
        iter++;
        if (iter >= tokens.size())
            errorAndExit("Vector Prematurely Ended (mid-vector)");

        assert((tokens[iter] == "," || tokens[iter] == ">") && "Invalid Number separator");

        if(tokens[iter] != ">")
            iter++;
    }
    if (iter >= tokens.size())
        errorAndExit("Vector Prematurely Ended");
    //increment past end token
    iter++;
    SceneElemMod mod(modName);
    SceneElemMod::ModData data{};

    switch (nums.size())
    {
        case 4:
            std::copy(nums.begin(), nums.begin() + 4, data.vec4);
            break;
        case 3:
            std::copy(nums.begin(), nums.begin() + 3, data.vec3);
            break;
        case 2:
            std::copy(nums.begin(), nums.begin() + 2, data.vec2);
            break;
        case 1:
            data.dbl = nums[0];
            break;
        case 0:
            errorAndExit("Empty Vector");
            break;
        default:
            errorAndExit("unsupported vector size: " + nums.size());
    }
    mod.setData(data);
    return mod;
}
int addVectorToElem(const std::vector<std::string>& tokens, int iter, SceneElemMod& elem, std::string modName)
{
    SceneElemMod vectorMod = getVectorMod(tokens, iter, modName);
    elem.setModifier(modName, vectorMod);

    return iter;

}
int addVectorToElem(const std::vector<std::string>& tokens, int iter, SceneElem& elem, std::string modName)
{
    SceneElemMod vectorMod = getVectorMod(tokens, iter, modName);
    elem.setModifier(modName, vectorMod);

    return iter;

}

int addPigmentMod(const std::vector<std::string>& tokens, int iter, SceneElem& elem)
{
    SceneElemMod pigmentMod("pigment");

    assert(tokens[iter] == "{" && "Invalid Pigment block begin");
    iter++;

    assert(tokens[iter] == "color" && "Invalid Pigment block type");
    iter++;

    SceneElemMod colorMod("color");

    std::string colorType = tokens[iter];
    assert((colorType == "rgb" || colorType == "rgbf") && "Invalid Color Type");
    iter++;

    iter = addVectorToElem(tokens, iter, colorMod, colorType);

    assert(tokens[iter] == "}" && "Invalid Pigment block end");
    iter++;

    pigmentMod.setModifier("color", colorMod);
    elem.setModifier("pigment", pigmentMod);

    return iter;

}

int addFinishMod(const std::vector<std::string>& tokens, int iter, SceneElem& elem)
{
    SceneElemMod finishMod("finish");

    assert(tokens[iter] == "{" && "Invalid Finish block begin");
    iter++;

    while (iter < tokens.size() && tokens[iter] != "}")
    {
        std::string token = tokens[iter];
        iter++;
        if (std::find(finishModTokens.begin(), finishModTokens.end(), token) == finishModTokens.end())
            errorAndExit("Invalid finish mod token: " + token);

        SceneElemMod finishSubMod(token);
        SceneElemMod::ModData data;
        data.dbl = atof(tokens[iter].c_str());
        iter++;
        finishSubMod.setData(data);
        finishMod.setModifier(finishSubMod.name, finishSubMod);
    }
    if (iter >= tokens.size())
        errorAndExit("Finish prematurely Ended");

    assert(tokens[iter] == "}" && "Invalid Finish block end");
    iter++;

    elem.setModifier("finish", finishMod);

    return iter;

}

int addCameraElem(const std::vector<std::string>& tokens, int iter, std::vector<SceneElem>& objects)
{
    assert(tokens[iter] == "{" && "Invalid Camera Block Start");
    iter++;
    SceneElem cameraElem("camera", SceneElem::CAMERA);
    while (iter < tokens.size() && tokens[iter] != "}")
    {
        std::string token = tokens[iter];
        iter++;
        if (std::find(cameraModTokens.begin(), cameraModTokens.end(), token) == cameraModTokens.end())
        {
            errorAndExit("Invalid camera token: " + token);
        }
        iter = addVectorToElem(tokens, iter, cameraElem, token);

    }
    assert(tokens[iter] == "}" && "Invalid Camera Block End");
    iter++;

    objects.push_back(cameraElem);

    return iter;
}

int addLightElem(const std::vector<std::string>& tokens, int iter, std::vector<SceneElem>& objects)
{
    assert(tokens[iter] == "{" && "Invalid Light Block Start");
    iter++;

    SceneElem lightElem("light_source", SceneElem::LIGHT);
    iter = addVectorToElem(tokens, iter, lightElem, "location");

    assert(tokens[iter] == "color" && "Invalid Light Block Color");
    iter++;

    SceneElemMod colorMod("color");


    assert(tokens[iter] == "rgb" && "Invalid Light Block RGB");
    iter++;

    iter = addVectorToElem(tokens, iter, colorMod, "rgb");

    assert(tokens[iter] == "}" && "Invalid Light Block End");
    iter++;

    lightElem.setModifier("color", colorMod);

    objects.push_back(lightElem);

    return iter;
}

void parseAndAddShapeMods(const std::vector<std::string>& tokens, int iter, SceneElem& elem)
{
    assert(tokens[iter] == "{" && "Invalid Pov Block");
    iter++;
    while (iter != tokens.size() && tokens[iter] != "}")
    {
        std::string token = tokens[iter];
        if (std::find(shapeModTokens.begin(), shapeModTokens.end(), token) == shapeModTokens.end())
            iter++;
        else if (token == "translate")
        {
            iter++;
            iter = addVectorToElem(tokens, iter, elem, "translate");
        }
        else if (token == "scale")
        {
            iter++;
            iter = addVectorToElem(tokens, iter, elem, "scale");
        }
        else if (token == "rotate")
        {
            iter++;
            //if rotation exsists, save old rot and add to the rot that will be overwritten
            if (elem.hasMod("rotate"))
            {
                std::array<Number,3> oldRotData;
                const SceneElemMod::ModData& oldModData = elem.getMod("rotate").getData();
                std::copy(std::begin(oldModData.vec3), std::end(oldModData.vec3), oldRotData.begin());
                iter = addVectorToElem(tokens, iter, elem, "rotate");

                std::array<Number,3> newRotData;
                const SceneElemMod::ModData& newModData = elem.getMod("rotate").getData();
                std::copy(std::begin(newModData.vec3), std::end(newModData.vec3), newRotData.begin());
                newRotData[0] += oldRotData[0];
                newRotData[1] += oldRotData[1];
                newRotData[2] += oldRotData[2];

                SceneElemMod::ModData finalModData{};
                std::copy(newRotData.begin(),newRotData.end(),finalModData.vec3);
                elem.getMod("rotate").setData(finalModData);
            }
            else
            {
                iter = addVectorToElem(tokens, iter, elem, "rotate");
            }
        }
        else if (token == "pigment")
        {
            iter++;
            iter = addPigmentMod(tokens, iter, elem);
        }
        else if (token == "finish")
        {
            iter++;
            iter = addFinishMod(tokens, iter, elem);
        }
    }
    if (iter >= tokens.size())
    {
        errorAndExit("Pov block not properly ended");
    }
}

/**
 * used to find the end of a POV block
 * @param iter the initial iter to search through
 * @param tokens tokens to scan
 * @return the index AFTER the closing bracket that ends the bloock
 */
int exhaustBlock(int iter, const std::vector<std::string>& tokens, int initStack = 1)
{
    int bracketStack = initStack;
    while (iter < tokens.size() && bracketStack > 0)
    {
        if (tokens[iter] == "{")
            bracketStack++;
        else if (tokens[iter] == "}")
            bracketStack--;

        iter++;
    }

    if (iter > tokens.size() || bracketStack > 0)
        errorAndExit("Premature end in block");

    return iter;
}
int addSphereElem(const std::vector<std::string>& tokens, int iter, std::vector<SceneElem>& objects)
{
    SceneElem sphereElem("sphere", SceneElem::SHAPE);
    parseAndAddShapeMods(tokens, iter, sphereElem);

    assert(tokens[iter] == "{" && "Invalid Sphere block begin");
    iter++;

    iter = addVectorToElem(tokens, iter, sphereElem, "center");
    assert(tokens[iter] == "," && "invalid parse for Sphere");
    iter++;

    SceneElemMod radElem("radius");
    SceneElemMod::ModData radData;
    radData.dbl = atof(tokens[iter].c_str());
    iter++;
    radElem.setData(radData);
    sphereElem.setModifier("radius", radElem);

    iter = exhaustBlock(iter,tokens);

    objects.push_back(sphereElem);

    return iter;
}

int addBoxElem(const std::vector<std::string>& tokens, int iter, std::vector<SceneElem>& objects)
{

    SceneElem boxElem("box", SceneElem::SHAPE);
    parseAndAddShapeMods(tokens, iter, boxElem);

    assert(tokens[iter] == "{" && "Invalid Box block begin");
    iter++;

    iter = addVectorToElem(tokens, iter, boxElem, "min");

    assert(tokens[iter] == "," && "invalid parse for Box min");
    iter++;

    iter = addVectorToElem(tokens, iter, boxElem, "max");

    iter = exhaustBlock(iter,tokens);

    objects.push_back(boxElem);
    return iter;
}

int addTriangleElem(const std::vector<std::string>& tokens, int iter, std::vector<SceneElem>& objects)
{

    SceneElem triangleElem("triangle", SceneElem::SHAPE);
    parseAndAddShapeMods(tokens, iter, triangleElem);

    assert(tokens[iter] == "{" && "Invalid Triangle block begin");
    iter++;

    iter = addVectorToElem(tokens, iter, triangleElem, "a");
    assert(tokens[iter] == "," && "invalid parse for Triangle 'a'");
    iter++;

    iter = addVectorToElem(tokens, iter, triangleElem, "b");
    assert(tokens[iter] == "," && "invalid parse for Triangle 'b'");
    iter++;

    iter = addVectorToElem(tokens, iter, triangleElem, "c");

    iter = exhaustBlock(iter,tokens);

    objects.push_back(triangleElem);

    return iter;
}

int addPlaneElem(const std::vector<std::string>& tokens, int iter, std::vector<SceneElem>& objects)
{

    SceneElem planeElem("plane", SceneElem::CUSTOM);
    parseAndAddShapeMods(tokens, iter, planeElem);

    assert(tokens[iter] == "{" && "Invalid Plane block begin");
    iter++;

    iter = addVectorToElem(tokens, iter, planeElem, "normal");
    assert(tokens[iter] == "," && "invalid parse for Sphere");
    iter++;

    SceneElemMod pointPlaneMod("d");
    SceneElemMod::ModData pointData;
    pointData.dbl = atof(tokens[iter].c_str());
    iter++;
    pointPlaneMod.setData(pointData);
    planeElem.setModifier("d", pointPlaneMod);

    iter = exhaustBlock(iter,tokens);

    objects.push_back(planeElem);
    return iter;
}

void POVParser::parseTokens(const std::vector<std::string>& tokens)
{
    int i = 0;
    while (i < tokens.size())
    {
        std::string token = tokens[i];
        if (token == "camera")
            i = addCameraElem(tokens, ++i, objects);
        else if (token == "light_source")
            i = addLightElem(tokens, ++i, objects);
        else if (token == "sphere")
            i = addSphereElem(tokens, ++i, objects);
        else if (token == "box")
            i = addBoxElem(tokens, ++i, objects);
        else if (token == "triangle")
            i = addTriangleElem(tokens, ++i, objects);
        else if (token == "plane")
            i = addPlaneElem(tokens, ++i, objects);
        else
            errorAndExit("Invalid Top-Level Token: " + token);
    }
}

std::vector<std::string> POVParser::tokenize(std::ifstream& stream)
{
    std::vector<std::string> tokens = std::vector<std::string>();
    char nextChar;
    long size = 0;
    while (stream.get(nextChar))
    {
        //check for potential keyword
        if (isalpha(nextChar))
        {
            std::string word;
            word += nextChar;
            const std::string& parsedWord = parseWord(word, stream);
            if (std::find(keywords.begin(), keywords.end(), parsedWord) == keywords.end())
            {
                errorAndExit("Invalid keyword: " + parsedWord);
            }
            tokens.push_back(parsedWord);
        }

        //check for numbers
        else if (isdigit(nextChar) || nextChar == '-' || nextChar == '.')
        {
            std::string wordNum;
            wordNum += nextChar;
            tokens.push_back(parseNum(wordNum, stream));
        }

        //check for operator characters, like for vectors or scope
        else if (std::find(specialChars.begin(), specialChars.end(), nextChar) != specialChars.end())
        {
            std::string charString;
            charString += nextChar;
            tokens.push_back(charString);
        }
            //check for comments
        else if (nextChar == '/')
        {
            stream.get(nextChar);
            //single
            if (nextChar == '/')
            {
                parseSingleCommentFromStream(stream);
            }
                //multi
            else if (nextChar == '*')
            {
                parseMultiCommentFromStream(stream);
            }
            else
            {
                std::string errorMessage;
                errorMessage += "characters '/";
                errorMessage + nextChar + "' not recognized";
                errorAndExit(errorMessage);
            }
        }
            //make sure that whiteSpace is ignored before throwing error
        else if (!isspace(nextChar))
        {
            std::string errorMessage;
            errorMessage += "Invalid character: '";
            errorMessage += nextChar;
            errorMessage += "'";
            errorAndExit(errorMessage);
        }
//        if(size < tokens.size())
//        {
//            size = tokens.size();
//            std::cout << tokens.back() << std::endl;
//        }
    }

    return tokens;
}


