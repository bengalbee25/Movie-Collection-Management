#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Movie {
private:
    string title;
    string director;
    int year;
    string countryOfOrigin;
    string remarks;
    string status;
public:
    Movie(string t, string d, int y, string country, string r, string s)
        : title(t), director(d), year(y), countryOfOrigin(country), remarks(r), status(s) {}

    void display() const {
        cout << "Title: " << title << "\n";
        cout << "Director: " << director << "\n";
        cout << "Year: " << year << "\n";
        cout << "Country of Origin: " << countryOfOrigin << "\n";
        cout << "Status: " << status << "\n";
        cout << "Remarks: " << remarks << "\n\n";
    }

    string getTitle() const {
        return title;
    }

    void editMovie() {
        cout << "Enter new title: ";
        getline(cin, title);
        cout << "Enter new director: ";
        getline(cin, director);
        cout << "Enter new year: ";
        cin >> year;
        cout << "Enter new country of origin: ";
        cin.ignore();
        getline(cin, countryOfOrigin);

        cout << "Choose new status:\n";
        cout << "1. Watched\n";
        cout << "2. Did not watch\n";
        cout << "3. Want to watch\n";
        int choice;
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        switch (choice) {
            case 1:
                status = "Watched";
                break;
            case 2:
                status = "Did not watch";
                break;
            case 3:
                status = "Want to watch";
                break;
            default:
                cout << "Invalid choice. Setting status to 'Unknown'.\n";
                status = "Unknown";
                break;
        }

        cout << "Enter remarks: ";
        cin.ignore();
        getline(cin, remarks);
    }

    void saveToFile(ofstream& outFile) const {
        outFile << title << "\n";
        outFile << director << "\n";
        outFile << year << "\n";
        outFile << countryOfOrigin << "\n";
        outFile << status << "\n";
        outFile << remarks << "\n";
    }
};

class MovieLibrary {
private:
    vector<Movie> movies;

public:
    void addMovie(const Movie& movie) {
        movies.push_back(movie);
        cout << "Movie added successfully!\n";
    }

    void viewMovies() const {
        if (movies.empty()) {
            cout << "Library is empty.\n";
            return;
        }

        for (const Movie& movie : movies) {
            movie.display();
        }
    }

    void editMovie(string targetTitle) {
        for (Movie& movie : movies) {
            if (movie.getTitle() == targetTitle) {
                movie.editMovie();
                cout << "Movie edited successfully!\n";
                return;
            }
        }

        cout << "Movie not found.\n";
    }

    void deleteMovie(string targetTitle) {
        for (auto it = movies.begin(); it != movies.end(); ++it) {
            if (it->getTitle() == targetTitle) {
                movies.erase(it);
                cout << "Movie deleted successfully!\n";
                return;
            }
        }

        cout << "Movie not found.\n";
    }

    void searchMovie(string targetTitle) const {
        for (const Movie& movie : movies) {
            if (movie.getTitle() == targetTitle) {
                movie.display();
                return;
            }
        }

        cout << "Movie not found.\n";
    }

    void saveLibraryToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Error opening file for writing.\n";
            return;
        }

        for (const Movie& movie : movies) {
            movie.saveToFile(outFile);
        }

        outFile.close();
        cout << "Library saved to file successfully.\n";
    }

    void loadLibraryFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Error opening file for reading.\n";
            return;
        }

        string title, director, country, remarks, status;
        int year;

        while (getline(inFile, title) && getline(inFile, director) && inFile >> year
               && inFile.ignore() && getline(inFile, country) && getline(inFile, status)
               && getline(inFile, remarks)) {
            Movie movie(title, director, year, country, remarks, status);
            movies.push_back(movie);
        }

        inFile.close();
        cout << "Library loaded from file successfully.\n";
    }
};

int main() {
    MovieLibrary library;
    string filename = "movies.txt";

    library.loadLibraryFromFile(filename);

    int choice;

    do {
        cout << "Movie Library Menu:\n";
        cout << "1. Add Movie\n";
        cout << "2. View Movies\n";
        cout << "3. Edit Movie\n";
        cout << "4. Delete Movie\n";
        cout << "5. Search Movie\n";
        cout << "6. Save Library to File\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, director, country, remarks, status;
                int year;
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter director: ";
                getline(cin, director);
                cout << "Enter year: ";
                cin >> year;
                cout << "Enter country of origin: ";
                cin.ignore();
                getline(cin, country);

                cout << "Choose status:\n";
                cout << "1. Watched\n";
                cout << "2. Did not watch\n";
                cout << "3. Want to watch\n";
                int choice;
                cout << "Enter your choice (1-3): ";
                cin >> choice;
                switch (choice) {
                    case 1:
                        status = "Watched";
                        break;
                    case 2:
                        status = "Did not watch";
                        break;
                    case 3:
                        status = "Want to watch";
                        break;
                    default:
                        cout << "Invalid choice. Setting status to 'Unknown'.\n";
                        status = "Unknown";
                        break;
                }

                cout << "Enter remarks: ";
                cin.ignore();
                getline(cin, remarks);
                Movie newMovie(title, director, year, country, remarks, status);
                library.addMovie(newMovie);
                break;
            }
            case 2:
                library.viewMovies();
                break;
            case 3: {
                string targetTitle;
                cout << "Enter the title of the movie you want to edit: ";
                cin.ignore();
                getline(cin, targetTitle);
                library.editMovie(targetTitle);
                break;
            }
            case 4: {
                string targetTitle;
                cout << "Enter the title of the movie you want to delete: ";
                cin.ignore();
                getline(cin, targetTitle);
                library.deleteMovie(targetTitle);
                break;
            }
            case 5: {
                string targetTitle;
                cout << "Enter the title of the movie you want to search for: ";
                cin.ignore();
                getline(cin, targetTitle);
                library.searchMovie(targetTitle);
                break;
            }
            case 6:
                library.saveLibraryToFile(filename);
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 7);

    return 0;
}
