#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
int getDifficultyRange(int *maxAttempts);
void playRound(int range, int maxAttempts, int *score);
int getValidGuess(int lower, int upper);

int main() {
    srand(time(NULL));  // Seed random number generator once, at program start

    char playAgain;
    int score = 0;
    int roundsPlayed = 0;

    printf("=========================================\n");
    printf("        NUMBER GUESSING GAME\n");
    printf("=========================================\n");

    do {
        int maxAttempts;
        int range = getDifficultyRange(&maxAttempts);

        playRound(range, maxAttempts, &score);
        roundsPlayed++;

        printf("\nCurrent Score: %d / %d rounds\n", score, roundsPlayed);
        printf("Play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("\n=========================================\n");
    printf("Final Score: %d / %d rounds\n", score, roundsPlayed);
    printf("Thanks for playing!\n");
    printf("=========================================\n");

    return 0;
}

// Lets the player choose a difficulty; sets the attempt limit accordingly
int getDifficultyRange(int *maxAttempts) {
    int choice;
    int range;

    printf("\nSelect Difficulty:\n");
    printf("1. Easy   (1-50,  10 attempts)\n");
    printf("2. Medium (1-100,  7 attempts)\n");
    printf("3. Hard   (1-200,  5 attempts)\n");
    printf("Enter choice: ");

    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        printf("Invalid input! Enter 1, 2, or 3: ");
        while (getchar() != '\n');  // clear bad input from buffer
    }

    switch (choice) {
        case 1: range = 50;  *maxAttempts = 10; break;
        case 2: range = 100; *maxAttempts = 7;  break;
        case 3: range = 200; *maxAttempts = 5;  break;
    }

    return range;
}

// Reads a guess from the user, ensuring it's a valid integer within range
int getValidGuess(int lower, int upper) {
    int guess;

    while (1) {
        printf("Enter your guess (%d-%d): ", lower, upper);

        if (scanf("%d", &guess) != 1) {
            printf("That's not a number! Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        if (guess < lower || guess > upper) {
            printf("Out of range! Guess between %d and %d.\n", lower, upper);
            continue;
        }

        return guess;
    }
}

// Runs a single round of guessing
void playRound(int range, int maxAttempts, int *score) {
    int secretNumber = (rand() % range) + 1;  // random number from 1 to range
    int attempts = 0;
    int guess;
    int won = 0;

    printf("\nI'm thinking of a number between 1 and %d.\n", range);
    printf("You have %d attempts. Good luck!\n\n", maxAttempts);

    while (attempts < maxAttempts) {
        guess = getValidGuess(1, range);
        attempts++;

        if (guess == secretNumber) {
            printf("\nCorrect! You guessed it in %d attempt(s)!\n", attempts);
            won = 1;
            break;
        } else if (guess < secretNumber) {
            printf("Too Low! ");
        } else {
            printf("Too High! ");
        }

        printf("Attempts left: %d\n", maxAttempts - attempts);
    }

    if (won) {
        // Fewer attempts used = more points
        int points = (maxAttempts - attempts + 1);
        *score += points;
        printf("You earned %d point(s) this round.\n", points);
    } else {
        printf("\nOut of attempts! The number was: %d\n", secretNumber);
    }
}