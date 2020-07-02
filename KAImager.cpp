#include <iostream>
#include <conio.h>
#include "Windows.h"
#include <string>
#include <vector>
using namespace std;

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.h"
}

// Loads as RGBA... even if file is only RGB
bool load_image(std::vector<unsigned char>& image, const std::string& filename, int& x, int&y)
{
    int n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 4);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y * 4);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

//Copies text to clipbaord (taken from http://www.cplusplus.com/forum/general/48837/)
void toClipboard(const std::string &s){
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size() + 1);
	if (!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg),s.c_str(),s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
}

//Initializes some strings
string name;
string filename;
string addImage = "";

int main()
{
    cout << "Input the name you want for the image: ";
    cin >> name;
    cout << "\nInput the name of the file: ";
    cin >> filename;
    cout << "\nLoading...\n\n";

    int width, height;
    vector<unsigned char> image;
    bool success = load_image(image, filename, width, height);
    if (!success)
    {
        cout << "\nError loading image\n";
    } else {
        const size_t RGBA = 4;

        addImage+="var " + name + "W = " + to_string(width)
                + ", " + name + "H = " + to_string(height)
                + ",\n\n" + name + "Pixels = [\n";

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                size_t index = RGBA * (y * width + x);
                if (static_cast<int>(image[index + 3]) != 0) {
                    addImage += "color("
                             + to_string(static_cast<int>(image[index + 0])) + ", "
                             + to_string(static_cast<int>(image[index + 1])) + ", "
                             + to_string(static_cast<int>(image[index + 2])) + "), ";
                } else {
                    addImage += "\'color(0, 0)\', ";
                }
            }
        }

        addImage+="\n];\n\nbackground(0, 0);\nstrokeWeight(1);\nfor (var x = 0; x < "
                + name + "W; x++) {\n"
                + "\tfor (var y = 0; y < " + name + "H; y++) {\n"
                + "\t\tvar id = (x * " + name + "H) + y;\n"
                + "\t\tstroke(" + name + "Pixels[id]);\n"
                + "\t\tpoint(x, y);\n"
                + "\t}\n}\n\nvar " + name + " = get(0, 0, " + name + "W, " + name + "H);\n\n";

        toClipboard(addImage);

        cout << "Compiling done! The pixels have been copied to your clipboard!";
    }

    cout << "\n\nPress any key to exit...";

    //Waits for the user to input a number, then ends the program
    getch();

    return 0;
}
