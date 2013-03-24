#include <InGameObjects\Tracks.h>


    Tracks::Tracks(std::string trackFileName)
    {
        loadFromFile(trackFileName);
    }

    int Tracks::getNumberofTracks()
    {
        return filenames.size();
    }

    std::string Tracks::getTrackFilename(int i)
    {
        return filenames.at(i);
    }

    void Tracks::loadFromFile(std::string filename)
    {
        std::string line;
        std::ifstream myfile (filename);

        filenames.clear();

        if (myfile.is_open())
            {
                while ( myfile.good() )
                {
                    getline (myfile,line);
                    filenames.push_back(line);
                }
                myfile.close();
            }

        else printf("Tracks: Unable to open file\n"); 
    }



