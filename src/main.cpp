//
// Created by lejonmcgowan on 8/1/16.
//

#include <iostream>

std::string sceneFile;
std::string outputFile;
int width, height;

void printUsage()
{
    std::cerr << "Usage: [input scene filename] [output image filename] [output image width] [output image height]"
              << std::endl;
}

bool processArguments(int argc, char **argv)
{
    /**
     * process pointed ini file
     */
    if (argc == 2)
    {

    }
    /**
     * return proper usage if parameters are an incorrect number (not for a file config, but not for a command line config
     */
    if (argc == 1 || argc < 5 && argc > 2)
    {
        printUsage();
    }

    //parse the 4 fields and set the respective global variables

    //print usage and exit if at any point any of the parameters are invalid

    //todo nothing is ready to be rendered. make configs, fool.
    return false;
}

int main(int argc, char **argv)
{
    std::cout << "Hello World!" << std::endl;

    //proceed to parse file and render if the arguments are valid
    if (processArguments(argc, argv))
    {
        /*set the SceneContext fields from command-line arguments OR
            via config file (ini)*/

        //retrieve the scene to be rendered (config with the proper integrators, renderer, options, etc)

        //render the scene
    }

    return 0;
}

