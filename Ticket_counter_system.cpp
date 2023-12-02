#include <bits/stdc++.h>

class Event {
public:
    Event(std::string eventName, int availableTickets)
        : eventName(std::move(eventName)), availableTickets(availableTickets) {}

    std::string getEventName() const {
        return eventName;
    }

    int getAvailableTickets() const {
        return availableTickets;
    }

    void sellTickets(int quantity) {
        if (quantity > 0 && quantity <= availableTickets) {
            std::cout << quantity << " ticket(s) sold for " << eventName << std::endl;
            availableTickets -= quantity;
        } else {
            std::cout << "Not enough tickets available for " << eventName << std::endl;
        }
    }

private:
    std::string eventName;
    int availableTickets;
};

class TicketMasterApp {
public:
    void addEvent(const Event& event) {
        events.push_back(event);
    }

    void displayEvents() const {
        std::cout << "Available Events:" << std::endl;
        for (const auto& event : events) {
            std::cout << "- " << event.getEventName() << " (" << event.getAvailableTickets() << " tickets)" << std::endl;
        }
    }

    void sellTickets(const std::string& eventName, int quantity) {
        auto it = std::find_if(events.begin(), events.end(),
                               [&eventName](const Event& event) { return event.getEventName() == eventName; });

        if (it != events.end()) {
            it->sellTickets(quantity);
        } else {
            std::cout << "Event not found: " << eventName << std::endl;
        }
    }

private:
    std::vector<Event> events;
};

int main() {
    TicketMasterApp ticketMaster;

    ticketMaster.addEvent(Event("Concert", 100));
    ticketMaster.addEvent(Event("Sports Game", 50));

    while (true) {
        std::cout << "1. Display Events\n2. Sell Tickets\n3. Exit" << std::endl;
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                ticketMaster.displayEvents();
                break;
            case 2: {
                std::cout << "Enter event name: ";
                std::string eventName;
                std::cin.ignore();
                std::getline(std::cin, eventName);

                std::cout << "Enter number of tickets to sell: ";
                int quantity;
                std::cin >> quantity;

                ticketMaster.sellTickets(eventName, quantity);
                break;
            }
            case 3:
                return 0;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    }

    return 0;
}
