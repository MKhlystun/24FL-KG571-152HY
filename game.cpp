#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

enum Rules_Game {
  CLASSIC,
  MODERN,
};

enum Result {
  WIN,
  GAME_OVER,
  LESS,
  MORE
};

class GameResult {
  private:
    std::vector<bool> is_win;
    std::vector<bool> is_lost;
    std::vector<int> num_attempts;
    int num_players;
  public:
    GameResult(int players=3) {
      num_players = players;
      for (int i = 0; i < num_players; ++i) {
        is_win.push_back(false);
        is_lost.push_back(false);
        num_attempts.push_back(-1);
      }
    }
    bool is_in_game(int player_id) {
      bool in_game = true;
      if (is_win[player_id]) {
        in_game = false;
      }
      if (is_lost[player_id]) {
        in_game = false;
      }
      return in_game;
    }
    void winner(int player_id, int num) {
      cout << "Congrats! You win!" << endl;
      is_win[player_id] = true;
      is_lost[player_id] = true;
      num_attempts[player_id] = num;
    }
    void loser(int player_id, int num) {
      cout << "Player " << player_id << " is loser !" << endl;
      is_lost[player_id] = true;
      num_attempts[player_id] = num;
    }
    void print() {
      cout << "Print the results table" << endl;
      for (int i = 0; i < num_players; i++) {
        if (is_win[i]) {
          cout << "WINNER!!! ";
        }
        cout << "Player number " << i << " is " << is_win[i] << " with number of attempts " << num_attempts[i] << endl;
      }
    }

    bool is_all_finished() {
      bool result = true;
      for (int i=0; i<num_players; i++) {
//        cout << "Check is_all_finished" << i << " " << is_lost[i] << endl;
        if (is_lost[i] == false) {
          result = false;
        }
      }
      return result;
    }
};

class Game {
  private:
    int counter;
    int max_value;
    int number;
    int max_attempts;

  public:
    Game(int max_value=10, int max_att=5) {
      std::srand(std::time(0));
      number = std::rand() % max_value;
      counter = max_att;
      max_attempts = max_att;
    }
    enum Result make_a_guess(int guess) {
      enum Result result;
      if (counter >= 1) {
        counter = counter -1;
        if (number > guess) {
          result = MORE; //MORE
        } else {
          result = LESS; //LESS
        }
        if (number == guess) {
          result = WIN; //WIN
        }
      } else {
        cout << "GAME_OVER" << endl;
        result = GAME_OVER; //GAME OVER
      }
      return result;
    }
    int get_num_attempt() {
      return max_attempts - counter;
    }
};
int get_number_players(int max_players) {
  int playerCount;
  do {
    cout << "Enter the number of players (1-10): ";
    try {
      cin >> playerCount;
      if (playerCount < 1 || playerCount > max_players) {
          cout << "Invalid number of players. Try again\n";
          playerCount = 0;
      }
    }
    catch (const std::exception& e) {
      cout << "Invalid number of players. Try again\n";
      playerCount = 0;
    }
  }
  while ( playerCount < 1 || playerCount > max_players);
  return playerCount;
}

int get_level_game(const int levels[3][3]) {
  int choice;
  do {
    cout << "Choose a level:\n";
    cout << "1. Easy (Range: 1-"   << levels[0][1] << ", Guess Limit: " << levels[0][2] << ")\n";
    cout << "2. Medium (Range: 1-" << levels[1][1] << ", Guess Limit: " << levels[1][2] << ")\n";
    cout << "3. Hard (Range: 1-"   << levels[2][1] << ", Guess Limit: " << levels[2][2] << ", Time Limit: 120 sec)\n";
    cout << "Enter your choice (1/2/3): ";
    cin >> choice;
  }
  while (0 > choice || choice > 3);
  return choice - 1;
}

Rules_Game get_type_rules() {
  Rules_Game rules;
  int input;
  do {
    cout << "Choose rules:\n";
    cout << "1. Classic rules\n";
    cout << "2. Modern rules\n";
    cout << "Enter your choice (1/2): ";
    cin >> input;
  }
  while (input < 1 || input > 2);
  rules = (input == 1) ? CLASSIC : MODERN;
  return rules;
}

void playGame(int range, int guessLimit, int  lev, int playerCount) {
  string levels[3] = { "Easy", "Medium", "Hard" };
  string level = levels[lev];
  srand(time(0)); // Seed random number generator
  int target = rand() % range + 1; // Generate random number in the given range
  vector<int> attempts(playerCount, 0); // Track attempts for each player
  vector<int> previousGuess(playerCount, -1); // Track previous guesses for each player
  int currentPlayer = 0; // Start with the first player
  time_t startTime = time(0);

  cout << "\nYou selected " << level << " level." << endl;
  cout << "Guess the number between 1 and " << range << ". Each player has " << guessLimit << " attempts";
  if (level == "Hard") cout << " and 120 seconds total.";
  cout << endl;

  while (true) {
      // Check for time limit in Hard level
      if (level == "Hard") {
          time_t currentTime = time(0);
          if (difftime(currentTime, startTime) > 120) {
              cout << "\nTime's up! None of the players guessed the number within 120 seconds. The correct number was " << target << ".\n";
              return;
          }
      }

      cout << "\nPlayer " << (currentPlayer + 1) << "'s turn." << endl;
      int guess, adjustment;
      char operation;

      // Medium level logic: Add or Subtract
      if ((level == "Medium") && attempts[currentPlayer] > 0) {
          cout << "Your previous guess was " << previousGuess[currentPlayer] << ".\n";
          cout << "Would you like to add or subtract? Enter '+' or '-': ";
          cin >> operation;
          cout << "Enter the number to " << (operation == '+' ? "add" : "subtract") << ": ";
          cin >> adjustment;

          if (operation == '+') {
              guess = previousGuess[currentPlayer] + adjustment;
          } else if (operation == '-') {
              guess = previousGuess[currentPlayer] - adjustment;
          } else {
              cout << "Invalid operation. Try again.\n";
              continue;
          }
      }
      // Hard level logic: Add, Subtract, Multiply, Divide
      else if ((level == "Hard") && attempts[currentPlayer] > 0) {
          cout << "Your previous guess was " << previousGuess[currentPlayer] << ".\n";
          cout << "Would you like to add, subtract, multiply, or divide? Enter '+', '-', '*', or '/': ";
          cin >> operation;
          cout << "Enter the number to " << (operation == '+' ? "add" : operation == '-' ? "subtract" : operation == '*' ? "multiply" : "divide") << ": ";
          cin >> adjustment;

          if (operation == '+') {
              guess = previousGuess[currentPlayer] + adjustment;
          } else if (operation == '-') {
              guess = previousGuess[currentPlayer] - adjustment;
          } else if (operation == '*') {
              guess = previousGuess[currentPlayer] * adjustment;
          } else if (operation == '/') {
              if (adjustment != 0) {
                  guess = previousGuess[currentPlayer] / adjustment;
              } else {
                  cout << "Division by zero is not allowed. Try again.\n";
                  continue;
              }
          } else {
              cout << "Invalid operation. Try again.\n";
              continue;
          }
      }
      // Easy level or first guess
      else {
          cout << "Enter your guess: ";
          cin >> guess;
      }

      attempts[currentPlayer]++;
      previousGuess[currentPlayer] = guess;

      if (guess == target) {
          cout << "\nCongratulations, Player " << (currentPlayer + 1) << "! You guessed the correct number (" << target << ") in " << attempts[currentPlayer] << " attempts.\n";
          return;
      }

      if (guess < target) {
          cout << "Too low! ";
      } else {
          cout << "Too high! ";
      }

      cout << "Try again.\n";

      // Check if the player has reached the guess limit
      if (attempts[currentPlayer] >= guessLimit) {
          cout << "\nPlayer " << (currentPlayer + 1) << " has used all their attempts.\n";
          currentPlayer = (currentPlayer + 1) % playerCount;
          if (currentPlayer == 0) {
              cout << "\nAll players have used their attempts. The correct number was " << target << ". Better luck next time!\n";
              return;
          }
      } else {
          currentPlayer = (currentPlayer + 1) % playerCount;
      }
  }
}

int main() {
  const int max_players = 10;
  int choice, num_players;
  const int levels[3][3] = {{ 1,  100, 10 },
                           {  2, 1000, 12 },
                           {  3, 5000, 14 }};
  Rules_Game rules;
  cout << "\n****************************************************************";
  cout << "\n* Welcome to the Multiplayer Guessing Game!                    *";
  cout << "\n* The program provides two sets of rules: class and modern.    *";
  cout << "\n* Classic rules: you need guess a number                       *";
  cout << "\n* Modern rules: you need guess a number using math operations  *";
  cout << "\n* Welcome to the Multiplayer Guessing Game!                    *";
  cout << "\n****************************************************************";
  cout << "\n";

  num_players = get_number_players(max_players);
  choice = get_level_game(levels);
  rules = get_type_rules();

  if ( rules == CLASSIC ) {
    std::vector<Game> game_players;
    for (int i = 0; i < num_players; i++) {
      game_players.emplace_back(levels[choice][1], levels[choice][2]);
    }
    int g;
    Result result;
    int player = 0;
    GameResult game_results(num_players);
    do {
      if (game_results.is_in_game(player) == false ) {
        cout << "Skip the player " << player << endl;
        if (player < num_players - 1) {
          player++;
        } else {
          player = 0;
        }
        continue;
      }
      cout << "The turn of the player number " << player << endl;
      cout << "Enter your guess: ";
      cin >> g;

      result = game_players[player].make_a_guess(g);
      if (result == MORE) {
        cout << "You should try to bigger number!" << endl;
      }
      if (result == LESS) {
        cout << "You should try to smaller number!" << endl;
      }
      if (result == GAME_OVER) {
        game_results.loser(player, game_players[player].get_num_attempt());
      }
      if (result == WIN) {
        game_results.winner(player, game_players[player].get_num_attempt());
       }
      if (player < num_players - 1) {
        player++;
      } else {
        player = 0;
      }
    }
    while (game_results.is_all_finished() == false);
    game_results.print();

    return 0;
  }
  else
  {
    playGame(levels[choice][1], levels[choice][2], levels[choice][0], num_players);
  }
}
