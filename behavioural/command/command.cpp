#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Text {
    bool isBold = false;
    bool isItalic = false;
    bool isUnderlined = false;

public:
    void setBold(bool b) { 
        isBold = b; 
        printStatus(); 
    }
    void setItalic(bool i) { 
        isItalic = i; 
        printStatus(); 
    }
    void setUnderline(bool u) { 
        isUnderlined = u; 
        printStatus(); 
    }

private:
    void printStatus() {
        cout << "Text is now:";
        if (isBold) cout << " Bold";
        if (isItalic) cout << " Italic";
        if (isUnderlined) cout << " Underlined";
        cout << endl;
    }
};

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class BoldCommand : public Command {
    Text* text;
public:
    BoldCommand(Text* t) : text(t) {}
    void execute() override { text->setBold(true); }
    void undo() override { text->setBold(false); }
};

class ItalicCommand : public Command {
    Text* text;
public:
    ItalicCommand(Text* t) : text(t) {}
    void execute() override { text->setItalic(true); }
    void undo() override { text->setItalic(false); }
};

class CompositeCommand : public Command {
    vector<Command*> commands;
public:
    void addCommand(Command* cmd) {
        commands.push_back(cmd);
    }

    void execute() override {
        for (Command* cmd : commands) {
            cmd->execute();
        }
    }

    void undo() override {
        for (int i = commands.size() - 1; i >= 0; i--) {
            commands[i]->undo();
        }
    }
};

class Editor {
    vector<Command*> history;

public:
    void executeCommand(Command* command) {
        command->execute();
        history.push_back(command);
    }

    void undo() {
        if (!history.empty()) {
            Command* command = history.back();
            command->undo();
            history.pop_back();
            delete command;
        }
    }

    ~Editor() {
        for (Command* cmd : history) {
            delete cmd;
        }
    }
};

int main() {
    Text text;
    Editor editor;

    editor.executeCommand(new BoldCommand(&text));
    editor.executeCommand(new ItalicCommand(&text));

    editor.undo();  // Undoes italic
    editor.undo();  // Undoes bold

    CompositeCommand* composite = new CompositeCommand();
    composite->addCommand(new BoldCommand(&text));
    composite->addCommand(new ItalicCommand(&text));
    editor.executeCommand(composite);

    editor.undo();  // Undoes composite command
    return 0;
}