#include <iostream>
#include <string>
using namespace std;

// Node class representing one song
class Node {
public:
    string title;
    string artist;
    Node* prev;
    Node* next;

    Node(string t, string a) {
        title = t;
        artist = a;
        prev = nullptr;
        next = nullptr;
    }
};

// Doubly Linked List for Music Playlist
class MusicPlaylist {
private:
    Node* head;       // Points to the first song
    Node* current;    // Points to the currently selected song

public:
    MusicPlaylist() {
        head = nullptr;
        current = nullptr;
    }

    // Add a new song at the end
    void addSong(string title, string artist) {
        Node* p = new Node(title, artist); // p is the new node

        if (head == nullptr) {
            head = p;
            current = p;
        } else {
            Node* q = head; // q traverses the list

            while (q->next != nullptr) {
                q = q->next;
            }

            q->next = p;
            p->prev = q;
        }

        cout << "Song added successfully!\n";
    }

    // Delete a song by its title
    void deleteSong(string title) {
        Node* p = nullptr;
        Node* q = head;

        // Find the song to delete
        while (q != nullptr && q->title != title) {
            q = q->next;
        }

        if (q == nullptr) {
            cout << "Song not found!\n";
            return;
        }

        p = q; // p points to the node being deleted

        // Update current if the selected song is deleted
        if (current == p) {
            if (p->next != nullptr)
                current = p->next;
            else
                current = p->prev;
        }

        // Connect the previous node to the next node
        if (p->prev != nullptr)
            p->prev->next = p->next;
        else
            head = p->next;

        // Connect the next node to the previous node
        if (p->next != nullptr)
            p->next->prev = p->prev;

        delete p;

        cout << "Song deleted successfully!\n";
    }

    // Display playlist from first to last
    void displayPlaylist() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        Node* q = head;
        cout << "\n--- Music Playlist ---\n";

        while (q != nullptr) {
            cout << q->title << " - " << q->artist << '\n';
            q = q->next;
        }
    }

    // Display playlist from last to first
    void displayReverse() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        Node* q = head;

        // Move q to the last song
        while (q->next != nullptr) {
            q = q->next;
        }

        cout << "\n--- Reverse Playlist ---\n";

        while (q != nullptr) {
            cout << q->title << " - " << q->artist << '\n';
            q = q->prev;
        }
    }

    // Play the currently selected song
    void playCurrentSong() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        cout << "Now Playing: " << current->title
             << " - " << current->artist << '\n';
    }

    // Move to the next song
    void playNextSong() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
        } else if (current->next == nullptr) {
            cout << "You are already at the last song!\n";
        } else {
            current = current->next;
            playCurrentSong();
        }
    }

    // Move to the previous song
    void playPreviousSong() {
        if (current == nullptr) {
            cout << "Playlist is empty!\n";
        } else if (current->prev == nullptr) {
            cout << "You are already at the first song!\n";
        } else {
            current = current->prev;
            playCurrentSong();
        }
    }

    // Show the complete playlist as playback
    void playCompletePlaylist() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        current = head;
        Node* q = head;

        cout << "\n--- Playing Complete Playlist ---\n";

        while (q != nullptr) {
            current = q;
            playCurrentSong();
            q = q->next;
        }
    }

    // Play the complete playlist a specified number of times
    void repeatAll(int repetitions) {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        if (repetitions <= 0) {
            cout << "Enter a positive number of repetitions!\n";
            return;
        }

        for (int i = 1; i <= repetitions; i++) {
            cout << "\nRepetition " << i << ":\n";
            playCompletePlaylist();
        }

        cout << "Repeat All completed!\n";
    }

    // Display the currently selected song
    void showCurrentSong() {
        if (current == nullptr) {
            cout << "No song selected!\n";
        } else {
            cout << "Current Song: " << current->title
                 << " - " << current->artist << '\n';
        }
    }

    // Free all allocated memory
    ~MusicPlaylist() {
        Node* q = head;

        while (q != nullptr) {
            Node* p = q;
            q = q->next;
            delete p;
        }

        head = nullptr;
        current = nullptr;
    }
};

// Main function
int main() {
    MusicPlaylist playlist;
    int choice;

    do {
        cout << "\n===== MUSIC PLAYLIST MANAGER =====\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist\n";
        cout << "4. Display Playlist in Reverse\n";
        cout << "5. Play Current Song\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Play Complete Playlist\n";
        cout << "9. Repeat All\n";
        cout << "10. Show Current Song\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string title, artist;
        int repetitions;

        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, title);

                cout << "Enter artist name: ";
                getline(cin, artist);

                playlist.addSong(title, artist);
                break;

            case 2:
                cout << "Enter title of song to delete: ";
                getline(cin, title);
                playlist.deleteSong(title);
                break;

            case 3:
                playlist.displayPlaylist();
                break;

            case 4:
                playlist.displayReverse();
                break;

            case 5:
                playlist.playCurrentSong();
                break;

            case 6:
                playlist.playNextSong();
                break;

            case 7:
                playlist.playPreviousSong();
                break;

            case 8:
                playlist.playCompletePlaylist();
                break;

            case 9:
                cout << "Enter number of repetitions: ";

                if (!(cin >> repetitions)) {
                    cout << "Invalid repetition count!\n";
                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n'
                    );
                    break;
                }

                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
                playlist.repeatAll(repetitions);
                break;

            case 10:
                playlist.showCurrentSong();
                break;

            case 11:
                cout << "Exiting Music Playlist Manager.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 11);

    return 0;
}
/*

PS D:\DSACCE2> cd "d:\DSACCE2\SarthakCCE2.CPP\" ; if ($?) { g++ main.cpp -o main } ; if ($?) { .\main }

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 1
Enter song title: Kesariyan
Enter artist name: Arijit Singh
Song added successfully!

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 1
Enter song title: Softly
Enter artist name: Karan Aujla
Song added successfully!

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 1
Enter song title: Tere Liye
Enter artist name: Atif aslam
Song added successfully!

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 1
Enter song title: ve kamleyan
Enter artist name: Arijit Singh
Song added successfully!

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 2
Enter title of song to delete: Kesariyan
Song deleted successfully!

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 3

--- Music Playlist ---
Softly - Karan Aujla
Tere Liye - Atif aslam
ve kamleyan - Arijit Singh

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 4

--- Reverse Playlist ---
ve kamleyan - Arijit Singh
Tere Liye - Atif aslam
Softly - Karan Aujla

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 5
Now Playing: Softly - Karan Aujla

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 6
Now Playing: Tere Liye - Atif aslam

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 7
Now Playing: Softly - Karan Aujla

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 8

--- Playing Complete Playlist ---
Now Playing: Softly - Karan Aujla
Now Playing: Tere Liye - Atif aslam
Now Playing: ve kamleyan - Arijit Singh

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 9
Enter number of repetitions: 2

Repetition 1:

--- Playing Complete Playlist ---
Now Playing: Softly - Karan Aujla
Now Playing: Tere Liye - Atif aslam
Now Playing: ve kamleyan - Arijit Singh

Repetition 2:

--- Playing Complete Playlist ---
Now Playing: Softly - Karan Aujla
Now Playing: Tere Liye - Atif aslam
Now Playing: ve kamleyan - Arijit Singh
Repeat All completed!

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 10
Current Song: ve kamleyan - Arijit Singh

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter your choice: 11
Exiting Music Playlist Manager.
PS D:\DSACCE2\SarthakCCE2.CPP> */