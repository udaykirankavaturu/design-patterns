#include <iostream>
using namespace std;
#include <string>

// Forward declarations
class FormMediator;

// Abstract Component class
class FormComponent {
protected:
    FormMediator* mediator;
    string value;

public:
    virtual void changed() = 0;
    void setMediator(FormMediator* m) { mediator = m; }
    string getValue() { return value; }
    virtual void setValue(const string& val) { value = val; }
};

// Concrete Components
class UsernameField : public FormComponent {
public:
    void changed() override;
};

class PasswordField : public FormComponent {
public:
    void changed() override;
};

class ConfirmPasswordField : public FormComponent {
public:
    void changed() override;
};

class SubmitButton : public FormComponent {
private:
    bool enabled = false;
public:
    void changed() override {}
    void setEnabled(bool state) { 
        enabled = state;
        cout << "Submit button " << (state ? "enabled" : "disabled") << endl;
    }
    bool isEnabled() { return enabled; }
};

class ErrorLabel : public FormComponent {
public:
    void changed() override {}
    void showError(const string& message) {
        cout << "Error: " << message << endl;
    }
    void clearError() {
        cout << "Errors cleared" << endl;
    }
};

// Mediator
class FormMediator {
private:
    UsernameField* username;
    PasswordField* password;
    ConfirmPasswordField* confirmPassword;
    SubmitButton* submitButton;
    ErrorLabel* errorLabel;

public:
    void setUsername(UsernameField* u) { username = u; }
    void setPassword(PasswordField* p) { password = p; }
    void setConfirmPassword(ConfirmPasswordField* cp) { confirmPassword = cp; }
    void setSubmitButton(SubmitButton* s) { submitButton = s; }
    void setErrorLabel(ErrorLabel* e) { errorLabel = e; }

    void notify(FormComponent* sender) {
        validateForm();
    }

private:
    void validateForm() {
        errorLabel->clearError();
        
        // Validate username
        if (username->getValue().length() < 3) {
            errorLabel->showError("Username must be at least 3 characters");
            submitButton->setEnabled(false);
            return;
        }

        // Validate password
        if (password->getValue().length() < 6) {
            errorLabel->showError("Password must be at least 6 characters");
            submitButton->setEnabled(false);
            return;
        }

        // Validate password match
        if (password->getValue() != confirmPassword->getValue()) {
            errorLabel->showError("Passwords do not match");
            submitButton->setEnabled(false);
            return;
        }

        // All validations passed
        submitButton->setEnabled(true);
    }
};

// Implementation of Component changed() methods
void UsernameField::changed() { mediator->notify(this); }
void PasswordField::changed() { mediator->notify(this); }
void ConfirmPasswordField::changed() { mediator->notify(this); }

int main() {
    // Create components
    UsernameField username;
    PasswordField password;
    ConfirmPasswordField confirmPassword;
    SubmitButton submitButton;
    ErrorLabel errorLabel;

    // Create mediator and set up relationships
    FormMediator mediator;
    mediator.setUsername(&username);
    mediator.setPassword(&password);
    mediator.setConfirmPassword(&confirmPassword);
    mediator.setSubmitButton(&submitButton);
    mediator.setErrorLabel(&errorLabel);

    // Set mediator for all components
    username.setMediator(&mediator);
    password.setMediator(&mediator);
    confirmPassword.setMediator(&mediator);
    submitButton.setMediator(&mediator);
    errorLabel.setMediator(&mediator);

    // Simulate user interaction
    cout << "\n--- Setting username to 'jo' ---\n";
    username.setValue("jo");
    username.changed();

    cout << "\n--- Setting username to 'john' ---\n";
    username.setValue("john");
    username.changed();

    cout << "\n--- Setting password to '123' ---\n";
    password.setValue("123");
    password.changed();

    cout << "\n--- Setting password to '123456' ---\n";
    password.setValue("123456");
    password.changed();

    cout << "\n--- Setting confirm password to '123457' ---\n";
    confirmPassword.setValue("123457");
    confirmPassword.changed();

    cout << "\n--- Setting confirm password to '123456' ---\n";
    confirmPassword.setValue("123456");
    confirmPassword.changed();

    return 0;
}