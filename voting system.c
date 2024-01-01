#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxVoters 100
#define maxCandidates 100

typedef struct Voter {
    char username[50];
    char password[50];
    int hasVoted;  // New field to track whether the user has voted
    struct Voter *next;
} Voter;

typedef struct {
    char name[50];
} Candidate;

typedef struct {
    int candidate_id;
    int vote_count;
} VoteTally;

Voter *createUser(const char *username, const char *password) {
    Voter *newUser = (Voter *)malloc(sizeof(Voter));
    if (newUser == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->hasVoted = 0;  // Initialize hasVoted to 0 (not voted yet)
    newUser->next = NULL;

    return newUser;
}

void addUser(Voter **head, const char *username, const char *password) {
    // Check if the user already exists
    Voter *current = *head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            printf("User already exists. Registration failed.\n");
            return; // Exit without adding the user
        }
        else{
            printf("Voter has been registered successfully!\n\n");
        }
        current = current->next;
    }

    // If the user doesn't exist, proceed with registration
    Voter *newUser = createUser(username, password);
    newUser->next = *head;
    *head = newUser;
}

Voter *authenticateUser(const Voter *head, const char *username, const char *password) {
    while (head != NULL) {
        if (strcmp(head->username, username) == 0 && strcmp(head->password, password) == 0) {
            return (Voter *)head;
        }
        head = head->next;
    }
    return NULL;
}

void castVote(Voter *voter, Candidate *candidates, int numCandidates, VoteTally *tallies) {
    // Check if the user has already voted
    if (voter->hasVoted) {
        printf("You have already voted. Multiple votes are not allowed.\n");
        return;
    }

    printf("Available candidates:\n");
    for (int i = 0; i < numCandidates; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }

    int choice;
    printf("Enter the candidate number to vote: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= numCandidates) {
        tallies[choice - 1].vote_count++;

        // Update the hasVoted flag for the user
        voter->hasVoted = 1;
    } else {
        printf("Invalid candidate choice.\n");
    }
}

void displayResults(Candidate *candidates, int numCandidates, VoteTally *tallies) {
    printf("Current vote tallies:\n");
    for (int i = 0; i < numCandidates; i++) {
        printf("%s: %d votes\n", candidates[i].name, tallies[i].vote_count);
    }
}

int main() {
    Voter *userHead = NULL;
    int decide;
    char username[50], password[50];

    Candidate candidates[maxCandidates];
    int numCandidates = 6;

    candidates[0] = (Candidate){"BJP"};
    candidates[1] = (Candidate){"AAP"};
    candidates[2] = (Candidate){"Congress"};
    candidates[3] = (Candidate){"JDS"};
    candidates[4] = (Candidate){"BSP"};
    candidates[5] = (Candidate){"TMC"};

    VoteTally tallies[maxCandidates];
    for (int i = 0; i < numCandidates; i++) {
        tallies[i] = (VoteTally){i + 1, 0};
    }

    printf("\n*Online Voting System*\n\n");

    do {
        printf("Do you want to proceed...? \n");
        printf("If yes press 1, or else press 0: ");
        scanf("%d", &decide);

        if (decide == 1) {
            int ch;
            printf("\n\nHave you registered? If yes press 1, or press 0: ");
            scanf("%d", &ch);

            if (ch == 0) {
                printf("\n**Register**\n\n");
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                addUser(&userHead, username, password);
                //printf("Voter has been registered successfully!\n\n");
            } else if (ch == 1) {
                printf("\n**Login**\n\n");
                printf("Enter registered username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);

                Voter *authenticatedUser = authenticateUser(userHead, username, password);

                if (authenticatedUser != NULL) {
                    if (authenticatedUser->hasVoted) {
                        printf("You have already voted. Multiple votes are not allowed.\n");
                    } else {
                        int viewResults;
                        printf("Voter login successful.\n\n");
                        printf("**********Cast Your Vote!**********\n\n");
                        castVote(authenticatedUser, candidates, numCandidates, tallies);
                        printf("Thank you for Voting!\n\n");
                        // Display results after voting
                        printf("Do you want to view Results?...if yes press 1, or press 0: ");
                        scanf("%d", &viewResults);
                        if (viewResults == 1)
                        {
                            displayResults(candidates, numCandidates, tallies);
                        }
                        else{
                            continue;
                        }
                    }
                } else {
                    printf("Invalid credentials or Voter not registered.\n\n");
                }
            }
        } else if (decide == 1) {
            printf("Thank you for visiting!\n");
        } else {
            printf("Thankyou for Voting\n");
            break;
        }
    } while (decide != 0);

    // Free allocated memory before exiting
    Voter *current = userHead;
    while (current != NULL) {
        Voter *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}