//
// Created by lejonmcgowan on 10/5/16.
//

#include <fstream>
#include <algorithm>
#include <assert.h>
#include <scene/SceneElemMod.h>
#include <utils/UnitUtils.h>
#include "POVParser.h"

const std::vector<char> specialChars = {'{', '}', '<', '>', ','};

const std::vector<std::string> keywords =
    {
        "camera",
        "light_source",
        "translate",
        "rotate",
        "scale",
        "box",
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
    while (stream.get(nextChar) && isalpha(nextChar))
        word += nextChar;

    if (!(stream.rdstate() & std::ifstream::eofbit))
        stream.putback(nextChar);

    return word;
}

std::string parseNum(std::string wordNum, std::istream& stream)
{
    int decsLeft = 1;
    char nextChar;

    while (stream.get(nextChar) && (isdigit(nextChar) || (nextChar == '.' && decsLeft > 0)))
        wordNum += nextChar;

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

SceneElemMod parseAndGetVector(const std::vector<std::string>& tokens, int& iter, std::string modName)
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
            std::runtime_error("Vector Prematurely Ended (mid-vector)");

        assert(tokens[iter] == "," && "Invalid Number separator");
        iter++;
    }
    if (iter >= tokens.size())
        std::runtime_error("Vector Prematurely Ended");
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
            std::runtime_error("Empty Vector");
            break;
        default:
            std::runtime_error("unsupported vector size: " + nums.size());
    }
    mod.setData(data);
    return mod;
}
int parseAndAddVectorMod(const std::vector<std::string>& tokens, int iter, SceneElemMod& elem, std::string modName)
{
    SceneElemMod vectorMod = parseAndGetVector(tokens, iter, modName);
    elem.addModifier(modName, vectorMod);

    return iter;

}
int parseAndAddVectorMod(const std::vector<std::string>& tokens, int iter, SceneElem& elem, std::string modName)
{
    SceneElemMod vectorMod = parseAndGetVector(tokens, iter, modName);
    elem.addModifier(modName, vectorMod);

    return iter;

}

int parseAndAddPigmentMod(const std::vector<std::string>& tokens, int iter, SceneElem& elem)
{
    SceneElemMod pigmentMod("pigment");
    elem.addModifier("pigment", pigmentMod);

    assert(tokens[iter] == "{" && "Invalid Pigment block begin");
    iter++;

    assert(tokens[iter] == "color" && "Invalid Pigment block type");
    iter++;

    SceneElemMod colorMod("color");
    pigmentMod.addModifier("color", colorMod);

    std::string colorType = tokens[iter];
    assert((colorType == "rgb" || colorType == "rgbf") && "Invalid Color Type");
    iter++;

    iter = parseAndAddVectorMod(tokens, iter, colorMod, colorType);

    assert(tokens[iter] == "}" && "Invalid Pigment block end");
    iter++;

    return iter;

}

int parseAndAddFinishMod(const std::vector<std::string>& tokens, int iter, SceneElem& elem)
{
    SceneElemMod finishMod("finish");
    elem.addModifier("finish", finishMod);

    assert(tokens[iter] == "{" && "Invalid Finish block begin");
    iter++;

    while (iter < tokens.size() && tokens[iter] != "}")
    {
        std::string token = tokens[iter];
        iter++;
        if (std::find(finishModTokens.begin(), finishModTokens.end(), token) == finishModTokens.end())
            std::runtime_error("Invalid finish mod token: " + token);

        SceneElemMod finishSubMod(token);
        SceneElemMod::ModData data;
        data.dbl = atof(tokens[iter].c_str());
        finishMod.addModifier(finishSubMod.name, finishSubMod);
    }
    if (iter >= tokens.size())
        std::runtime_error("Finish prematurely Ended");

    assert(tokens[iter] == "}" && "Invalid Finish block end");
    iter++;

    return iter;

}

int parseAndAddCamera(const std::vector<std::string>& tokens, int iter, std::vector<SceneElem>& objects)
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
            std::runtime_error("Invalid camera token: " + token);
        }
        iter = parseAndAddVectorMod(tokens, iter, cameraElem, token);

    }
    assert(tokens[iter] == "}" && "Invalid Camera Block End");
    iter++;

    objects.push_back(cameraElem);

    return iter;
}

int parseAndAddLight(const std::vector<std::string>& tokens, int iter, std::vector<SceneElem>& objects)
{
    assert(tokens[iter] == "{" && "Invalid Light Block Start");
    iter++;

    SceneElem lightElem("light_source", SceneElem::LIGHT);
    iter = parseAndAddVectorMod(tokens, iter, lightElem, "location");

    assert(tokens[iter] == "color" && "Invalid Light Block Color");
    iter++;

    SceneElemMod colorMod("color");
    lightElem.addModifier("color", colorMod);

    assert(tokens[iter] == "rgb" && "Invalid Light Block RGB");
    iter++;

    iter = parseAndAddVectorMod(tokens, iter, colorMod, "rgb");

    assert(tokens[iter] == "}" && "Invalid Light Block End");
    iter++;

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
        if (std::find(shapeModTokens.begin(), shapeModTokens.end(), token) != shapeModTokens.end())
            iter++;
        else if (token == "translate")
        {
            iter++;
            iter = parseAndAddVectorMod(tokens, iter, elem, "translate");
        }
        else if (token == "rotate")
        {
            iter++;
            //if rotation exsists, save old rot and add to the rot that will be overwritten
            if (elem.hasMod("rotate"))
            {
                std::array<Number,3> oldRotData;
                const SceneElemMod::ModData& oldModData = elem.getMod("rotate").getData();
                std::copy(std::begin(oldModData.vec3), std::begin(oldModData.vec3), oldRotData.begin());
                iter = parseAndAddVectorMod(tokens, iter, elem, "rotate");

                std::array<Number,3> newRotData;
                const SceneElemMod::ModData& newModData = elem.getMod("rotate").getData();
                std::copy(std::begin(newModData.vec3), std::begin(newModData.vec3), newRotData.begin());
                newRotData[0] += oldRotData[0];
                newRotData[1] += oldRotData[1];
                newRotData[2] += oldRotData[2];

                SceneElemMod::ModData finalModData{};
                std::copy(newRotData.begin(),newRotData.end(),finalModData.vec3);
                elem.getMod("rotate").setData(finalModData);
            }
            else
            {
                iter = parseAndAddVectorMod(tokens, iter, elem, "rotate");
            }
        }
        else if (token == "pigment")
        {
            iter++;
            iter = parseAndAddPigmentMod(tokens, iter, elem);
        }
        else if (token == "finish")
        {
            iter++;
            iter = parseAndAddFinishMod(tokens, iter, elem);
        }
    }
    if (tokens.size() >= iter)
    {
        std::runtime_error("Pov block not properly ended");
    }
}

int parseAndAddSphere(const std::vector<std::string>& tokens, int iter, std::vector<SceneElem>& objects)
{
    SceneElem sphereElem("sphere", SceneElem::SHAPE);
    parseAndAddShapeMods(tokens, iter, sphereElem);
    iter = parseAndAddVectorMod(tokens, iter, sphereElem, "center");
    assert(tokens[iter] == "," && "invalid parse for Sphere");
    SceneElemMod radElem("radius");
    SceneElemMod::ModData radData;
    radData.dbl = atof(tokens[iter].c_str());
    iter++;
    radElem.setData(radData);
    sphereElem.addModifier("radius", radElem);
    while (iter < tokens.size() && tokens[iter] != "}")
        iter++;

    if (iter >= tokens.size())
        std::runtime_error("Premature end in sphere block");
    //take out final block token
    iter++;

    objects.push_back(sphereElem);

    return iter;
}

int parseAndAddBox(const std::vector<std::string>& tokens, int iter, std::vector<SceneElem>& objects)
{
    SceneElem boxElem("box", SceneElem::SHAPE);
    parseAndAddShapeMods(tokens, iter, boxElem);
    iter = parseAndAddVectorMod(tokens, iter, boxElem, "min");
    assert(tokens[iter] == "," && "invalid parse for Box min");
    iter = parseAndAddVectorMod(tokens, iter, boxElem, "max");
    //set iter to the ending bracket
    while (iter < tokens.size() && tokens[iter] != "}")
        iter++;

    if (iter >= tokens.size())
        std::runtime_error("Premature end in Box block");

    //take out final block token
    iter++;

    objects.push_back(boxElem);
    return iter;
}

int parseAndAddTriangle(const std::vector<std::string>& tokens, int iter, std::vector<SceneElem>& objects)
{
    SceneElem triangleElem("triangle", SceneElem::SHAPE);
    parseAndAddShapeMods(tokens, iter, triangleElem);
    iter = parseAndAddVectorMod(tokens, iter, triangleElem, "a");
    assert(tokens[iter] == "," && "invalid parse for Triangle 'a'");
    iter = parseAndAddVectorMod(tokens, iter, triangleElem, "b");
    assert(tokens[iter] == "," && "invalid parse for Triangle 'b'");
    iter = parseAndAddVectorMod(tokens, iter, triangleElem, "c");
    //set iter to the ending bracket
    while (iter < tokens.size() && tokens[iter] != "}")
        iter++;

    if (iter >= tokens.size())
        std::runtime_error("Premature end in Box block");

    //take out final block token
    iter++;

    objects.push_back(triangleElem);

    return iter;
}

int parseAndAddPlane(const std::vector<std::string>& tokens, int iter, std::vector<SceneElem>& objects)
{
    SceneElem planeElem("plane", SceneElem::CUSTOM);
    parseAndAddShapeMods(tokens, iter, planeElem);
    iter = parseAndAddVectorMod(tokens, iter, planeElem, "normal");
    assert(tokens[iter] == "," && "invalid parse for Sphere");
    SceneElemMod pointPlaneMod("d");
    SceneElemMod::ModData pointData;
    pointData.dbl = atof(tokens[iter].c_str());
    iter++;
    pointPlaneMod.setData(pointData);
    planeElem.addModifier("d", pointPlaneMod);
    while (iter < tokens.size() && tokens[iter] != "}")
        iter++;

    if (iter >= tokens.size())
        std::runtime_error("Premature end in sphere block");
    //take out final block token
    iter++;

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
            i = parseAndAddCamera(tokens, i, objects);
        else if (token == "light_source")
            i = parseAndAddLight(tokens, i, objects);
        else if (token == "sphere")
            i = parseAndAddSphere(tokens, i, objects);
        else if (token == "box")
            i = parseAndAddBox(tokens, i, objects);
        else if (token == "traingle")
            i = parseAndAddTriangle(tokens, i, objects);
        else if (token == "plane")
            i = parseAndAddPlane(tokens, i, objects);
        else
            std::runtime_error("Invalid Top-Level Token: " + token);
    }
}

std::vector<std::string> POVParser::tokenize(std::istream& stream)
{
    std::vector<std::string> tokens = std::vector<std::string>();
    char nextChar;
    while (stream.get(nextChar))
    {
        //check for potential keyword
        if (isalpha(nextChar))
        {
            std::string word = "" + nextChar;
            const std::string& parsedWord = parseWord(word, stream);
            if (std::find(keywords.begin(), keywords.end(), parsedWord) != keywords.end());
            {
                std::runtime_error("Invalid keyword: " + parsedWord);
            }
            tokens.push_back(parsedWord);
        }
            //check for numbers
        else if (isdigit(nextChar) || nextChar == '-' || nextChar == '.')
        {
            std::string wordNum = "" + nextChar;
            tokens.push_back(parseNum(wordNum, stream));
        }
            //check for operator characters, like for vectors or scope
        else if (std::find(specialChars.begin(), specialChars.end(), nextChar) != specialChars.end())
        {
            std::string charString = "" + nextChar;
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
                std::runtime_error(errorMessage.c_str());
            }
        }
            //make sure that whiteSpace is ignored before throwing error
        else if (!isspace(nextChar))
        {
            std::string errorMessage;
            errorMessage += "Invalid character: '";
            errorMessage += nextChar;
            errorMessage += "'";
            std::runtime_error(errorMessage.c_str());
        }

    }

    return tokens;
}


