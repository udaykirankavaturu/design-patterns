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

    virtual DocumentBuilder& setTitle() = 0;
    virtual DocumentBuilder& setHeader() = 0;
    virtual DocumentBuilder& setFooter() = 0;

    unique_ptr<Document> getResult() { return std::move(document); }
};

// Concrete Builders
class PDFBuilder : public DocumentBuilder {
public:
    DocumentBuilder& setTitle() override {
        document->setTitle("PDF Title");
        return *this;
    }

    DocumentBuilder& setHeader() override {
        document->setHeader("PDF Header");
        return *this;
    }

    DocumentBuilder& setFooter() override {
        document->setFooter("PDF Footer");
        return *this;
    }
};

class DOCXBuilder : public DocumentBuilder {
public:
    DocumentBuilder& setTitle() override {
        document->setTitle("DOCX Title");
        return *this;
    }

    DocumentBuilder& setHeader() override {
        document->setHeader("DOCX Header");
        return *this;
    }

    DocumentBuilder& setFooter() override {
        document->setFooter("DOCX Footer");
        return *this;
    }
};

// Director
class DocumentDirector {
public:
    void construct(DocumentBuilder& builder) {
        builder.setTitle()
               .setHeader()
               .setFooter();
    }
};

int main() {
    DocumentDirector director;
    
    // create pdf 
    PDFBuilder pdfBuilder;
    director.construct(pdfBuilder);
    unique_ptr<Document> finalPDFDoc = pdfBuilder.getResult();
    cout << finalPDFDoc->getTitle() << endl;
    cout << finalPDFDoc->getHeader() << endl;
    cout << finalPDFDoc->getFooter() << endl;

    // create docx 
    DOCXBuilder docxBuilder;
    docxBuilder.setTitle();
    docxBuilder.setHeader();
    unique_ptr<Document> finalDocX = docxBuilder.getResult();
    cout << finalDocX->getTitle() << endl;
    cout << finalDocX->getHeader() << endl;
    cout << finalDocX->getFooter() << endl;



    return 0;
}
