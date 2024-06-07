#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv){
    if (std::string(argv[1]) == "make"){
        std::ofstream playlist(std::string(argv[2]) + ".txt", std::ios::in | std::ios::trunc);
        
        std::string content = argv[3];
        std::string cacheSong;
    
        playlist << "-[playlist file]-\n";
        for (unsigned i = 0; i < content.length(); i++){
            if (i+1 == content.length() && !(content[i] == 'n')){
                cacheSong += content[i];
                playlist << cacheSong << "\n";

                cacheSong = "";
            }
            
            if (content[i] == '/' && content[i+1] == 'n' && content[i+2] == ';'){
                playlist << cacheSong << "\n";

                cacheSong = "";
                i+=2;
            }
            else{
                cacheSong += content[i];
            }
        }
        playlist << "-[end of file/n]-";
        playlist.close();
    }
    if (std::string(argv[1]) == "read"){
        int index = std::stoi(argv[2]);

        std::string trackToPlay;
        std::string playlistContent;
        std::string playlistName = std::string(argv[3]);

        std::ifstream playlist(playlistName, std::ios::out);
        
        if (!playlist.good()){
            return 1;
        }
        playlist >> playlistContent;
        //for (int i = 0; i < playlistSize; i++){
        //     playlist.read(playlistContent.c_str(), i);
        //}
        for (int i = 0; i < index+1; i++){
            std::getline(playlist, trackToPlay);
            
            //if (trackToPlay == "\z"){
             //   std::cout << "f in de czat";
             //   return -1;
            //} 
        }
        std::cout << trackToPlay;

    }
    
    return 0;
}