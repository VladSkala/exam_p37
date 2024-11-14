#include <iostream>
using namespace std;
struct Music {
    char namesong[50];
    char singer[50];
    int theyear;
    char text[500];
};

void showMusic(const Music& music) {
    cout << "Song: " << music.namesong << endl;
    cout << "Singer: " << music.singer << endl;
    cout << "The year of song: " << music.theyear << endl;
    cout << "Text: " << music.text << " seconds" << endl;
}

void fillMusic(Music& music) {
    cout << "Enter song name: ";
    cin >> music.namesong;
    cout << "Enter singer: ";
    cin >> music.singer;
    cout << "Enter the year of song: ";
    cin >> music.theyear;
    cout << "Enter text: ";
    cin >> music.text;
}


void findSongsBySinger(Music* musics, int count, const char* singer) {
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (strcmp(musics[i].singer, singer) == 0) {
            showMusic(musics[i]);
            cout << "==========================" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Error " << singer << endl;
    }
}
void findSongsByWord(Music* musics, int count, const char* word) {
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (strcmp(musics[i].text, word) == 0) {
            showMusic(musics[i]);
            cout << "==========================" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Error " << endl;
    }
}
void saveToFile(const char* pathToFile, Music* musics, int count) {
    FILE* file;
    if (fopen_s(&file, pathToFile, "w") == 0) {
        fwrite(musics, sizeof(Music), count, file);
        fclose(file);
    }
    else {
        cout << "Failed to open file for writing." << endl;
    }
}
void loadTextFromFile(const char* pathToFile, Music* musics, int count) {
    FILE* file;
    if (fopen_s(&file, pathToFile, "r") == 0) {
        fread(musics, sizeof(Music), count, file);
        fclose(file);
        cout << "Successfully\n";
    }
    else {
        cout << "Error\n";
    }
}



int main() {
    const int maxMusic = 100;
    const char* pathToFile = "music.bin";
    Music musics[maxMusic];
    int count = 0;

    int choice = 0;
    int index = 1;

    while (true) {
        cout << "\nMenu: \n";
        cout << "1. Add songs\n";
        cout << "2. Show all songs\n";
        cout << "3. Delete song\n";
        cout << "4. Change text\n";
        cout << "5. Search by singer\n";
        cout << "6. Search by word in text\n";
        cout << "7. Load text from file\n";
        cout << "8. Exit and save to file\n";

        cin >> choice;

        switch (choice) {
        case 1: {
            if (count < maxMusic) {
                fillMusic(musics[count]);
                count++;
                saveToFile(pathToFile, musics, count);
            }
            else {
                cout << "Maximum number of songs reached." << endl;
            }
            break;
        }
        case 2:
            for (int i = 0; i < count; i++) {
                showMusic(musics[i]);
                cout << "==========================" << endl;
            }
            break;

        case 3:
            cout << "Enter the index of song to delete (0 to " << count - 1 << "): ";
            cin >> index;
            if (index >= 0 && index < count) {
                for (int i = index; i < count - 1; i++) {
                    musics[i] = musics[i + 1];
                }
                count--;
                cout << "Song deleted." << endl;
            }
            else {
                cout << "Invalid song index." << endl;
            }
            break;

        case 4:
            cout << "Enter the index of song to change text (0 to " << count << "): ";
            cin >> index;
            if (index >= 0 && index < count) {
                cout << "Enter new text: ";
                cin.ignore();
                cin.getline(musics[index].text, 500);
                cout << "Text of song '" << musics[index].namesong << "' has been updated." << endl;
            }
            else {
                cout << "Invalid song index." << endl;
            }
            break;

        case 5: {
            char search[50];
            cout << "Enter the name of the singer to search: ";
            cin.ignore();
            cin.getline(search, 50);
            findSongsBySinger(musics, count, search);
            break;
        }

        case 6: {
            char word[50];
            cout << "Enter the word to search in song texts: ";
            cin.ignore();
            cin.getline(word, 50);
            findSongsByWord(musics, count, word);
            break;
        }
        case 7: {
            loadTextFromFile(pathToFile, musics, count);
            break;
        }

        case 8:
            saveToFile(pathToFile, musics, count);
            cout << "Exiting program." << endl;
            return 0;

        default:
            cout << "Error: Invalid choice." << endl;
            break;
        }
    }

    return 0;
}
