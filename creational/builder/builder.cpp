#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Document {
private:
    string title;
    string header;
    string footer;

public:
    void setTitle(string title) { this->title = title; }
    void setHeader(string header) { this->header = header; }
    void setFooter(string footer) { this->footer = footer; }

    string getTitle() const { return title; }
    string getHeader() const { return header; }
    string getFooter() const { return footer; }
};

// Abstract Builder
class DocumentBuilder {
protected:
    unique_ptr<Document> document;

public:
    DocumentBuilder() : document(unique_ptr<Document>(new Document())) {}
    virtual ~DocumentBuilder() = default;

    virtual DocumentBuilder& setTitle(string) = 0;
    virtual DocumentBuilder& setHeader(string) = 0;
    virtual DocumentBuilder& setFooter(string) = 0;

    unique_ptr<Document> getResult() { return std::move(document); }
};

// Concrete Builder
class PDFBuilder : public DocumentBuilder {
public:
    DocumentBuilder& setTitle(string title) override {
        document->setTitle(title);
        return *this;
    }

    DocumentBuilder& setHeader(string header) override {
        document->setHeader(header);
        return *this;
    }

    DocumentBuilder& setFooter(string footer) override {
        document->setFooter(footer);
        return *this;
    }
};

// Director
class DocumentDirector {
public:
    void construct(DocumentBuilder& builder) {
        builder.setTitle("This is the title!")
               .setHeader("This is the header!")
               .setFooter("This is the footer!");
    }
};

int main() {
    PDFBuilder pdfBuilder;
    DocumentDirector director;

    director.construct(pdfBuilder);

    unique_ptr<Document> finalDoc = pdfBuilder.getResult();

    cout << finalDoc->getTitle() << endl;
    cout << finalDoc->getHeader() << endl;
    cout << finalDoc->getFooter() << endl;

    return 0;
}
