//
// Created by lejonmcgowan on 8/1/16.
//

#include <iostream>

std::string sceneFile;
std::string outputFile;
int width,height;

void printUsage()
{
    std::cerr << "Usage: [input scene filename] [output image filename] [output image width] [output image height]"
              << std::endl;
}

bool processArguments(int argc, char** argv)
{
    /**
     * return proper usage if enough parameters are not defined
     */
    if(argc < 5)
    {
        printUsage();
        return false;
    }

    //parse the 4 fields and set the respective global variables

    //print usage and exit if at any point any of the parameters are invalid


}

int main(int argc, char **argv)
{
    std::cout << "Hello World!" << std::endl;

    //proceed to parse file and render if the arguments are valid
    if(processArguments(argc,argv))
    {
        //set the SceneOptions fields from command-line arguments

        //parse the config file for the remaining SceneOptions

        //parse the scene file to get the scene to be rendered

        //render the scene
    }

    return 0;
}

