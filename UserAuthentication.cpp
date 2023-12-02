#include <bits/stdc++.h>


class UserManager {
public:
    void registerUser(const std::string& username, const std::string& password) {
        if (users.find(username) == users.end()) {
            users[username] = password;
            std::cout << "User registered successfully.\n";
        } else {
            std::cout << "Username already exists. Choose another username.\n";
        }
    }

    bool loginUser(const std::string& username, const std::string& password) const {
        auto it = users.find(username);
        if (it != users.end() && it->second == password) {
            std::cout << "Login successful. Welcome, " << username << "!\n";
            return true;
        } else {
            std::cout << "Invalid username or password. Please try again.\n";
            return false;
        }
    }

private:
    std::map<std::string, std::string> users;
};

int main() {
    UserManager userManager;

    while (true) {
        std::cout << "1. Register\n2. Login\n3. Exit\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                userManager.registerUser(username, password);
                break;
            }
            case 2: {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (userManager.loginUser(username, password)) {
                    // Perform actions after successful login
                }
                break;
            }
            case 3:
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
