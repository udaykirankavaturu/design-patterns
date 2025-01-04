#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// Class to store document state (Memento)
class DocumentState {
private:
    string content;
    string timestamp;

public:
    DocumentState(const string& text) : content(text) {
        time_t now = time(0);
        timestamp = ctime(&now);
    }

    string getContent() const { 
        return content; 
    }

    string getTimestamp() const { 
        return timestamp; 
    }
};

// Document class (Originator)
class Document {
private:
    string content;
    string documentName;

public:
    Document(const string& name) : documentName(name) {
        cout << "Created new document: " << name << "\n";
    }

    void addText(const string& text) {
        content += text;
        cout << "Added text: \"" << text << "\"\n";
    }

    DocumentState* save() {
        cout << "Saving document...\n";
        return new DocumentState(content);
    }

    void restore(DocumentState* savedState) {
        content = savedState->getContent();
        cout << "Restored document from: " << savedState->getTimestamp();
    }

    void display() const {
        cout << "\n=== " << documentName << " ===\n";
        cout << (content.empty() ? "[Empty document]" : content) << "\n";
        cout << "=== End of document ===\n";
    }
};

// Manual Save Manager class (Caretaker)
class SaveManager {
private:
    vector<DocumentState*> saves;

public:
    void saveDocument(Document& doc) {
        saves.push_back(doc.save());
        cout << "Manual save created (Save #" << saves.size() << ")\n";
    }

    void restoreSave(Document& doc, size_t saveIndex) {
        if (saveIndex < 1 || saveIndex > saves.size()) {
            cout << "Invalid save index!\n";
            return;
        }
        doc.restore(saves[saveIndex - 1]);
    }

    void showSaves() const {
        cout << "\nAvailable Saves:\n";
        for (size_t i = 0; i < saves.size(); ++i) {
            cout << i + 1 << ". Created at: " << saves[i]->getTimestamp();
        }
    }

    ~SaveManager() {
        for (auto state : saves) {
            delete state;
        }
    }
};

int main() {
    Document myDoc("MyNote.txt");
    SaveManager saveManager;

    myDoc.addText("Hello ");
    saveManager.saveDocument(myDoc);
    myDoc.display();

    myDoc.addText("World! ");
    saveManager.saveDocument(myDoc);
    myDoc.display();

    myDoc.addText("This is not saved yet.");
    myDoc.display();

    saveManager.showSaves();

    cout << "\nRestoring to the first save...\n";
    saveManager.restoreSave(myDoc, 1);
    myDoc.display();

    return 0;
}
