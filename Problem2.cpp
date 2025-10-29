#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


//Using a user defined data type to store the ID sent in each message and the timestamp when it was sent
struct Message {
    int ID, timestamp;

    Message(int ID_, int timestamp_) : ID(ID_), timestamp(timestamp_) {} //Constructor
};

//When using a heap we'll need to sort the messages by timestamp
struct timestamp_sort {
    bool operator()(Message const& a, Message const& b) const {
        return a.timestamp > b.timestamp;
    }
};

//When sending a message:
void onSend(int msgID, int msgTimestamp, std::vector<Message>& sent) {

    //Add the message to the heap
    sent.push_back(Message(msgID, msgTimestamp));

    //Sort the added message into the correct place in the heap
    std::push_heap(sent.begin(), sent.end(), timestamp_sort());
}

//When receiveing a reply:
void onReply(int replyID, std::vector<Message>& sent) {

    //Check if the ID is in the heap
    auto it = std::find_if(sent.begin(), sent.end(), [replyID](const Message& m) { return m.ID == replyID; });

    //If the ID is in the heap we remove the message
    if (it != sent.end()) {
        sent.erase(it);

        //Rebuilding the heap
        std::make_heap(sent.begin(), sent.end());
    }
}

//Checking for timeouts of messages periodically
void checkTimeouts(std::vector<Message>& sent)
{
    //Since the heap is sorted by timestamps we can check the oldest one
    const Message& oldestMessage = sent.front();
    if (oldestMessage.timestamp > 1000)
    {
        std::cout << "Communication error";
    }
}

int main()
{
    std::vector<Message> sent;

    //Defining the heap we'll use to store the values of the sent messages
    std::make_heap(sent.begin(), sent.end(), timestamp_sort());
}
