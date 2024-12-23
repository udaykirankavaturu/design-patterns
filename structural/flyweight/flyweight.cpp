#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
using namespace std;

// Flyweight class containing intrinsic state
class Character {
private:
    char symbol;
    string font;
    int size;

public:
    Character(char s, const string& f, int sz)
        : symbol(s), font(f), size(sz) {}

    // Display method takes extrinsic state as parameters
    void display(int x, int y) const {
        cout << "Character '" << symbol << "' at (" << x << "," << y 
                  << ") with font " << font << " and size " << size << endl;
    }
};

// Flyweight Factory
class CharacterFactory {
private:
    unordered_map<string, shared_ptr<Character>> characters;

    // Helper method to create key
    static string createKey(char symbol, const string& font, int size) {
        return string(1, symbol) + font + to_string(size);
    }

public:
    shared_ptr<Character> getCharacter(char symbol, const string& font, int size) {
        string key = createKey(symbol, font, size);
        
        auto it = characters.find(key);
        if (it == characters.end()) {
            // Create new character if it doesn't exist
            auto newChar = make_shared<Character>(symbol, font, size);
            characters[key] = newChar;
            cout << "Creating new character: " << key << endl;
            return newChar;
        }
        
        cout << "Reusing existing character: " << key << endl;
        return it->second;
    }

    size_t getTotalCharacters() const {
        return characters.size();
    }
};

// TextEditor class that uses the flyweight pattern
class TextEditor {
private:
    struct CharacterPosition {
        shared_ptr<Character> character;
        int x;
        int y;
    };

    vector<CharacterPosition> characters;
    CharacterFactory& factory;

public:
    TextEditor(CharacterFactory& f) : factory(f) {}

    void addCharacter(char symbol, const string& font, int size, int x, int y) {
        auto character = factory.getCharacter(symbol, font, size);
        characters.push_back({character, x, y});
    }

    void render() const {
        cout << "\nRendering text:" << endl;
        for (const auto& charPos : characters) {
            charPos.character->display(charPos.x, charPos.y);
        }
    }
};

// Main function demonstrating usage
int main() {
    CharacterFactory factory;
    TextEditor editor(factory);

    // Adding text "Hello!"
    string text = "Hello!";
    string font = "Arial";
    int size = 12;
    int x_pos = 0;

    // Add each character with increasing x position
    for (char c : text) {
        editor.addCharacter(c, font, size, x_pos, 0);
        x_pos += 10;
    }

    // Add some repeated characters at different positions
    editor.addCharacter('l', font, size, 50, 20);  // Reuses existing 'l'
    editor.addCharacter('o', font, size, 60, 20);  // Reuses existing 'o'

    // Display results
    cout << "\nTotal unique characters created: " 
              << factory.getTotalCharacters() << endl;
    
    editor.render();

    return 0;
}